#ifndef	_BUMPER_SENSOR_H_
#define	_BUMPER_SENSOR_H_

#include "Sensor.h"

class BumperSensorProfile : public SensorProfile
{
public:
	BumperSensorProfile(void) { };
	virtual ~BumperSensorProfile(void) { };
};

class BumperSensor : public Sensor
{
public:
	BumperSensor(void) { };
	virtual ~BumperSensor(void) { };

public:
	virtual int GetBumperSensorData(vector<bool> &bumperSensorData) { return API_NOT_SUPPORTED; };
};

#endif	//	_BUMPER_SENSOR_H_