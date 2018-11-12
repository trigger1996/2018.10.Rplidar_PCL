#include "include/main_task.h"

#define IS_USE_RC_OVERRIDE 1
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

static bool is_use_lidar = false;
int main_ros(int argc, char *argv[]) {
    ros::init(argc, argv, "mavros_rplidar_pid");
    ros::NodeHandle nh;

    ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>
            ("mavros/state", 10, state_cb);
    ros::Subscriber imuqua_sub = nh.subscribe<sensor_msgs::Imu>
                ("mavros/imu/data", 100, imuqua_cb);
    ros::Subscriber rc_in_sub = nh.subscribe<mavros_msgs::RCIn>
                ("mavros/rc/in", 200, RC_in_cb);

#if IS_USE_RC_OVERRIDE
    ros::Publisher  rc_adjusted_pub = nh.advertise<mavros_msgs::OverrideRCIn>
            ("mavros/rc/override", 200);
#else
    ros::Publisher att_ctrl_xy_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_attitude/attitude", 100);
    ros::Publisher att_ctrl_z_pub  = nh.advertise<std_msgs::Float64>("mavros/setpoint_attitude/att_throttle", 100);
    ros::ServiceClient arming_client = nh.serviceClient<mavros_msgs::CommandBool>
            ("mavros/cmd/arming");
    ros::ServiceClient set_mode_client = nh.serviceClient<mavros_msgs::SetMode>
            ("mavros/set_mode");

    mavros_msgs::SetMode offb_set_mode;
    offb_set_mode.request.custom_mode = "OFFBOARD";

    mavros_msgs::CommandBool arm_cmd;
    arm_cmd.request.value = true;
#endif

    mavros_msgs::OverrideRCIn rc_override;
    geometry_msgs::PoseStamped cmd_attr;
    std_msgs::Float64 cmd_thr;

    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(200.0);       // 20.0

    // wait for FCU connection
    while(ros::ok() && !current_state.connected){
        ros::spinOnce();
        rate.sleep();
    }

    ros::Time last_request = ros::Time::now();

#if IS_USE_RC_OVERRIDE

#else
    double v[3] = { 1., 0., 0, };
    double v_norm = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    int count = 0;
    float theta = 0.;
    double lambda = 0.3;

    //send a few setpoints before starting
    cmd_attr.pose.position.x = 0.;
    cmd_attr.pose.position.y = 0.;
    cmd_attr.pose.position.z = 0.;
    cmd_attr.pose.orientation.x = sin(theta / 2.) * v[0]/v_norm;
    cmd_attr.pose.orientation.y = sin(theta / 2.) * v[1]/v_norm;
    cmd_attr.pose.orientation.z = sin(theta / 2.) * v[2]/v_norm;
    cmd_attr.pose.orientation.w = cos(theta / 2.);
    cmd_thr.data = lambda;

    for(int i = 1000; ros::ok() && i > 0; --i){
        att_ctrl_xy_pub.publish(cmd_attr);
        att_ctrl_z_pub.publish(cmd_thr);
        ros::spinOnce();
        rate.sleep();
    }
#endif

    while(ros::ok()){

        if (rc_in.ch_8 > 1500)
            is_use_lidar = true;
        else
            is_use_lidar = false;

        if (is_ctrl_rc_updated) {
            if (is_use_lidar) {
                rc_override.channels[0] = rc_out.roll;
                rc_override.channels[1] = rc_out.pitch;
                rc_override.channels[2] = rc_in.thurst; // rc_out.thurst
                rc_override.channels[3] = rc_in.yaw;
                rc_override.channels[4] = rc_in.ch_5;
                rc_override.channels[5] = rc_in.ch_6;
                rc_override.channels[6] = rc_in.ch_7;
                rc_override.channels[7] = rc_in.ch_8;

                //cout << rc_override.channels[0] << endl;
            }
            else {
                rc_override.channels[0] = rc_in.roll;
                rc_override.channels[1] = rc_in.pitch;
                rc_override.channels[2] = rc_in.thurst;
                rc_override.channels[3] = rc_in.yaw;
                rc_override.channels[4] = rc_in.ch_5;
                rc_override.channels[5] = rc_in.ch_6;
                rc_override.channels[6] = rc_in.ch_7;
                rc_override.channels[7] = rc_in.ch_8;

            }

            is_ctrl_rc_updated = false;
        }

#if IS_USE_RC_OVERRIDE
        rc_adjusted_pub.publish(rc_override);
#else
        if(current_state.mode != "OFFBOARD"){
            if( set_mode_client.call(offb_set_mode) &&
                offb_set_mode.response.mode_sent){
                ROS_INFO("Offboard enabled");
            }
            last_request = ros::Time::now();
        }
        if(!current_state.armed){
            if( arming_client.call(arm_cmd) &&
                arm_cmd.response.success){
                ROS_INFO("Vehicle armed");
            }
            last_request = ros::Time::now();
        }
        else {
            cmd_attr.pose.position.x = 0.;
            cmd_attr.pose.position.y = 0.;
            cmd_attr.pose.position.z = 0.;
            cmd_attr.pose.orientation.x = sin(theta / 2.) * v[0]/v_norm;
            cmd_attr.pose.orientation.y = sin(theta / 2.) * v[1]/v_norm;
            cmd_attr.pose.orientation.z = sin(theta / 2.) * v[2]/v_norm;
            cmd_attr.pose.orientation.w = cos(theta / 2.);

            cmd_thr.data = lambda;
            att_ctrl_xy_pub.publish(cmd_attr);
            att_ctrl_z_pub.publish(cmd_thr);
        }

        count+=100;
        if (count > 1000)
            count = 0;
        theta = 0.3 * sin(count / 300.);

#endif



        last_request = ros::Time::now();
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}

