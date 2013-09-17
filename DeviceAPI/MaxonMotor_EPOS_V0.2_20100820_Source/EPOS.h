#pragma once

#include "CANOpen.h"

class EPOS
{
public:
	EPOS(long id, CANOpen *canOpen);
	virtual ~EPOS(void);

private:
	long id;
	CANOpen *canOpen;
	unsigned short _operationMode;

public:
	//	Motor Information
	int EPOS_SetMotorType(unsigned short motorType);
	int EPOS_GetMotorType(unsigned short *motorType);
	
	int EPOS_SetPolePair(unsigned char polePair);
	int EPOS_GetPolePair(unsigned char *polePair);

	int EPOS_SetPositionSensorType(unsigned short positionSensorType);
	int EPOS_GetPositionSensorType(unsigned short *positionSensorType);

	//	Control, Operation and Status
	int EPOS_EnableOperation();
	int EPOS_ShutDown();
	int EPOS_StartHoming();
	int EPOS_HaltHoming();
	int EPOS_FaultReset();

	int EPOS_GetStatus(unsigned short *status);
	int EPOS_GetError(unsigned char *error);
	int EPOS_SetOperMode(unsigned char mode);
	int EPOS_GetOperMode(unsigned char *mode);

	//	Current Control
	int EPOS_SetContinuousCurrent(unsigned short continuousCurrent);
	int EPOS_GetContinuousCurrent(unsigned short *continuousCurrent);
	int EPOS_SetOutputCurrent(unsigned short outputCurrent);
	int EPOS_GetOutputCurrent(unsigned short *outputCurrent);

	int EPOS_SetTargetCurrent(short targetCurrent);
	int EPOS_GetActualCurrent(short *actualCurrent);
	int EPOS_GetAveragedCurrent(short *averagedCurrent);

	//	Velocity Control
	int EPOS_SetEncoderCount(unsigned long encoderCount);
	int EPOS_GetEncoderCount(unsigned long *encoderCount);

	int EPOS_SetProMaxVel(unsigned long proMaxVel);
	int EPOS_GetProMaxVel(unsigned long *proMaxVel);

	int EPOS_SetProAccel(unsigned long proAccel);
	int EPOS_GetProAccel(unsigned long *proAccel);

	int EPOS_SetProDecel(unsigned long proDecel);
	int EPOS_GetProDecel(unsigned long *proDecel);

	int EPOS_SetQuickStopDecel(unsigned long quickStopDecel);
	int EPOS_GetQuickStopDecel(unsigned long *quickStopDecel);

	int EPOS_SetTargetVelocity(long targetVelocity);
	int EPOS_GetActualVelocity(long *actualVelocity);

	int EPOS_QuickStop();
	int EPOS_Stop();

	//	Position Control
	int EPOS_SetHomePosition(long homePosition);
	int EPOS_GetHomePosition(long *homePosition);
	int EPOS_SetTargetPosition(long targetPosition);
	int EPOS_SetTargetPositionDelta(long targetPosition);
	int EPOS_GetActualPosition(long *actualPosition);
};
