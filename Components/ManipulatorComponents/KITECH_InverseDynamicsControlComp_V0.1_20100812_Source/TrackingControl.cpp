#include "TrackingControl.h"

TrackingControl::TrackingControl(double gravity[3], double dt, double fsi, double fvi)
: DynamicsControl(gravity, dt, fsi, fvi)
{
	controlMode = 0;
	Ki = 0.0;
	Kd = 0.0;
}

TrackingControl::~TrackingControl(void)
{
}

bool TrackingControl::SetControlMode(int controlMode)
{
	switch(controlMode) {
		case 0 :
		case 1 :
		case 2 :
			break;
		default :
			return false;
	}

	this->controlMode = controlMode;

	return true;
}

int TrackingControl::GetcontrolMode(void)
{
	return controlMode;
}

bool TrackingControl::SetKi(double Ki)
{
	if(Ki < 0.0) {
		return false;
	}

	this->Ki = Ki;

	return true;
}

double TrackingControl::GetKi(void)
{
	return Ki;
}

bool TrackingControl::SetKd(double Kd)
{
	if(Kd < 0.0) {
		return false;
	}
	
	this->Kd = Kd;

	return true;
}

double TrackingControl::GetKd(void)
{
	return Kd;
}