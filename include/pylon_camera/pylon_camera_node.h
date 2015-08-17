/*
 * pylon_camera_node.h
 *
 *  Created on: Jun 10, 2015
 *      Author: md
 */
#ifndef PYLON_CAMERA_NODE_H_
#define PYLON_CAMERA_NODE_H_

#include <iostream>
#include <memory>
#include <ros/ros.h>
#include <numeric>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/image_encodings.h>
#include <boost/array.hpp>
#include <image_transport/image_transport.h>

#include <pylon_camera/pylon_camera_parameter.h>
#include <pylon_camera/pylon_interface.h>
#include <pylon_camera_msgs/SetExposureSrv.h>
#include <pylon_camera_msgs/SetBrightnessSrv.h>
#include <pylon_camera_msgs/SetSleepingSrv.h>

using std::cout;
using std::endl;
#ifdef WITH_OPENCV
using namespace cv;
#endif

namespace pylon_camera
{

class PylonCameraNode
{
public:
    PylonCameraNode();
    virtual ~PylonCameraNode();

    bool init();
    bool initAndRegister();
    bool startGrabbing();
    void createPylonInterface();
    void getInitialCameraParameter();
    void updateAquisitionSettings();
    uint32_t getNumSubscribers();
    bool grabImage();
    bool setExposureCallback(pylon_camera_msgs::SetExposureSrv::Request &req,
        pylon_camera_msgs::SetExposureSrv::Response &res);
    bool setBrightnessCallback(pylon_camera_msgs::SetBrightnessSrv::Request &req,
        pylon_camera_msgs::SetBrightnessSrv::Response &res);
    bool setSleepingCallback(pylon_camera_msgs::SetSleepingSrv::Request &req,
        pylon_camera_msgs::SetSleepingSrv::Response &res);
    bool have_intrinsic_data();
    bool is_sleeping();
    void checkForPylonAutoFunctionRunning();

    virtual bool brightnessValidation(int target);
    virtual int calcCurrentBrightness();
    virtual float getCurrenCurrentExposure();

    PylonInterface *pylon_interface_;
    PylonCameraParameter params_;

    int target_brightness_;

    ros::ServiceServer set_exposure_service_;
    ros::ServiceServer set_brightness_service_;
    ros::ServiceServer set_sleeping_service_;

    sensor_msgs::Image img_raw_msg_;
    sensor_msgs::CameraInfo cam_info_msg_;

    image_transport::CameraPublisher img_raw_pub_;

    int params_update_counter_;
    bool brightness_service_running_;

protected:

    ros::NodeHandle nh_;
    image_transport::ImageTransport* it_;
    bool is_sleeping_;

};
} /* namespace pylon_camera */
#endif /* PYLON_CAMERA_NODE_H_ */
