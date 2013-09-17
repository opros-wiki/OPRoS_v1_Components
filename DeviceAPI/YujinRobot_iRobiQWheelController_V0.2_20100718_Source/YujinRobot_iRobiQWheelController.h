#pragma once

#include "WheelController.h"
#include "iRobiQWheelController.h"

class YujinRobot_iRobiQWheelController : public WheelController
{
public:
	YujinRobot_iRobiQWheelController(void);
	virtual ~YujinRobot_iRobiQWheelController(void);

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);
	int Move(double distance);
	int Rotate(double degree);
	int Drive(double forwardVelocity, double angularVelocity);
	int Stop(void);
	int EmergencyStop(void);
	int SetPosition(ObjectLocation position);
	int GetPosition(ObjectLocation &position);

private:
	Property parameter;
	WheelControllerProfile _profile;

	iRobiQWheelController *wheelController;
	string ip;
	unsigned int port;
	unsigned short serviceId;
};
