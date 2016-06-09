#ifndef WALKER_CONF_H_
#define WALKER_CONF_H_

/* dynamixel TTL */

#define DXL_BUS 3		// Serial select -> 1: OpenCM9.04, 2: LN101,BT210, 3: OpenCM 485EXP
#define DXL_BUS_SPEED 3		// Dynamixel 2.0 Protocol -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps

/* actuators */
#define RF_HIP_MOTORID 7
#define RF_KNEE_MOTORID 7
#define RR_HIP_MOTORID 7
#define RR_KNEE_MOTORID 7
#define LF_HIP_MOTORID 7
#define LF_KNEE_MOTORID 7
#define LR_HIP_MOTORID 7
#define LR_KNEE_MOTORID 7

/* sensors */
#define FRONT_IR_SENSORID 1





#endif // WALKER_CONF_H_
