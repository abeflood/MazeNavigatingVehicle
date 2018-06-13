#pragma once

#include "CControlPi.h"
#include "CCamera.h"
#include "CMotor.h"
#include "server.h"
#include "Cbase.h"
#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <vector>
// OpenCV Include
#include <opencv2/opencv.hpp>
using namespace std;


class CCar : public Cbase
{
protected:
	Server serv;
	CCamera cam;
	char getkey;
	CMotor motor;
	std::vector<std::string> cmds;
	bool forward_flag, reverse_flag, right_flag, left_flag, stop_flag, cmd_flag, green_flag, red_flag;
	int xcord;
	int pbtime1, timer_time;
	int set;
	

public:
	CCar();
	
	
	void update();

	void draw();

	void run();


};
