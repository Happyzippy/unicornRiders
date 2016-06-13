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
	void setIsReversed(bool isHipReversed, bool isKneeReversed);
	void setServoConf(float hipBias, float kneeBias, float angleMax, float angleMin);
	void setGoalPosition(float hipAngle, float kneeAngle);
	void setGoalPositionCommand(int hipCommand, int kneeCommand);
	float getHipPosition();
	float getKneePosition();
private:
	int hipMotorId_;
	int kneeMotorId_;
	int hipBias_;
	int kneeBias_;
	int servo_max_;
	int servo_min_;
	bool isHipReversed_;
	bool isKneeReversed_;
	Dynamixel* dxl_;
};

#endif // WALKER_LEG_H_
