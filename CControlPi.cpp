
#include <iostream>
#include <sstream>
#include "pigpio.h"

using namespace std;
#define ADCBITS 1024
#include "CControlPi.h"

//intializes PIGPIO
 CControlPi::CControlPi()
{
	 if (gpioInitialise() < 0)
	 {
		 cout << "GPIO INTIALIZED FAILED\n\n";
	 }
}

//closes PIGPIO
 CControlPi::~CControlPi()
 {
	 gpioTerminate();
 }

 //sets pin to input and reads digital value
void CControlPi::get_data(int channel, int &value)
{
	gpioSetMode(channel, PI_INPUT);
	value  = gpioRead(channel);
}

//set pin to output and send digital signal
void CControlPi::set_data(int channel, int value)
{
	gpioSetMode(channel, PI_OUTPUT);
	gpioWrite(channel, value);

}

//set pin to output and set servo using pin
void CControlPi::set_servo(int channel, int value)
{
	gpioSetMode(channel, PI_OUTPUT);
	gpioServo(channel, value);

}

//set pin to output and set motor -- Via PWM setting
void CControlPi::set_motor(int channel, int value)
{
	gpioSetMode(channel, PI_OUTPUT);
	gpioPWM(channel, value);
}



