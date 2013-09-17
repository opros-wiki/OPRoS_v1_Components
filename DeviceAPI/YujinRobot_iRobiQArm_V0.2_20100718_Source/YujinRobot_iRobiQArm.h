#pragma once

#include "Manipulator.h"
#include "iRobiQArm.h"

class YujinRobot_iRobiQArm : public Manipulator
{
public:
	YujinRobot_iRobiQArm(void);
	virtual ~YujinRobot_iRobiQArm(void);

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

	iRobiQArm *arm;
	string ip;
	unsigned int port;
	unsigned short serviceId;
};
