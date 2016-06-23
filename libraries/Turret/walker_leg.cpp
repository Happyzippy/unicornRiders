#include "walker_leg.h"
#include <../RobotisHelper/robotis_helper.h>

WalkerLeg::WalkerLeg(){

}


/**
 * @brief      Initializes a leg of the Walker Robot.
 *
 * @param[in]  dxl          The dynamixel motor communicator.
 * @param[in]  hipMotorId   The hip motor identifier
 * @param[in]  kneeMotorId  The knee motor identifier
 */
void WalkerLeg::init(Dynamixel* dxl, int hipMotorId, int kneeMotorId){
	// set internal variables
	dxl_ = dxl;
	hipMotorId_ = hipMotorId;
	kneeMotorId_= kneeMotorId;
	hipBias_ = SERVO_BIAS;
	kneeBias_ = SERVO_BIAS;
	isHipReversed_ = false;
	isKneeReversed_ = false;
	servo_max_ = SERVO_MAX;
	servo_min_ = SERVO_MIN;

	// setup
  	dxl_->jointMode(hipMotorId_);	
  	dxl_->jointMode(kneeMotorId_);
}


/**
 * @brief      Sets the is reversed.
 *
 * @param[in]  isHipReversed   Indicates if hip reversed
 * @param[in]  isKneeReversed  Indicates if knee reversed
 */
void WalkerLeg::setIsReversed(bool isHipReversed, bool isKneeReversed){
	isHipReversed_ = isHipReversed;
	isKneeReversed_ = isKneeReversed;
}


/**
 * @brief      Sets the servo configuration.
 *
 * @param[in]  hipBias   The hip bias
 * @param[in]  kneeBias  The knee bias
 * @param[in]  angleMax  The angle maximum
 * @param[in]  angleMin  The angle minimum
 */
void WalkerLeg::setServoConf(float hipBias, float kneeBias, float angleMax, float angleMin){
	hipBias_ = hipBias * SERVO_ANGLE2COMMAND + SERVO_BIAS;
	kneeBias_ = kneeBias * SERVO_ANGLE2COMMAND + SERVO_BIAS;

	if (angleMax * SERVO_ANGLE2COMMAND < SERVO_MAX){
		servo_max_ = angleMax * SERVO_ANGLE2COMMAND;
	}
	if (angleMin * SERVO_ANGLE2COMMAND > SERVO_MIN){
		servo_min_ = angleMin * SERVO_ANGLE2COMMAND;
	}
}


/**
 * @brief      Sets the goal position. Convenience method translating to unbiased servo commands;
 *
 * @param[in]  hipAngle   The hip angle
 * @param[in]  kneeAngle  The knee angle
 */
void WalkerLeg::setGoalPosition(float hipAngle, float kneeAngle){
	setGoalPositionCommand(hipAngle*SERVO_ANGLE2COMMAND, kneeAngle*SERVO_ANGLE2COMMAND);
	
	
	/*
	// angle 2 servo command
	hipAngle = isHipReversed_ ? -hipAngle : hipAngle;
	int hipCommand = hipAngle * SERVO_ANGLE2COMMAND + hipBias_;
	hipCommand = hipCommand > servo_max_ ? servo_max_ : (hipCommand < servo_min_ ? servo_min_ : hipCommand);

	kneeAngle = isKneeReversed_ ? -kneeAngle : kneeAngle;
	int kneeCommand = kneeAngle * SERVO_ANGLE2COMMAND + hipBias_;
	kneeCommand = kneeCommand > servo_max_ ? servo_max_ : (kneeCommand < servo_min_ ? servo_min_ : kneeCommand);
	
	//hipCommand = 512;
	//kneeCommand = 512;
	
	// write to motors
	dxl_->writeWord(hipMotorId_,  REG_GOAL_POSITION, hipCommand);
	dxl_->writeWord(kneeMotorId_, REG_GOAL_POSITION, kneeCommand);
	*/
}

/**
 * @brief      Sets the goal position in unbiased servo units
 *
 * @param[in]  hipAngle   The hip command
 * @param[in]  kneeAngle  The knee command
 */
void WalkerLeg::setGoalPositionCommand(int hipCommand, int kneeCommand){
	hipCommand = isHipReversed_ ? -hipCommand : hipCommand;
	hipCommand += hipBias_;
	kneeCommand = isKneeReversed_ ? -kneeCommand : kneeCommand;
	kneeCommand += kneeBias_;

	hipCommand = hipCommand > servo_max_ ? servo_max_ : (hipCommand < servo_min_ ? servo_min_ : hipCommand);
	kneeCommand = kneeCommand > servo_max_ ? servo_max_ : (kneeCommand < servo_min_ ? servo_min_ : kneeCommand);
	
	// write to motors
	
	dxl_->writeWord(hipMotorId_,  REG_GOAL_POSITION, hipCommand);
	if(!dxl_->getResult()){
		// Comm error
	}
	dxl_->writeWord(kneeMotorId_, REG_GOAL_POSITION, kneeCommand);
	if(!dxl_->getResult()){
		// Comm error
	}
}

/**
 * @brief      Sets the goal position in unbiased servo units
 *
 * @param[in]  hipAngle   The hip command
 * @param[in]  kneeAngle  The knee command
 */
void WalkerLeg::setGoalAbsoluteCommand(int hipCommand, int kneeCommand){
	dxl_->goalPosition(hipMotorId_, hipCommand);
	dxl_->goalPosition(kneeMotorId_, kneeCommand);
}


/**
 * @brief      Gets the hip position.
 *
 * @return     The hip position.
 */
int WalkerLeg::getHipPosition(){
	return (dxl_->getPosition(hipMotorId_));// - SERVO_BIAS) * SERVO_COMMAND2ANGLE - hipBias_;
}


/**
 * @brief      Gets the knee position.
 *
 * @return     The knee position.
 */
int WalkerLeg::getKneePosition(){
	return (dxl_->getPosition(kneeMotorId_));// - SERVO_BIAS) * SERVO_COMMAND2ANGLE - kneeBias_;
}

void WalkerLeg::setGoalSpeedCommand(int speed){
	if(isKneeReversed_){
		speed = -speed;
	}
	if(speed > 0){
		dxl_->goalSpeed(kneeMotorId_ , speed);
	} else{
		dxl_->goalSpeed(kneeMotorId_ , speed | 0x400);
	}	
}

void WalkerLeg::setHipWheelMode(bool isWheel){
	if(isWheel){
		dxl_->wheelMode(hipMotorId_);
	}else{
		dxl_->jointMode(hipMotorId_);
	}
}

void WalkerLeg::setKneeWheelMode(bool isWheel){
	if(isWheel){
		dxl_->wheelMode(kneeMotorId_);
	}else{
		dxl_->jointMode(kneeMotorId_);
	}
}

void WalkerLeg::lockHip(){
	dxl_->jointMode(hipMotorId_);
	dxl_->goalPosition(hipMotorId_, getHipPosition());
}

void WalkerLeg::lockKnee(){
	dxl_->jointMode(kneeMotorId_);
	dxl_->goalPosition(hipMotorId_, getKneePosition());
}