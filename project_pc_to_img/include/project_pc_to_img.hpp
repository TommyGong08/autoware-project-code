//opencv
#include<opencv2/video.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/calib3d/calib3d.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;

#include<cv_bridge/cv_bridge.h>
#include <sensor_msgs/PointCloud2.h>
#include <image_transport/image_transport.h>
#include <pcl/io/pcd_io.h>

#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>


#include<math.h>
#include<Eigen/Dense>
using namespace cv;
using namespace std;
using namespace Eigen;

Eigen::Quaterniond Q_l2v = Eigen::Quaterniond(-0.003936, 0.007856, 0.707845, 0.706313).normalized();
Eigen::Quaterniond Q_c2v = Eigen::Quaterniond(-0.716810, 0.000349, -0.005084, 0.697250).normalized();
Eigen::Vector3d T_l2v(0.010524, 1.613485, 1.228857);
Eigen::Vector3d T_c2v(0.046892, 1.845396, 1.189992);

// Eigen::Isometry3d T_l = Isometry3d::Identity();
// Eigen::Isometry3d T_c = Isometry3d::Identity();


// camera intrinsic
Eigen::MatrixXf K(3,3);

Eigen::VectorXf D(5);


// color point cloud
pcl::PointCloud<pcl::PointXYZRGB> color_cloud;
pcl::PointCloud<pcl::PointXYZ> cloud;
sensor_msgs::PointCloud2 output;
sensor_msgs::PointCloud2 output_color_cloud;










