#ifndef _DASAROBOT_TETRAPANTILT_H_
#define _DASAROBOT_TETRAPANTILT_H_

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "Manipulator.h"


class DasaRobot_TetraPanTilt : public Manipulator
{
public:
	DasaRobot_TetraPanTilt (void);
	virtual ~DasaRobot_TetraPanTilt (void);

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);

	int StartHoming(void);
	int Stop(void);
	int EmergencyStop(void);
	int SetPower(vector<double> power, vector<unsigned long> time);
	int GetPower(vector<double> &power);
	int SetVelocity(vector<double> velocity, vector<unsigned long> time);
	int GetVelocity(vector<double> &velocity);
	int SetPosition(vector<double> position, vector<unsigned long> time);
	int GetPosition(vector<double> &position);

private:
	Property parameter;

	std::string robotIP;
	int robotPort;

	bool PowerDown (int servoID);
	bool SetServoPosition (int servoID, int position);
	bool GetServoPosition (int servoID, int *position);
	bool SetServoSpeed (int servoID, int speed);

#if defined(WIN32)
	HMODULE hOprosAPI;
#endif
};

#endif