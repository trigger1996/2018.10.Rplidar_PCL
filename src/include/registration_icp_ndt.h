#ifndef REGISTRATION_ICP_NDT_H
#define REGISTRATION_ICP_NDT_H

#include "config.h"
#include "registration_abs.hpp"

class __registration_icp_ndt : public __registration_abs {
public:
    __registration_icp_ndt() : __registration_abs() {
        src_cloud_name = "src_cloud";
        ref_cloud_name = "ref_cloud";

        icpTransMat = new Matrix4f;
        icpTransMat->setZero(4, 4);

        init();
    }

    __registration_icp_ndt(bool _is_show) : __registration_abs(_is_show) {
        src_cloud_name = "src_cloud";
        ref_cloud_name = "ref_cloud";

        icpTransMat = new Matrix4f;
        icpTransMat->setZero(4, 4);

        init();
    }

    __registration_icp_ndt(bool _is_show, char _viewer_name_in[]) : __registration_abs(_is_show, _viewer_name_in) {
        src_cloud_name = "src_cloud";
        ref_cloud_name = "ref_cloud";

        icpTransMat = new Matrix4f;
        icpTransMat->setZero(4, 4);

        init();
    }

    int init();

    int update();

protected:
    const char *src_cloud_name = NULL;
    const char *ref_cloud_name = NULL;

    bool   is_icp_converged, is_ndt_converged;
    double icp_score,        ndt_score;

    Matrix4f *icpTransMat;

    pcl::StatisticalOutlierRemoval<pcl::PointXYZ>::Ptr sor;                          // 创建滤波器对象
    pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ>::Ptr icp;               // 创建ICP对象，用于ICP配准
    pcl::NormalDistributionsTransform<pcl::PointXYZ, pcl::PointXYZ>::Ptr ndt;        // 创建正态分布变换（NDT）
};

#endif // REGISTRATION_ICP_NDT_H
