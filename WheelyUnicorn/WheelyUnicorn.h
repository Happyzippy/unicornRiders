#ifndef WHEELYUNICORN_H
#define WHEELYUNICORN_H

/* Serial device defines for dxl bus */
#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 2  //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 3  //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP

/* Dynamixel ID defines */
#define ID_SERVO_RIGHT 22
#define ID_SERVO_LEFT 10
#define ID_SERVO_FRONT 7

/* Sensor port defines */
#define PORT_SENSOR_FRONT 1
#define PORT_SENSOR_SIDE 4

/* Control table defines */
#define REG_MOVING_SPEED_LOW 32
#define REG_MOVING_SPEED_HIGH 33
#define REG_CCW_Angle_Limit 8
#define REG_CONTROL_MODE 11
#define REG_GOAL_POSITION 30

/* Robot metrics */
#define WHEEL_BASE_DIST 135
#define FRONT_WHEEL_DIST 135
#define RADIUS_WHEEL 25

#define CW = 0
#define CCW = 1

#include "Dynamixel.h"
#include "nvic.h"
#include "Arduino-compatibles.h"
#include "dxl.h"
#include <OLLO.h>
#include <math.h>
#include "usb_serial.h"

class WheelyUnicorn {
private:
	Dynamixel* dxl;
	OLLO* myOLLO;

public:
	WheelyUnicorn();
	void begin();
	int getSideDistance();
	int getFrontDistance();
	int angle2motor(int angle);
	void setDirection(int angle, int velocity);
	int calc_fw_angle(boolean direction, int radius);
	int calc_lw_speed(boolean direction, int radius, int velocity);
	int calc_rw_speed(boolean direction, int radius, int velocity);
	void turn(boolean direction, int angle, int radius, int velocity);
	void followWall(int distance, int velocity);
	int speed2motor(int velocity);
	int sensor2mm(int sensor);
	
};

#endif