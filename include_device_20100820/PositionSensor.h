#ifndef	_POSITION_SENSOR_H_
#define	_POSITION_SENSOR_H_

#include "Sensor.h"

class PositionSensor : public Sensor
{
public:
	PositionSensor(void) { };
	virtual ~PositionSensor(void) { };

public:
	virtual int GetPositionSensorData(vector<ObjectPosition> &positionSensorData) { return API_NOT_SUPPORTED; };
};

#endif	//	_POSITION_SENSOR_H_