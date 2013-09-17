#ifndef	_LASER_SCANNER_H_
#define	_LASER_SCANNER_H_

#include "Sensor.h"

class LaserScanner : public Sensor
{
public:
	LaserScanner(void) { };
	virtual ~LaserScanner(void) { };

public:
	virtual int GetLaserScannerData(vector<double> &laserScannerData) { return API_NOT_SUPPORTED; };
};


#endif	//	_LASER_SCANNER_H_