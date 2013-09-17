#ifndef	_ACCELERATION_SENSOR_H_
#define	_ACCELERATION_SENSOR_H_

#include "Sensor.h"

namespace OPRoS
{

class AccelerationSensor : public Sensor
{
public:
	AccelerationSensor(void) { };
	virtual ~AccelerationSensor(void) { };

public:
	virtual int getValue(int index, valarray<double> *value) = 0;
};

};

#endif	//	_ACCELERATION_SENSOR_H_