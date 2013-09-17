#ifndef	_ULTRASONIC_SENSOR_H_
#define	_ULTRASONIC_SENSOR_H_

#include "Sensor.h"

namespace OPRoS
{

class UltrasonicSensor : public Sensor
{
public:
	UltrasonicSensor(void) { };
	virtual ~UltrasonicSensor(void) { };

public:
	virtual int getValue(int index, std::valarray<double> *value) = 0;
};

};


#endif	//	_ULTRASONIC_SENSOR_H_