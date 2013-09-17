#pragma once

#include <string>
#include "UltrasonicSensor.h"
#include "iRobiQSonar.h"

class YujinRobot_iRobiQSonar : public UltrasonicSensor
{
public:
	YujinRobot_iRobiQSonar(void);
	virtual ~YujinRobot_iRobiQSonar(void);

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);
	int GetUltrasonicSensorData(vector<double> &ultrasonicSensorData);

private:
	Property parameter;

	iRobiQSonar *sonar;
	string ip;
	unsigned int port;
	unsigned short serviceId;
};
