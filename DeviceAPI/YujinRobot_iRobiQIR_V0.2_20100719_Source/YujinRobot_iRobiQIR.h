#pragma once

#include "InfraredSensor.h"
#include "iRobiQIR.h"

class YujinRobot_iRobiQIR : public InfraredSensor
{
public:
	YujinRobot_iRobiQIR(void);
	virtual ~YujinRobot_iRobiQIR(void);

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);
	int GetInfraredSensorData(vector<double> &infraredSensorData);

private:
	Property parameter;

	iRobiQIR *ir;
	string ip;
	unsigned int port;
	unsigned short serviceId;
};
