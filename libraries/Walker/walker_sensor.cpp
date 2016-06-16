#include "walker_sensor.h"

WalkerSensor::WalkerSensor(){

}

void WalkerSensor::init(OLLO* ollo, int id, OlloDeviceIndex type, int averages, float a, float b){
	id_  = id;
	type_= type;
	averages_ = averages;
	last_ = 0;
	a_ = a;
	b_ = b;
	
	ollo_ = ollo;
	ollo_->begin(id, type);
}
float WalkerSensor::readSensor(){
	readSensorRaw();
	return last_;
}

float WalkerSensor::last(){
	return last_;
}

int WalkerSensor::readSensorRaw(){
	lastRaw_ = 0;
	for(int i = 0; i < averages_; i++) {
	  lastRaw_ += ollo_->read(id_, type_);
	}
	lastRaw_ /= averages_;
	last_ = a_/lastRaw_ + b_;
	return lastRaw_;
}

int WalkerSensor::lastRaw(){
	return lastRaw_;
}
