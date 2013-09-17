#pragma once

#include "BumperSensor.h"
#include "iRobiQBumper.h"

class YujinRobot_iRobiQBumper : public BumperSensor
{
public:
	YujinRobot_iRobiQBumper(void);
	virtual ~YujinRobot_iRobiQBumper(void);

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);
	int GetBumperSensorData(vector<bool> &bumperSensorData);

private:
	Property parameter;

	iRobiQBumper *bumper;
	string ip;
	unsigned int port;
	unsigned short serviceId;
};
