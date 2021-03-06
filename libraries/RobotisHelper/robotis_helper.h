/***
	Helper header file for Robotis specific defines
***/
#ifndef ROBOTIS_HELPER_H_
#define ROBOTIS_HELPER_H_

/* Serial device defines for dxl bus */
#define DXL_BUS_SERIAL1 1   //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 2   //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 3   //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP

#define DXL_BUS_SPEED 3		// Dynamixel 2.0 Protocol -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps

/* Dynamixel Instruction Ids */
#define REG_MOVING_SPEED_LOW 32
#define REG_MOVING_SPEED_HIGH 33
#define REG_CCW_Angle_Limit 8
#define REG_CONTROL_MODE 11
#define REG_GOAL_POSITION 30
	

/* Dynamixel Joint constants */
#define SERVO_MAX 1023
#define SERVO_MIN 0
#define SERVO_BIAS 512
#define SERVO_COMMAND2ANGLE 0.29296875 			// 300/1024
#define SERVO_ANGLE2COMMAND 3.413333333333334	// 1024/300

#endif // ROBOTIS_HELPER_H_