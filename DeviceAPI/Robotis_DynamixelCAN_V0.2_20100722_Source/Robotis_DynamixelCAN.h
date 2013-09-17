#pragma once

#include "ServoActuator.h"
#include "CAN.h"
#include "DynamixelCAN.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

class Robotis_DynamixelCAN : public ServoActuator
{
public:
	Robotis_DynamixelCAN(void);
	virtual ~Robotis_DynamixelCAN(void);

private:
	Property parameter;

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);
	int SetPower(double power, unsigned long time);
	int GetPower(double &power);
	int SetVelocity(double velocity, unsigned long time);
	int GetVelocity(double &velocity);
	int SetPosition(double position, unsigned long time);
	int GetPosition(double &position);

private:
	CAN *can;
	DynamixelCAN *dynamixel;
#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	ServoActuatorProfile _profile;

	int InitializeCAN(Property parameter);
};
