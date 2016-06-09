#include <walker_leg.h>
#include <walker_conf.h>
#include <walker.h>
#include <robotis_helper.h>

Dynamixel dxl(DXL_BUS_SERIAL3);
Walker walker;

void setup() {
  dxl.begin(DXL_BUS_SPEED);
  walker.init(dxl);
}

void loop(){

}

