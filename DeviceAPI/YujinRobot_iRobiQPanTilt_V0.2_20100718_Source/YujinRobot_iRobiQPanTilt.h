#pragma once

#include "Manipulator.h"
#include "iRobiQPanTilt.h"

class YujinRobot_iRobiQPanTilt : public Manipulator
{
public:
	YujinRobot_iRobiQPanTilt(void);
	virtual ~YujinRobot_iRobiQPanTilt(void);

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
	vector<ManipulatorProfile> _profile;

	iRobiQPanTilt *panTilt;
	string ip;
	unsigned int port;
	unsigned short serviceId;
};
