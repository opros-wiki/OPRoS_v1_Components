#ifndef _DASAROBOT_TETRABUMPER_H_
#define _DASAROBOT_TETRABUMPER_H_

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif
#include "BumperSensor.h"

class DasaRobot_TetraBumper : public BumperSensor
{
public:
	DasaRobot_TetraBumper(void);
	virtual ~DasaRobot_TetraBumper(void);

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

	int bumperCount;
	std::string robotIP;
	int robotPort;

	bool ReadBumperArray (bool *bumperValue, int &bumperSize);
	void SetBumperDirMode ();
	void SetBumperOffMode ();

#if defined(WIN32)
	HMODULE hOprosAPI;
#endif

};

#endif