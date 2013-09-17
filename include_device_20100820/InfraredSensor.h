#ifndef	_INFRARED_SENSOR_H_
#define	_INFRARED_SENSOR_H_

#include "Sensor.h"

class InfraredSensor : public Sensor
{
public:
	InfraredSensor(void) { };
	virtual ~InfraredSensor(void) { };

public:
	virtual int GetInfraredSensorData(vector<double> &infraredSensorData) { return API_NOT_SUPPORTED; };
};

#endif	//	_INFRARED_SENSOR_H_
