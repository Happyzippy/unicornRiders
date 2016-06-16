#ifndef WALKER_SENSOR_H_
#define WALKER_SENSOR_H_

#include "OLLO.h"

class WalkerSensor
{
public:
	WalkerSensor();
	
	void init(OLLO* ollo, int id, OlloDeviceIndex type, int averages, float a, float  b);

	float readSensor(); 
	float last();
	int readSensorRaw();
	int lastRaw();

private:
	OLLO* ollo_;
	int id_;
	float last_;
	int lastRaw_;
	OlloDeviceIndex type_;
	int averages_;
	float a_;
	float b_;
};



#endif // WALKER_SENSOR_H_
	