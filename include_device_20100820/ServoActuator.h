#ifndef	_SERVO_ACTUATOR_H_
#define	_SERVO_ACTUATOR_H_

#include "Actuator.h"

class ServoActuatorProfile : public ActuatorProfile
{
public:
	ServoActuatorProfile(void)
	{
		linePerRevolution = 0.0;
		reductionRatio = 0.0;
		maximumVelocity = 0.0;
		acceleration = 0.0;
		minimumPositionLimit = 0.0;
		maximumPositionLimit = 0.0;
	}
	virtual ~ServoActuatorProfile(void) { };

	double linePerRevolution;
	double reductionRatio;
	double maximumVelocity;
	double acceleration;
	double minimumPositionLimit;
	double maximumPositionLimit;
};

class ServoActuator : public Actuator
{
public:
	ServoActuator(void) { };
	virtual ~ServoActuator(void) { };

public:
	virtual int SetVelocity(double velocity, unsigned long time = 0) { return API_NOT_SUPPORTED; }
	virtual int GetVelocity(double &velocity) { return API_NOT_SUPPORTED; }
	virtual int SetPosition(double position, unsigned long time = 0) { return API_NOT_SUPPORTED; }
	virtual int GetPosition(double &position) { return API_NOT_SUPPORTED; }
};


#endif	//	_SERVO_ACTUATOR_H_