//#include "stdafx.h"
#include "CCamera.h"
#include <vector>


#define PASS_AREA 6000
#define XCORD_AREA 1000

//intializes PiCam
CCamera::CCamera()
{
	cam.open(0);
}

//checks location of red marker and returns its x-cord
//returns true if the marker is greater than the pass area
bool CCamera::red_check(int &xcord)
{
	bool test = false;

	//crop and flip captured image
	cam.grab();
	cam.retrieve(intial);
	cv::flip(intial, intial, 0);
	cv::Rect croprect(0,100,640,380);
	intial = intial(croprect);

	//convert image to HSV and turn to binary image where only red is showing
	cv::cvtColor(intial, hsv, CV_BGR2HSV);
	cv::inRange(hsv, cv::Scalar(2, 170, 100), cv::Scalar(10, 255, 255), bluesel);
	
	//clean up binary image
	cv::erode(bluesel, erode, cv::Mat());
	cv::dilate(erode, dilate, cv::Mat());
	
	bounded = intial;
	
	//find shapes within binary image
	findContours(dilate, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	for (unsigned int i = 0; i < contours.size(); i++)
	{
		cv::Rect r = boundingRect(contours.at(i));
		drawContours(bounded, contours, i, cv::Scalar(255, 255, 255), -1, 8, hierarchy);
		
		//set xcordinate
		xcord = r.x + (r.width/2);
		
		//check if area is greater than pass area
		if (r.area() > PASS_AREA)
		{
			cv::rectangle(bounded, r, cv::Scalar(255, 255, 255));
			test = true;
		}
	}
	
	
	//print image with proccessed red marker overtop
	cv::imshow("Redbounded", bounded);

	return test;
}

//checks location of green marker and returns its x-cord
//returns true if the marker is greater than the pass area
bool CCamera::green_check(int &xcord)
{
	bool test = false;
	
	//crop and flip captured image
	cam.grab();
	cam.retrieve(intial);
	cv::flip(intial, intial, 0);
	cv::Rect croprect(0,100,640,380);
	intial = intial(croprect);
	
	//convert image to HSV and turn to binary image where only red is showing
	cv::cvtColor(intial, hsv, CV_BGR2HSV);
	cv::inRange(hsv, cv::Scalar(42, 100, 100), cv::Scalar(55, 255, 255), bluesel);

	//clean up binary image
	cv::erode(bluesel, erode, cv::Mat());
	cv::dilate(erode, dilate, cv::Mat());
	

	bounded = intial;

	//find shapes within binary image
	findContours(dilate, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	for (unsigned int i = 0; i < contours.size(); i++)
	{
		cv::Rect r = boundingRect(contours.at(i));
		drawContours(bounded, contours, i, cv::Scalar(255, 255, 255), -1, 8, hierarchy);
		
		//set xcordinate
		xcord = r.x + (r.width/2);
		
		//check if area is greater than pass area
		if (r.area() > PASS_AREA)
		{
			cv::rectangle(bounded, r, cv::Scalar(255, 255, 255));
			test = true;
		}
	}
	

	cv::imshow("Greenbounded", bounded);

	return test;
}


cv::Mat CCamera::return_frame()
{
	cv::Mat ret;
	cam.grab();
	cam.retrieve(ret);
	return ret;
}
