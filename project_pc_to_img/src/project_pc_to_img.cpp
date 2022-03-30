#include <ros/ros.h>
#include"project_pc_to_img.hpp"


cv::Mat projectPcToImage(cv::Mat image, pcl::PointCloud<pcl::PointXYZ> point_cloud){
    color_cloud.clear();
    cv::Mat visual_img = image.clone();
    Eigen::VectorXf X(3);
    Eigen::VectorXf Y(3);
    for(int i = 0; i <point_cloud.size(); i++){
        Eigen::Vector3d point_i = Eigen::Vector3d(point_cloud[i].x, point_cloud[i].y, point_cloud[i].z);
        point_i = Q_l2v.inverse() * Q_c2v * (point_i - T_c2v) + T_l2v;
        //std::cout << point_i.transpose() << std::endl;
        
        // transform into pixel coordinate
        X(0) = point_i[0];
        X(1) = point_i[1];
        X(2) = point_i[2];
        Y = K * X;
        cv::Point pt;
        pt.x = Y(0) / Y(2);
        pt.y = Y(1) / Y(2);
        if(pt.x >=0 && pt.x < 1920 &&pt.y >=0 && pt.y< 1080 && point_cloud[i].x>0){
            // // create color point cloud
            pcl::PointXYZRGB p;
            p.x = point_cloud[i].x;
            p.y = point_cloud[i].y;
            p.z = point_cloud[i].z;
            p.b = image.at<cv::Vec3b>(pt.y, pt.x)[0];
            p.g = image.at<cv::Vec3b>(pt.y, pt.x)[1];
            p.r = image.at<cv::Vec3b>(pt.y, pt.x)[2];
            color_cloud.points.push_back(p);

            // draw points on front image
            cv::circle(visual_img, pt, 2, Scalar(255,255,255));
        }
    }
    return visual_img;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "pc_2_img");
    ROS_INFO("Start project point cloud to image");

    //publisher
    ros::NodeHandle nh;
    ros::Publisher pcl_pub = nh.advertise<sensor_msgs::PointCloud2>("pcl_output", 1);
    ros::Publisher color_cloud_pub = nh.advertise<sensor_msgs::PointCloud2>("pcl_color_cloud", 1);
    image_transport::ImageTransport it(nh);
    image_transport::Publisher img_pub = it.advertise("camera/image", 1);
    image_transport::Publisher visual_img_pub = it.advertise("visual_image", 1);


    //init param
    K << 2029.1089355290503, 0.0, 961.105118299655, 0.0, 2029.404084256603, 585.5222597066615, 0.0, 0.0, 1.0;
    D << -0.3713391106016114, 0.1439459925562498, -9.793218981776926e-05, 0.0014091097954690595, 0.0;
    
    //read data_seq
    ifstream infile;
    infile.open("/home/neousys/hailong/project1_ws/src/project1_raw_data/data_seq.txt", ios::in);
    string s;
    string img_name;
    string pcd_name;
    while(getline(infile, s)){
        v_img.push_back(s);
        getline(infile,s);
        v_pcd.push_back(s);
    }
    infile.close();


    ros::Rate loop_rate(1);
    while (ros::ok)
    {
        string pcd_file_name;
        string image_file_name;
        for (int i = 0; i < v_img.size(); i++){
            pcd_file_name = pcd_path_name + v_pcd[i];
            image_file_name = img_path_name + v_img[i];
            //read pointcloud
            pcl::io::loadPCDFile(pcd_file_name, cloud);

            //read camera image
            cv::Mat image = cv::imread(image_file_name, CV_LOAD_IMAGE_COLOR);
            //main fucntion
            //sensor_msgs::ImagePtr final_image = projectPcToImage(image, cloud);
            cv::Mat visual_img = projectPcToImage(image, cloud);

            // message conversion
            sensor_msgs::ImagePtr image_msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
            sensor_msgs::ImagePtr visual_image_msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", visual_img).toImageMsg();
            pcl::toROSMsg(cloud, output);
            pcl::toROSMsg(color_cloud, output_color_cloud);
            output.header.frame_id = "base_link";
            output_color_cloud.header.frame_id = "base_link";

            pcl_pub.publish(output);
            color_cloud_pub.publish(output_color_cloud);

            img_pub.publish(image_msg);
            visual_img_pub.publish(visual_image_msg);

            ros::spinOnce();
            loop_rate.sleep();
        }
    }
    return 0;
}
