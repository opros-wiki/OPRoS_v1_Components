#ifndef	_DISTANCE_SENSOR_H_
#define	_DISTANCE_SENSOR_H_

#include "Sensor.h"

class DistanceSensor : public Sensor
{
public:
	DistanceSensor(void) { };
	virtual ~DistanceSensor(void) { };

public:
	virtual int GetDistanceSensorData(int index, double *data, int size) { return API_NOT_SUPPORTED; };
};


#endif	//	_DISTANCE_SENSOR_H_