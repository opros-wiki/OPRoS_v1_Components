#ifndef	_SENSOR_H_
#define	_SENSOR_H_

#include "Device.h"

class SensorProfile
{
public:
	SensorProfile(void) {
		x = y = z = roll = pitch = yaw = 0.0;
	}
	virtual ~SensorProfile(void) { };

	double x;
	double y;
	double z;
	double roll;
	double pitch;
	double yaw;
};

class Sensor : public Device
{
public:
	Sensor(void) { };
	virtual ~Sensor(void) { };
};

#endif	//	_SENSOR_H_
