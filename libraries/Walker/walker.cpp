#include "walker.h"
#include "walker_conf.h"

Walker::Walker(){
}

void Walker::init(Dynamixel dxl){
	legFL.init(dxl, FL_HIP_MOTORID, RL_KNEE_MOTORID);
	legFR.init(dxl, FR_HIP_MOTORID, FR_KNEE_MOTORID);
	legRL.init(dxl, RL_HIP_MOTORID, RL_KNEE_MOTORID);
	legRR.init(dxl, RR_HIP_MOTORID, RR_KNEE_MOTORID);
}

void Walker::update(){

}