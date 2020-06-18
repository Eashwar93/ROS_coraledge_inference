//
// Created by eashwara on 11.06.20.
//

#ifndef ROS_CORALEDGE_INFERENCE_POSE_ESTIMATION_NODECORE_H
#define ROS_CORALEDGE_INFERENCE_POSE_ESTIMATION_NODECORE_H

#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>
#include "humanpose_engine.h"

class CoralPoseEstimationNodeCore
{
private:
	ros::NodeHandle nh_;
	image_transport::ImageTransport it_;
	image_transport::Subscriber imageSubscriber_;
	image_transport::Publisher imagePublisher_;
	float pose_threshold_;
	float keypoint_threshold_;
	int image_height_;
	int image_width_;
	std::string input_image_topic_;
	std::string output_image_topic_;
	std::string model_path_;
	bool with_edgetpu_;
	std::vector<int> required_input_tensor;
	std::unique_ptr<edge::HumanPoseEngine> engine_;
public:

	CoralPoseEstimationNodeCore(const ros::NodeHandle& nh, const ros::NodeHandle& nh_private);

	void imageCallback(const sensor_msgs::Image::ConstPtr& msg);

	static void run()
	{
		ros::spin();
	}
};
#endif //ROS_CORALEDGE_INFERENCE_POSE_ESTIMATION_NODECORE_H
