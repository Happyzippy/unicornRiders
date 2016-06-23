/***
	Walker Robot configuration file

***/
#ifndef TURRET_CONF_H_
#define TURRET_CONF_H_

/* actuators */
#define ARM_HIP_MOTORID 22
#define ARM_KNEE_MOTORID 10

/* sensors */
#define FRONT_IR_SENSORID 2
#define FRONT_IR_a 327.2736
#define FRONT_IR_b -0.0342

#define RIGHT_IR_SENSORID 3
#define RIGHT_IR_a 361.8412
#define RIGHT_IR_b -0.0397

#define LEFT_IR_SENSORID 1
#define LEFT_IR_a 348.6308
#define LEFT_IR_b -0.0334

#define TRIGGER_SENSORID 1
#define GOAL_SENSORID 2

#endif // TURRET_CONF_H_
