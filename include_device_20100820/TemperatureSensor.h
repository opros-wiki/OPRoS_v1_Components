#ifndef	_TEMPERATURE_SENSOR_H_
#define	_TEMPERATURE_SENSOR_H_

#include "Sensor.h"

class TemperatureSensor : public Sensor
{
public:
	TemperatureSensor(void) { };
	virtual ~TemperatureSensor(void) { };

public:
	virtual int GetTemperatureSensorData(int index, double *data, int size) { return API_NOT_SUPPORTED; };
};

#endif	//	_TEMPERATURE_SENSOR_H_
