/*
 *  RPLIDAR
 *  Ultra Simple Data Grabber Demo App
 *
 *  Copyright (c) 2009 - 2014 RoboPeak Team
 *  http://www.robopeak.com
 *  Copyright (c) 2014 - 2018 Shanghai Slamtec Co., Ltd.
 *  http://www.slamtec.com
 *
 */
/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

// http://www.p-chao.com/2017-08-07/pcl%E8%AF%BB%E5%8F%96%E7%82%B9%E4%BA%91%E5%B9%B6%E5%8F%AF%E8%A7%86%E5%8C%96/
// https://www.cnblogs.com/lifeofershisui/p/9037829.html
// https://blog.csdn.net/qq_37124765/article/details/82262754
// https://blog.csdn.net/qq_34719188/article/details/79179430
// https://www.cnblogs.com/21207-iHome/p/6034462.html
// https://segmentfault.com/a/1190000005930422
// https://blog.csdn.net/peach_blossom/article/details/78506483
// https://blog.csdn.net/u010696366/article/details/8941938
// SDK中Rplidar的ultra_simple

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <vector>
#include <cmath>

#include "sdk/include/rplidar.h" //RPLIDAR standard sdk, all-in-one header

#include <boost/shared_ptr.hpp>

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/registration/icp.h>
#include <pcl/registration/ndt.h>

#ifndef _countof
#define _countof(_Array) (int)(sizeof(_Array) / sizeof(_Array[0]))
#endif

typedef struct {
    double  dst;
    double  angle;
    int32_t quality;
    bool    is_start;

} __scandot;

#ifdef _WIN32
#include <Windows.h>
#define delay(x)   ::Sleep(x)
#else
#include <unistd.h>
static inline void delay(_word_size_t ms){
    while (ms>=1000){
        usleep(1000*1000);
        ms-=1000;
    };
    if (ms!=0)
        usleep(ms*1000);
}
#endif

using namespace std;
using namespace rp::standalone::rplidar;

bool checkRPLIDARHealth(RPlidarDriver * drv)
{
    u_result     op_result;
    rplidar_response_device_health_t healthinfo;


    op_result = drv->getHealth(healthinfo);
    if (IS_OK(op_result)) { // the macro IS_OK is the preperred way to judge whether the operation is succeed.
        printf("RPLidar health status : %d\n", healthinfo.status);
        if (healthinfo.status == RPLIDAR_STATUS_ERROR) {
            fprintf(stderr, "Error, rplidar internal error detected. Please reboot the device to retry.\n");
            // enable the following code if you want rplidar to be reboot by software
            // drv->reset();
            return false;
        } else {
            return true;
        }

    } else {
        fprintf(stderr, "Error, cannot retrieve the lidar health code: %x\n", op_result);
        return false;
    }
}

#include <signal.h>
bool ctrl_c_pressed;
void ctrlc(int)
{
    ctrl_c_pressed = true;
}

int main(int argc, const char * argv[]) {
    const char * opt_com_path = NULL;
    _u32         baudrateArray[2] = {115200, 256000};
    _u32         opt_com_baudrate = 0;
    u_result     op_result;

    bool useArgcBaudrate = false;

    //自增加
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>), cloud_last(new pcl::PointCloud<pcl::PointXYZ>);
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));

    viewer->setBackgroundColor(0, 0, 0);
    //viewer->addPointCloud<pcl::PointXYZ>(cloud, "sample cloud");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "sample cloud");     // 1
    viewer->addCoordinateSystem(1.0);
    viewer->initCameraParameters();

    pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;   //创建滤波器对象

    pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp; //创建ICP对象，用于ICP配准
    icp.setMaximumIterations(1);  // 设置为1以便下次调用
    icp.setMaxCorrespondenceDistance(40);
    icp.setTransformationEpsilon(1e-10);
    icp.setEuclideanFitnessEpsilon(0.05);      // 0.001
    icp.setMaximumIterations(20);

    //NDT配准
    //初始化正态分布变换（NDT）
    pcl::NormalDistributionsTransform<pcl::PointXYZ, pcl::PointXYZ> ndt;
    //设置匹配迭代的最大次数
    ndt.setMaximumIterations(80);
    //为终止条件设置最小转换差异
    ndt.setTransformationEpsilon(0.001);        // 0.05
    //为More-Thuente线搜索设置最大步长
    ndt.setStepSize(0.007);
    //设置NDT网格结构的分辨率（VoxelGridCovariance）（体素格的大小）
    ndt.setResolution(0.07);


    static double x_esti = 0, y_esti = 0;


    printf("Ultra simple LIDAR data grabber for RPLIDAR.\n"
           "Version: "RPLIDAR_SDK_VERSION"\n");

    // read serial port from the command line...
    if (argc>1) opt_com_path = argv[1]; // or set to a fixed value: e.g. "com3"

    // read baud rate from the command line if specified...
    if (argc>2)
    {
        opt_com_baudrate = strtoul(argv[2], NULL, 10);
        useArgcBaudrate = true;
    }

    if (!opt_com_path) {
#ifdef _WIN32
        // use default com port
        opt_com_path = "\\\\.\\com3";
#else
        opt_com_path = "/dev/ttyUSB0";
#endif
    }

    // create the driver instance
    RPlidarDriver * drv = RPlidarDriver::CreateDriver(DRIVER_TYPE_SERIALPORT);
    if (!drv) {
        fprintf(stderr, "insufficent memory, exit\n");
        exit(-2);
    }

    rplidar_response_device_info_t devinfo;
    bool connectSuccess = false;
    // make connection...
    if(useArgcBaudrate)
    {
        if(!drv)
            drv = RPlidarDriver::CreateDriver(DRIVER_TYPE_SERIALPORT);
        if (IS_OK(drv->connect(opt_com_path, opt_com_baudrate)))
        {
            op_result = drv->getDeviceInfo(devinfo);

            if (IS_OK(op_result))
            {
                connectSuccess = true;
            }
            else
            {
                delete drv;
                drv = NULL;
            }
        }
    }
    else
    {
        size_t baudRateArraySize = (sizeof(baudrateArray))/ (sizeof(baudrateArray[0]));
        for(size_t i = 0; i < baudRateArraySize; ++i)
        {
            if(!drv)
                drv = RPlidarDriver::CreateDriver(DRIVER_TYPE_SERIALPORT);
            if(IS_OK(drv->connect(opt_com_path, baudrateArray[i])))
            {
                op_result = drv->getDeviceInfo(devinfo);

                if (IS_OK(op_result))
                {
                    connectSuccess = true;
                    break;
                }
                else
                {
                    delete drv;
                    drv = NULL;
                }
            }
        }
    }
    if (!connectSuccess) {

        fprintf(stderr, "Error, cannot bind to the specified serial port %s.\n"
            , opt_com_path);
        goto on_finished;
    }

    // print out the device serial number, firmware and hardware version number..
    printf("RPLIDAR S/N: ");
    for (int pos = 0; pos < 16 ;++pos) {
        printf("%02X", devinfo.serialnum[pos]);
    }

    printf("\n"
            "Firmware Ver: %d.%02d\n"
            "Hardware Rev: %d\n"
            , devinfo.firmware_version>>8
            , devinfo.firmware_version & 0xFF
            , (int)devinfo.hardware_version);



    // check health...
    if (!checkRPLIDARHealth(drv)) {
        goto on_finished;
    }

    signal(SIGINT, ctrlc);

    drv->startMotor();
    // start scan...
    drv->startScan(0,1);

    // fetech result and print it out...
    while (1) {
        rplidar_response_measurement_node_t nodes[8192];
        size_t   count = _countof(nodes);

        op_result = drv->grabScanData(nodes, count);

        if (IS_OK(op_result)) {
            drv->ascendScanData(nodes, count);
            vector<__scandot> data;

            cloud_last->points.resize(cloud->points.size());
            for (int pos = 0; pos < (int)cloud_last->points.size(); pos++) {
                cloud_last->points[pos] = cloud->points[pos];
            }

            cloud->points.resize(count);
            for (int pos = 0; pos < (int)count ; ++pos) {
                __scandot temp;
                temp.angle    = (nodes[pos].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT)/64.0f;
                temp.dst      =  nodes[pos].distance_q2/4.0f;
                temp.quality  =  nodes[pos].sync_quality >> RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT;
                temp.is_start = (nodes[pos].sync_quality & RPLIDAR_RESP_MEASUREMENT_SYNCBIT);
                data.push_back(temp);

//                printf("%s theta: %03.2f Dist: %08.2f Q: %d \n",
//                    (nodes[pos].sync_quality & RPLIDAR_RESP_MEASUREMENT_SYNCBIT) ?"S ":"  ",
//                    (nodes[pos].angle_q6_checkbit >> RPLIDAR_RESP_MEASUREMENT_ANGLE_SHIFT)/64.0f,
//                    nodes[pos].distance_q2/4.0f,
//                    nodes[pos].sync_quality >> RPLIDAR_RESP_MEASUREMENT_QUALITY_SHIFT);

//                printf("%s theta: %03.2f Dist: %08.2f Q: %d \n",
//                    temp.is_start ?"S ":"  ",
//                    temp.angle,
//                    temp.dst,
//                    temp.quality);

                if (!temp.quality)
                    continue;

                cloud->points[pos].x = -temp.dst * sin(temp.angle * M_PI / 180.) / 10.;
                cloud->points[pos].y =  temp.dst * cos(temp.angle * M_PI / 180.) / 10.;         // cm
                cloud->points[pos].z =  0.;
            }
        }

        sor.setInputCloud (cloud);                           //设置待滤波的点云
        sor.setMeanK (50);                               //设置在进行统计时考虑查询点临近点数
        sor.setStddevMulThresh (1.2);                      //设置判断是否为离群点的阀值, 1.0
        sor.filter (*cloud);                    //存储

        icp.setInputCloud(cloud_last); //设置输入点云
        icp.setInputTarget(cloud); //设置目标点云（输入点云进行仿射变换，得到目标点云）
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_t(new pcl::PointCloud<pcl::PointXYZ>); //存储结果
        //进行配准，结果存储在Final中
        icp.align(*cloud_t);
        //输出ICP配准的信息（是否收敛，拟合度）
        std::cout << "has converged:" << icp.hasConverged() << " score: " <<
        icp.getFitnessScore() << std::endl;
        //输出最终的变换矩阵（4x4）
        std::cout << icp.getFinalTransformation() << std::endl;


        // 设置要配准的点云
        ndt.setInputCloud(cloud_t);
        //设置点云配准目标
        ndt.setInputTarget(cloud);
        //计算需要的刚体变换以便将输入的点云匹配到目标点云
        pcl::PointCloud<pcl::PointXYZ>::Ptr output_cloud(new pcl::PointCloud<pcl::PointXYZ>);
        ndt.align(*output_cloud, icp.getFinalTransformation());


        x_esti += ndt.getFinalTransformation()(0, 3);
        y_esti += ndt.getFinalTransformation()(1, 3);
        std::cout << x_esti << " " << y_esti << std::endl;

        viewer->removePointCloud("sample cloud");
        viewer->addPointCloud<pcl::PointXYZ> (cloud, "sample cloud");
        viewer->spinOnce(10);
        boost::this_thread::sleep(boost::posix_time::microseconds(10));

        if (ctrl_c_pressed){
            break;
        }
    }

    drv->stop();
    drv->stopMotor();
    // done!
on_finished:
    RPlidarDriver::DisposeDriver(drv);
    drv = NULL;
    return 0;
}

