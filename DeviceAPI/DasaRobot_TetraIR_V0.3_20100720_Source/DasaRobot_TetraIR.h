#ifndef _DASAROBOT_TETRAIR_H_
#define _DASAROBOT_TETRAIR_H_

#include "InfraredSensor.h"

class DasaRobot_TetraIR : public InfraredSensor
{
public:
	DasaRobot_TetraIR(void);
	virtual ~DasaRobot_TetraIR(void);

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
	int sensorCount;
	std::string robotIP;
	int robotPort;

	bool ReadPsdSensorArray (int sensorValue [], int &sensorSize);

#if defined(WIN32)
	HMODULE hOprosAPI;
#endif

};

#endif