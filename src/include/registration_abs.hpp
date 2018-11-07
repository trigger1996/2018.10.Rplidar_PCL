#ifndef REGISTRATION_ABS_HPP
#define REGISTRATION_ABS_HPP

#include "config.h"
#include <boost/shared_ptr.hpp>
#include <eigen3/Eigen/Dense>

#include <pcl-1.8/pcl/point_types.h>
#include <pcl-1.8/pcl/point_cloud.h>
#include <pcl-1.8/pcl/visualization/cloud_viewer.h>
#include <pcl-1.8/pcl/filters/statistical_outlier_removal.h>
#include <pcl-1.8/pcl/filters/voxel_grid.h>
#include <pcl-1.8/pcl/filters/approximate_voxel_grid.h>
#include <pcl-1.8/pcl/registration/registration.h>
#include <pcl-1.8/pcl/registration/icp.h>
#include <pcl-1.8/pcl/registration/ndt.h>

using namespace std;
using namespace Eigen;

#define Z_Const_Val 1.      // 使用1是为了防止奇异值

class __registration_abs {
public:
    __registration_abs() {
        is_show = true;
        viewer_name = "3D_Viewer";
        init_Param();
    }

    __registration_abs(bool _is_show) {
        is_show = _is_show;
        viewer_name = "3D_Viewer";
        init_Param();
    }

    __registration_abs(bool _is_show, char _viewer_name_in[]) {
        is_show = _is_show;
        viewer_name = (const char *)_viewer_name_in;
        init_Param();
    }

    ~__registration_abs() {

    }

    void set_Src_PointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr in) {          // 移动点云
        cloud_last->points.resize(in->points.size());
        for (size_t i = 0; i < in->points.size(); i++)
            cloud_last->points[i] = in->points[i];
    }

    void set_Src_PointCloud(pcl::PointCloud<pcl::PointXYZ> in) {
        cloud_last->points.resize(in.points.size());
        for (size_t i = 0; i < in.points.size(); i++)
            cloud_last->points[i] = in.points[i];
    }

    void set_Src_PointCloud(vector<__scandot> in) {
        cloud_last->points.resize(in.size());
        for (size_t i = 0; i < in.size(); i++) {
            double x, y, z;
            Cylindrical_2_Cartesian(in[i].dst, in[i].angle, Z_Const_Val, x, y, z);
            cloud_last->points[i].x = x / 10.;
            cloud_last->points[i].y = y / 10.;
            cloud_last->points[i].z = z / 10.;
        }
    }

    void set_Ref_PointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr in) {          // 参考点云，不动的那个
        cloud->points.resize(in->points.size());
        for (size_t i = 0; i < in->points.size(); i++)
            cloud->points[i] = in->points[i];
    }

    void set_Ref_PointCloud(pcl::PointCloud<pcl::PointXYZ> in) {
        cloud->points.resize(in.points.size());
        for (size_t i = 0; i < in.points.size(); i++)
            cloud->points[i] = in.points[i];
    }

    void set_Ref_PointCloud(vector<__scandot> in) {
        // 角度需要以角度形式输入，而非弧度
        cloud->points.resize(in.size());
        for (size_t i = 0; i < in.size(); i++) {
            double x, y, z;
            Cylindrical_2_Cartesian(in[i].dst, in[i].angle, Z_Const_Val, x, y, z);
            cloud->points[i].x = x / 10.;
            cloud->points[i].y = y / 10.;
            cloud->points[i].z = z / 10.;
        }
    }

    pcl::PointCloud<pcl::PointXYZ>::Ptr get_Src_PointCloud()        { return cloud_last; }
    pcl::PointCloud<pcl::PointXYZ>::Ptr get_Ref_PointCloud()        { return cloud; }
    pcl::PointCloud<pcl::PointXYZ>::Ptr get_Converged_PointCloud()  { return cloud_converged; }

    double      get_dx()        { return dx;   }
    double      get_dy()        { return dy;   }
    double      get_dyaw()      { return dyaw; }
    Matrix4f    get_TransMat()  { return *transMat; }

    int init_Param() {
        pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud(new pcl::PointCloud<pcl::PointXYZ>),
                                            _cloud_last(new pcl::PointCloud<pcl::PointXYZ>),
                                            _cloud_converged(new pcl::PointCloud<pcl::PointXYZ>);
        cloud           = _cloud;
        cloud_last      = _cloud_last;
        cloud_converged = _cloud_converged;
        if (is_show) {
            boost::shared_ptr<pcl::visualization::PCLVisualizer> _viewer(new pcl::visualization::PCLVisualizer(viewer_name));
            viewer = _viewer;
        }
        transMat = new Matrix4f;
        transMat->setZero(4, 4);

        return 0;
    }

    virtual int init() {
        if (is_show) {
            viewer->setBackgroundColor(0, 0, 0);
            //viewer->addPointCloud<pcl::PointXYZ>(cloud, "sample cloud");
            //viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "sample cloud");     // 1
            viewer->addCoordinateSystem(1.0);
            viewer->initCameraParameters();
        }
    }

    virtual int update() = 0;

protected:

    bool is_show;
    const char *viewer_name = NULL;

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, cloud_last, cloud_converged;
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;

    Matrix4f *transMat;
    double dx, dy, dyaw;

    // 柱坐标系转直角坐标系
    inline void Cylindrical_2_Cartesian(double rho, double theta, double z_in, double &x, double &y, double &z) {
        x = -rho * sin(theta * M_PI / 180.);
        y =  rho * cos(theta * M_PI / 180.);
        z = z_in;
    }

};

#endif // REGISTRATION_ABS_HPP
