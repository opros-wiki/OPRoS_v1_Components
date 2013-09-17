#ifndef	_TOUCH_SENSOR_H_
#define	_TOUCH_SENSOR_H_

#include "Sensor.h"

class TouchSensor : public Sensor
{
public:
	TouchSensor(void) { };
	virtual ~TouchSensor(void) { };

public:
	virtual int GetTouchSensorData(vector<bool> &touchSensorData) { return API_NOT_SUPPORTED; };
};

#endif	//	_TOUCH_SENSOR_H_
