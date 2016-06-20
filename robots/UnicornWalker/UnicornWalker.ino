#include <walker_leg.h>
#include <walker_conf.h>
#include <walker.h>
#include <robotis_helper.h>
#include <OLLO.h>

Dynamixel dxl(DXL_BUS_SERIAL3);
OLLO ollo;
Walker walker;

void setup() {
  dxl.begin(DXL_BUS_SPEED);
  Serial2.begin(57600);
  Serial2.attachInterrupt(serialInterrupt);
  walker.init(&dxl, &Serial2, &ollo);
}

void loop(){

	delay(7);
	walker.update(1);
}

void serialInterrupt(byte buffer){
	walker.serialInterrupt((char)buffer);
}
