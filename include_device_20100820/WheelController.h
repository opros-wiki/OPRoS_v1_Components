#ifndef	_WHEEL_CONTROLLER_H_
#define	_WHEEL_CONTROLLER_H_

#include "Device.h"

class WheelControllerProfile
{
public:
	WheelControllerProfile(void)
	{
		wheelDiameter = 0.0;
		axleDistance = 0.0;
		varianceDistance = 0.0;
		varianceDirection = 0.0;
		safeRadius = 0.0;
		maximumVelocity = 0.0;
		acceleration = 0.0;
	}
	virtual ~WheelControllerProfile(void) { };

	double wheelDiameter;
	double axleDistance;
	double varianceDistance;
	double varianceDirection;
	double safeRadius;
	double maximumVelocity;
	double acceleration;
};

class WheelController : public Device
{
public:
	WheelController(void) { };
	virtual ~WheelController(void) { };

public:
	virtual int Stop(void) { return API_NOT_SUPPORTED; }
	virtual int EmergencyStop(void) { return API_NOT_SUPPORTED; }
	virtual int Move(double distance) { return API_NOT_SUPPORTED; }
	virtual int Rotate(double degree) { return API_NOT_SUPPORTED; }
	virtual int Drive(double forwardVelocity, double angularVelocity) { return API_NOT_SUPPORTED; }
	virtual int SetPosition(ObjectLocation position) { return API_NOT_SUPPORTED; }
	virtual int GetPosition(ObjectLocation &position) { return API_NOT_SUPPORTED; }
};

#endif	//	_WHEEL_CONTROLLER_H_