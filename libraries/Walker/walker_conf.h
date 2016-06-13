/***
	Walker Robot configuration file

***/
#ifndef WALKER_CONF_H_
#define WALKER_CONF_H_

/* actuators */
#define FL_HIP_MOTORID 9
#define FL_KNEE_MOTORID 7 
#define FR_HIP_MOTORID 5
#define FR_KNEE_MOTORID 6

#define RL_HIP_MOTORID 13
#define RL_KNEE_MOTORID 8
#define RR_HIP_MOTORID 2
#define RR_KNEE_MOTORID 4

/* sensors */
#define FRONT_IR_SENSORID 1


int hipCycle(int index, float phase);
int kneeCycle(int index, float phase);

#endif // WALKER_CONF_H_
