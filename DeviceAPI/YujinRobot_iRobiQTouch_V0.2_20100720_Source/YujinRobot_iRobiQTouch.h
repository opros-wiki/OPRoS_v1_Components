#pragma once

#include "TouchSensor.h"
#include "iRobiQTouch.h"

class YujinRobot_iRobiQTouch : public TouchSensor
{
public:
	YujinRobot_iRobiQTouch(void);
	virtual ~YujinRobot_iRobiQTouch(void);

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);
	int GetTouchSensorData(vector<bool> &touchSensorData);

private:
	Property parameter;

	iRobiQTouch *touch;
	string ip;
	unsigned int port;
	unsigned short serviceId;
};
