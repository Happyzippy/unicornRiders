#include "walker.h"
#include "walker_conf.h"


Walker::Walker(){
}


/**
 * @brief      Initializes the Waker robot motors.
 *
 * @param[in]  dxl   The Dynmaixel object for communicating with the motors.
 */
void Walker::init(Dynamixel dxl){
	legFL.init(dxl, FL_HIP_MOTORID, FL_KNEE_MOTORID);
	legFR.init(dxl, FR_HIP_MOTORID, FR_KNEE_MOTORID);
	legRL.init(dxl, RL_HIP_MOTORID, RL_KNEE_MOTORID);
	legRR.init(dxl, RR_HIP_MOTORID, RR_KNEE_MOTORID);
	clock_ = 0;

	legFL.setIsReversed(true, false);
	legFR.setIsReversed(false, true);
	legRL.setIsReversed(true, true);
	legRR.setIsReversed(false, false);
}


/**
 * @brief      Updates the motor position
 *
 * @param[in]  dt    Time since last call.
 */
void Walker::update(int dt){
	clock_ += dt;
	
	/*
	// Trot
	switch(clock_%4){
	case 0: 
		setDiagonal(true,   15, 20);
		setDiagonal(false, -15, 45);
		break;
	case 1:
		setDiagonal(true,   15, 45);
		setDiagonal(false, -15, 20);
		break;
	case 2:
		setDiagonal(true,  -15, 45);
		setDiagonal(false,  15, 20);
		break;
	case 3:
		setDiagonal(true,  -15, 20);
		setDiagonal(false,  15, 45);
		break;
	}
	*/

	// Trot 2
	setDiagonal(true,   hipCycle(dt, 0), kneeCycle(dt, 0));
	setDiagonal(false,  hipCycle(dt, 0.5), kneeCycle(dt, 0.5));
	
	/*
	// Rotate
	switch(clock_%7){
	case 0: 
  		legFR.setGoalPosition(65, 45);
  		legRR.setGoalPosition(-25, 45);
  		legRL.setGoalPosition(-65, 45);
		legFL.setGoalPosition(25, 45);
		break;
	case 1:
		legFR.setGoalPosition(25, 45);
  		legRR.setGoalPosition(-65, 45);
  		legRL.setGoalPosition(-25, 45);
		legFL.setGoalPosition(65, 45);
		break;
	case 2:
		legFR.setGoalPosition(65, 70);
  		legRR.setGoalPosition(-65, 45);
  		legRL.setGoalPosition(-25, 45);
  		legFL.setGoalPosition(65, 45);
		break;
	case 3:
		legFR.setGoalPosition(65, 45);
  		legRR.setGoalPosition(-25, 70);
  		legRL.setGoalPosition(-25, 45);
  		legFL.setGoalPosition(65, 45);
		break;
	case 4:
		legFR.setGoalPosition(65, 45);
  		legRR.setGoalPosition(-25, 45);
  		legRL.setGoalPosition(-65, 70);
  		legFL.setGoalPosition(65, 45);
		break;
	case 5:
		legFR.setGoalPosition(65, 45);
  		legRR.setGoalPosition(-25, 45);
  		legRL.setGoalPosition(-65, 45);
  		legFL.setGoalPosition(25, 70);
  	case 6:
		legFR.setGoalPosition(65, 45);
  		legRR.setGoalPosition(-25, 45);
  		legRL.setGoalPosition(-65, 45);
  		legFL.setGoalPosition(25, 45);
		break;
	}
	*/
	/*
	// Rotate 2
	int kneeUp = 70;
	int kneeDown = 45;
	int hipFwd = 65;
	int hipBwd = 25  
	switch(clock_%7){
	case 0: 
  		legFR.setGoalPosition( hipFwd, kneeDown);
  		legRR.setGoalPosition(-hipBwd, kneeDown);
  		legRL.setGoalPosition(-hipFwd, kneeDown);
		legFL.setGoalPosition( hipBwd, kneeDown);
		break;
	case 1:
		legFR.setGoalPosition( hipBwd, kneeDown);
  		legRR.setGoalPosition(-hipFwd, kneeDown);
  		legRL.setGoalPosition(-hipBwd, kneeDown);
		legFL.setGoalPosition( hipFwd, kneeDown);
		break;
	case 2:
		legFR.setGoalPosition( hipFwd, kneeUp);
  		legRR.setGoalPosition(-hipFwd, kneeDown);
  		legRL.setGoalPosition(-hipBwd, kneeDown);
  		legFL.setGoalPosition( hipFwd, kneeDown);
		break;
	case 3:
		legFR.setGoalPosition( hipFwd, kneeDown);
  		legRR.setGoalPosition(-hipBwd, kneeUp);
  		legRL.setGoalPosition(-hipBwd, kneeDown);
  		legFL.setGoalPosition( hipFwd, kneeDown);
		break;
	case 4:
		legFR.setGoalPosition( hipFwd, kneeDown);
  		legRR.setGoalPosition(-hipBwd, kneeDown);
  		legRL.setGoalPosition(-hipFwd, kneeUp);
  		legFL.setGoalPosition( hipFwd, kneeDown);
		break;
	case 5:
		legFR.setGoalPosition( hipFwd, kneeDown);
  		legRR.setGoalPosition(-hipBwd, kneeDown);
  		legRL.setGoalPosition(-hipFwd, kneeDown);
  		legFL.setGoalPosition( hipBwd, kneeUp);
  	case 6:
		legFR.setGoalPosition( hipFwd, kneeDown);
  		legRR.setGoalPosition(-hipBwd, kneeDown);
  		legRL.setGoalPosition(-hipFwd, kneeDown);
  		legFL.setGoalPosition( hipBwd, kneeDown);
		break;
	}
	*/
	/*
	// Rotate Continuous
	float kneeUp = 70;
	float kneeDown = 45;
	float hipStart = 65;
	float hipEnd = 25;

	float hip1 = hipStart;
	float hip2 = hipStart + (hipEnd - hipStart)/3.0;
	float hip3 = hipEnd   - (hipEnd - hipStart)/3.0;
	float hip4 = hipEnd;
	switch(clock_%5){
	case 0:
		legFR.setGoalPosition( hip1, kneeUp);
  		legRR.setGoalPosition(-hip1, kneeDown);
  		legRL.setGoalPosition(-hip3, kneeDown);
  		legFL.setGoalPosition( hip3, kneeDown);
		break;
	case 1:
		legFR.setGoalPosition( hip2, kneeDown);
  		legRR.setGoalPosition(-hip4, kneeUp);
  		legRL.setGoalPosition(-hip4, kneeDown);
  		legFL.setGoalPosition( hip2, kneeDown);
		break;
	case 2:
		legFR.setGoalPosition( hip3, kneeDown);
  		legRR.setGoalPosition(-hip3, kneeDown);
  		legRL.setGoalPosition(-hip1, kneeUp);
  		legFL.setGoalPosition( hip1, kneeDown);
		break;
	case 3:
		legFR.setGoalPosition( hip4, kneeDown);
  		legRR.setGoalPosition(-hip2, kneeDown);
  		legRL.setGoalPosition(-hip2, kneeDown);
  		legFL.setGoalPosition( hip4, kneeUp);
		break;
	}
	*/
	
	
	/*
	// Test
	if (clock_%2 == 0){
		legFL.setGoalPosition(0, 45);
  		legFR.setGoalPosition(0, 45);
  		legRR.setGoalPosition(0, 45);
  		legRL.setGoalPosition(0, 45);
	}else {
		legFL.setGoalPosition(20, 45);
  		legFR.setGoalPosition(20, 45);
  		legRR.setGoalPosition(20, 45);
  		legRL.setGoalPosition(20, 45);
	}
	*/
	
}


/**
 * @brief      Sets the diagonal legs to the same position.
 *
 * @param[in]  isFR       Indicates if front right is in the diagonal
 * @param[in]  hipAngle   The hip angle
 * @param[in]  kneeAngle  The knee angle
 */
void Walker::setDiagonal(bool isFR, int hipCommand, int kneeCommand){
	if (isFR){
		legFR.setGoalPositionCommand(hipCommand, kneeCommand);
		legRL.setGoalPositionCommand(hipCommand, kneeCommand);
	}else{
		legFL.setGoalPositionCommand(hipCommand, kneeCommand);
		legRR.setGoalPositionCommand(hipCommand, kneeCommand);
	}
}
