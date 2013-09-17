#ifndef	_POSITION_SENSOR_H_
#define	_POSITION_SENSOR_H_

#include "Sensor.h"

namespace OPRoS
{

class PositionSensor : public Sensor
{
public:
	PositionSensor(void) { };
	virtual ~PositionSensor(void) { };

public:
	virtual int getValue(int index, ObjectPosition *value, int size) = 0;
};

};

#endif