#include "include/main_task.h"

#include "include/lidar_driver.h"
#include "include/registration_icp_ndt.h"
#include "include/control.hpp"
#include "iir1/Iir.h"

void laser_imu_fusion(vector<__scandot> &data, double roll, double pitch, double yaw);
bool rotate_Grid2Grid(double &x, double &y, double &z, double roll, double pitch, double yaw);

double x_gnd, y_gnd;
double x_body      = 0., y_body      = 0.;
double x_body_last = 0., y_body_last = 0.;
double z_body      = 0.;
double vx_body     = 0., vy_body     = 0.;
bool is_pose_updated = false, is_ctrl_rc_updated = false;

#include <signal.h>
bool ctrl_c_pressed;
void ctrlc(int) {
    ctrl_c_pressed = true;
}

int main_rplidar(int argc, char *argv[]) {
    // Lidar Driver
    __lidar *lidar = new __lidar;
    // ICP_NDT
    __registration_abs *reg = new __registration_icp_ndt(false);
    // control
    __control_pid pos_x_ctrl(0., 0., 0.,  0.5, 10),
                  pos_y_ctrl(0., 0., 0.,  0.5, 10),
                  vel_x_ctrl(1., 0., 0.5, 50., 10),
                  vel_y_ctrl(1., 0., 0.5, 50., 10);

    // IIR
    const int order = 6;
    Iir::Butterworth::LowPass<order> iir_vx, iir_vy;
    const float samplingrate = 12;                            // Hz
    const float cutoff_frequency = 150;                       // Hz
    iir_vx.setup(order, samplingrate, cutoff_frequency);
    iir_vy.setup(order, samplingrate, cutoff_frequency);


    // timer
    struct timeval t, t_last;
    struct timeval tx;          // overall-time
    gettimeofday(&t, NULL);


    // for exiting
    signal(SIGINT, ctrlc);      // 这个主要是让雷达停止旋转的，一个是省电，另一个是出错了马上可以发现

    while (true) {
        // update time
        t_last = t;
        gettimeofday(&t, NULL);
        double dt = (t.tv_usec - t_last.tv_usec);
        if (dt < 0.)
            dt += 1e6;
        tx.tv_usec += dt;
        if (tx.tv_usec >= 1e6) {
            tx.tv_sec++;
            tx.tv_usec -= 1e6;
        }


        if (lidar->update_Data()) {
            if(lidar->get_Data().size() && lidar->get_LastData().size()) {
                vector<__scandot> data, data_last;
                data_last = lidar->get_LastData();
                data = lidar->get_Data();

                /// 数据预处理
                laser_imu_fusion(data, Current_euler.x, Current_euler.y, Current_euler.z);// 利用飞控测得地磁偏航角锁定激光雷达的旋转，尝试获得更高的精度
                laser_imu_fusion(data_last, Current_euler.x, Current_euler.y, Current_euler.z);

                /// 点云配准
                reg->set_Src_PointCloud(data_last);
                reg->set_Ref_PointCloud(data);
                reg->update();

                x_gnd += reg->get_dx();                                         // cm
                y_gnd += reg->get_dy();
                // 位置更新
                x_body_last = x_body; y_body_last = y_body;
                x_body = x_gnd, y_body = y_gnd, z_body = 0.;
                rotate_Grid2Grid(x_body, y_body, z_body, 0, 0, Current_euler.z);
                //位置微分得到速度
                vx_body = (x_body - x_body_last) / (dt / 1.e6);
                vy_body = (y_body - y_body_last) / (dt / 1.e6);
                vx_body = iir_vx.filter(vx_body);
                vy_body = iir_vy.filter(vy_body);

                is_pose_updated = true;

                // 若RC数据更新
                if (is_rc_updated) {
                    double exp_x = ((double)rc_in.pitch - 1500) / 500 * 150;        // 遥控器行程: 500 150cm/s->1.5m/s
                    double exp_y = ((double)rc_in.roll  - 1500) / 500 * 150;

                    /// 控制律计算
                    double vx_ctrl = vel_x_ctrl.get_PID(vx_body, exp_x);
                    double vy_ctrl = vel_y_ctrl.get_PID(vy_body, exp_y);

                    vx_ctrl =  -vx_ctrl + 1500;
                    vy_ctrl =   vy_ctrl + 1500;

                    rc_out.roll   = vy_ctrl;
                    rc_out.pitch  = vx_ctrl;
                    rc_out.thurst = rc_in.thurst;
                    rc_out.yaw    = rc_in.yaw;
                    rc_out.ch_5   = rc_in.ch_5;
                    rc_out.ch_6   = rc_in.ch_6;
                    rc_out.ch_7   = rc_in.ch_7;
                    rc_out.ch_8   = rc_in.ch_8;

                    is_rc_updated = false;
                    is_ctrl_rc_updated = true;
                    //cout << "vx: " << vx_ctrl << " \t\t vy: " << vy_ctrl << "\t dt:" << (dt / 1.e6) << endl;
                }
                cout << "x_body: " << x_body << " y_body: " << y_body << endl;
            }
        }

        if (ctrl_c_pressed) {
            break;
        }
    }
    delete lidar;
    delete reg;
    return 0;
}

void laser_imu_fusion(vector<__scandot> &data, double roll, double pitch, double yaw) {
    for (int i = 0; i < data.size(); i++) {
        // 做倾角补偿
        double x, y, z;
        x = data[i].dst * cos(data[i].angle * 180. / M_PI);
        y = data[i].dst * sin(data[i].angle * 180. / M_PI);
        z = 0;
        rotate_Grid2Grid(x, y, z, -roll, -pitch, -yaw);         // Current_euler.x, Current_euler.y, data[i].angle * 3.14 / PI
        data[i].dst = sqrt(x*x + y*y);

        // 做旋转补偿
        data[i].angle -= Current_euler.z * 180. / M_PI + 90.;
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
