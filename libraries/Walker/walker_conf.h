/***
	Walker Robot configuration file

***/
#ifndef WALKER_CONF_H_
#define WALKER_CONF_H_

/* actuators */
#define FR_HIP_MOTORID 2
#define FR_KNEE_MOTORID 6

#define FL_HIP_MOTORID 5
#define FL_KNEE_MOTORID 7


#define RL_HIP_MOTORID 13
#define RL_KNEE_MOTORID 8

#define RR_HIP_MOTORID 3
#define RR_KNEE_MOTORID 4

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


int hipCycle(int index, float phase);
int kneeCycle(int index, float phase);
int frontNN(int index);
int rightNN(int index);
int leftNN(int index);

#endif // WALKER_CONF_H_
