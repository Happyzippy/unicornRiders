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
	void update(int dt);
private:

	int clock_;

	WalkerLeg legFL;
	WalkerLeg legFR;
	WalkerLeg legRL;
	WalkerLeg legRR;
	//WalkerLeg* legs[4] = {legFR, legFL, legRR, legRL};
	void setDiagonal(bool isFR, int hipCommand, int kneeCommand);
};

#endif // WALKER_H_
