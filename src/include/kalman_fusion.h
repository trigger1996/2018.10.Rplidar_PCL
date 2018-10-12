#ifndef KALMAN_FUSION_H
#define KALMAN_FUSION_H

#include "config.h"
#include "eigen3/Eigen/Dense"
#include "../iir1/Iir.h"

using namespace std;
using namespace Eigen;

#define IMU_ACC_CUTOFF 15.0     // Hz
#define IMU_VEL_CUTOFF 0.01     // Hz
#define IMU_DST_CUTOFF 0.01     // Hz

// https://wenku.baidu.com/view/63441d4aa5e9856a561260ed.html

// 这个代码是不可能模块化的，要么就直接重写
// 这里的速度是对地速度，但是方向是以机体正向指向为参考方向
class __kalman_filter {
public:
    __kalman_filter();

    void reset();

    void update_Estimation(double acc_x_in, double acc_y_in, double _roll, double _pitch, double _yaw);

    void update_Measurement(double lidar_x_in, double lidar_y_in);

    void get_XY_Out(double &x_out, double &y_out);

protected:

    MatrixXd X;             // 状态矩阵
    MatrixXd P;             // 观测协方差矩阵

    MatrixXd F, H;          // 状态转移矩阵，Jacob矩阵

    MatrixXd K;             // 卡尔曼增益
    MatrixXd Q, R;          // 观测噪声

    double dt;

    double acc_x_imu, acc_y_imu;
    double acc_x,     acc_y;
    double vel_x_imu, vel_y_imu;
    double vel_x,     vel_y;
    double x_imu,     y_imu;
    double x,         y;

    double roll, pitch, yaw;

    const static int acc_iir_order = 10;                                    // 加速度滤波器阶数

    Iir::Butterworth::LowPass<acc_iir_order>  acc_x_lpf, acc_y_lpf;         // 加速度主要处理其高频分量，其实最好是带通，但是带通非常难调

    void integrate_in_F();  // 频域积分

    void acc_ButterWorth(); // 加速度巴特沃斯滤波器
};

#endif // KALMAN_FUSION_H
