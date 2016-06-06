#include "WheelyUnicorn.h"

WheelyUnicorn::WheelyUnicorn(int dxlBusSerial, int leftID, int rightID, int frontID) {
	dxl_ = new Dynamixel(dxlBusSerial);
	leftID_ = leftID;
	rightID_ = rightID;
	frontID_ = frontID;
}

void WheelyUnicorn::begin() {
	dxl_->begin(3);
	dxl_->jointMode(frontID_);
	dxl_->wheelMode(leftID_);
	dxl_->wheelMode(rightID_);
}