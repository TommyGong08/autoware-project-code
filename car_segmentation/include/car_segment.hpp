#include<sys/types.h>
#include<dirent.h>
#include<fstream>
#include<vector>
#include<string>
#include<stdexcept>
#include<sstream>
#include<float.h>


#include<cv_bridge/cv_bridge.h>
#include <sensor_msgs/PointCloud2.h>
#include <image_transport/image_transport.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/segmentation/extract_clusters.h>
// #include <pcl/search/impl/kdtree.hpp>
//#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/filters/extract_indices.h>
// #include <pcl/segmentation/progressive_morphological_filter.h>
#include <pcl/segmentation/sac_segmentation.h>
#include<pcl/point_types.h>
#include<pcl/common/transforms.h>
#include<visualization_msgs/Marker.h>
#include<visualization_msgs/MarkerArray.h>

//opencv
#include<opencv2/video.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/calib3d/calib3d.hpp>
#include<opencv2/highgui/highgui.hpp>


#include<math.h>
#include<Eigen/Dense>
using namespace cv;
using namespace std;
using namespace Eigen;

// color point cloud
pcl::PointCloud<pcl::PointXYZ>::Ptr pc_raw(new pcl::PointCloud<pcl::PointXYZ>);
pcl::PointCloud<pcl::PointXYZ>::Ptr pc_raw2(new pcl::PointCloud<pcl::PointXYZ>);
pcl::PointCloud<pcl::PointXYZ>::Ptr pc_filter(new pcl::PointCloud<pcl::PointXYZ>);
pcl::PointCloud<pcl::PointXYZ>::Ptr pc_ground(new pcl::PointCloud<pcl::PointXYZ>);
pcl::PointCloud<pcl::PointXYZ>::Ptr pc_no_ground(new pcl::PointCloud<pcl::PointXYZ>);
sensor_msgs::PointCloud2 output1;
sensor_msgs::PointCloud2 output2;
sensor_msgs::PointCloud2 output3;
sensor_msgs::PointCloud2 output4;
sensor_msgs::PointCloud2 output5;
vector<string> v_pcd;

string pcd_path_name = "/home/neousys/hailong/project1_ws/src/car_segmentation/data/pcd_data/";
visualization_msgs::MarkerArray bounding_boxes;









