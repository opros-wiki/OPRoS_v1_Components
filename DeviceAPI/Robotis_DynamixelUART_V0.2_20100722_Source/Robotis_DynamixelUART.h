#pragma once

#include "ServoActuator.h"
#include "UART.h"
#include "DynamixelUART.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

class Robotis_DynamixelUART : public ServoActuator
{
public:
	Robotis_DynamixelUART(void);
	virtual ~Robotis_DynamixelUART(void);

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
	UART *uart;
#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	ServoActuatorProfile _profile;
	DynamixelUART *dynamixel;

	int InitializeUART(Property parameter);
};
