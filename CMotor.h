#pragma once
#include <unistd.h>
#include "CControlPi.h"
#include "CCamera.h"
#include "Cbase.h"
// OpenCV Include
#include <opencv2/opencv.hpp>

//sets pins for H-Bridge
#define AIN1 23
#define BIN1 19
#define AIN2 24
#define BIN2 13
#define PWMA 18
#define PWMB 6
#define STBY 17
#define RLED 4
#define GLED 12

using namespace std;


class CMotor
{
protected:
	CControlPi port;
	int direction;	// 0 is stopped, 1 is forward, 2 is backwards
	int l_m_speed;	//positive is forward, negative is backwards
	int r_m_speed;	//positive is forward, negative is backwards
public:
	CMotor();
	~CMotor();
	void forward();
	void left(int set);
	void right(int set);
	void reverse();
	void stop();
	void on_led(int channel);
	void off_led(int channel);
};
