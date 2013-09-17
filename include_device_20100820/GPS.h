#ifndef	_GPS_H_
#define	_GPS_H_

#include "Sensor.h"

class GPS : public Sensor
{
public:
	GPS(void) { };
	virtual ~GPS(void) { };

public:
	virtual int GetGPSData(GPSData &gpsData) { return API_NOT_SUPPORTED; };
};

#endif	//	_GPS_H_
