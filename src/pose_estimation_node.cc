//
// Created by eashwara on 11.06.20.
//


# include "pose_estimation_nodecore.h"

int main(int argc, char** argv)
{
	ros::init(argc, argv, "pose_estimation");

	CoralPoseEstimationNodeCore node(ros::NodeHandle(), ros::NodeHandle("~"));
	node.run();
}