#ifndef	_POSTURE_SENSOR_H_
#define	_POSTURE_SENSOR_H_

#include "Sensor.h"

class PostureSensor : public Sensor
{
public:
	PostureSensor(void) { };
	virtual ~PostureSensor(void) { };

public:
	virtual int GetPostureSensorData(int index, ObjectPosture *data, int size) { return API_NOT_SUPPORTED; };
};


#endif	//	_POSTURE_SENSOR_H_