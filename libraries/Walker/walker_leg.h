/***
	Walker Leg class
	Abstracting the use of motors on each leg
***/
#ifndef WALKER_LEG_H_
#define WALKER_LEG_H_

#include "Dynamixel.h"


class WalkerLeg
{
public:
	WalkerLeg();
	void init(Dynamixel dxl, int hipMotorId, int kneeMotorId);
	void setServoConf(float hipBias, float kneeBias, bool isReversed);
	void setGoalPosition(float hipAngle, float kneeAngle);
	float getHipPosition();
	float getKneePosition();
private:
	int hipMotorId_;
	int kneeMotorId_;
	float hipBias_;
	float kneeBias_;
	bool isReversed_;
	Dynamixel* dxl_;
};

#endif // WALKER_LEG_H_
