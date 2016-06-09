#ifndef WALKER_H_
#define WALKER_H_

#include "Dynamixel.h"
#include "walker_leg.h"
//#include <../RobotisHelper/robotis_helper.h>

class Walker
{
public:
	Walker();
	void init(Dynamixel dxl);
	void update();
private:
	WalkerLeg legFL;
	WalkerLeg legFR;
	WalkerLeg legRL;
	WalkerLeg legRR;
};

#endif // WALKER_H_
