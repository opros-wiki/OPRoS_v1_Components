#ifndef	_INERTIAL_MEASUREMENT_UNIT_H_
#define	_INERTIAL_MEASUREMENT_UNIT_H_

#include "Sensor.h"

namespace OPRoS
{

class InertialMeasurementUnit : public Sensor
{
public:
	InertialMeasurementUnit(void) { };
	virtual ~InertialMeasurementUnit(void) { };

public:
	virtual int getValue(int index, valarray<ObjectPosture> *value) = 0;
};

};

#endif	//	_INERTIAL_MEASUREMENT_UNIT_H_