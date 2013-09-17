#pragma once

#include "CAN.h"

class UCMC
{
public:
	UCMC(long id, CAN *can);
	virtual ~UCMC(void);

private:
	CAN *can;
	long id;
	unsigned char _mode;

	int WriteObject(unsigned short index, unsigned char subIndex, unsigned char *data, int size, unsigned long timeOut = 0);
	int WriteObject(unsigned short index, unsigned char subIndex, char data, unsigned long timeOut = 0);
	int WriteObject(unsigned short index, unsigned char subIndex, unsigned char data, unsigned long timeOut = 0);
	int WriteObject(unsigned short index, unsigned char subIndex, short data, unsigned long timeOut = 0);
	int WriteObject(unsigned short index, unsigned char subIndex, unsigned short data, unsigned long timeOut = 0);
	int WriteObject(unsigned short index, unsigned char subIndex, long data, unsigned long timeOut = 0);
	int WriteObject(unsigned short index, unsigned char subIndex, unsigned long data, unsigned long timeOut = 0);

	int ReadObject(unsigned short index, unsigned char subIndex, unsigned char *data, int size, unsigned long timeOut = 0);
	int ReadObject(unsigned short index, unsigned char subIndex, char *data, unsigned long timeOut = 0);
	int ReadObject(unsigned short index, unsigned char subIndex, unsigned char *data, unsigned long timeOut = 0);
	int ReadObject(unsigned short index, unsigned char subIndex, short *data, unsigned long timeOut = 0);
	int ReadObject(unsigned short index, unsigned char subIndex, unsigned short *data, unsigned long timeOut = 0);
	int ReadObject(unsigned short index, unsigned char subIndex, long *data, unsigned long timeOut = 0);
	int ReadObject(unsigned short index, unsigned char subIndex, unsigned long *data, unsigned long timeOut = 0);
	

public:
	//device information
	int UCMC_GetDeviceType(unsigned long *deviceType);	//new
	int UCMC_GetDeviceVersion(double *softwareVersion, double *hardwareVersion); //new

	//	Command
	int UCMC_ResetVariables();
	int UCMC_EnableMotorPower();
	int UCMC_DisableMotorPower();
	int UCMC_QuickStop();
	int UCMC_StartHoming();
	int UCMC_ClearError();
	int UCMC_SetNodeID(long id);
	int UCMC_SaveToEEPROM(void);	//new
	int UCMC_LoadFromEEPROM(void);	//new

	//	Status
	int UCMC_GetStatus(unsigned short *status);
	int UCMC_GetErrorRegister(unsigned char *error);
	int UCMC_GetDeviceError(unsigned short *error);

	//	Operation Mode
	int UCMC_SetControlMode(unsigned long controlMode);
	int UCMC_GetControlMode(unsigned long *controlMode);
	int UCMC_SetMode(unsigned char mode);
	int UCMC_GetMode(unsigned char *mode);

	//	Current Control
	int UCMC_SetContinuousCurrent(unsigned long current);
	int UCMC_GetContinuousCurrent(unsigned long *current);
	int UCMC_SetOutputCurrent(unsigned long current);
	int UCMC_GetOutputCurrent(unsigned long *current);
	
	int UCMC_SetCurrentPGain(short pGain);
	int UCMC_GetCurrentPGain(short *pGain);
	int UCMC_SetCurrentIGain(short iGain);
	int UCMC_GetCurrentIGain(short *iGain);

	int UCMC_SetTargetCurrent(long current);
	int UCMC_GetTargetCurrent(long *current);
	int UCMC_GetActualCurrent(long *current);
	int UCMC_GetAveragedCurrent(long *current);

	//	Velocity Control
	int UCMC_SetEncoderCount(short encoderCount);
	int UCMC_GetEncoderCount(short *encoderCount);

	int UCMC_SetMaxVelocity(short velocity);
	int UCMC_GetMaxVelocity(short *velocity);
	int UCMC_SetProfileVelocity(short velocity);
	int UCMC_GetProfileVelocity(short *velocity);
	int UCMC_SetAcceleration(long acceleration);
	int UCMC_GetAcceleration(long *acceleration);
	int UCMC_SetDeceleration(long deceleration);
	int UCMC_GetDeceleration(long *deceleration);
	int UCMC_SetQuickStopDeceleration(long quickStopDeceleration);
	int UCMC_GetQuickStopDeceleration(long *quickStopDeceleration);

	int UCMC_SetVelocityPGain(short pGain);
	int UCMC_GetVelocityPGain(short *pGain);
	int UCMC_SetVelocityIGain(short iGain);
	int UCMC_GetVelocityIGain(short *iGain);
	int UCMC_SetVelocityDGain(short dGain);
	int UCMC_GetVelocityDGain(short *dGain);

	int UCMC_SetProfileTargetVelocity(short profileTargetVelocity);
	int UCMC_GetProfileTargetVelocity(short *profileTargetVelocity);
	int UCMC_SetTargetVelocity(short velocity);
	int UCMC_GetTargetVelocity(short *velocity);
	int UCMC_GetActualVelocity(short *velocity);

	//	Position Control
	int UCMC_SetNegativePositionLimit(long position);
	int UCMC_GetNegativePositionLimit(long *position);
	int UCMC_SetPositivePositionLimit(long position);
	int UCMC_GetPositivePositionLimit(long *position);

	int UCMC_SetPositionPGain(short pGain);
	int UCMC_GetPositionPGain(short *pGain);
	int UCMC_SetPositionIGain(short iGain);
	int UCMC_GetPositionIGain(short *iGain);
	int UCMC_SetPositionDGain(short dGain);
	int UCMC_GetPositionDGain(short *dGain);

	int UCMC_SetProfileTargetPosition(long profilePosition);
	int UCMC_GetProfileTargetPosition(long *profilePosition);
	int UCMC_SetTargetPosition(long targetPosition);
	int UCMC_GetTargetPosition(long *targetPosition);
	int UCMC_SetActualPosition(long position);
	int UCMC_GetActualPosition(long *position);
	int UCMC_GetAbsolutePosition(long *position);

	//	Homing
	int UCMC_SetHomingMethod(unsigned char homingMethod);
	int UCMC_GetHomingMethod(unsigned char *homingMethod);
	int UCMC_SetSwitchSearchVelocity(short velocity);
	int UCMC_GetSwitchSearchVelocity(short *velocity);
	int UCMC_SetZeroSearchVelocity(short velocity);
	int UCMC_GetZeroSearchVelocity(short *velocity);

	//	IO
	int UCMC_GetDI(unsigned long *di);
	int UCMC_GetAI(unsigned short *ai);
	int UCMC_GetDigitalInput(unsigned long *digitalInput);

	//	Synchronization
	int UCMC_SynchronizeObject(unsigned char syncOption, unsigned short *status, long *current, short *velocity, long *position);
};
