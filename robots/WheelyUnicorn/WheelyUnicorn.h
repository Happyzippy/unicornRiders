#ifndef WHEELYUNICORN_H
#define WHEELYUNICORN_H

#include "Dynamixel.h"
#include "nvic.h"
#include "Arduino-compatibles.h"
#include "dxl.h"

class WheelyUnicorn {
private:
	Dynamixel* dxl_;
	int leftID_; 
	int rightID_;
	int frontID_;

public:
	WheelyUnicorn(int dxlBusSerial, int leftID, int righID, int frontID);
	void begin();
	
};

#endif