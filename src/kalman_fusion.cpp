#include "include/kalman_fusion.h"

using namespace Iir;

__kalman_filter::__kalman_filter() {
    reset();
}

void __kalman_filter::reset() {
    const float samplingrate = 100;                                      // Hz
    const float cutoff_frequency = 20;                                   // Hz
    acc_x_lpf.setup (acc_iir_order, samplingrate, cutoff_frequency);
    acc_y_lpf.setup (acc_iir_order, samplingrate, cutoff_frequency);
}

void __kalman_filter::update_Estimation(double acc_x_in, double acc_y_in) {
    acc_x_imu = acc_x_in; acc_y_imu = acc_y_in;
}

void __kalman_filter::update_Measurement(double lidar_x_in, double lidar_y_in) {

}

void __kalman_filter::get_XY_Out(double &x_out, double &y_out) {

}
