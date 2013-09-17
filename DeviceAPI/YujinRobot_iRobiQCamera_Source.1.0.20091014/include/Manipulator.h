#ifndef	_MANIPULATOR_H_
#define	_MANIPULATOR_H_

#include "Actuator.h"
#include "OprosApiTypes.h"

namespace OPRoS
{

class Manipulator : public Device
{
public:
	Manipulator(void) { };
	virtual ~Manipulator(void) { };

public:
	virtual bool setPower(int index, double power, unsigned long time = 0) = 0;
	virtual bool getPower(int index, double *power) = 0;
	virtual bool setVelocity(int index, double velocity, unsigned long time = 0) = 0;
	virtual bool getVelocity(int index, double *velocity) = 0;
	virtual bool setPosition(int index, double position, unsigned long time = 0) = 0;
	virtual bool getPosition(int index, double *position) = 0;
};

};

#endif	//	_MANIPULATOR_H_