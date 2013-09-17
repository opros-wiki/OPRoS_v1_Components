#ifndef _DASAROBOT_TETRAULTRASONIC_H_
#define _DASAROBOT_TETRAULTRASONIC_H_

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif
#include "UltrasonicSensor.h"

class DasaRobot_TetraUltrasonic : public UltrasonicSensor
{
public:
	DasaRobot_TetraUltrasonic(void);
	virtual ~DasaRobot_TetraUltrasonic(void);

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

	int sensorCount;
	std::string robotIP;
	int robotPort;

#if defined(WIN32)
	HMODULE hOprosAPI;
#endif

	bool ReadUltraSonicSensorArray (int sensorValue [], int &sensorSize);
};

#endif