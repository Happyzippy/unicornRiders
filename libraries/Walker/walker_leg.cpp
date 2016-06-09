#include "walker_leg.h"
//#include <../RobotisHelper/robotis_helper.h>

WalkerLeg::WalkerLeg(){
}

void WalkerLeg::init(Dynamixel dxl, int hipMotorId, int kneeMotorId){
	dxl_ = &dxl;	
}
