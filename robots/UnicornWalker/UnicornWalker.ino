#include <walker_leg.h>
#include <walker_conf.h>
#include <walker.h>
#include <robotis_helper.h>

Dynamixel dxl(DXL_BUS_SERIAL3);
Walker walker;

void setup() {
  dxl.begin(DXL_BUS_SPEED);
  walker.init(dxl);
  
  /*
  WalkerLeg* leg1 = new WalkerLeg();
  leg1->init(dxl, 5, 9);
  leg1->setServoConf(0.0f, 0.0f, false, -45.0f, 45.0f);
  leg1->setGoalPosition(0.0f, 0.0f);
  */
}

void loop(){

delay(150);
walker.update(1);



}

