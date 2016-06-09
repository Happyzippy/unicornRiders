#include <walker_leg.h>
#include <walker_conf.h>
#include <walker.h>
#include <robotis_helper.h>


/* Minimum_Source */
Dynamixel dxl(DXL_BUS_SERIAL3);
Walker walker;

void setup() {
  dxl.begin(DXL_BUS_SPEED);
  walker.init(dxl);
  //initMotors();
  //m.initMotors();
}

void loop(){
  // put your main code here, to run repeatedly: 
}

