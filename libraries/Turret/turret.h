/***
	Turret class
	Containing the robot as an entity
***/
#ifndef Turret_H_
#define Turret_H_o

#include "HardwareSerial.h"
#include "Dynamixel.h"
#include "OLLO.h"
#include "walker_leg.h"
#include "walker_sensor.h"

class Turret
{
public:
	Turret();
	void init(Dynamixel* dxl, HardwareSerial* serial, OLLO* ollo);
	void update(int dt);
	void serialInterrupt(char buffer);
private:

	int clock_;

	HardwareSerial* serial_;

	WalkerLeg arm;

	WalkerSensor irFront;
	WalkerSensor irRight;
	WalkerSensor irLeft;

	WalkerSensor triggerButton;
	WalkerSensor goalButton;

	int kneeCommand;
	int hipCommand;
	int buttonState;
	int goalState;

};

#endif // Turret_H_
