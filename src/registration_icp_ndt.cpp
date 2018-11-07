#include "include/registration_icp_ndt.h"

int __registration_icp_ndt::init() {

    pcl::StatisticalOutlierRemoval<pcl::PointXYZ>::Ptr _sor(new pcl::StatisticalOutlierRemoval<pcl::PointXYZ>);
    pcl::VoxelGrid<pcl::PointXYZ>::Ptr _vox(new pcl::VoxelGrid<pcl::PointXYZ>);
    pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ>::Ptr _icp(new pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ>);
    pcl::NormalDistributionsTransform<pcl::PointXYZ, pcl::PointXYZ>::Ptr _ndt(new pcl::NormalDistributionsTransform<pcl::PointXYZ, pcl::PointXYZ>);

    sor = _sor;
    vox = _vox;
    icp = _icp;
    ndt = _ndt;
    //sor.setInputCloud (cloud);                    //      设置待滤波的点云
    sor->setMeanK (30);                             // 50   设置在进行统计时考虑查询点临近点数
    sor->setStddevMulThresh (1.2);                  //      设置判断是否为离群点的阀值, 1.0
    vox->setLeafSize(0.04f, 0.04f, 0.04f);


    icp->setMaxCorrespondenceDistance(10);          // 40
    icp->setTransformationEpsilon(1e-10);           // 1e-10
    icp->setEuclideanFitnessEpsilon(0.01);          // 0.001
    icp->setMaximumIterations(20);                  // 20

    ndt->setMaximumIterations(55);                  // 80   设置匹配迭代的最大次数
    ndt->setTransformationEpsilon(0.01);            // 0.05 为终止条件设置最小转换差异
    ndt->setStepSize(0.007);                        //      为More-Thuente线搜索设置最大步长
    ndt->setResolution(1.00);                       //      设置NDT网格结构的分辨率（VoxelGridCovariance）（体素格的大小）

    if (is_show) {
        viewer->setBackgroundColor(0, 0, 0);
        viewer->addCoordinateSystem(1.0);
        viewer->addPointCloud<pcl::PointXYZ>(cloud_last, src_cloud_name);
        viewer->addPointCloud<pcl::PointXYZ>(cloud, ref_cloud_name);
        viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, src_cloud_name);     // 1
        viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, ref_cloud_name);     // 1
        viewer->initCameraParameters();
    }

    return 0;
}

int __registration_icp_ndt::update() {
    /// 点云滤波
    sor->setInputCloud(cloud);
    sor->filter(*cloud);

    sor->setInputCloud(cloud_last);
    sor->filter(*cloud_last);

    vox->setInputCloud(cloud);
    vox->filter(*cloud);
    vox->setInputCloud(cloud_last);
    vox->filter(*cloud_last);

    /// ICP配准
    icp->setInputCloud(cloud_last);                 // 设置输入点云
    icp->setInputTarget(cloud);                     // 设置目标点云（输入点云进行仿射变换，得到目标点云）
    icp->align(*cloud_converged);
    *icpTransMat = icp->getFinalTransformation();
    is_icp_converged = icp->hasConverged();
    icp_score        = icp->getFitnessScore();

    /// NDT配准
    ndt->setInputCloud(cloud_converged);
    ndt->setInputTarget(cloud);
    ndt->align(*cloud_converged, icp->getFinalTransformation());
    *transMat = ndt->getFinalTransformation();      // 两个矩阵不用加，这个直接就是最后的结果
    is_ndt_converged = ndt->hasConverged();
    ndt_score        = ndt->getFitnessScore();

    dx = ndt->getFinalTransformation()(0, 3);
    dy = ndt->getFinalTransformation()(1, 3);
    dyaw = asin(ndt->getFinalTransformation()(0, 1)) * 180. / M_PI;


    /// 显示
    if (is_show) {
        viewer->removePointCloud(ref_cloud_name);
        viewer->removePointCloud(src_cloud_name);
        viewer->addPointCloud<pcl::PointXYZ> (cloud_last, src_cloud_name);
        viewer->addPointCloud<pcl::PointXYZ> (cloud, ref_cloud_name);
        viewer->spinOnce(5);
        boost::this_thread::sleep(boost::posix_time::microseconds(5));

    }

    return 0;
}
