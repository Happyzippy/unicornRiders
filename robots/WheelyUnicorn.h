#ifndef WHEELYUNICORN_H
#define

#include "Dynamixel.h"
#include "nvic.h"
#include "Arduino-compatibles.h"
#include "dxl.h"

class WheelyUnicorn {
private:
	Dynamixel dxl_
	int leftID_, rightID_, frontID_;

public:
	WheelyUnicorn();
	
};

#endif