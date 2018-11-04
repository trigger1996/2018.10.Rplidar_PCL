#include "include/main_task.h"

/**
 * @file offb_node.cpp
 * @brief Offboard control example node, written with MAVROS version 0.19.x, PX4 Pro Flight
 * Stack and tested in Gazebo SITL
 */

mavros_msgs::State current_state;
void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}

geometry_msgs::Vector3 Current_euler;
geometry_msgs::Vector3 Current_acc;
void imuqua_cb(const sensor_msgs::Imu::ConstPtr& msg){
    tf::Quaternion IMU_q(msg->orientation.x,msg->orientation.y,msg->orientation.z,msg->orientation.w);
    tf::Matrix3x3 m(IMU_q);
    m.getRPY(Current_euler.x,Current_euler.y,Current_euler.z);
    //Current_euler.z=-Current_euler.z;
    //Current_euler.y=-Current_euler.y;
    Current_acc = msg->linear_acceleration;

    //cout << Current_euler.x << endl;
}

__rc_channels rc_in, rc_out;
bool is_rc_updated = false, is_ctrl_rc_updated = false;
void RC_in_cb(const mavros_msgs::RCIn::ConstPtr& msg){
    rc_in.roll   = msg->channels[0];
    rc_in.pitch  = msg->channels[1];
    rc_in.thrust = msg->channels[2];
    rc_in.yaw    = msg->channels[3];
    rc_in.ch_5   = msg->channels[4];
    rc_in.ch_6   = msg->channels[5];
    rc_in.ch_7   = msg->channels[6];
    rc_in.ch_8   = msg->channels[7];

    is_rc_updated = true;
    //cout << rc_in.thrust << endl;
}

int main_ros(int argc, char *argv[])
{
    ros::init(argc, argv, "mavros_rplidar_pid");
    ros::NodeHandle nh;

    ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>
            ("mavros/state", 10, state_cb);


    ros::Subscriber imuqua_sub = nh.subscribe<sensor_msgs::Imu>
                ("mavros/imu/data", 10, imuqua_cb);
    ros::Subscriber rc_in_sub = nh.subscribe<mavros_msgs::RCIn>
                ("mavros/rc/in", 10, RC_in_cb);
    ros::Publisher  rc_adjusted_pub = nh.advertise<mavros_msgs::OverrideRCIn>
            ("mavros/rc/override", 10);

    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(100.0);       // 20.0

    // wait for FCU connection
    while(ros::ok() && !current_state.connected){
        ros::spinOnce();
        rate.sleep();
    }

    ros::Time last_request = ros::Time::now();

    while(ros::ok()){
        if (is_rc_updated) {

        }

        last_request = ros::Time::now();
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
