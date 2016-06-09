/* Dynamixel Wheel Mode Example
 
 This example shows how to use dynamixel as wheel mode
 All dynamixels are set as joint mode in factory,
 but if you want to make a wheel using dynamixel, 
 you have to change it to wheel mode by change CCW angle limit to 0
 
               Compatibility
 CM900                  O
 OpenCM9.04             O
 
                  Dynamixel Compatibility
               AX    MX      RX    XL-320    Pro
 CM900          O      O      O        O      X
 OpenCM9.04     O      O      O        O      X
 **** OpenCM 485 EXP board is needed to use 4 pin Dynamixel and Pro Series ****  
 
 created 16 Nov 2012
 by ROBOTIS CO,.LTD.
 */
 /* Serial device defines for dxl bus */
#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 2  //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 3  //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP

/* Dynamixel ID defines */
#define ID_SERVO_RIGHT 22
#define ID_SERVO_LEFT 10
#define ID_SERVO_FRONT 7

/* Sensor port defines */
#define PORT_SENSOR_FRONT 1
#define PORT_SENSOR_SIDE 4

/* Control table defines */
#define REG_MOVING_SPEED_LOW 32
#define REG_MOVING_SPEED_HIGH 33
#define REG_CCW_Angle_Limit 8
#define REG_CONTROL_MODE 11
#define REG_GOAL_POSITION 30

/* Robot metrics */
#define WHEEL_BASE_DIST 135
#define FRONT_WHEEL_DIST 135
#define RADIUS_WHEEL 25

#define CW = 0
#define CCW = 1

#include <OLLO.h>
#include <math.h>

Dynamixel Dxl(DXL_BUS_SERIAL3);
OLLO myOLLO;

int sensor2mm(int sensor){
  return 30000/sensor;
}

int getSideDistance(){
  int avg = 0;
  avg += myOLLO.read(PORT_SENSOR_SIDE, IR_SENSOR);
  avg += myOLLO.read(PORT_SENSOR_SIDE, IR_SENSOR);
  avg += myOLLO.read(PORT_SENSOR_SIDE, IR_SENSOR);
  avg += myOLLO.read(PORT_SENSOR_SIDE, IR_SENSOR);
  avg += myOLLO.read(PORT_SENSOR_SIDE, IR_SENSOR);
  
  return sensor2mm(avg/5);
}

int getFrontDistance(){
  int avg = 0;
  avg += myOLLO.read(PORT_SENSOR_FRONT, IR_SENSOR);
  avg += myOLLO.read(PORT_SENSOR_FRONT, IR_SENSOR);
  avg += myOLLO.read(PORT_SENSOR_FRONT, IR_SENSOR);
  avg += myOLLO.read(PORT_SENSOR_FRONT, IR_SENSOR);
  avg += myOLLO.read(PORT_SENSOR_FRONT, IR_SENSOR);
  
  return sensor2mm(avg/5);
}

int angle2motor(int angle){
  return angle*1024/300 + 512;
}

void setDirection(int angle, int velocity){
  int motorsignal = angle2motor(angle);
  
  Dxl.writeWord(ID_SERVO_FRONT, REG_GOAL_POSITION, motorsignal);
  Dxl.goalSpeed(ID_SERVO_RIGHT, speed2motor(velocity) | 0x400);
  Dxl.goalSpeed(ID_SERVO_LEFT, speed2motor(velocity));
}

int calc_fw_angle(boolean direction, int radius){
  SerialUSB.print("calc_fw_angle(d, r): ");
   
  int fw_r = sqrt(FRONT_WHEEL_DIST*FRONT_WHEEL_DIST + radius*radius);
  
  SerialUSB.println(90 - asin((float)FRONT_WHEEL_DIST/fw_r)*180/M_PI);
  if(direction == true)
    return  90 - asin((float)FRONT_WHEEL_DIST/fw_r)*180/M_PI;
  else
    return  90 + asin((float)FRONT_WHEEL_DIST/fw_r)*180/M_PI;
}

int calc_lw_speed(boolean direction, int radius, int velocity){
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

int calc_rw_speed(boolean direction, int radius, int velocity){
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

void turn(boolean direction, int angle, int radius, int velocity){
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
  Dxl.writeWord(ID_SERVO_FRONT, REG_GOAL_POSITION, angle2motor(fw_angle));
  Dxl.goalSpeed(ID_SERVO_RIGHT, speed2motor(rw_speed) | 0x400);
  Dxl.goalSpeed(ID_SERVO_LEFT, speed2motor(lw_speed));
  
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

void followWall(int distance, int velocity){
  
}

int speed2motor(int velocity){
 return (float)velocity*60/(2*M_PI*RADIUS_WHEEL)/0.111; 
}

void setup() {
  // Dynamixel 2.0 Protocol -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps 
  Dxl.begin(3);
  
  // Configre front servo to run in joint mode
  Dxl.jointMode(ID_SERVO_FRONT);
  
  // Configure side servos to run in wheel mode
  Dxl.writeWord(ID_SERVO_RIGHT, REG_CCW_Angle_Limit, 0);
  Dxl.writeWord(ID_SERVO_LEFT, REG_CCW_Angle_Limit, 0);
  
  // Configure IR sensors
  myOLLO.begin(PORT_SENSOR_SIDE, IR_SENSOR);
  myOLLO.begin(PORT_SENSOR_FRONT, IR_SENSOR);
}

void loop() {
  
  // Follow left wall until wall appears in front
  //while(getFrontDistance() > 100){
  //  followWall(100, 100);
  //}
  
  // Turn right
  setDirection(0, 50);
    delay(1000);
  
  turn(true, 90, 100, 50);
  
  // Follow left wall until wall disappears on left
  while(getSideDistance() < 150){
    followWall(100, 10);
  }
  
  setDirection(0, 50);
  delay(1000);
  
  // Turn left
  turn(false, 90, 100, 50);
  
  setDirection(0, 50);
  delay(1000);
  
  // Follow left wall
  while(true){
    followWall(100, 100);
  }

}




