#include "turret.h"
#include "turret_conf.h"
#include "robotis_helper.h"
#include "Arduino-compatibles.h"

Turret::Turret(){
	
}


/**
 * @brief     Initialize turret
 *
 * @param[in]  dxl   The Dynmaixel object for communicating with the motors. 
 * @param[in]  serial   Pointer to the USBSerial object for writing to the serial bus.
 */
void Turret::init(Dynamixel* dxl, HardwareSerial* serial, OLLO* ollo){
	serial_ = serial;
	clock_ = 0;
	buttonState = 0;
	goalState = 0;

	hipCommand = 512;
	kneeCommand = 512;

	arm.init(dxl, ARM_HIP_MOTORID, ARM_KNEE_MOTORID);

	arm.setIsReversed(false, true);
	
	irFront.init(ollo, FRONT_IR_SENSORID, IR_SENSOR, 5, FRONT_IR_a, FRONT_IR_b);
	irRight.init(ollo, RIGHT_IR_SENSORID, IR_SENSOR, 5, RIGHT_IR_a, RIGHT_IR_b);
	irLeft.init(ollo,  LEFT_IR_SENSORID,  IR_SENSOR, 5, LEFT_IR_a,  LEFT_IR_b );

	triggerButton.init(ollo,  TRIGGER_SENSORID,  TOUCH_SENSOR, 5, 0,0);
	goalButton.init(ollo,  GOAL_SENSORID,  TOUCH_SENSOR, 5, 0,0);
}


/**
 * @brief      Function for interrupting the serial communication.
 *
 * @param[in]  buffer  The buffer
 */
void Turret::serialInterrupt(char buffer){
	// Repeat character to acknowledge command
	//serial_->print(buffer);

	// React to commands
	switch(buffer){
	case 't':
		/*
		serial_->print(triggerButton.readSensorRaw());
		serial_->print(",");
		serial_->print(arm.getHipPosition());
		serial_->print(",");
		serial_->print(arm.getKneePosition());
		*/
		break;
	case 'g':
		arm.lockHip();
		arm.lockKnee();
		arm.setHipWheelMode(true);
		arm.setKneeWheelMode(true);
		break;
	case 'f':
		//arm.lockHip();
		//arm.lockKnee();
		kneeCommand = arm.getKneePosition();
		arm.setKneeWheelMode(true);

		break;
	case 'F':
		arm.setKneeWheelMode(false);
		hipCommand = arm.getHipPosition();
		arm.setGoalAbsoluteCommand(hipCommand, kneeCommand);
		break;
	}

	// End answer with line ending
	//serial_->println("");
}

/**
 * @brief      Updates the motor position
 *
 * @param[in]  dt    Time since last call.
 */
void Turret::update(int dt){
	clock_ += dt;

	// Read sensors
	int button = triggerButton.readSensorRaw();
	if (button == 1 && buttonState == 0){
		
		kneeCommand = arm.getKneePosition();
		arm.setKneeWheelMode(true);
	}
	if (button == 0 && buttonState == 1){
		// Throw
		arm.setKneeWheelMode(false);
		hipCommand = arm.getHipPosition();
		arm.setGoalAbsoluteCommand(hipCommand, kneeCommand);
		delay(2000);
		
		//Run free
		serial_->println("THROW");
		arm.lockHip();
		arm.lockKnee();
		arm.setHipWheelMode(true);
		arm.setKneeWheelMode(true);
	}
	buttonState = button;
	
	int goal = goalButton.readSensorRaw();
	if (goalState == 0 & goal == 1){
		serial_->println("GOAL");
	}
	goalState = goal;
	//irRight.readSensorRaw();
	//irLeft.readSensorRaw();

	//armRot_   = (armRot_*19   + armRotTarget_)/20;
	//armThrow_   = armThrowTarget_;//(armThrow_*4   + armThrowTarget_)/5;

	//arm.setGoalPosition(armRot_, armThrow_);

}

