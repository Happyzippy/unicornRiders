/***
	Walker class
	Containing the robot as an entity
***/
#ifndef WALKER_H_
#define WALKER_H_

#include "Dynamixel.h"
#include "walker_leg.h"

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
