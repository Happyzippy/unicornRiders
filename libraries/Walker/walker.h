/***
	Walker class
	Containing the robot as an entity
***/
#ifndef WALKER_H_
#define WALKER_H_

#include "Dynamixel.h"
#include "walker_leg.h"
#include <stdint.h>

class Walker
{
public:
	Walker();
	void init(Dynamixel dxl);
	void update(uint32_t dt);

private:

	uint32_t clock_;

	WalkerLeg legFL;
	WalkerLeg legFR;
	WalkerLeg legRL;
	WalkerLeg legRR;
};

#endif // WALKER_H_
