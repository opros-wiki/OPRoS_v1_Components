#include <string.h>

#include "UCMC.h"
#include "UCMCDef.h"

#include "OprosPrintMessage.h"
#include "OprosTimer.h"


UCMC::UCMC(long id, CAN *can)
{
	this->id = id;
	this->can = can;
}

UCMC::~UCMC(void)
{
	can = NULL;
}

int UCMC::WriteObject(unsigned short index, unsigned char subIndex, unsigned char *data, int size, unsigned long timeOut)
{
	eSDO_COMMAND command;

	if(can == NULL || size < 0 || size > 4) {
		return -1;
	}

	switch(size) {
		case 1 :	command = WRITE_REQUEST_1BYTE;			break;
		case 2 :	command = WRITE_REQUEST_2BYTE;			break;
		case 4 :	command = WRITE_REQUEST_4BYTE;			break;
		default :	command = WRITE_REQUEST;	size = 4;	break;
	}

	unsigned char buffer[8] = { command, (unsigned char)(index>>0), (unsigned char)(index>>8), (unsigned char)subIndex};
	memcpy(&buffer[4], data, size);

	can->Lock();
	int ret = can->Write(FC_SDO1_TX + id, buffer, 4 + size);

	if (ret != 4 + size) {
		PrintMessage("ERROR : UCMC::WriteObject() -> Can't write data.\n");
		can->Unlock();	return -1;
	}

	OprosSleep(timeOut);

	long recvId;
	unsigned char recvCommand;
	unsigned short recvIndex;
	unsigned char recvSubIndex;

	size = can->Read(recvId, buffer, 8);
	if(size < 0) {
		PrintMessage("ERROR : UCMC::WriteObject() -> Can't receive data.\n");
		can->Unlock();	return -1;
	}
	can->Unlock();

	recvCommand = buffer[0];
	recvIndex = buffer[1] | (buffer[2] << 8);
	recvSubIndex = buffer[3];

	if((recvId != (id | FC_SDO1_RX)) || (recvCommand != WRITE_RESPONSE) || (recvIndex != index) || (recvSubIndex != subIndex)) {
		PrintMessage("ERROR : UCMC::WriteObject() -> %x, %x, %x, %x\n", recvId, recvCommand, recvIndex, recvSubIndex);
		return -1;
	}

	return 0;
}

int UCMC::WriteObject(unsigned short index, unsigned char subIndex, char data, unsigned long timeOut)
{
	return WriteObject(index, subIndex, (unsigned char *)&data, 1, timeOut);
}

int UCMC::WriteObject(unsigned short index, unsigned char subIndex, unsigned char data, unsigned long timeOut)
{
	return WriteObject(index, subIndex, (unsigned char *)&data, 1, timeOut);
}

int UCMC::WriteObject(unsigned short index, unsigned char subIndex, short data, unsigned long timeOut)
{
	return WriteObject(index, subIndex, (unsigned char *)&data, 2, timeOut);
}

int UCMC::WriteObject(unsigned short index, unsigned char subIndex, unsigned short data, unsigned long timeOut)
{
	return WriteObject(index, subIndex, (unsigned char *)&data, 2, timeOut);
}

int UCMC::WriteObject(unsigned short index, unsigned char subIndex, long data, unsigned long timeOut)
{
	return WriteObject(index, subIndex, (unsigned char *)&data, 4, timeOut);
}

int UCMC::WriteObject(unsigned short index, unsigned char subIndex, unsigned long data, unsigned long timeOut)
{
	return WriteObject(index, subIndex, (unsigned char *)&data, 4, timeOut);
}

int UCMC::ReadObject(unsigned short index, unsigned char subIndex, unsigned char *data, int size, unsigned long timeOut)
{
	if(can == NULL || size < 0 || size > 4) {
		return -1;
	}

	unsigned char buffer[8] = { READ_REQUEST, (unsigned char)(index >> 0), (unsigned char)(index >> 8), (unsigned char)subIndex};
	
	can->Lock();
	int ret = can->Write(FC_SDO1_TX + id, buffer, 4 + size);
	if (ret != 4 + size) {
		can->Unlock();	return -1;
	}

	OprosSleep(timeOut);

	long recvId;
	unsigned char recvCommand;
	unsigned short recvIndex;
	unsigned char recvSubIndex;

	if(can->Read(recvId, buffer, 8) < 0) {
		PrintMessage("ERROR : UCMC::ReadObject() -> Can't receive data.\n");
		can->Unlock();	return -1;
	}

	can->Unlock();

	recvCommand = buffer[0];
	recvIndex = buffer[1] | (buffer[2] << 8);
	recvSubIndex = buffer[3];

	switch(size) {
		case 1 :
			if((recvCommand == READ_RESPONSE_MAX4BYTE) || (recvCommand == READ_RESPONSE_1BYTE)) break;
			else 	return -1;
		case 2 :
			if((recvCommand == READ_RESPONSE_MAX4BYTE) || (recvCommand == READ_RESPONSE_2BYTE)) break;
			else	return -1;
		case 4 :
			if((recvCommand == READ_RESPONSE_MAX4BYTE) || (recvCommand == READ_RESPONSE_4BYTE)) break;
			else	return -1;
		default :
			return -1;
	}

	if((recvId != (id | FC_SDO1_RX)) || (recvIndex != index) || (recvSubIndex != subIndex)) {
		return -1;
	}

	memcpy(data, &buffer[4], size);

	return 0;
}

int UCMC::ReadObject(unsigned short index, unsigned char subIndex, char *data, unsigned long timeOut)
{
	return ReadObject(index, subIndex, (unsigned char *)data, 1, timeOut);
}

int UCMC::ReadObject(unsigned short index, unsigned char subIndex, unsigned char *data, unsigned long timeOut)
{
	return ReadObject(index, subIndex, (unsigned char *)data, 1, timeOut);
}

int UCMC::ReadObject(unsigned short index, unsigned char subIndex, short *data, unsigned long timeOut)
{
	return ReadObject(index, subIndex, (unsigned char *)data, 2, timeOut);
}

int UCMC::ReadObject(unsigned short index, unsigned char subIndex, unsigned short *data, unsigned long timeOut)
{
	return ReadObject(index, subIndex, (unsigned char *)data, 2, timeOut);
}

int UCMC::ReadObject(unsigned short index, unsigned char subIndex, long *data, unsigned long timeOut)
{
	return ReadObject(index, subIndex, (unsigned char *)data, 4, timeOut);
}

int UCMC::ReadObject(unsigned short index, unsigned char subIndex, unsigned long *data, unsigned long timeOut)
{
	return ReadObject(index, subIndex, (unsigned char *)data, 4, timeOut);
}

int UCMC::UCMC_GetDeviceType(unsigned long *deviceType)
{
	return ReadObject(UCMC_DEVICE_TYPE, deviceType);
}

int UCMC::UCMC_GetDeviceVersion(double *softwareVersion, double *hardwareVersion)
{
	unsigned long version;

	if(!ReadObject(UCMC_PRODUCT_CODE, &version)) {
		return false;
	}

	*softwareVersion = (double)((0x0000FF00 & version) >> 8) + (double)(0x000000FF & version) * 0.1;
	*hardwareVersion = (double)((0xFF000000 & version) >> 24) + (double)((0x00FF0000 & version) >> 16) * 0.1;

	return true;
}

///////////////////////////////////////////////////////////////////////////////
//
//	Command, Operation Mode and Status Functions for UCMC Servo Controller
//
///////////////////////////////////////////////////////////////////////////////

int UCMC::UCMC_ResetVariables()
{
	// 제어기의 내부 동작 변수들을 초기화 한다. 
	// 초기화 되는 변수는 아래와 같다.
	//   mode, status, error and error code
	//   current/velocity/position/homing control
	//   genreral purpose digital input/output
	_mode = 0x00;
	return WriteObject(UCMC_CONTROL_WORD, (unsigned char)UCMC_RESET);
}

int UCMC::UCMC_EnableMotorPower()
{
	return WriteObject(UCMC_CONTROL_WORD, (unsigned char)UCMC_EN_SERVO);
}

int UCMC::UCMC_DisableMotorPower()
{
	return WriteObject(UCMC_CONTROL_WORD, (unsigned char)UCMC_DI_SERVO);
}

int UCMC::UCMC_QuickStop()
{
	return WriteObject(UCMC_CONTROL_WORD, (unsigned char)UCMC_QUICK_STOP);
}

int UCMC::UCMC_StartHoming()
{
	_mode = 0x00;
	UCMC_SetMode(UCMC_MODE_PRO_POS);
	return WriteObject(UCMC_CONTROL_WORD, (unsigned char)UCMC_START_HOMING);
}

int UCMC::UCMC_ClearError()
{
	return WriteObject(UCMC_CONTROL_WORD, (unsigned char)UCMC_CLEAR_ERROR);
}

int UCMC::UCMC_SetNodeID(long id)
{
	return WriteObject(UCMC_COMMUNICATION_ID, id);
}

int UCMC::UCMC_SaveToEEPROM(void)
{
	return WriteObject(UCMC_CONTROL_WORD, (unsigned char)UCMC_SAVE_TO_EEPROM);
}

int UCMC::UCMC_LoadFromEEPROM(void)
{
	return WriteObject(UCMC_CONTROL_WORD, (unsigned char)UCMC_LOAD_FROM_EEPROM);
}

int UCMC::UCMC_GetStatus(unsigned short * status)
{
	return ReadObject(UCMC_STATUS_WORD, status);
}

int UCMC::UCMC_GetErrorRegister(unsigned char * error)
{
	return ReadObject(UCMC_ERROR_REGISTER, error);
}

int UCMC::UCMC_GetDeviceError(unsigned short *error)
{
	return ReadObject(UCMC_DEVICE_ERROR, error);
}

////////////////////////////////////////////////////////////////////////////////
//
// operating mode for UCMC Servo Controller
//
////////////////////////////////////////////////////////////////////////////////
int UCMC::UCMC_SetMode(unsigned char mode)
{
	if(this->_mode == mode) {
		return 0;
	}

	if(WriteObject(UCMC_MODES_OF_OPERATION, mode) < 0)	
	{
		PrintMessage("ERROR : UCMC::UCMC_SetMode()\n");
		return -1;
	}
	
	PrintMessage("INFO : UCMC::UCMC_SetMode() -> Mode is changed.\n");
	this->_mode = mode;

	UCMC_EnableMotorPower();
	
	return 0;
}

int UCMC::UCMC_GetMode(unsigned char *mode)
{
	if(ReadObject(UCMC_MODES_OF_OPERATION, mode) < 0) {
		PrintMessage("ERROR : UCMC::UCMC_GetMode()\n");
		return -1;
	}
	
	this->_mode = *mode;
	
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//
//	Current Control Functions for UCMC Servo Controller
//
///////////////////////////////////////////////////////////////////////////////
int UCMC::UCMC_SetContinuousCurrent(unsigned long current)
{
	return WriteObject(UCMC_CONTINUOUS_CURRENT_LIMIT, current);
}

int UCMC::UCMC_GetContinuousCurrent(unsigned long *current)
{
	return ReadObject(UCMC_CONTINUOUS_CURRENT_LIMIT, current);
}

int UCMC::UCMC_SetOutputCurrent(unsigned long current)
{
	return WriteObject(UCMC_OUTPUT_CURRENT_LIMIT, current);
}

int UCMC::UCMC_GetOutputCurrent(unsigned long *current)
{
	return ReadObject(UCMC_OUTPUT_CURRENT_LIMIT, current);
}
	
int UCMC::UCMC_SetCurrentPGain(short pGain)
{
	return WriteObject(UCMC_CURRENT_REGULATOR_P_GAIN, pGain);
}

int UCMC::UCMC_GetCurrentPGain(short *pGain)
{
	return ReadObject(UCMC_CURRENT_REGULATOR_P_GAIN, (unsigned short *)pGain);
}

int UCMC::UCMC_SetCurrentIGain(short iGain)
{
	return WriteObject(UCMC_CURRENT_REGULATOR_I_GAIN, iGain);
}

int UCMC::UCMC_GetCurrentIGain(short *iGain)
{
	return ReadObject(UCMC_CURRENT_REGULATOR_I_GAIN, (unsigned short *)iGain);
}

int UCMC::UCMC_SetTargetCurrent(long current)
{
	// !!! 제어기의 모드 변수를 제어S/W에서 가지고 있으면 안된다.
	// !!! 어떠한 이유로 제어기가 모드를 스스로 변경하는 경우가 있다.
	unsigned char mode;
	UCMC_GetMode((unsigned char *)&mode);

	UCMC_SetMode(UCMC_MODE_CUR);
	return WriteObject(UCMC_TARGET_CURRENT, current);
}

int UCMC::UCMC_GetActualCurrent(long *current)
{
	return ReadObject(UCMC_CURRENT_ACTUAL_VALUE, (unsigned long *)current);
}

int UCMC::UCMC_GetAveragedCurrent(long *current)
{
	return ReadObject(UCMC_CURRENT_ACTUAL_VALUE_AVERAGED, (unsigned long *)current);
}

///////////////////////////////////////////////////////////////////////////////
//
//	Velocity Control Functions for UCMC Servo Controller
//
///////////////////////////////////////////////////////////////////////////////
int UCMC::UCMC_SetEncoderCount(short encoderCount)
{
	return WriteObject(UCMC_ENCODER_PULSE_NUMBER, encoderCount);
}

int UCMC::UCMC_GetEncoderCount(short* encoderCount)
{
	return ReadObject(UCMC_ENCODER_PULSE_NUMBER, (unsigned short *)encoderCount);
}

int UCMC::UCMC_SetMaxVelocity(short velocity)
{
	return WriteObject(UCMC_MAX_VELOCITY, (unsigned short)velocity);
}

int UCMC::UCMC_GetMaxVelocity(short *velocity)
{
	return ReadObject(UCMC_MAX_VELOCITY, (unsigned short *)velocity);
}

int UCMC::UCMC_SetProfileVelocity(short velocity)
{
	return WriteObject(UCMC_PROFILE_VELOCITY, velocity);
}

int UCMC::UCMC_GetProfileVelocity(short *profileVelocity)
{
	return ReadObject(UCMC_PROFILE_VELOCITY, (unsigned short *)profileVelocity);
}

int UCMC::UCMC_SetAcceleration(long acceleration)
{
	return WriteObject(UCMC_PROFILE_ACCELERATION, acceleration);
}

int UCMC::UCMC_GetAcceleration(long *acceleration)
{
	return ReadObject(UCMC_PROFILE_ACCELERATION, (unsigned long *)acceleration);
}

int UCMC::UCMC_GetDeceleration(long *deceleration)
{
	return ReadObject(UCMC_PROFILE_DECELERATION, (unsigned long *)deceleration);
}

int UCMC::UCMC_SetDeceleration(long deceleration)
{
	return WriteObject(UCMC_PROFILE_DECELERATION, deceleration);
}

int UCMC::UCMC_SetQuickStopDeceleration(long quickStopDeceleration)
{
	return WriteObject(UCMC_QUICKSTOP_DECELERATION, quickStopDeceleration);
}

int UCMC::UCMC_GetQuickStopDeceleration(long *quickStopDeceleration)
{
	return ReadObject(UCMC_QUICKSTOP_DECELERATION, (unsigned long *)quickStopDeceleration);
}

int UCMC::UCMC_SetVelocityPGain(short pGain)
{
	return WriteObject(UCMC_SPEED_REGULATOR_P_GAIN, pGain);
}

int UCMC::UCMC_GetVelocityPGain(short *pGain)
{
	return ReadObject(UCMC_SPEED_REGULATOR_P_GAIN, (unsigned short *)pGain);
}

int UCMC::UCMC_SetVelocityIGain(short iGain)
{
	return WriteObject(UCMC_SPEED_REGULATOR_I_GAIN, iGain);
}

int UCMC::UCMC_GetVelocityIGain(short *iGain)
{
	return ReadObject(UCMC_SPEED_REGULATOR_I_GAIN, (unsigned short *)iGain);
}

int UCMC::UCMC_SetVelocityDGain(short dGain)
{
	return WriteObject(UCMC_SPEED_REGULATOR_D_GAIN, dGain);
}

int UCMC::UCMC_GetVelocityDGain(short *dGain)
{
	return ReadObject(UCMC_SPEED_REGULATOR_D_GAIN, (unsigned short *)dGain);
}

int UCMC::UCMC_SetTargetVelocity(short velocity)
{
	// !!! 제어기의 모드 변수를 제어S/W에서 가지고 있으면 안된다.
	// !!! 어떠한 이유로 제어기가 모드를 스스로 변경하는 경우가 있다.
	unsigned char mode;
	UCMC_GetMode((unsigned char *)&mode);

	UCMC_SetMode(UCMC_MODE_VEL);
	return WriteObject(UCMC_REFERENCE_VELOCITY, velocity);
}

int UCMC::UCMC_GetActualVelocity(short *velocity)
{
	return ReadObject(UCMC_VELOCITY_ACTUAL_VALUE, (unsigned short *)velocity);
}


int UCMC::UCMC_SetProfileTargetVelocity(short profileTargetVelocity)
{
	// !!! 제어기의 모드 변수를 제어S/W에서 가지고 있으면 안된다.
	// !!! 어떠한 이유로 제어기가 모드를 스스로 변경하는 경우가 있다.
	unsigned char mode;
	UCMC_GetMode((unsigned char *)&mode);

	UCMC_SetMode(UCMC_MODE_PRO_VEL);
	return WriteObject(UCMC_PROFILE_TARGET_VELOCITY, profileTargetVelocity);
}

int UCMC::UCMC_GetProfileTargetVelocity(short *profileTargetVelocity)
{
	return ReadObject(UCMC_PROFILE_TARGET_VELOCITY, (unsigned short *)profileTargetVelocity);
}

///////////////////////////////////////////////////////////////////////////////
//
//	Position Control Functions for UCMC Servo Controller
//
///////////////////////////////////////////////////////////////////////////////
int UCMC::UCMC_SetNegativePositionLimit(long position)
{
	return WriteObject(UCMC_MIN_POSITION_LIMIT, position);
}

int UCMC::UCMC_GetNegativePositionLimit(long *position)
{
	return ReadObject(UCMC_MIN_POSITION_LIMIT, (unsigned long *)position);
}

int UCMC::UCMC_SetPositivePositionLimit(long position)
{
	return WriteObject(UCMC_MAX_POSITION_LIMIT, position);
}

int UCMC::UCMC_GetPositivePositionLimit(long *position)
{
	return ReadObject(UCMC_MAX_POSITION_LIMIT, (unsigned long *)position);
}

int UCMC::UCMC_SetPositionPGain(short pGain)
{
	return WriteObject(UCMC_POSITION_REGULATOR_P_GAIN, pGain);
}

int UCMC::UCMC_GetPositionPGain(short *pGain)
{
	return ReadObject(UCMC_POSITION_REGULATOR_P_GAIN, (unsigned short *)pGain);
}

int UCMC::UCMC_SetPositionIGain(short iGain)
{
	return WriteObject(UCMC_POSITION_REGULATOR_I_GAIN, iGain);
}

int UCMC::UCMC_GetPositionIGain(short *iGain)
{
	return ReadObject(UCMC_POSITION_REGULATOR_I_GAIN, (unsigned short *)iGain);
}

int UCMC::UCMC_SetPositionDGain(short dGain)
{
	return WriteObject(UCMC_POSITION_REGULATOR_D_GAIN, dGain);
}

int UCMC::UCMC_GetPositionDGain(short *dGain)
{
	return ReadObject(UCMC_POSITION_REGULATOR_D_GAIN, (unsigned short *)dGain);
}

int UCMC::UCMC_SetProfileTargetPosition(long profilePosition)
{
	// !!! 제어기의 모드 변수를 제어S/W에서 가지고 있으면 안된다.
	// !!! 어떠한 이유로 제어기가 모드를 스스로 변경하는 경우가 있다.
	unsigned char mode;
	UCMC_GetMode((unsigned char *)&mode);

	UCMC_SetMode(UCMC_MODE_PRO_POS);
	return WriteObject(UCMC_PROFILE_TARGET_POSITION, profilePosition);
}

int UCMC::UCMC_GetProfileTargetPosition(long *profilePosition)
{
	return ReadObject(UCMC_PROFILE_TARGET_POSITION, (unsigned long *)profilePosition);
}

int UCMC::UCMC_SetTargetPosition(long targetPosition)
{
	// !!! 제어기의 모드 변수를 제어S/W에서 가지고 있으면 안된다.
	// !!! 어떠한 이유로 제어기가 모드를 스스로 변경하는 경우가 있다.
	unsigned char mode;
	UCMC_GetMode((unsigned char *)&mode);

	UCMC_SetMode(UCMC_MODE_POS);
	return WriteObject(UCMC_REFERENCE_POSITION, targetPosition);
}

int UCMC::UCMC_GetTargetPosition(long *targetPosition)
{
	return ReadObject(UCMC_REFERENCE_POSITION, (unsigned long *)targetPosition);
}

int UCMC::UCMC_SetActualPosition(long position)
{
	return WriteObject(UCMC_POSITION_ACTUAL_VALUE, position);
}

int UCMC::UCMC_GetActualPosition(long *position)
{
	return ReadObject(UCMC_POSITION_ACTUAL_VALUE, (unsigned long *)position);
}

int UCMC::UCMC_GetAbsolutePosition(long *position)
{
	return ReadObject(UCMC_ABSOLUTE_POSITION, (unsigned long *)position);
}

int UCMC::UCMC_SetHomingMethod(unsigned char homingMethod)
{
	return WriteObject(UCMC_HOMING_METHOD, homingMethod);
}

int UCMC::UCMC_GetHomingMethod(unsigned char *homingMethod)
{
	return ReadObject(UCMC_HOMING_METHOD, homingMethod);
}

int UCMC::UCMC_SetSwitchSearchVelocity(short velocity)
{
	return WriteObject(UCMC_SPEED_FOR_SWITCH_SEARCH, velocity);
}

int UCMC::UCMC_GetSwitchSearchVelocity(short *velocity)
{
	return ReadObject(UCMC_SPEED_FOR_SWITCH_SEARCH, (unsigned short *)velocity);
}

int UCMC::UCMC_SetZeroSearchVelocity(short velocity)
{
	return WriteObject(UCMC_SPEED_FOR_ZERO_SEARCH, velocity);
}

int UCMC::UCMC_GetZeroSearchVelocity(short *velocity)
{
	return ReadObject(UCMC_SPEED_FOR_ZERO_SEARCH, (unsigned short *)velocity);
}

int UCMC::UCMC_GetDI(unsigned long *di)
{
	return ReadObject(UCMC_DI_0, di);
}

int UCMC::UCMC_GetAI(unsigned short *ai)
{
	return ReadObject(UCMC_AI_0, ai);
}


///////////////////////////////////////////////////////////////////////////////
//
//	Interpolation Mode Functions for UCMC Servo Controller
//
///////////////////////////////////////////////////////////////////////////////

int UCMC::UCMC_SynchronizeObject(unsigned char syncOption, unsigned short *status, long *position, short *velocity, long *current)
{
	long recv_id;
	unsigned char data[17] = {0x01, syncOption};
	int len = 2;

	if((syncOption & 0x0F) == UCMC_SYNC_SET_NONE) {
	}
	else if((syncOption & 0x0F) == UCMC_SYNC_SET_CURRENT) {
		*(long *)&data[len] = *current;
		len += 4;
		UCMC_SetMode(UCMC_MODE_CUR);
	}
	else if((syncOption & 0x0F) == UCMC_SYNC_SET_VELOCITY) {
		*(short *)&data[len] = *velocity;
		len += 2;
		UCMC_SetMode(UCMC_MODE_VEL);
	}
	else if((syncOption & 0x0F) == UCMC_SYNC_SET_POSITION) {
		*(long *)&data[len] = *position;
		len += 4;
		UCMC_SetMode(UCMC_MODE_POS);
	}

	//	Lock Code 필요

	if(can->Write(id + 0x600, data, len) != len) {
		return false;
	}
	
	len = 0;

	if((syncOption & UCMC_SYNC_GET_STATUS) == UCMC_SYNC_GET_STATUS) {
		len += 2;
	}
	if((syncOption & UCMC_SYNC_GET_CURRENT) == UCMC_SYNC_GET_CURRENT) {
		len += 4;
	}
	if((syncOption & UCMC_SYNC_GET_VELOCITY) == UCMC_SYNC_GET_VELOCITY) {
		len += 2;
	}
	if((syncOption & UCMC_SYNC_GET_POSITION) == UCMC_SYNC_GET_POSITION) {
		len += 4;
	}

	for (int i=0; i<len; i+=8) {
		int n = min_val(8, len-i);
		if(can->Read(recv_id, &data[i], n) != n) {
			return false;
		}
	}

	len = 0;

	if((syncOption & UCMC_SYNC_GET_STATUS) == UCMC_SYNC_GET_STATUS) {
		*status = *(unsigned short *)&data[len];		
		len += 2;
	}
	if((syncOption & UCMC_SYNC_GET_CURRENT) == UCMC_SYNC_GET_CURRENT) {
		*current = *(long *)&data[len];
		len += 4;
	}
	if((syncOption & UCMC_SYNC_GET_VELOCITY) == UCMC_SYNC_GET_VELOCITY) {
		*velocity = *(short *)&data[len];
		len += 2;
	}
	if((syncOption & UCMC_SYNC_GET_POSITION) == UCMC_SYNC_GET_POSITION) {
		*position = *(long *)&data[len];
		len += 4;
	}
	return true;
}
