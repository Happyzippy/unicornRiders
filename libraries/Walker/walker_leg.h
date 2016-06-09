#ifndef WALKER_LEG_H_
#define WALKER_LEG_H_

#include "Dynamixel.h"
//#include <../RobotisHelper/robotis_helper.h>

class WalkerLeg
{
public:
	WalkerLeg();
	void init(Dynamixel dxl, int hipMotorId, int kneeMotorId);
	void setGoalPosition();
	void getLegPosition();
private:
	Dynamixel* dxl_;
};

#endif // WALKER_LEG_H_
