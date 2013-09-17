#ifndef	_ACTUATOR_H_
#define	_ACTUATOR_H_

#include "Device.h"

class ActuatorProfile
{
public:
	ActuatorProfile(void)
	{
		maximumPower = 0.0;
	}

	virtual ~ActuatorProfile(void) { }

	double maximumPower;
};

class Actuator : public Device
{
public:
	Actuator(void) { };
	virtual ~Actuator(void) { };

public:
	virtual int SetPower(double power, unsigned long time = 0) { return API_NOT_SUPPORTED; }
	virtual int GetPower(double &power) { return API_NOT_SUPPORTED; }
};

#endif	//	_ACTUATOR_H_