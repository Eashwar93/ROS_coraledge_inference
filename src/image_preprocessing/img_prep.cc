//
// Created by eashwara on 14.05.20.
//
#include "img_prep.h"
#include <iostream>

namespace edge
{
	//void GetInputFromImage(cv::Mat input_frame, const int& width, const int& height, const int& channels)
	std::vector<uint8_t> GetInputFromImage(cv::Mat input_frame, const int& width, const int& height, const int& channels)
	{
		cv::resize(input_frame, input_frame, cv::Size(width,height));
		cv::Mat flat = input_frame.reshape(1, input_frame.total()*input_frame.channels());
		std::vector<uint8_t> in_vec= input_frame.isContinuous()? flat : flat.clone();
		return in_vec;
	}
}