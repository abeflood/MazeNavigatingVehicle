#pragma once

#include "CControlPi.h"
#include "CMotor.h"
#include "Cbase.h"

// OpenCV Include
#include <opencv2/opencv.hpp>
using namespace std;

class CCamera
{
protected:
	cv::VideoCapture cam;
	std::vector<cv::Vec4i> hierarchy;
	std::vector<vector<cv::Point>> contours;
	std::vector<cv::Point> contour;
	std::vector<cv::Vec4i> hierarchy2;
	std::vector<vector<cv::Point>> contours2;
	std::vector<cv::Point> contour2;
	cv::Mat intial, hsv, bluesel, dilate, erode, bounded,grey,threshold, between, between2, ballcheck;
	CMotor motor;
public:

	CCamera();

	bool red_check(int &xcord);
	bool green_check(int &xcord);
	cv::Mat return_frame();



};
