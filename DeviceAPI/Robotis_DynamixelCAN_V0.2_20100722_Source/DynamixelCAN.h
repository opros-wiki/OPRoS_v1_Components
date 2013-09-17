#pragma once

#include "CAN.h"

class DynamixelCAN
{
public:
	DynamixelCAN(long id, CAN *can);
	virtual ~DynamixelCAN(void);

private:
	CAN *_can;
	long _id;
	unsigned char canStdHostId;

public:
	unsigned char CheckSum(unsigned char *buf, int len);
	int Transaction(unsigned char *send_data, int send_len, unsigned char recv_data[8], int recv_len = -1);
	int Transaction(unsigned char *send_data, int send_len);

	int WriteByte (unsigned char address, unsigned char data);
	int WriteBytes (unsigned char address, unsigned char *data, int len);
	int WriteWord (unsigned char address, unsigned short data);
	int ReadByte (unsigned char address, unsigned char *data);
	int ReadBytes (unsigned char address, unsigned char *data, int len);
	int ReadWord (unsigned char address, unsigned short *data);
	
	//	EEPROM Area
	int GetModelNumber(unsigned short modelNumber[]);
	int GetVersion(unsigned char version[]);
	int SetID(unsigned char id);
	int GetID(unsigned char id[]);
	int SetBaudRate(unsigned char baudRate);
	int GetBaudRate(unsigned char baudRate[]);
	int SetReturnDealyTime(unsigned char dealyTime);
	int GetReturnDealyTime(unsigned char dealyTime[]);
	int SetCWAngleLimit(unsigned short cwAngleLimit);
	int GetCWAngleLimit(unsigned short cwAngleLimit[]);
	int SetCCWAngleLimit(unsigned short ccwAngleLimit);
	int GetCCWAngleLimit(unsigned short ccwAngleLimit[]);
	int SetHighLimitTemp(unsigned char highLimitTemp);
	int GetHighLimitTemp(unsigned char highLimitTemp[]);
	int SetLowLimitVolt(unsigned char lowLimitVolt);
	int GetLowLimitVolt(unsigned char lowLimitVolt[]);
	int SetHighLimitVolt(unsigned char highLimitVolt);
	int GetHighLimitVolt(unsigned char highLimitVolt[]);
	int SetMaxTorque(unsigned short maxTorque);
	int GetMaxTorque(unsigned short maxTorque[]);
	int SetStatusReturnLevel(unsigned char statusReturnLevel);
	int GetStatusReturnLevel(unsigned char statusReturnLevel[]);
	int SetAlarmLed(unsigned char alarmLed);
	int GetAlarmLed(unsigned char alarmLed[]);
	int SetAlarmShutdown(unsigned char alarmShutdown);
	int GetAlarmShutdown(unsigned char alarmShutdown[]);
	int GetDownCalibration(unsigned short downCalibration[]);
	int GetUpCalibration(unsigned short upCalibration[]);
	//	RAM Area
	int SetTorqueEnable(unsigned char torqueEnable);
	int GetTorqueEnable(unsigned char torqueEnable[]);
	int SetLed(unsigned char led);
	int GetLed(unsigned char led[]);
	int SetCWComplianceMargin(unsigned char cwComplianceMargin);
	int GetCWComplianceMargin(unsigned char cwComplianceMargin[]);
	int SetCCWComplianceMargin(unsigned char ccwComplianceMargin);
	int GetCCWComplianceMargin(unsigned char ccwComplianceMargin[]);
	int SetCWComplianceSlope(unsigned char cwComplianceSlope);
	int GetCWComplianceSlope(unsigned char cwComplianceSlope[]);
	int SetCCWComplianceSlope(unsigned char ccwComplianceSlope);
	int GetCCWComplianceSlope(unsigned char ccwComplianceSlope[]);
	int SetGoalPosition(unsigned short goalPosition);
	int GetGoalPosition(unsigned short goalPosition[]);
	int SetMovingSpeed(unsigned short movingSpeed);
	int GetMovingSpeed(unsigned short movingSpeed[]);
	int SetTorqueLimit(unsigned short torqueLimit);
	int GetTorqueLimit(unsigned short torqueLimit[]);
	int GetPresentPosition(unsigned short presentPosition[]);
	int GetPresentSpeed(unsigned short presentSpeed[]);
	int GetPresentLoad(unsigned short presentLoad[]);
	int GetPresentVolt(unsigned char presentVolt[]);
	int GetPresentTemp(unsigned char presentTemp[]);
	int SetRegisterInstruction(unsigned char registeredInstructino);
	int GetRegisterInstruction(unsigned char registeredInstructino[]);
	int GetMoving(unsigned char moving[]);
	int SetLock(unsigned char lock);
	int GetLock(unsigned char lock[]);
	int SetPunch(unsigned short punch);
	int GetPunch(unsigned short punch[]);
};
