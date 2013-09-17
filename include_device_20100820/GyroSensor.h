#ifndef	_GYRO_SENSOR_H_
#define	_GYRO_SENSOR_H_

#include "Sensor.h"

class GyroSensor : public Sensor
{
public:
	GyroSensor(void) { };
	virtual ~GyroSensor(void) { };

public:
	virtual int GetGyroSensorData(vector<ObjectLocation> &gyroSensorData) { return API_NOT_SUPPORTED; };
};

#endif	//	_GYRO_SENSOR_H_