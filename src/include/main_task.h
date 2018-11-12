#ifndef MAIN_TASK_H
#define MAIN_TASK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include<sys/types.h>
#include<sys/sysinfo.h>
#include<unistd.h>
//#define _GNU_SOURCE
#include<sched.h>
#include<ctype.h>
#include<pthread.h>

#include "config.h"

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>

#include <geometry_msgs/Quaternion.h>
#include <mavros_msgs/RCIn.h>
#include <mavros_msgs/HilGPS.h>

#include <std_msgs/Float64.h>

#include <sensor_msgs/Imu.h>
#include <sensor_msgs/Range.h>
#include <tf/transform_datatypes.h>

using namespace std;

int main_ros(int argc, char *argv[]);
int main_rplidar(int argc, char *argv[]);

// main_ros
extern mavros_msgs::State current_state;
extern geometry_msgs::Vector3 Current_euler;
extern geometry_msgs::Vector3 Current_acc;
extern __rc_channels rc_in, rc_out;
extern bool is_rc_updated;

// main_rplidar
extern double x_gnd,           y_gnd;
extern double x_body,          y_body;
extern double x_body_last,     y_body_last;
extern double z_body;
extern double vx_body,         vy_body;
extern bool   is_pose_updated, is_ctrl_rc_updated;

#endif // MAIN_TASK_H

