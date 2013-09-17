#pragma once

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif


#include "ServoActuator.h"
#include "UART.h"

class Faulhaber_MCDC2805 : public ServoActuator
{
public:
	Faulhaber_MCDC2805(void);
	virtual ~Faulhaber_MCDC2805(void);

private:
	Property parameter;

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
	UART *_uart;
#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	ServoActuatorProfile _profile;

	int InitializeUART(Property parameter);

public:
	int MCDC2805_SendPack(unsigned char data[], int len);
	int MCDC2805_RecvPack(unsigned char data[]);

	//	Setting
	int MCDC2805_SetBaudRate(int baudRate);
	int MCDC2805_SetNodeAddr(unsigned char nodeAddr);
	int MCDC2805_GetNodeAddr(unsigned char nodeAddr[]);
	
	//	Command
	int MCDC2805_ResetNode(void);
	int MCDC2805_SaveToEeprom(void);
	int MCDC2805_EnDrive(void);
	int MCDC2805_DiDrive(void);

	//	Status
	int MCDC2805_GetStatus(unsigned char status[]);
	int MCDC2805_GetFault(unsigned char fault[]);
	int MCDC2805_GetActualStatus(unsigned char actualStatus[]);

	//	Current
	int MCDC2805_SetPickCur(unsigned short pickCur);
	int MCDC2805_GetPickCur(unsigned short pickCur[]);
	int MCDC2805_SetContCur(unsigned short contCur);
	int MCDC2805_GetContCur(unsigned short contCur[]);
	int MCDC2805_GetCur(short cur[]);
	
	//	Velocity
	int MCDC2805_SetEncRes(unsigned short encRes);
	int MCDC2805_GetEncRes(unsigned short encRes[]);
	int MCDC2805_SetPGain(unsigned char pGain);
	int MCDC2805_GetPGain(unsigned char pGain[]);
	int MCDC2805_SetIGain(unsigned char iGain);
	int MCDC2805_GetIGain(unsigned char iGain[]);
	int MCDC2805_SetAccel(unsigned short accel);
	int MCDC2805_GetAccel(unsigned short accel[]);
	int MCDC2805_SetMaxSpeed(unsigned short speed);
	int MCDC2805_GetMaxSpeed(unsigned short speed[]);
	int MCDC2805_SetVel(short vel);
	int MCDC2805_GetVel(short vel[]);

	//	Position
	int MCDC2805_SetPositiveLimit(long positiveLimit);
	int MCDC2805_GetPositiveLimit(long positiveLimit[]);
	int MCDC2805_SetNegativeLimit(long negativeLimit);
	int MCDC2805_GetNegativeLimit(long negativeLimit[]);
	int MCDC2805_SetPos(long pos);
	int MCDC2805_GetPos(long pos[]);
};
