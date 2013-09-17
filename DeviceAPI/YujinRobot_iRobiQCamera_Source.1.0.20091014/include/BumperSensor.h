#ifndef	_BUMPER_SENSOR_H_
#define	_BUMPER_SENSOR_H_

#include "Sensor.h"

namespace OPRoS
{

class BumperSensor : public Sensor
{
public:
	BumperSensor(void) { };
	virtual ~BumperSensor(void) { };

public:
	virtual int getState(int index, std::valarray<bool> *state) = 0;
};

};

#endif	//	_BUMPER_SENSOR_H_