//#include "stdafx.h"
#include "CCar.h"


#define MAX_X 370
#define MIN_X 270
#define REG 1
#define SLIGHT 0
#define TURN_TIME 600

//returns time in ms since comp start
double GetTickCount(void)		//not my code...from https://stackoverflow.com/questions/7729686/convert-gettickcount-vxworks-to-linux
{
	struct timespec now;
	if (clock_gettime(CLOCK_MONOTONIC, &now))
		return 0;
	return now.tv_sec * 1000.0 + now.tv_nsec / 1000000.0;
}

//intialize starting values
CCar::CCar()
{
	forward_flag = false;
	reverse_flag = false;
	right_flag = false;
	left_flag = false;
	stop_flag = false;
	cmd_flag = false;
	green_flag =false;
	red_flag = false;
	xcord = 320;
	pbtime1 = 0;
	timer_time = -1;
}


//sets motor according to different motor flags
void CCar::update()
{

	//moves car forward
	if (forward_flag == true)
		{
		motor.forward();
		forward_flag = false;
		cout << "FORWARD\n";
		motor.on_led(GLED);
		motor.on_led(RLED);
		}
	//moves car left -- either sharp turn or slight correction depending on set variable
	else if (left_flag == true)
		{
				
		motor.left(set);
		left_flag = false;
		cout << "LEFT\n";
		motor.off_led(GLED);
		motor.on_led(RLED);
		}
	//moves car right -- either sharp turn or slight correction depending on set variable
	else if (right_flag == true)
		{
		motor.right(set);
		right_flag = false;
		cout << "RIGHT\n";
		motor.on_led(GLED);
		motor.off_led(RLED);
		}
}

//checks camera and sets motor flags
void CCar::draw()
{
	//checks size of and x cordinate of marker
	green_flag = cam.green_check(xcord);
	red_flag = cam.red_check(xcord);
	
	//ensure new command only occurs every 600 ms, giving time for previous command to intiate
	if (((pbtime1 + timer_time) - GetTickCount()) < 0)
	{
		//if both markers are close then move striaght
		if (red_flag && green_flag)
			{
			forward_flag =true;
			red_flag = false;
			green_flag = false;
			pbtime1 = GetTickCount();
			timer_time = 500;
			cout << "red and green flag\n";
			}
			
		//if red marker is close turn left
		else if (red_flag)
			{
			motor.stop();
			left_flag = true;
			red_flag = false;
			pbtime1 = GetTickCount();
			set = REG;
			timer_time = TURN_TIME;
			cout << "red flag\n";
			}
			
		//if green marker is close turn right
		else if (green_flag)
			{
			motor.stop();
			right_flag = true;
			green_flag = false;
			pbtime1 = GetTickCount();
			set = REG;
			timer_time = TURN_TIME;
			cout << "green flag\n";
			}
			
		//if xcord is greater then threshold cordinate then slight correction left
		else if (xcord > MAX_X)  
			{
			cout << "slight left\n";
			left_flag = true;
			set = SLIGHT;
			pbtime1 = GetTickCount();
			timer_time = 10;
			}
			
		//if xcord is less then the threshold coordinate then slight correction right
		else if (xcord < MIN_X)
			{
			cout << "slight right\n";
			right_flag = true;
			set = SLIGHT;
			pbtime1 = GetTickCount();
			timer_time = 10;
			}
			
		//if none of these are true then continue going forward
		else 
			{
			cout << "remain forward\n";
			forward_flag = true;
			pbtime1 = GetTickCount();
			timer_time = 10;
			}
	 }
}

//runs program in loop
void CCar::run()
{
	cout << "program start\n";
	char test = 0;
	do
	{
		update(test);
		draw();
		
		test = cv::waitKey(1);
	} while (test != 'q');
}
