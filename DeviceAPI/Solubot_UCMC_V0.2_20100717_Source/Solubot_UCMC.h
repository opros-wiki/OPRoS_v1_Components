#pragma once

#include "ServoActuator.h"
#include "CAN.h"
#include "UCMC.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

class Solubot_UCMC : public ServoActuator
{
public:
	Solubot_UCMC(void);
	virtual ~Solubot_UCMC(void);

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
	ServoActuatorProfile _profile;
	
	UCMC *ucmc;
	CAN *can;

#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif

	int InitializeCAN(Property parameter);
	int FinalizeCAN(void);
	
	
};
