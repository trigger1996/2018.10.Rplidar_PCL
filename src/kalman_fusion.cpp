#include "include/kalman_fusion.h"

using namespace Iir;

__kalman_filter::__kalman_filter() {
    reset();
}

void __kalman_filter::reset() {
    const float samplingrate = IMU_RATE;                                        // Hz
    const float acc_cutoff_frequency = 15;                                      // Hz
    const float vel_cutoff_frequency = 0.001;                                   // Hz

    acc_x_lpf.setup(acc_iir_order, samplingrate, acc_cutoff_frequency);
    acc_y_lpf.setup(acc_iir_order, samplingrate, acc_cutoff_frequency);

    vel_x_hpf.setup(vel_iir_order, samplingrate, vel_cutoff_frequency);
    vel_y_hpf.setup(vel_iir_order, samplingrate, vel_cutoff_frequency);

    acc_x_imu = 0., acc_y_imu = 0.;
    acc_x     = 0., acc_y     = 0.;
    vel_x_imu = 0., vel_y_imu = 0.;
    vel_x     = 0., vel_y     = 0.;
    x_imu     = 0., y_imu     = 0.;
    x         = 0., y         = 0.;

    dt = 1. / IMU_RATE;

    X.resize(4, 1);
}

void __kalman_filter::update_Estimation(double acc_x_in, double acc_y_in, double _roll, double _pitch, double _yaw) {
    roll = _roll, pitch = _pitch, yaw = _yaw;
    acc_x_imu = acc_x_in; acc_y_imu = acc_y_in;

    // 加速度剔除重力分量
    acc_x = acc_x * cos(pitch * 180. / M_PI);
    acc_y = acc_y * cos(roll  * 180. / M_PI);

    // 加速度过LPF
    acc_x = acc_x_lpf.filter(acc_x_imu);
    acc_y = acc_y_lpf.filter(acc_y_imu);

    // 积分
    vel_x_imu += acc_x * dt;
    vel_y_imu += acc_y * dt;

    // 速度过HPF
    vel_x_imu = vel_x_hpf.filter(vel_x_imu);
    vel_y_imu = vel_y_hpf.filter(vel_y_imu);

    // 积分
    x_imu += vel_x_imu * dt;
    y_imu += vel_y_imu * dt;

    // 位移过HPF
    //x_imu = dst_x_hpf.filter(x_imu);
    //y_imu = dst_y_hpf.filter(y_imu);

    X << x_imu,
         y_imu,
         vel_x_imu,
         vel_y_imu;

    //cout << acc_x << "\t" << acc_y << "\t\t" << acc_x_imu << "\t" << acc_y_imu << endl;
    cout << vel_x_imu << "\t" << vel_y_imu << "\t\t" << x_imu << "\t" << y_imu << endl;
}

void __kalman_filter::update_Measurement(double lidar_x_in, double lidar_y_in) {

}

void __kalman_filter::get_XY_Out(double &x_out, double &y_out) {

}
