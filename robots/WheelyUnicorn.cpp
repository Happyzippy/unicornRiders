#include "WheelyUnicorn.h"

WheelyUnicorn::WheelyUnicorn(int dxlBusSerial, int leftID, int righID, int frontID) {
	dxl_ = new Dynamixel(dxlBusSerial);
	leftID_ = leftID;
	righID_ = righID;
	frontID_ = frontID;
}

WheelyUnicorn::begin() {
	dxl_->begin(3);
	dxl_->jointMode(frontID_);
	dxl_->wheelMode(leftID_);
	dxl_->wheelMode(righID_);
}