#include "walker_leg.h"
#include <../RobotisHelper/robotis_helper.h>

WalkerLeg::WalkerLeg(){
}

void WalkerLeg::init(Dynamixel dxl, int hipMotorId, int kneeMotorId){
	// set internal variables
	dxl_ = &dxl;
	hipMotorId_ = hipMotorId;
	kneeMotorId_= kneeMotorId;

	// setup
  	dxl_->jointMode(hipMotorId_);	
  	dxl_->jointMode(kneeMotorId_);
}

void WalkerLeg::setServoConf(float hipBias, float kneeBias, bool isReversed){
	hipBias_ = hipBias;
	kneeBias_ = kneeBias;
	isReversed_ = isReversed;
}

void WalkerLeg::setGoalPosition(float hipAngle, float kneeAngle){

	// angle 2 servo command	
	int hipCommand = (hipAngle + hipBias_) * SERVO_ANGLE2COMMAND + SERVO_BIAS;
	hipCommand = SATURATE(hipCommand, SERVO_MAX, SERVO_MIN);
	

	int kneeCommand = (kneeAngle + kneeBias_) * SERVO_ANGLE2COMMAND + SERVO_BIAS;
	kneeCommand = SATURATE(kneeCommand, SERVO_MAX, SERVO_MIN);
	
	// write to motors
	dxl_->writeWord(hipMotorId_,  REG_GOAL_POSITION, hipCommand);
	dxl_->writeWord(kneeMotorId_, REG_GOAL_POSITION, kneeCommand);
}

float WalkerLeg::getHipPosition(){
	return (dxl_->getPosition(hipMotorId_) - SERVO_BIAS) * SERVO_COMMAND2ANGLE - hipBias_;
}

float WalkerLeg::getKneePosition(){
	return (dxl_->getPosition(kneeMotorId_) - SERVO_BIAS) * SERVO_COMMAND2ANGLE - kneeBias_;
}