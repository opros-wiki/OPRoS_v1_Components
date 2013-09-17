#ifndef	_ILLUMINATION_SENSOR_H_
#define	_ILLUMINATION_SENSOR_H_

#include "Sensor.h"

class IlluminationSensor : public Sensor
{
public:
	IlluminationSensor(void) { };
	virtual ~IlluminationSensor(void) { };

public:
	virtual int GetIlluminationSensorData(int index, double *data, int size) { return API_NOT_SUPPORTED; };
};


#endif	//	_ILLUMINATION_SENSOR_H_