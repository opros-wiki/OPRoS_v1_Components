#ifndef	_ACCELERATION_SENSOR_H_
#define	_ACCELERATION_SENSOR_H_

#include "Sensor.h"

class AccelerationSensor : public Sensor
{
public:
	AccelerationSensor(void) { };
	virtual ~AccelerationSensor(void) { };

public:
	virtual int GetAccelerationSensorData(vector<double> &accelerationSensorData) { return API_NOT_SUPPORTED; };
};


#endif	//	_ACCELERATION_SENSOR_H_