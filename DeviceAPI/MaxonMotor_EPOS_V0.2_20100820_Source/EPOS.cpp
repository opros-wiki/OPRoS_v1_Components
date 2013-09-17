#include "EPOS.h"
#include "EPOSDef.h"

EPOS::EPOS(long id, CANOpen *canOpen)
{
	this->id = id;
	this->canOpen = canOpen;

	_operationMode = 0x0000;
}

EPOS::~EPOS(void)
{
	canOpen = NULL;
}

///////////////////////////////////////////////////////////////////////////////
//	Motor Information
///////////////////////////////////////////////////////////////////////////////
int EPOS::EPOS_SetMotorType(unsigned short motorType)
{
	if(canOpen == NULL)		return -1;

	if(!(motorType == 1 ||		//	Phase modulated DC motor
		motorType == 10 ||		//	Sinusoidal PM BL motor
		motorType == 11)) {		//	Trapezoidal PM BL motor
		return -1;
	}
	
	return canOpen->WriteObject (id, EPOS_MOTOR_TYPE, motorType);
}

int EPOS::EPOS_GetMotorType(unsigned short *motorType)
{
	if(canOpen == NULL)		return -1;

	return canOpen->ReadObject (id, EPOS_MOTOR_TYPE, motorType);
}
int EPOS::EPOS_SetPolePair(unsigned char polePair)
{
	if(canOpen == NULL)		return -1;

	return canOpen->WriteObject (id, EPOS_POLEPAIR_NUMBER, polePair);
}

int EPOS::EPOS_GetPolePair(unsigned char *polePair)
{
	if(canOpen == NULL)		return -1;

	return canOpen->ReadObject (id, EPOS_POLEPAIR_NUMBER, polePair);
}

int EPOS::EPOS_SetPositionSensorType(unsigned short positionSensorType)
{
	if(canOpen == NULL)		return -1;

	switch(positionSensorType) {
		case 1 :	//	Incremental Encoder with index (3-channel)
		case 2 :	//	Incremental Encoder without index (2-channel)
		case 3 :	//	Hall Sensors (Remark: consider worse resolution)
			break;
		default :
			return -1;
	}

	return canOpen->WriteObject (id, EPOS_POLEPAIR_NUMBER, positionSensorType);
}

int EPOS::EPOS_GetPositionSensorType(unsigned short *positionSensorType)
{
	if(canOpen == NULL)		return -1;

	return canOpen->ReadObject (id, EPOS_POLEPAIR_NUMBER, positionSensorType);
}

///////////////////////////////////////////////////////////////////////////////
//	Commmand, Operation Mode and Status Functions for EPOS Servo Controller
///////////////////////////////////////////////////////////////////////////////

int EPOS::EPOS_EnableOperation()
{
	if(canOpen == NULL)		return -1;

	return canOpen->WriteObject(id, EPOS_CONTROL_WORD, (unsigned short)EPOS_CTRL_ENABLE_OPERATION);
}

int EPOS::EPOS_ShutDown()
{
	if(canOpen == NULL)		return -1;

	return canOpen->WriteObject(id, EPOS_CONTROL_WORD, (unsigned short)EPOS_CTRL_SHUTDOWN);
}

int EPOS::EPOS_StartHoming()
{
	if(canOpen == NULL)		return -1;

	return canOpen->WriteObject(id, EPOS_CONTROL_WORD, (unsigned short)EPOS_CTRL_START_HOMING);
}

int EPOS::EPOS_HaltHoming()
{
	if(canOpen == NULL)		return -1;

	return canOpen->WriteObject(id, EPOS_CONTROL_WORD, (unsigned short)EPOS_CTRL_HALT_HOMING);
}

int EPOS::EPOS_FaultReset()
{
	if(canOpen == NULL)		return -1;

	return canOpen->WriteObject(id, EPOS_CONTROL_WORD, (unsigned short)EPOS_CTRL_FAULT_RESET);
}

int EPOS::EPOS_GetStatus(unsigned short *status)
{
	if(canOpen == NULL)		return -1;

	// 0x8000	 bit15 Position referenced to home position
	// 0x4000	 bit14 Refresh cycle of power stage
	// 0x2000	 bit13 Operation mode specific
	// 0x1000	 bit12 Operation mode specific
	// 0x0800	 bit11 not used (Internal limit active)
	// 0x0400	 bit10 Operation mode specific
	// 0x0200	 bit9  Remote (NMT operational state)
	// 0x0100	 bit8  Offset current measured
	// 0x0080	 bit7  Warning
	// 0x0040	 bit6  Switch on disable
	// 0x0020	 bit5  Quick stop
	// 0x0010	 bit4  Voltage enabled (power stage on)
	// 0x0008	 bit3  Fault
	// 0x0004	 bit2  Operation enable
	// 0x0002	 bit1  Switched on
	// 0x0001	 bit0  Ready to switch on
	return canOpen->ReadObject(id, EPOS_STATUS_WORD, status);
}

int EPOS::EPOS_GetError(unsigned char *error)
{
	if(canOpen == NULL)		return -1;

	// bit 7: Motion error
	// bit 6: Reserved (always 0)
	// bit 5: Device profile specific
	// bit 4: Communication error
	// bit 3: Temperature error
	// bit 2: Voltage error
	// bit 1: Current error
	// bit 0: Generic error
	return canOpen->ReadObject(id, EPOS_ERROR_REGISTER, error);
}

int EPOS::EPOS_SetOperMode(unsigned char mode)
{
	if(canOpen == NULL)		return -1;

	if(_operationMode == mode) {
		return true;
	}

	//  Operation Mode	Description
	//  6 Homing Mode
	//  3 Profile Velocity Mode
	//  1 Profile Position Mode
	// -1 Position Mode
	// -2 Velocity Mode
	// -3 Current Mode
	// -4 Diagnostic Mode
	// -5 MasterEncoder Mode
	// -6 Step/Direction Mode
	if (canOpen->WriteObject(id, EPOS_MODES_OF_OPERATION, mode)) {
		_operationMode = mode;
		
		//EPOS_ShutDown();
		//EPOS_EnableOperation();
		return true;
	}
	return false;
}

int EPOS::EPOS_GetOperMode(unsigned char *mode)
{
	if(canOpen == NULL)		return -1;

	return canOpen->ReadObject(id, EPOS_MODES_OF_OPERATION_DISPLAY, mode);
}

///////////////////////////////////////////////////////////////////////////////
//	Current Control Functions for EPOS Servo Controller
///////////////////////////////////////////////////////////////////////////////
int EPOS::EPOS_SetContinuousCurrent(unsigned short continuousCurrent)
{
	if(canOpen == NULL)		return -1;
	
	return canOpen->WriteObject (id, EPOS_CONTINUOUS_CURRENT_LIMIT, continuousCurrent);
}

int EPOS::EPOS_GetContinuousCurrent(unsigned short *continuousCurrent)
{
	if(canOpen == NULL)		return -1;

	return canOpen->ReadObject (id, EPOS_CONTINUOUS_CURRENT_LIMIT, continuousCurrent);
}

int EPOS::EPOS_SetOutputCurrent(unsigned short outputCurrent)
{
	if(canOpen == NULL)		return -1;

	return canOpen->WriteObject (id, EPOS_OUTPUT_CURRENT_LIMIT, outputCurrent);
}

int EPOS::EPOS_GetOutputCurrent(unsigned short *outputCurrent)
{
	if(canOpen == NULL)		return -1;

	return canOpen->ReadObject (id, EPOS_OUTPUT_CURRENT_LIMIT, outputCurrent);
}

int EPOS::EPOS_SetTargetCurrent(short targetCurrent)
{
	if(canOpen == NULL)		return -1;

	if(!EPOS_SetOperMode(EPOS_CUR_MODE)) {
		return false;
	}
	return canOpen->WriteObject(id, EPOS_CURRENTMODE_SETTING_VALUE, targetCurrent);
}

int EPOS::EPOS_GetActualCurrent(short *actualCurrent)
{
	if(canOpen == NULL)		return -1;

	return canOpen->ReadObject(id, EPOS_CURRENT_ACTUAL_VALUE, actualCurrent);
}

int EPOS::EPOS_GetAveragedCurrent(short *averagedCurrent)
{
	if(canOpen == NULL)		return -1;

	return canOpen->ReadObject(id, EPOS_CURRENT_ACTUAL_VALUE_AVERAGED, averagedCurrent);
}

///////////////////////////////////////////////////////////////////////////////
//	Velocity Control Functions for EPOS Servo Controller
///////////////////////////////////////////////////////////////////////////////
int EPOS::EPOS_SetEncoderCount(unsigned long encoderCount)
{
	if(canOpen == NULL)		return -1;

	return canOpen->WriteObject (id, EPOS_ENCODER_PULSE_NUMBER, encoderCount);
}

int EPOS::EPOS_GetEncoderCount(unsigned long *encoderCount)
{
	if(canOpen == NULL)		return -1;

	return canOpen->ReadObject (id, EPOS_ENCODER_PULSE_NUMBER, encoderCount);
}

int EPOS::EPOS_SetProMaxVel(unsigned long proMaxVel)
{
	if(canOpen == NULL)		return -1;

	return canOpen->WriteObject(id, EPOS_MAX_PROFILE_VELOCITY, proMaxVel);
}

int EPOS::EPOS_GetProMaxVel(unsigned long *proMaxVel)
{
	if(canOpen == NULL)		return -1;

	return canOpen->ReadObject(id, EPOS_MAX_PROFILE_VELOCITY, proMaxVel);
}

int EPOS::EPOS_SetProAccel(unsigned long proAccel)
{
	if(canOpen == NULL)		return -1;

	return canOpen->WriteObject(id, EPOS_PROFILE_ACCELERATION, proAccel);
}

int EPOS::EPOS_GetProAccel(unsigned long *proAccel)
{
	if(canOpen == NULL)		return -1;

	return canOpen->ReadObject(id, EPOS_PROFILE_ACCELERATION, proAccel);
}

int EPOS::EPOS_SetProDecel(unsigned long proDecel)
{
	if(canOpen == NULL)		return -1;

	return canOpen->WriteObject(id, EPOS_PROFILE_DECELERATION, proDecel);
}

int EPOS::EPOS_GetProDecel(unsigned long *proDecel)
{
	if(canOpen == NULL)		return -1;

	return canOpen->ReadObject(id, EPOS_PROFILE_DECELERATION, proDecel);
}

int EPOS::EPOS_SetQuickStopDecel(unsigned long quickStopDecel)
{
	if(canOpen == NULL)		return -1;

	return canOpen->WriteObject(id, EPOS_QUICKSTOP_DECELERATION, quickStopDecel);
}

int EPOS::EPOS_GetQuickStopDecel(unsigned long *quickStopDecel)
{
	if(canOpen == NULL)		return -1;

	return canOpen->ReadObject(id, EPOS_QUICKSTOP_DECELERATION, quickStopDecel);
}

int EPOS::EPOS_SetTargetVelocity(long targetVelocity)
{
	if(canOpen == NULL)		return -1;

	if(!EPOS_SetOperMode(EPOS_PRO_VEL_MODE)) {
		return false;
	}
	if (!canOpen->WriteObject(id, EPOS_TARGET_VELOCITY, targetVelocity)) {
		return false;
	}
	return canOpen->WriteObject(id, EPOS_CONTROL_WORD, (unsigned short)EPOS_CTRL_START_PRO_VEL);
}

int EPOS::EPOS_GetActualVelocity(long *actualVelocity)
{
	if(canOpen == NULL)		return -1;

	return canOpen->ReadObject(id, EPOS_VELOCITY_ACTUAL_VALUE, actualVelocity);
}

int EPOS::EPOS_QuickStop()
{
	if(canOpen == NULL)		return -1;

	_operationMode = 0;

	canOpen->WriteObject (id, EPOS_TARGET_VELOCITY, (long)0);
	return canOpen->WriteObject (id, EPOS_CONTROL_WORD, (unsigned short)EPOS_CTRL_QUICK_STOP);
}

int EPOS::EPOS_Stop()
{
	if(canOpen == NULL)		return -1;

	_operationMode = 0;

	canOpen->WriteObject (id, EPOS_TARGET_VELOCITY, (long)0);
	return canOpen->WriteObject (id, EPOS_CONTROL_WORD, (unsigned short)EPOS_CTRL_STOP_POS);
}

///////////////////////////////////////////////////////////////////////////////
//	Position Control Functions for EPOS Servo Controller
///////////////////////////////////////////////////////////////////////////////
int EPOS::EPOS_SetHomePosition(long homePosition)
{
	if(canOpen == NULL)		return -1;

	return canOpen->WriteObject(id, EPOS_HOME_POSITION, homePosition);
}

int EPOS::EPOS_GetHomePosition(long *homePosition)
{
	if(canOpen == NULL)		return -1;

	return canOpen->ReadObject(id, EPOS_HOME_POSITION, homePosition);
}

int EPOS::EPOS_SetTargetPosition(long targetPosition)
{
	if(canOpen == NULL)		return -1;

	if(!EPOS_SetOperMode(EPOS_PRO_POS_MODE)) {
		return false;
	}
	if (!canOpen->WriteObject(id, EPOS_TARGET_POSITION, targetPosition)) {
		return false;
	}
	return canOpen->WriteObject(id, EPOS_CONTROL_WORD, (unsigned short)EPOS_POS_CTRL_ABS_IMM);
}

int EPOS::EPOS_SetTargetPositionDelta(long targetPosition)
{
	if(canOpen == NULL)		return -1;

	if(!EPOS_SetOperMode(EPOS_PRO_POS_MODE)) {
		return false;
	}
	if (!canOpen->WriteObject(id, EPOS_TARGET_POSITION, targetPosition)) {
		return false;
	}
	return canOpen->WriteObject(id, EPOS_CONTROL_WORD, (unsigned short)EPOS_POS_CTRL_REL_IMM);
}

int EPOS::EPOS_GetActualPosition(long *actualPosition)
{
	if(canOpen == NULL)		return -1;

	return canOpen->ReadObject(id, EPOS_POSITION_ACTUAL_VALUE, actualPosition);
}
