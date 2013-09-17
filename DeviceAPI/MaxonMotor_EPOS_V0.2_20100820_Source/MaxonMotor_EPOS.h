#pragma once

#include "ServoActuator.h"
#include "CANOpen.h"
#include "EPOS.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

class EPOSProfile : public ServoActuatorProfile
{
public:
	EPOSProfile(void)
	{
		motorType = 1;
		polePair = 0;
		positionSensorType = 0;
	}
	virtual ~EPOSProfile(void)
	{
	}

public:
	unsigned short motorType;
	unsigned char polePair;
	unsigned short positionSensorType;
};

class MaxonMotor_EPOS : public ServoActuator
{
public:
	MaxonMotor_EPOS(void);
	virtual ~MaxonMotor_EPOS(void);

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);

	int SetPower(double power, unsigned long time = 0);
	int GetPower(double &power);
	int SetVelocity(double velocity, unsigned long time = 0);
	int GetVelocity(double &velocity);
	int SetPosition(double position, unsigned long time = 0);
	int GetPosition(double &position);

private:
	Property parameter;
	CAN *can;
	CANOpen *canOpen;
	EPOS *epos;
	EPOSProfile profile;

	bool isActive;
#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif

	int InitializeCAN(Property parameter);
};
