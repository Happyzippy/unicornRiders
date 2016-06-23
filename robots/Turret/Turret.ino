#include <turret.h>
#include <robotis_helper.h>
#include <OLLO.h>

Dynamixel dxl(DXL_BUS_SERIAL3);
OLLO ollo;
Turret turret;

void setup() {
  dxl.begin(DXL_BUS_SPEED);
  Serial2.begin(57600);
  Serial2.attachInterrupt(serialInterrupt);
  turret.init(&dxl, &Serial2, &ollo);
}

void loop(){

	//delay(2);
	turret.update(1);
}

void serialInterrupt(byte buffer){
	turret.serialInterrupt((char)buffer);
}
