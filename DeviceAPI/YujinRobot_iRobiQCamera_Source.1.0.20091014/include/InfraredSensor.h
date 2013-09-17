#ifndef	_INFRARED_SENSOR_H_
#define	_INFRARED_SENSOR_H_

#include "Sensor.h"

namespace OPRoS
{

class InfraredSensor : public Sensor
{
public:
	InfraredSensor(void) { };
	virtual ~InfraredSensor(void) { };

public:
	virtual int getValue(int index, std::valarray<double> *value) = 0;
};

};

#endif	//	_INFRARED_SENSOR_H_