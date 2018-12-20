#include "include/main_task.h"
#include "include/ned_2_lat_lon.hpp"

mavros_msgs::State current_state;
void state_cb(const mavros_msgs::State::ConstPtr& msg) {
    current_state = *msg;
}

sensor_msgs::Imu current_imu_raw;
geometry_msgs::Vector3 Current_euler;
geometry_msgs::Vector3 Current_acc;
static void imuqua_cb(const sensor_msgs::Imu::ConstPtr& msg) {
    current_imu_raw = *msg;

    tf::Quaternion IMU_q(msg->orientation.x,msg->orientation.y,msg->orientation.z,msg->orientation.w);
    tf::Matrix3x3 m(IMU_q);
    m.getRPY(Current_euler.x,Current_euler.y,Current_euler.z);
    Current_acc = msg->linear_acceleration;

    //cout << Current_euler.z << endl;
}


__rc_channels rc_in, rc_out;
bool is_rc_updated = false;
void RC_in_cb(const mavros_msgs::RCIn::ConstPtr& msg){
    rc_in.roll   = msg->channels[0];
    rc_in.pitch  = msg->channels[1];
    rc_in.thurst = msg->channels[2];
    rc_in.yaw    = msg->channels[3];
    rc_in.ch_5   = msg->channels[4];
    rc_in.ch_6   = msg->channels[5];
    rc_in.ch_7   = msg->channels[6];
    rc_in.ch_8   = msg->channels[7];

    is_rc_updated = true;
    //cout << rc_in.thurst << endl;
}

double alt_global = 0.;
void rel_alt_cb(const std_msgs::Float64::ConstPtr& msg) {
    std_msgs::Float64 temp = *msg;
    alt_global = temp.data;
}

int main_ros(int argc, char *argv[]) {
    ros::init(argc, argv, "mavros_rplidar_pid");
    ros::NodeHandle nh;

    ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>
            ("mavros/state", 20, state_cb);
    ros::Subscriber imuqua_sub = nh.subscribe<sensor_msgs::Imu>
                ("mavros/imu/data", 20, imuqua_cb);
//    ros::Subscriber rc_in_sub = nh.subscribe<mavros_msgs::RCIn>
//            ("mavros/rc/in", 200, RC_in_cb);

    ros::Subscriber rel_alt_sub = nh.subscribe<std_msgs::Float64>
            ("mavros/global_position/rel_alt", 20, rel_alt_cb);
    ros::Publisher vision_pos_pub = nh.advertise<geometry_msgs::PoseStamped>
            ("mavros/vision_pose/pose", 5);
    ros::Publisher vision_pos_pub_mocap = nh.advertise<geometry_msgs::PoseStamped>
            ("mavros/fake_gps/mocap/pose", 5);

//    mavros_msgs::HilGPS fake_gps;
    geometry_msgs::PoseStamped vision_pose;

    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(10.0);       // 20.0

    ros::ServiceClient stream_rate_client = nh.serviceClient<mavros_msgs::StreamRate>
            ("mavros/set_stream_rate");
    mavros_msgs::StreamRate stream_rate;
    stream_rate.request.stream_id = 0;      // STREAN)AKK
    stream_rate.request.message_rate = 20;
    stream_rate.request.on_off = true;
    stream_rate_client.call(stream_rate);

    // wait for FCU connection
    while(ros::ok() && !current_state.connected){
        stream_rate_client.call(stream_rate);
        ros::spinOnce();
        rate.sleep();
    }

    ros::Time last_request = ros::Time::now();

    while(ros::ok()){

        if (is_ctrl_rc_updated) {
            // Vision
            vision_pose.header.stamp = ros::Time::now();
            vision_pose.pose.position.x = -x_body / 100.;          //  y_body / 100. //  x_body
            vision_pose.pose.position.y =  y_body / 100.;          // -x_body / 100. // -y_body
            vision_pose.pose.position.z = alt_global;
            vision_pose.pose.orientation.x = current_imu_raw.orientation.x;
            vision_pose.pose.orientation.y = current_imu_raw.orientation.y;
            vision_pose.pose.orientation.z = current_imu_raw.orientation.z;
            vision_pose.pose.orientation.w = current_imu_raw.orientation.w;

            vision_pos_pub.publish(vision_pose);

            // Fake GPS/ENU
            vision_pose.pose.position.x = -x_gnd / 100.;            // lat
            vision_pose.pose.position.y =  y_gnd / 100.;            // lon

            //vision_pos_pub_mocap.publish(vision_pose);

            cout << "x_body: " << vision_pose.pose.position.x << "\t y_body:: " << vision_pose.pose.position.y << endl;

            is_ctrl_rc_updated = false;
        }

        last_request = ros::Time::now();
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}

