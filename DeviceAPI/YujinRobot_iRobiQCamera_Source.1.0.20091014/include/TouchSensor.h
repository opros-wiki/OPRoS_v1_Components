#ifndef	_TOUCH_SENSOR_H_
#define	_TOUCH_SENSOR_H_

#include "Sensor.h"

namespace OPRoS
{

class TouchSensor : public Sensor
{
public:
	TouchSensor(void) { };
	virtual ~TouchSensor(void) { };

public:
	virtual int getState(int index, std::valarray<bool> *state) = 0;
};

};

#endif	//	_TOUCH_SENSOR_H_