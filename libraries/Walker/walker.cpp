#include "walker.h"
#include "walker_conf.h"
#include "robotis_helper.h"


Walker::Walker(){
	
}


/**
 * @brief      Initializes the Waker robot motors.
 *
 * @param[in]  dxl   The Dynmaixel object for communicating with the motors. 
 * @param[in]  serial   Pointer to the USBSerial object for writing to the serial bus.
 */
void Walker::init(Dynamixel* dxl, HardwareSerial* serial, OLLO* ollo){
	serial_ = serial;
	clock_ = 0;
	speed_ = 0;
	dir_ = 0;
	isAutonomous = false;

	legFL.init(dxl, FL_HIP_MOTORID, FL_KNEE_MOTORID);
	legFR.init(dxl, FR_HIP_MOTORID, FR_KNEE_MOTORID);
	legRL.init(dxl, RL_HIP_MOTORID, RL_KNEE_MOTORID);
	legRR.init(dxl, RR_HIP_MOTORID, RR_KNEE_MOTORID);
	legRR.init(dxl, RR_HIP_MOTORID, RR_KNEE_MOTORID);
	arm.init(dxl, ARM_HIP_MOTORID, ARM_KNEE_MOTORID);

	legFL.setIsReversed(true, false);
	legFR.setIsReversed(false, true);
	legRL.setIsReversed(true, true);
	legRR.setIsReversed(false, false);

	irFront.init(ollo, FRONT_IR_SENSORID, IR_SENSOR, 5, FRONT_IR_a, FRONT_IR_b);
	irRight.init(ollo, RIGHT_IR_SENSORID, IR_SENSOR, 5, RIGHT_IR_a, RIGHT_IR_b);
	irLeft.init(ollo,  LEFT_IR_SENSORID,  IR_SENSOR, 5, LEFT_IR_a,  LEFT_IR_b );
}


/**
 * @brief      Function for interrupting the serial communication.
 *
 * @param[in]  buffer  The buffer
 */
void Walker::serialInterrupt(char buffer){
	// Repeat character to acknowledge command
	serial_->print(buffer);

	// React to commands
	switch(buffer){
	case 'w':
		speedTarget_ = 1;
		break;
	case 'a':
		dirTarget_ = 0.5;		
		break;
	case 's':
		speedTarget_ = -1;
		break;
	case 'd':
		dirTarget_ = -0.5;
		break;
	case 'A':
	case 'D':
		dirTarget_ = 0;
		break;
	case 'W':
	case 'S':
		speedTarget_ = 0;
		break;
	case 'r':
		isAutonomous = !isAutonomous;
		if(isAutonomous){
			serial_->print("Autonomous mode on");
		}else{
			serial_->print("Autonomous mode off");
		}
		dirTarget_ = 0;
		speedTarget_ = 0;
		freezeDir_ = 100;

	case 't':
		//serial_->print(dirTarget_);
		serial_->print(irFront.last());
		serial_->print(",");
		serial_->print(irRight.last());
		serial_->print(",");
		serial_->print(irLeft.last());
		serial_->print(",");
		serial_->print(speedTarget_);
		serial_->print(",");
		serial_->print(dirTarget_);
	}


	// End answer with line ending
	serial_->println("");
}

/**
 * @brief      Updates the motor position
 *
 * @param[in]  dt    Time since last call.
 */
void Walker::update(int dt){
	clock_ += dt;

	// Read sensors
	irFront.readSensorRaw();
	irRight.readSensorRaw();
	irLeft.readSensorRaw();

	/*
	WalkerSensor* largestIr;
	if (irLeft.lastRaw() >= irRight.lastRaw()){
		largestIr = irLeft;
	} else {
		largestIr = irRight
	}
	*/

	//

	if(isAutonomous){
		followTheLight();
		//nnCommander();
	}

	speed_ = (speed_*9 + speedTarget_)/10;
	dir_   = (dir_*9   + dirTarget_)/10;
	armRot_   = (armRot_*19   + armRotTarget_)/20;

	walkTrot(speed_, dir_);
}

/**
 * @brief      Trot walk cycle
 *
 * @param[in]  speed    Speed of trot.
 * @param[in]  direction    direction
 */
void Walker::walkTrot(float speed, float direction){
	direction = direction > 0.5 ? 0.5 : direction < -0.5 ? -0.5 : direction;
	
	if(speed<0){
		direction = -direction;
	}

	float hipMultL = speed;
	float hipMultR = speed;
	float kneeMultR = 1;
	float kneeMultL = 1;
	
	hipMultR += direction;
	hipMultL -= direction;
	
	/*
	if (direction > 0){
		hipMultL -= direction;
	}else{
		hipMultR -= direction;	
	}
	*/

	int hip0 = hipCycle(clock_, 0);
	int hip5 = hipCycle(clock_, 0.5);
	int knee0 = kneeCycle(clock_, 0);
	int knee5 = kneeCycle(clock_, 0.5);

	// Command lsegs
	int trans = 5*SERVO_ANGLE2COMMAND;
	legFR.setGoalPositionCommand(hip0*hipMultR+ trans, knee0*kneeMultR);
 	legRL.setGoalPositionCommand(hip0*hipMultL- trans, knee0*kneeMultL);
	
	legFL.setGoalPositionCommand(hip5*hipMultL- trans, knee5*kneeMultL);
  	legRR.setGoalPositionCommand(hip5*hipMultR+ trans, knee5*kneeMultR);
}

/**
 * @brief      Rotate walk cycle
 *
 * @param[in]  speed    Speed of rotation.
 * @param[in]  isClockwise    direction of rotation
 */
void Walker::walkRotate(float speed, bool isClockwise){
	float hipMultL = speed;
	float hipMultR = speed;
	float kneeMultR = 1;
	float kneeMultL = 1;

	int trans = 45*SERVO_ANGLE2COMMAND;
	
	legFR.setGoalPositionCommand(hipCycle(clock_, 0)*hipMultR + trans,   kneeCycle(clock_, 0)*kneeMultR);
  	legRR.setGoalPositionCommand(hipCycle(clock_, .25)*hipMultR - trans, kneeCycle(clock_, 0.25)*kneeMultR);
 	legRL.setGoalPositionCommand(hipCycle(clock_, .5)*hipMultL - trans,  kneeCycle(clock_, 0.5)*kneeMultL);
	legFL.setGoalPositionCommand(hipCycle(clock_, .75)*hipMultL + trans, kneeCycle(clock_, 0.75)*kneeMultL);
}

void Walker::followTheLight() {
	if (freezeDir_ >= 0){
		dirTarget_ = 0;
		freezeDir_--;
	}

	if(irFront.last() < 0.3){
		speedTarget_ = 0;
	}else{
		speedTarget_ = 1;
	}
	dirTarget_ = 3*(irLeft.last() - irRight.last()) / (irRight.last() + irLeft.last());
}

void Walker::nnCommander() {
	if (freezeDir_ >= 0){
		dirTarget_ = 0;
		freezeDir_--;
	}

	if(irFront.last() < 0.3){
		speedTarget_ = 0;
	}else{
		speedTarget_ = 1;
	}
	int buf = leftNN((int)(irLeft.last()*100)) + frontNN((int)(irLeft.last()*100)) + rightNN((int)(irLeft.last()*100));
	dirTarget_ = 0.001*buf;
}


// /**
//  * @brief      Sets the diag3onal legs to the same position.
//  *
//  * @param[in]  isFR       Indicates if front right is in the diagonal
//  * @param[in]  hipAngle   The hip angle
//  * @param[in]  kneeAngle  The knee angle
//  */
// void Walker::setDiagonal(bool isFR, float hipCommand, float kneeCommand){
// 	if (isFR){
// 		legFR.setGoalPosition(hipCommand, kneeCommand);
// 		legRL.setGoalPosition(hipCommand, kneeCommand);
// 	}else{
// 		legFL.setGoalPosition(hipCommand, kneeCommand);
// 		legRR.setGoalPosition(hipCommand, kneeCommand);
// 	}
// }
