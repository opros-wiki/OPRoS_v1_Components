#pragma once

#include "UART.h"
#include "RobotisDynamixelUARTDef.h"

class RobotisDynamixelUART
{
public:
	RobotisDynamixelUART(int nodeID, UART *uart);
	virtual ~RobotisDynamixelUART(void);

	// 변환 비율
	// 위치(position)    : 0 ~ 1023 = 0 ~ 300 deg
	// 속도(velocity)    : 0 ~ 1023 = 0 ~ 70 rpm
	// 부하(load, torque): 0 ~ 1023 = 0 ~ 100 percent
	// 전압(voltage)     : 0 ~ 250  = 0 ~ 25 volt
	void SetConfiguration (unsigned short cwAngleLimits, unsigned short ccwAngleLimits, unsigned short velocityLimit, unsigned short torqueLimits);

	bool EnableTorque(void);
	bool DisableTorque(void);

	bool SetReturnDelay (unsigned char value);
	bool SetCwanglelimit (unsigned short angle);
	bool SetCcwanglelimit (unsigned short angle);
	bool SetHighLimitTemp (unsigned char value);
	bool SetLowLimitVoltage (unsigned char value);
	bool SetHighLimitVoltage (unsigned char value);
	bool SetStatusReturn (unsigned char value);
	bool SetAlarmLED (unsigned char value);
	bool SetAlarmShutdown (unsigned char value);
	bool SetGoalposition (unsigned short angle);
	bool SetGoalpositionReg (unsigned short angle);
	bool SetMovingspeed (unsigned short angle);
	bool SetTorquelimit (unsigned short torque);

	bool IsMoving (bool *moving);
	bool GetCwanglelimit (unsigned short *angle);
	bool GetCcwanglelimit (unsigned short *angle);
	bool GetGoalposition (unsigned short *angle);
	bool GetMovingspeed (unsigned short *speed);
	bool GetTorquelimit (unsigned short *torque);
	bool GetPresentposition (unsigned short *angle);
	bool GetPresentspeed (unsigned short *speed);
	bool GetPresentload (unsigned short *load);
	bool GetPresentvoltage (unsigned char *voltage);
	bool GetPresenttemperature (unsigned char *temperature);

	bool SetGoalpositionSync_Broadcast (int size, unsigned short *position, unsigned char *id);
	

private:
	UART *uart;
	int nodeID;
	unsigned char _deviceStatus;

private:
	unsigned char Checksum(unsigned char *buf, int dataSize);

	int SendPacket (unsigned char *data, int dataSize);
	int ReceivePacket (unsigned char *data, int dataSize);
	bool Transaction (unsigned char *sendPacket, int sendPacketSize);
	bool Transaction (unsigned char *sendPacket, int sendPacketSize, unsigned char *receivePacket, int receivePacketSize);

protected:
	bool Ping ();
	bool ResetMemory ();
	bool WriteByte (unsigned char index, unsigned char data);
	bool WriteReg (unsigned char index, unsigned short data);
	bool WriteBytes (unsigned char index, unsigned char *data, int dataSize, int len = 1, bool sync_flag = false);
	bool WriteWord (unsigned char index, unsigned short data);
	bool ReadByte (unsigned char index, unsigned char *data);
	bool ReadBytes (unsigned char index, unsigned char *data, int dataSize);
	bool ReadWord (unsigned char index, unsigned short *data);
};
