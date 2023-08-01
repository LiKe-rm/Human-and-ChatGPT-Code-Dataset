#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <camera_info_manager/camera_info_manager.h>
#include <usb_cam/usb_cam.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <std_srvs/Empty.h>

class UsbCamNode {
public:
    UsbCamNode(ros::NodeHandle &nh) :
        nh_(nh),
        it_(nh),
        camera_info_manager_(nh) {

        // Parameters
        nh_.param("camera/frame_id", frame_id_, std::string("camera"));
        nh_.param("camera/image_width", image_width_, 640);
        nh_.param("camera/image_height", image_height_, 480);
        nh_.param("camera/image_format", image_format_, std::string("yuyv"));
        nh_.param("camera/pixel_format", pixel_format_, std::string("yuyv"));
        nh_.param("camera/camera_info_url", camera_info_url_, std::string(""));

        // Publishers
        image_pub_ = it_.advertise("image_raw", 1);

        // Services
        start_capture_srv_ = nh_.advertiseService("start_capture", &UsbCamNode::startCapture, this);
        stop_capture_srv_ = nh_.advertiseService("stop_capture", &UsbCamNode::stopCapture, this);

        // Initialize USB camera
        usb_cam::UsbCam::init(image_width_, image_height_, image_format_);

        // Initialize camera_info_manager
        camera_info_manager_.setCameraName("usb_camera");
        camera_info_manager_.loadCameraInfo(camera_info_url_);

        // Start capturing images
        capturing_ = true;
    }

    ~UsbCamNode() {
        usb_cam::UsbCam::shutdown();
    }

    void takeAndSendImage() {
        if (capturing_) {
            sensor_msgs::Image img;
            sensor_msgs::CameraInfo cam_info = camera_info_manager_.getCameraInfo();

            img.header.stamp = ros::Time::now();
            img.header.frame_id = frame_id_;
            img.width = image_width_;
            img.height = image_height_;
            img.encoding = sensor_msgs::image_encodings::YUV422;
            img.is_bigendian = false;
            img.step = image_width_ * 2;
            img.data.resize(img.step * img.height);

            usb_cam::UsbCam::grab_image(&img);

            image_pub_.publish(img, cam_info);
        }
    }

    bool startCapture(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res) {
        capturing_ = true;
        return true;
    }

    bool stopCapture(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res) {
        capturing_ = false;
        return true;
    }

private:
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    camera_info_manager::CameraInfoManager camera_info_manager_;
    image_transport::CameraPublisher image_pub_;
    ros::ServiceServer start_capture_srv_;
    ros::ServiceServer stop_capture_srv_;
    std::string frame_id_;
    int image_width_;
    int image_height_;
    std::string image_format_;
    std::string pixel_format_;
    std::string camera_info_url_;
    bool capturing_;
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "usb_cam_node");
    ros::NodeHandle nh;

    UsbCamNode usb_cam_node(nh);

    ros::Rate loop_rate(30); // 30 Hz

    while (ros::ok()) {
        usb_cam_node.takeAndSendImage();

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
