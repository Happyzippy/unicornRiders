#include "WheelyUnicorn.h"

WheelyUnicorn::WheelyUnicorn() {
	dxl = new Dynamixel(DXL_BUS_SERIAL3);
	myOLLO = new OLLO();
}

void WheelyUnicorn::begin() {
	dxl->begin(3);
	dxl->jointMode(ID_SERVO_FRONT);
	dxl->wheelMode(ID_SERVO_RIGHT);
	dxl->wheelMode(ID_SERVO_LEFT);
}

int WheelyUnicorn::sensor2mm(int sensor){
  return 30000/sensor;
}

int WheelyUnicorn::getSideDistance(){
  int avg = 0;
  avg += myOLLO->read(PORT_SENSOR_SIDE, IR_SENSOR);
  avg += myOLLO->read(PORT_SENSOR_SIDE, IR_SENSOR);
  avg += myOLLO->read(PORT_SENSOR_SIDE, IR_SENSOR);
  avg += myOLLO->read(PORT_SENSOR_SIDE, IR_SENSOR);
  avg += myOLLO->read(PORT_SENSOR_SIDE, IR_SENSOR);
  
  return sensor2mm(avg/5);
}

int WheelyUnicorn::getFrontDistance(){
  int avg = 0;
  avg += myOLLO->read(PORT_SENSOR_FRONT, IR_SENSOR);
  avg += myOLLO->read(PORT_SENSOR_FRONT, IR_SENSOR);
  avg += myOLLO->read(PORT_SENSOR_FRONT, IR_SENSOR);
  avg += myOLLO->read(PORT_SENSOR_FRONT, IR_SENSOR);
  avg += myOLLO->read(PORT_SENSOR_FRONT, IR_SENSOR);
  
  return sensor2mm(avg/5);
}

int WheelyUnicorn::angle2motor(int angle){
  return angle*1024/300 + 512;
}

void WheelyUnicorn::setDirection(int angle, int velocity){
  int motorsignal = angle2motor(angle);
  
  dxl->writeWord(ID_SERVO_FRONT, REG_GOAL_POSITION, motorsignal);
  dxl->goalSpeed(ID_SERVO_RIGHT, speed2motor(velocity) | 0x400);
  dxl->goalSpeed(ID_SERVO_LEFT, speed2motor(velocity));
}

int WheelyUnicorn::calc_fw_angle(boolean direction, int radius){
  SerialUSB.print("calc_fw_angle(d, r): ");
   
  int fw_r = sqrt(FRONT_WHEEL_DIST*FRONT_WHEEL_DIST + radius*radius);
  
  SerialUSB.println(90 - asin((float)FRONT_WHEEL_DIST/fw_r)*180/M_PI);
  if(direction == true)
    return  90 - asin((float)FRONT_WHEEL_DIST/fw_r)*180/M_PI;
  else
    return  90 + asin((float)FRONT_WHEEL_DIST/fw_r)*180/M_PI;
}

int WheelyUnicorn::calc_lw_speed(boolean direction, int radius, int velocity){
  SerialUSB.print("calc_lw_speed(d, r, v): ");
  int lw_r;
  
  if(direction == true){
    lw_r = radius + WHEEL_BASE_DIST/2;
  }
  else{
    lw_r = radius - WHEEL_BASE_DIST/2;
  }
  
  SerialUSB.println((float)velocity*lw_r/radius);
  return  (float)velocity*lw_r/radius;
}

int WheelyUnicorn::calc_rw_speed(boolean direction, int radius, int velocity){
  SerialUSB.print("calc_rw_speed(d, r, v): ");
  int rw_r;
  
  if(direction == true){
    rw_r = radius - WHEEL_BASE_DIST/2;
  }
  else{
    rw_r = radius + WHEEL_BASE_DIST/2;
  }
 
  SerialUSB.println((float)velocity*rw_r/radius);
  return  (float)velocity*rw_r/radius;
}

void WheelyUnicorn::turn(boolean direction, int angle, int radius, int velocity){
  SerialUSB.println("turn(d, a, r, v): ");
  SerialUSB.println(direction);
  SerialUSB.println(angle);
  SerialUSB.println(radius);
  SerialUSB.println(velocity);
  
  // Calculate parameters
  int fw_angle = calc_fw_angle(direction, radius);
  int lw_speed = calc_lw_speed(direction, radius, velocity);
  int rw_speed = calc_rw_speed(direction, radius, velocity);
  
  SerialUSB.print("fw_angle: ");
  SerialUSB.println(fw_angle);
  SerialUSB.print("lw_speed: ");
  SerialUSB.println(lw_speed);
  SerialUSB.print("rw_speed: ");
  SerialUSB.println(rw_speed);
  
  // Set parameters
  dxl->writeWord(ID_SERVO_FRONT, REG_GOAL_POSITION, angle2motor(fw_angle));
  dxl->goalSpeed(ID_SERVO_RIGHT, speed2motor(rw_speed) | 0x400);
  dxl->goalSpeed(ID_SERVO_LEFT, speed2motor(lw_speed));
  
  // Run until turn has completed
  unsigned long startT = millis();
  unsigned long endT = startT + (float)angle/180*M_PI*radius/velocity*1000;
  //unsigned long endT = (float)angle/180*M_PI*radius;
  SerialUSB.print("startT: ");
  SerialUSB.println(startT);
  SerialUSB.print("endT: ");
  SerialUSB.println(endT);
  
  while(millis() < endT){
    delay(10);
  }
}

void WheelyUnicorn::followWall(int distance, int velocity){
  
}

int WheelyUnicorn::speed2motor(int velocity){
 return (float)velocity*60/(2*M_PI*RADIUS_WHEEL)/0.111; 
}