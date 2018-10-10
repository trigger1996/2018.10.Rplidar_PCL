#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Vector3.h>
#include <sensor_msgs/Imu.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>

#include <tf/transform_datatypes.h>

#include <cmath>

#include "include/config.h"
#include "include/lidar_driver.h"
#include "include/registration_icp_ndt.h"

#include <eigen3/Eigen/Dense>

using namespace Eigen;

#include <signal.h>
bool ctrl_c_pressed;
void ctrlc(int) {
    ctrl_c_pressed = true;
}

mavros_msgs::State current_state;
void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}

geometry_msgs::Vector3 Current_euler;
geometry_msgs::Vector3 Current_acc;
void imuqua_cb(const sensor_msgs::Imu& msg){
    tf::Quaternion IMU_q(msg.orientation.x,msg.orientation.y,msg.orientation.z,msg.orientation.w);
    tf::Matrix3x3 m(IMU_q);
    m.getRPY(Current_euler.x,Current_euler.y,Current_euler.z);
    //Current_euler.z=-Current_euler.z;
    //Current_euler.y=-Current_euler.y;
    Current_acc = msg.linear_acceleration;
}

void laser_imu_fusion(vector<__scandot> data, double roll, double pitch, double yaw);
bool rotate_Grid2Grid(double &x, double &y, double &z, double roll, double pitch, double yaw);

int main(int argc, char *argv[]) {
    __lidar *lidar = new __lidar;
    __registration_abs *reg = new __registration_icp_ndt;

    static int i = 0;
    static double dx = 0., dy = 0.;

    ros::init(argc, argv, "offboard_rplidar_node");
	ros::NodeHandle nh;
	
    ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>
            ("mavros/state", 10, state_cb);
    ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>
            ("mavros/setpoint_position/local", 10);
    ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>
            ("mavros/cmd/arming");
    ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>
            ("mavros/set_mode");
    ros::Subscriber imuqua_sub = nh.subscribe
            ("mavros/imu/data", 10, imuqua_cb);
		
    //the setpoint publishing rate MUST be faster than 2Hz
	ros::Rate rate(100.0);

	signal(SIGINT, ctrlc);

	// wait for FCU connection
    while(ros::ok() && !current_state.connected){
        ros::spinOnce();
        rate.sleep();
	}
	
    geometry_msgs::PoseStamped pose;
    pose.pose.position.x = 0;
    pose.pose.position.y = 0;
    pose.pose.position.z = 2;

    //send a few setpoints before starting
    for(int i = 100; ros::ok() && i > 0; --i){
        local_pos_pub.publish(pose);
        ros::spinOnce();
        rate.sleep();
	}
	
    mavros_msgs::SetMode offb_set_mode;
    offb_set_mode.request.custom_mode = "OFFBOARD";

    mavros_msgs::CommandBool arm_cmd;
    arm_cmd.request.value = true;

	ros::Time last_request = ros::Time::now();
	
    while (true) {
		
        // roll pitch yaw ax ay az
        //ROS_INFO("%f\t%f\t%f\t%f\t%f\t%f", Current_euler.x * 180 / M_PI, Current_euler.y * 180 / M_PI, Current_euler.z * 180 / M_PI,
        //                                   Current_acc.x, Current_acc.y, Current_acc.z);

//       if( current_state.mode != "OFFBOARD" &&
//            (ros::Time::now() - last_request > ros::Duration(5.0))){
//            if( set_mode_client.call(offb_set_mode) &&
//                offb_set_mode.response.mode_sent){
//                ROS_INFO("Offboard enabled");
//            }
//            last_request = ros::Time::now();
//        } else {
//            if( !current_state.armed &&
//                (ros::Time::now() - last_request > ros::Duration(5.0))){
//                if( arming_client.call(arm_cmd) &&
//                    arm_cmd.response.success){
//                    ROS_INFO("Vehicle armed");
//                }
//                last_request = ros::Time::now();
//            }
//        }

//        local_pos_pub.publish(pose);		

        if (lidar->update_Data()) {
            if(lidar->get_Data().size() && lidar->get_LastData().size()) {
                vector<__scandot> data, data_last;
                data_last = lidar->get_LastData();
                data = lidar->get_Data();

                /// 数据预处理
                laser_imu_fusion(data, Current_euler.x, Current_euler.y, Current_euler.z);// 利用飞控测得地磁偏航角锁定激光雷达的旋转，尝试获得更高的精度
                laser_imu_fusion(data_last, Current_euler.x, Current_euler.y, Current_euler.z);

                reg->set_Src_PointCloud(data_last);
                reg->set_Ref_PointCloud(data);

                reg->update();

                dx += reg->get_dx();
                dy += reg->get_dy();

                struct timeval t;
                gettimeofday(&t, NULL);
                cout << (double)t.tv_usec / 1000. << "dx: " << dx << " dy: " << dy << endl;      // cm
            }
        }

        i++;
        if (ctrl_c_pressed){
            break;
        }
     	ros::spinOnce();
		rate.sleep();
    }

    delete lidar;
    delete reg;
    return 0;
}

void laser_imu_fusion(vector<__scandot> data, double roll, double pitch, double yaw) {
    for (int i = 0; i < data.size(); i++) {
        // 做倾角补偿
        double x, y, z;
        x = data[i].dst * cos(data[i].angle * 3.14 / M_PI);
        y = data[i].dst * sin(data[i].angle * 3.14 / M_PI);
        z = 0;
        rotate_Grid2Grid(x, y, z, -roll, -pitch, -yaw); // Current_euler.x, Current_euler.y, data[i].angle * 3.14 / PI
        data[i].dst = sqrt(x*x + y*y);

        // 做旋转补偿
        data[i].angle -= Current_euler.z * 180 / M_PI + 90.;
        while (data[i].angle < 0)
            data[i].angle += 360;
        while (data[i].angle > 360)
            data[i].angle -= 360;
    }
}

bool rotate_Grid2Grid(double &x, double &y, double &z, double roll, double pitch, double yaw) {

    double a, b, g;             // alpha, beta, gamma
    MatrixXd C1, C2, C3;
    MatrixXd X;
    bool is_singular = false;

    a = roll; b = pitch; g = yaw;

    C1.resize(3, 3);
    C1 << 1,            0,          0,
          0,            cos(a),     sin(a),
          0,           -sin(a),     cos(a);
    C2.resize(3, 3);
    C2 << cos(b),       0,         -sin(b),
          0,            1,          0,
          sin(b),       0,          cos(b);

    C3.resize(3, 3);
    C3 << cos(g),       sin(g),     0,
         -sin(g),       cos(g),     0,
          0,            0,          1;

    X.resize(3, 1);
    X   << x,
           y,
           z;

    X = C3 * C2 * C1 * X;
    x = X(0, 0);
    y = X(1, 0);
    z = X(2, 0);

    return is_singular;
}
