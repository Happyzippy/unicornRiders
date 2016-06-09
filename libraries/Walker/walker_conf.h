/***
	Walker Robot configuration file

***/
#ifndef WALKER_CONF_H_
#define WALKER_CONF_H_

/* dynamixel TTL */

#define DXL_BUS 3		// Serial select -> 1: OpenCM9.04, 2: LN101,BT210, 3: OpenCM 485EXP


/* actuators */
#define RL_HIP_MOTORID 7
#define RL_KNEE_MOTORID 7
#define RR_HIP_MOTORID 7
#define RR_KNEE_MOTORID 7
#define FL_HIP_MOTORID 7
#define FL_KNEE_MOTORID 7
#define FR_HIP_MOTORID 7
#define FR_KNEE_MOTORID 7

/* sensors */
#define FRONT_IR_SENSORID 1



#endif // WALKER_CONF_H_
