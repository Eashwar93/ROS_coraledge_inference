//
// Created by eashwara on 11.06.20.
//

#include <iostream>
#include <cv_bridge/cv_bridge.h>

#include "edgetpu.h"
#include "img_prep.h"
#include "humanpose_engine.h"
#include "opencv2/opencv.hpp"
#include "pose_estimation_nodecore.h"

CoralPoseEstimationNodeCore::CoralPoseEstimationNodeCore(const ros::NodeHandle &nh,
                                                         const ros::NodeHandle &nh_private)
                                                         : nh_(nh_private), it_(nh)
{

	nh_.getParam("Input_image_topic",input_image_topic_);
	nh_.getParam("Output_image_topic",output_image_topic_);
	nh_.getParam("model_path",model_path_);
	nh_.getParam("pose_threshold",pose_threshold_);
	nh_.getParam("keypoint_threshold",keypoint_threshold_);
	nh_.getParam("image_height",image_height_);
	nh_.getParam("image_width",image_width_);
	nh_.getParam("with_edgetpu",with_edgetpu_);

	std::shared_ptr<edgetpu::EdgeTpuContext> edgetpu_context =
					edgetpu::EdgeTpuManager::GetSingleton()->OpenDevice();
	engine_.reset(new edge::HumanPoseEngine(model_path_,edgetpu_context,with_edgetpu_));
	engine_->PrepEngine(model_path_, edgetpu_context, with_edgetpu_);
	std::cout << "Success" << std::endl;

	required_input_tensor=engine_->GetInputShape();


	imageSubscriber_ = it_.subscribe(input_image_topic_, 1000, &CoralPoseEstimationNodeCore::imageCallback, this);
	imagePublisher_ = it_.advertise(output_image_topic_,1);
}

void CoralPoseEstimationNodeCore::imageCallback(const sensor_msgs::Image::ConstPtr &msg)
{
	cv_bridge::CvImagePtr cv_ptr;
	try
	{
		cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8);
		//cv::imshow("try", cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::BGR8)->image);
	}
	catch (cv_bridge::Exception &e)
	{
		ROS_ERROR_STREAM("cv_bridge exception" << e.what());
		return;
	}

	cv_bridge::CvImage in_img;
	in_img.header = cv_ptr->header;
	in_img.encoding = cv_ptr->encoding;
	in_img.image = cv_ptr->image.clone();
	std::vector<float> raw_results;
	//edge::GetInputFromImage(in_img.image,required_input_tensor_width_,required_input_tensor_height_,required_input_tensor_channels_);
	const auto& input = edge::GetInputFromImage(in_img.image,required_input_tensor[2],required_input_tensor[1],required_input_tensor[3]);
	try
	{
		 raw_results = engine_->RunInference(input);
	}
	catch (std::runtime_error& e)
	{
		ROS_ERROR_STREAM("Tensorflow runtime detection error: " << e.what());
		return;
	}

	std::cout << "2" << std::endl;
	const auto& detection_result = engine_->PoseEstimateWithOutputVector(raw_results,pose_threshold_);
	std::cout << "3" << std::endl;
	edge::HumanPoseEngine::img_overlay(in_img.image,detection_result,keypoint_threshold_,required_input_tensor[2]
					,required_input_tensor[1], image_width_, image_height_);

	std::cout <<  "conversion successful" << std::endl;

}

