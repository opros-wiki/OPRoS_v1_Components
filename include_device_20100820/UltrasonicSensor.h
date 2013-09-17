#ifndef	_ULTRASONIC_SENSOR_H_
#define	_ULTRASONIC_SENSOR_H_

#include "Sensor.h"

class UltrasonicSensor : public Sensor
{
public:
	UltrasonicSensor(void) { };
	virtual ~UltrasonicSensor(void) { };

public:
	virtual int GetUltrasonicSensorData(vector<double> &ultrasonicSensorData) { return API_NOT_SUPPORTED; };
};

#endif	//	_ULTRASONIC_SENSOR_H_
