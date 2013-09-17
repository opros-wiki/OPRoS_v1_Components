#ifndef	_LASER_SCANNER_H_
#define	_LASER_SCANNER_H_

#include "Sensor.h"

namespace OPRoS
{

class LaserScanner : public Sensor
{
public:
	LaserScanner(void) { };
	virtual ~LaserScanner(void) { };

public:
	virtual int getValue(int index, double *value, int size) = 0;
};

};

#endif	//	_LASER_SCANNER_H_