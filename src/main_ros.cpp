#include "include/main_task.h"
#include "include/ned_2_lat_lon.hpp"

mavros_msgs::State current_state;
void state_cb(const mavros_msgs::State::ConstPtr& msg){
    current_state = *msg;
}

sensor_msgs::Imu current_imu_raw;
geometry_msgs::Vector3 Current_euler;
geometry_msgs::Vector3 Current_acc;
void imuqua_cb(const sensor_msgs::Imu::ConstPtr& msg){
    current_imu_raw = *msg;

    tf::Quaternion IMU_q(msg->orientation.x,msg->orientation.y,msg->orientation.z,msg->orientation.w);
    tf::Matrix3x3 m(IMU_q);
    m.getRPY(Current_euler.x,Current_euler.y,Current_euler.z);
    //Current_euler.z=-Current_euler.z;
    //Current_euler.y=-Current_euler.y;
    Current_acc = msg->linear_acceleration;

    //cout << Current_euler.x << endl;
}

float px4flow_range = 0.;
void px4flow_cb(const sensor_msgs::Range::ConstPtr& msg){
    sensor_msgs::Range temp;
    temp = *msg;
    px4flow_range = temp.range;
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

int main_ros(int argc, char *argv[]) {
    ros::init(argc, argv, "mavros_rplidar_pid");
    ros::NodeHandle nh;

    ros::Subscriber state_sub = nh.subscribe<mavros_msgs::State>
            ("mavros/state", 10, state_cb);
    ros::Subscriber imuqua_sub = nh.subscribe<sensor_msgs::Imu>
                ("mavros/imu/data", 100, imuqua_cb);
    ros::Subscriber rc_in_sub = nh.subscribe<mavros_msgs::RCIn>
                ("mavros/rc/in", 200, RC_in_cb);

    ros::Subscriber px4flow_sub = nh.subscribe<sensor_msgs::Range>
            ("mavros/px4flow/ground_distance", 25, px4flow_cb);
//    ros::Publisher vision_fake_gps_pub = nh.advertise<mavros_msgs::HilGPS>
//            ("mavros/hil/gps", 8);
//    ros::Publisher vision_pos_pub = nh.advertise<geometry_msgs::PoseStamped>
//            ("mavros/vision_pose/pose", 8);
    ros::Publisher vision_pos_pub_mocap = nh.advertise<geometry_msgs::PoseStamped>
            ("mavros/fake_gps/mocap/pose", 8);

//    mavros_msgs::HilGPS fake_gps;
    geometry_msgs::PoseStamped vision_pose;

    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(200.0);       // 20.0

    // wait for FCU connection
    while(ros::ok() && !current_state.connected){
        ros::spinOnce();
        rate.sleep();
    }

    ros::Time last_request = ros::Time::now();

    while(ros::ok()){

        if (is_ctrl_rc_updated) {
//            fake_gps.header.stamp = ros::Time::now();
//            fake_gps.fix_type = 3;

//            double lat, lon, alt;
//            ned_2_lat_lon(-x_gnd  / 100., -y_gnd / 100., px4flow_range,
//                          lat, lon, alt);

//            fake_gps.geo.longitude = (int32_t)(lon * 1e6);
//            fake_gps.geo.latitude  = (int32_t)(lat * 1e6);
//            fake_gps.geo.altitude  = (int32_t)alt / 10000;
//            fake_gps.eph = 2.;
//            fake_gps.epv = 2.;
//            fake_gps.vel = 65535;   // sqrt(vx_body*vx_body + vy_body*vy_body)
//            fake_gps.vn = 0.;
//            fake_gps.ve = 0.;
//            fake_gps.vd = 0.;
//            fake_gps.cog = 65535;
//            fake_gps.satellites_visible = 255;

//            //cout << fake_gps.geo.longitude << endl;

//            vision_fake_gps_pub.publish(fake_gps);

            // ENU
            vision_pose.header.stamp = ros::Time::now();
            vision_pose.pose.position.x = -x_gnd  / 100.;
            vision_pose.pose.position.y = -y_gnd / 100.;
            vision_pose.pose.position.z = px4flow_range;
            vision_pose.pose.orientation.x = current_imu_raw.orientation.x;
            vision_pose.pose.orientation.y = current_imu_raw.orientation.y;
            vision_pose.pose.orientation.z = current_imu_raw.orientation.z;
            vision_pose.pose.orientation.w = current_imu_raw.orientation.w;

            vision_pos_pub.publish(vision_pose);
            vision_pos_pub_mocap.publish(vision_pose);

            is_ctrl_rc_updated = false;
        }

        last_request = ros::Time::now();
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}

