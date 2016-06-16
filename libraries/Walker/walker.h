/***
	Walker class
	Containing the robot as an entity
***/
#ifndef WALKER_H_
#define WALKER_H_o

#include "HardwareSerial.h"
#include "Dynamixel.h"
#include "OLLO.h"
#include "walker_leg.h"
#include "walker_sensor.h"

class Walker
{
public:
	Walker();
	void init(Dynamixel* dxl, HardwareSerial* serial, OLLO* ollo);
	void update(int dt);
	void serialInterrupt(char buffer);
private:

	int clock_;

	HardwareSerial* serial_;

	WalkerLeg legFL;
	WalkerLeg legFR;
	WalkerLeg legRL;
	WalkerLeg legRR;

	WalkerSensor irFront;
	WalkerSensor irRight;
	WalkerSensor irLeft;

	float speed_;
	float dir_;
	float speedTarget_;
	float dirTarget_;

	bool isAutonomous;
	int freezeDir_;

	void followTheLight();
	void walkTrot(float speed, float direction);
	void walkRotate(float speed, bool isClockwise);

};

#endif // WALKER_H_
