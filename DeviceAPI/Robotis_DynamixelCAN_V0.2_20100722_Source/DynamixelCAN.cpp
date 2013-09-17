#include <assert.h>
#include <string.h>

#include "DynamixelCAN.h"
#include "DynamixelCANDef.h"

#define RETRY_COUNT		3

DynamixelCAN::DynamixelCAN(long id, CAN *can)
{
	_id = id;
	_can = can;
}

DynamixelCAN::~DynamixelCAN(void)
{
	_can = NULL;
}

unsigned char DynamixelCAN::CheckSum(unsigned char *buf, int len)
{
	int i;
	unsigned char result = 0;

	for(i = 0; i < len; ++i) {
		result += *(buf + i);
	}

	return ~result;
}

int DynamixelCAN::Transaction(unsigned char *send_data, int send_len, unsigned char recv_data[8], int recv_len)
{
	int i;
	int ret;
	unsigned char temp[8];
	long recv_id;
	
	if (!send_data) {
		send_data = temp;
	}
	if (!recv_data) {
		recv_data = temp;
	}

	if(_can == NULL) {
		return -1;
	}

	_can->Lock();

	for (i=0; i < RETRY_COUNT; ++i) {
		std::valarray<unsigned char> buf(send_len);
		memcpy(&buf[0], send_data, send_len);
		ret = _can->Write(_id, &buf[0], send_len);

		if(0 <= ret) {
			valarray<unsigned char> buf(8);
			ret = _can->Read(recv_id, &buf[0], 8);
			memcpy(recv_data, &buf[8], (buf.size() <= 8) ? (int)buf.size() : 8);
			if (0 <= ret) {
				if ((2 <= ret) && (recv_id == canStdHostId) && (send_len == -1 || recv_len == ret)) {
					break;
				}
			}
		}
	}

	_can->Unlock();
	
	return ret;
}

int DynamixelCAN::Transaction(unsigned char *send_data, int send_len)
{
	int i;
	int ret;

	if(_can == NULL) {
		return -1;
	}
	
	_can->Lock();

	for (i = 0; i < RETRY_COUNT; ++i) {
		valarray<unsigned char> buf(send_len);
		memcpy(&buf[0], send_data, send_len);
		ret = _can->Write(_id, &buf[0], send_len);
		if(0 <= ret) {
			break;
		}
	}
	
	_can->Unlock();

	return ret;
}

int DynamixelCAN::WriteByte (unsigned char address, unsigned char data)
{
	unsigned char packet[8];

	packet[0] = 4;
	packet[1] = WRITE_DATA;
	packet[2] = address;
	packet[3] = data;
	packet[4] = CheckSum (&packet[0], 4);

	return Transaction (packet, 5);
}

int DynamixelCAN::WriteBytes (unsigned char address, unsigned char *data, int len)
{
	assert (len <= 8 - 4);

	unsigned char packet[8];

	packet[0] = 3+len;
	packet[1] = WRITE_DATA;
	packet[2] = address;
	memcpy(&packet[3], data, len);
	packet[3+len] = CheckSum (&packet[0], 3+len);

	return Transaction (packet, 4+len);
}

int DynamixelCAN::WriteWord (unsigned char address, unsigned short data)
{
	unsigned char packet[8];

	packet[0] = 5;
	packet[1] = WRITE_DATA;
	packet[2] = address;
	packet[3] = (unsigned char)(data >> 0);
	packet[4] = (unsigned char)(data >> 8);
	packet[5] = CheckSum (&packet[0], 5);

	return Transaction (packet, 6);
}

int DynamixelCAN::ReadByte (unsigned char address, unsigned char *data)
{
	unsigned char packet[8];

	packet[0] = 4;
	packet[1] = READ_DATA;
	packet[2] = address;
	packet[3] = 1;
	packet[4] = CheckSum (&packet[0], 4);

	if (Transaction (packet, 5, packet, 5) == 5) {
		*data = packet[3];
		return 0;
	}

	return -1;
}

int DynamixelCAN::ReadBytes (unsigned char address, unsigned char *data, int len)
{
	assert (len <= 8 - 4);

	unsigned char packet[8];

	packet[0] = 4;
	packet[1] = READ_DATA;
	packet[2] = address;
	packet[3] = len;
	packet[4] = CheckSum (&packet[0], 4);

	if (Transaction (packet, 5, packet, 4+len) == 4+len) {
		memcpy (data, &packet[3], len);
		return 0;
	}

	return -1;
}

int DynamixelCAN::ReadWord (unsigned char address, unsigned short *data)
{
	unsigned char packet[8];

	packet[0] = 4;
	packet[1] = READ_DATA;
	packet[2] = address;
	packet[3] = 2;
	packet[4] = CheckSum (&packet[0], 4);

	if (Transaction (packet, 5, packet, 6) == 6) {
		*data = 
			((unsigned short)packet[3] << 0) | 
			((unsigned short)packet[4] << 8);
		return 0;
	}

	return -1;
}

int DynamixelCAN::GetModelNumber(unsigned short modelNumber[])
{
	return ReadWord(DynamixelCAN_MODEL_NUMBER_W, modelNumber);
}

int DynamixelCAN::GetVersion(unsigned char version[])
{
	return ReadByte(DynamixelCAN_VERSION_OF_FIRMWARE, version);
}

int DynamixelCAN::SetID(unsigned char id)
{
	return WriteByte(DynamixelCAN_ID, id);
}

int DynamixelCAN::GetID(unsigned char id[])
{
	return ReadByte(DynamixelCAN_ID, id);
}

int DynamixelCAN::SetBaudRate(unsigned char baudRate)
{
	//return WriteByte(DynamixelCAN_BAUDRATE, baudRate);
	return -1;
}

int DynamixelCAN::GetBaudRate(unsigned char buadRate[])
{
	//return ReadByte(DynamixelCAN_BAUDRATE, baudRate);
	return -1;
}

int DynamixelCAN::SetReturnDealyTime(unsigned char dealyTime)
{
	return WriteByte(DynamixelCAN_RETURN_DELAY_TIME, dealyTime);
}

int DynamixelCAN::GetReturnDealyTime(unsigned char dealyTime[])
{
	return ReadByte(DynamixelCAN_RETURN_DELAY_TIME, dealyTime);
}

int DynamixelCAN::SetCWAngleLimit(unsigned short cwAngleLimit)
{
	return WriteWord(DynamixelCAN_CW_ANGLE_LIMIT_W, cwAngleLimit);
}

int DynamixelCAN::GetCWAngleLimit(unsigned short cwAngleLimit[])
{
	return ReadWord(DynamixelCAN_CW_ANGLE_LIMIT_W, cwAngleLimit);
}

int DynamixelCAN::SetCCWAngleLimit(unsigned short ccwAngleLimit)
{
	return WriteWord(DynamixelCAN_CCW_ANGLE_LIMIT_W, ccwAngleLimit);
}

int DynamixelCAN::GetCCWAngleLimit(unsigned short ccwAngleLimit[])
{
	return ReadWord(DynamixelCAN_CCW_ANGLE_LIMIT_W, ccwAngleLimit);
}

int DynamixelCAN::SetHighLimitTemp(unsigned char highLimitTemp)
{
	return WriteByte(DynamixelCAN_HIGHTEST_LIMIT_TEMPERATURE, highLimitTemp);
}

int DynamixelCAN::GetHighLimitTemp(unsigned char highLimitTemp[])
{
	return ReadByte(DynamixelCAN_HIGHTEST_LIMIT_TEMPERATURE, highLimitTemp);
}

int DynamixelCAN::SetLowLimitVolt(unsigned char lowLimitVolt)
{
	return WriteByte(DynamixelCAN_LOWEST_LIMIT_VOLTAGE, lowLimitVolt);
}

int DynamixelCAN::GetLowLimitVolt(unsigned char lowLimitVolt[])
{
	return ReadByte(DynamixelCAN_LOWEST_LIMIT_VOLTAGE, lowLimitVolt);
}

int DynamixelCAN::SetHighLimitVolt(unsigned char highLimitVolt)
{
	return WriteByte(DynamixelCAN_HIGHEST_LIMIT_VOLTAGE, highLimitVolt);
}

int DynamixelCAN::GetHighLimitVolt(unsigned char highLimitVolt[])
{
	return ReadByte(DynamixelCAN_HIGHEST_LIMIT_VOLTAGE, highLimitVolt);
}

int DynamixelCAN::SetMaxTorque(unsigned short maxTorque)
{
	if(maxTorque == 1024) {
		maxTorque = 0;
	}
	else if(maxTorque == 0) {
		maxTorque = 1;
	}

	return WriteWord(DynamixelCAN_MAX_TORQUE_W, maxTorque);
}

int DynamixelCAN::GetMaxTorque(unsigned short maxTorque[])
{
	return ReadWord(DynamixelCAN_MAX_TORQUE_W, maxTorque);
}

int DynamixelCAN::SetStatusReturnLevel(unsigned char statusReturnLevel)
{
	return WriteByte(DynamixelCAN_STATUS_RETURN_VALUE, statusReturnLevel);
}

int DynamixelCAN::GetStatusReturnLevel(unsigned char statusReturnLevel[])
{
	return ReadByte(DynamixelCAN_STATUS_RETURN_VALUE, statusReturnLevel);
}

int DynamixelCAN::SetAlarmLed(unsigned char alarmLed)
{
	return WriteByte(DynamixelCAN_ALARM_LED, alarmLed);
}

int DynamixelCAN::GetAlarmLed(unsigned char alarmLed[])
{
	return ReadByte(DynamixelCAN_ALARM_LED, alarmLed);
}

int DynamixelCAN::SetAlarmShutdown(unsigned char alarmShutdown)
{
	return WriteByte(DynamixelCAN_ALARM_SHUTDOWN, alarmShutdown);
}

int DynamixelCAN::GetAlarmShutdown(unsigned char alarmShutdown[])
{
	return ReadByte(DynamixelCAN_ALARM_SHUTDOWN, alarmShutdown);
}

int DynamixelCAN::GetDownCalibration(unsigned short downCalibration[])
{
	return ReadWord(DynamixelCAN_DOWN_CALIBRATION_W, downCalibration);
}

int DynamixelCAN::GetUpCalibration(unsigned short upCalibration[])
{
	return ReadWord(DynamixelCAN_UP_CALIBRATION_W, upCalibration);
}

int DynamixelCAN::SetTorqueEnable(unsigned char torqueEnable)
{
	return WriteByte(DynamixelCAN_TORQUE_EABLE, torqueEnable);
}

int DynamixelCAN::GetTorqueEnable(unsigned char torqueEnable[])
{
	return ReadByte(DynamixelCAN_TORQUE_EABLE, torqueEnable);
}

int DynamixelCAN::SetLed(unsigned char led)
{
	return WriteByte(DynamixelCAN_LED, led);
}

int DynamixelCAN::GetLed(unsigned char led[])
{
	return ReadByte(DynamixelCAN_LED, led);
}

int DynamixelCAN::SetCWComplianceMargin(unsigned char cwComplianceMargin)
{
	return WriteByte(DynamixelCAN_CW_COMPLIANCE_MARGIN, cwComplianceMargin);
}

int DynamixelCAN::GetCWComplianceMargin(unsigned char cwComplianceMargin[])
{
	return ReadByte(DynamixelCAN_CW_COMPLIANCE_MARGIN, cwComplianceMargin);
}

int DynamixelCAN::SetCCWComplianceMargin(unsigned char ccwComplianceMargin)
{
	return WriteByte(DynamixelCAN_CCW_COMPLIANCE_MARGIN, ccwComplianceMargin);
}

int DynamixelCAN::GetCCWComplianceMargin(unsigned char ccwComplianceMargin[])
{
	return ReadByte(DynamixelCAN_CCW_COMPLIANCE_MARGIN, ccwComplianceMargin);
}

int DynamixelCAN::SetCWComplianceSlope(unsigned char cwComplianceSlope)
{
	return WriteByte(DynamixelCAN_CW_COMPLICANCE_SLOPE, cwComplianceSlope);
}

int DynamixelCAN::GetCWComplianceSlope(unsigned char cwComplianceSlope[])
{
	return ReadByte(DynamixelCAN_CW_COMPLICANCE_SLOPE, cwComplianceSlope);
}

int DynamixelCAN::SetCCWComplianceSlope(unsigned char ccwComplianceSlope)
{
	return WriteByte(DynamixelCAN_CCW_COMPLICANCE_SLOPE, ccwComplianceSlope);
}

int DynamixelCAN::GetCCWComplianceSlope(unsigned char ccwComplianceSlope[])
{
	return ReadByte(DynamixelCAN_CCW_COMPLICANCE_SLOPE, ccwComplianceSlope);
}

int DynamixelCAN::SetGoalPosition(unsigned short goalPosition)
{
	return WriteWord(DynamixelCAN_GOAL_POSITION_W, goalPosition);
}

int DynamixelCAN::GetGoalPosition(unsigned short goalPosition[])
{
	return ReadWord(DynamixelCAN_GOAL_POSITION_W, goalPosition);
}

int DynamixelCAN::SetMovingSpeed(unsigned short movingSpeed)
{
	return WriteWord(DynamixelCAN_MOVING_SPEED_W, movingSpeed);
}

int DynamixelCAN::GetMovingSpeed(unsigned short movingSpeed[])
{
	return ReadWord(DynamixelCAN_MOVING_SPEED_W, movingSpeed);
}

int DynamixelCAN::SetTorqueLimit(unsigned short torqueLimit)
{
	return WriteWord(DynamixelCAN_TORQUE_LIMIT_W, torqueLimit);
}

int DynamixelCAN::GetTorqueLimit(unsigned short torqueLimit[])
{
	return ReadWord(DynamixelCAN_TORQUE_LIMIT_W, torqueLimit);
}

int DynamixelCAN::GetPresentPosition(unsigned short presentPosition[])
{
	return ReadWord(DynamixelCAN_PRESENT_POSITION_W, presentPosition);
}

int DynamixelCAN::GetPresentSpeed(unsigned short presentSpeed[])
{
	return ReadWord(DynamixelCAN_PRESENT_SPEED_W, presentSpeed);
}

int DynamixelCAN::GetPresentLoad(unsigned short presentLoad[])
{
	return ReadWord(DynamixelCAN_PRESENT_LOAD_W, presentLoad);
}

int DynamixelCAN::GetPresentVolt(unsigned char presentVolt[])
{
	return ReadByte(DynamixelCAN_PRESENT_VOLTAGE, presentVolt);
}

int DynamixelCAN::GetPresentTemp(unsigned char presentTemp[])
{
	return ReadByte(DynamixelCAN_PRESETN_TEMPERATURE, presentTemp);
}

int DynamixelCAN::SetRegisterInstruction(unsigned char registeredInstructino)
{
	return WriteByte(DynamixelCAN_REGISTERED_INSTRUCTION, registeredInstructino);
}

int DynamixelCAN::GetRegisterInstruction(unsigned char registeredInstructino[])
{
	return ReadByte(DynamixelCAN_REGISTERED_INSTRUCTION, registeredInstructino);
}

int DynamixelCAN::GetMoving(unsigned char moving[])
{
	return ReadByte(DynamixelCAN_MOVING, moving);
}

int DynamixelCAN::SetLock(unsigned char lock)
{
	return WriteByte(DynamixelCAN_LOCK, lock);
}

int DynamixelCAN::GetLock(unsigned char lock[])
{
	return ReadByte(DynamixelCAN_LOCK, lock);
}

int DynamixelCAN::SetPunch(unsigned short punch)
{
	return WriteWord(DynamixelCAN_PUNCH_W, punch);
}

int DynamixelCAN::GetPunch(unsigned short punch[])
{
	return ReadWord(DynamixelCAN_PUNCH_W, punch);
}