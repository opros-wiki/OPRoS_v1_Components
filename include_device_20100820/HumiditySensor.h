#ifndef	_HUMIDITY_SENSOR_H_
#define	_HUMIDITY_SENSOR_H_

#include "Sensor.h"

class HumiditySensor : public Sensor
{
public:
	HumiditySensor(void) { };
	virtual ~HumiditySensor(void) { };

public:
	virtual int GetHumiditySensorData(int index, double *data, int size) { return API_NOT_SUPPORTED; };
};


#endif	//	_HUMIDITY_SENSOR_H_