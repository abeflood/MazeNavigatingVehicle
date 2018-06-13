#include "CMotor.h"
#include <unistd.h>

//speeds for various directions
#define MAX_A_RVS 1
#define MAX_B_RVS 1
#define MAX_A_FWD 125
#define MAX_B_FWD 135
#define MAX_A_RHT 85	
#define MAX_B_RHT 85	
#define MAX_A_LFT 85	
#define MAX_B_LFT 85
#define MAX_A_RHTSL 35	
#define MAX_B_RHTSL 0	
#define MAX_A_LFTSL 0	
#define MAX_B_LFTSL 50
//for controlling motor
#define SLIGHT 0
#define REG 1
#define FOR 1
#define REV 2
//intializes pins needed for H-bridge control
CMotor::CMotor()
{
	port.set_motor(PWMA, 0);
	port.set_motor(PWMB, 0);
	port.set_data(STBY,1);
	direction = 0;
	r_m_speed = 0;
	l_m_speed = 0;
}


CMotor::~CMotor()
{
	port.set_motor(PWMA, 0);
	port.set_motor(PWMB, 0);
	//port.set_data(STBY,0);
}

//sets car going forward
void CMotor::forward()
{
	//To avoid quick direction change of motor
	if (direction == REV)
		{
			stop();
			usleep(30000);
		}
	//sets neccesary pins
	port.set_data(AIN1,1);
	port.set_data(AIN2,0);
	port.set_data(BIN1,1);
	port.set_data(BIN2,0);
	
	port.set_motor(PWMA, MAX_A_FWD);
	port.set_motor(PWMB, MAX_B_FWD);
	
	direction = FOR;
	r_m_speed = MAX_A_FWD;
	l_m_speed = MAX_B_FWD;
}

//sets car going left
void CMotor::left(int set)
{
	//To avoid quick direction change of motor
	if (direction == REV)
		{
			stop();
			usleep(30000);
		}
		
	//sets neccesary pins
	port.set_data(AIN1,0);
	port.set_data(AIN2,1);
	port.set_data(BIN1,1);
	port.set_data(BIN2,0);
	
	if (set == REG)
	{
		port.set_motor(PWMA, MAX_A_LFT);
		port.set_motor(PWMB, MAX_B_LFT);
	}
	else if (set == SLIGHT)
	{
		port.set_motor(PWMA, MAX_A_LFTSL);
		port.set_motor(PWMB, MAX_B_LFTSL);
	}
	direction = FOR;
	r_m_speed = MAX_A_LFT;
	l_m_speed = MAX_B_LFT;
}

void CMotor::right(int set)
{
	//To avoid quick direction change of motor
	if (direction == REV)
		{
			stop();
			usleep(30000);
		}
		
	//sets neccesary pins
	port.set_data(AIN1,1);
	port.set_data(AIN2,0);
	port.set_data(BIN1,0);
	port.set_data(BIN2,1);
	
	if (set == REG)
	{
	port.set_motor(PWMA, MAX_A_RHT);
	port.set_motor(PWMB, MAX_B_RHT);
	}
	else if (set == SLIGHT)
	{
	port.set_motor(PWMA, MAX_A_RHTSL);
	port.set_motor(PWMB, MAX_B_RHTSL);
	}
	
	direction = FOR;
	r_m_speed = MAX_A_RHT;
	l_m_speed = MAX_B_RHT;
}

//puts car in reverse
void CMotor::reverse()
{
	if (direction == FOR)
		{
			stop();
			usleep(30000);
		}
	port.set_data(AIN1,0);
	port.set_data(AIN2,1);
	
	port.set_data(BIN1,0);
	port.set_data(BIN2,1);
	
	port.set_motor(PWMA, MAX_A_RVS);
	port.set_motor(PWMB, MAX_B_RVS);
	
	direction = REV;
	r_m_speed = -MAX_A_RVS;
	l_m_speed = -MAX_B_RVS;
}

void CMotor::stop()
{
	port.set_data(AIN1,1);
	port.set_data(AIN2,0);
	port.set_data(BIN1,1);
	port.set_data(BIN2,0);
	port.set_motor(PWMA, 0);
	port.set_motor(PWMB, 0);
	direction = 0;
	r_m_speed = 0;
	l_m_speed = 0;
}

//turn on/off LED
void CMotor::on_led(int channel)
{
		port.set_data(channel, 1); 
}

void CMotor::off_led(int channel)
{
		port.set_data(channel, 0); 
}
