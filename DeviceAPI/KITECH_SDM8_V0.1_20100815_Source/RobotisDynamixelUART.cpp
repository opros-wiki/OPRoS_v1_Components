#include <assert.h>
#include <string.h>

#include "RobotisDynamixelUART.h"
#include "OprosTimer.h"

#define RETRY_COUNT					5
#define TRANSACTION_WRITE_DELAY		6
#define TRANSACTION_READ_DELAY		1
#define TRANSACTION_TIMEOUT			10

#define	MAX_PACKET_SIZE		256
#define MAX_SYNCPACKET_SIZE	143

// RX64모터의 엔코더는 300도 회전할 동안 1023 펄스 발생
#define ENCODER_RESOLUTION		(long)(360.*1023/300)

RobotisDynamixelUART::RobotisDynamixelUART(int nodeID, UART *uart)
{
	this->nodeID = nodeID;
	this->uart = uart;
}

RobotisDynamixelUART::~RobotisDynamixelUART(void)
{
	nodeID = -1;
	uart = NULL;
}

void RobotisDynamixelUART::SetConfiguration (unsigned short cwAngleLimits, unsigned short ccwAngleLimits, unsigned short velocityLimits, unsigned short torqueLimits)
{
	SetStatusReturn (1);
	SetReturnDelay (0);
	SetAlarmLED (OVERLOAD_ERROR | OVERHEATING_ERROR | INPUTVOLTAGE_ERROR);
	SetAlarmShutdown (OVERLOAD_ERROR | OVERHEATING_ERROR | INPUTVOLTAGE_ERROR);
	
	EnableTorque();

	SetCwanglelimit (cwAngleLimits);
	SetCcwanglelimit (ccwAngleLimits);

	SetMovingspeed (velocityLimits);
	SetTorquelimit (torqueLimits);
}

bool RobotisDynamixelUART::SetReturnDelay (unsigned char value)
{
	// 지연시간: 2uSec * value
	return WriteByte(RETURN_DELAY_TIME, value);
}

bool RobotisDynamixelUART::SetCwanglelimit(unsigned short angle)
{
	return WriteWord (CW_ANGLE_LIMIT_W, angle);
}

bool RobotisDynamixelUART::SetCcwanglelimit(unsigned short angle)
{
	return WriteWord (CCW_ANGLE_LIMIT_W, angle);
}

bool RobotisDynamixelUART::SetHighLimitTemp (unsigned char value)
{
	// 섭씨 온도
	return WriteByte(HIGHTEST_LIMIT_TEMPERATURE, value);
}

bool RobotisDynamixelUART::SetLowLimitVoltage (unsigned char value)
{
	// 실제 전압의 10배
	return WriteByte(LOWEST_LIMIT_VOLTAGE, value);
}

bool RobotisDynamixelUART::SetHighLimitVoltage (unsigned char value)
{
	// 실제 전압의 10배
	return WriteByte(HIGHEST_LIMIT_VOLTAGE, value);
}

bool RobotisDynamixelUART::SetStatusReturn (unsigned char value)
{
	// 0 - 모든 instruction에 대해 return 하지 않음.
	// 1 - READ_DATA 명령에 대해 return 함.
	// 2 - 모든 instruction에 대해 return 함.
	return WriteByte(STATUS_RETURN_VALUE, value);
}

bool RobotisDynamixelUART::SetAlarmLED (unsigned char value)
{
	return WriteByte(ALARM_LED, value);
}

bool RobotisDynamixelUART::SetAlarmShutdown (unsigned char value)
{
	return WriteByte(ALARM_SHUTDOWN, value);
}

bool RobotisDynamixelUART::EnableTorque(void)
{
	return WriteByte(TORQUE_EABLE, 1);
}

bool RobotisDynamixelUART::DisableTorque(void)
{
	return WriteByte(TORQUE_EABLE, 0);
}

bool RobotisDynamixelUART::SetGoalposition(unsigned short angle)
{
	return WriteWord (GOAL_POSITION_W, angle);
}

bool RobotisDynamixelUART::SetGoalpositionReg (unsigned short angle)
{
	return WriteReg (GOAL_POSITION_W, angle);
}

bool RobotisDynamixelUART::SetMovingspeed(unsigned short angle)
{
	return WriteWord (MOVING_SPEED_W, angle);
}

bool RobotisDynamixelUART::SetTorquelimit (unsigned short torque)
{
	if (WriteWord (MAX_TORQUE_W, torque)) {
		return WriteWord (TORQUE_LIMIT_W, torque);
	}
	return false;
}

bool RobotisDynamixelUART::IsMoving (bool *moving)
{
	unsigned char stat;
	if (ReadByte (MOVING, &stat)) {
		*moving = stat ? true : false;
		return true;
	}
	return false;
}

bool RobotisDynamixelUART::GetCwanglelimit(unsigned short *angle)
{
	return ReadWord (CW_ANGLE_LIMIT_W, angle);
}

bool RobotisDynamixelUART::GetCcwanglelimit(unsigned short *angle)
{
	return ReadWord (CCW_ANGLE_LIMIT_W, angle);
}

bool RobotisDynamixelUART::GetGoalposition(unsigned short *angle)
{
	return ReadWord (GOAL_POSITION_W, angle);
}

bool RobotisDynamixelUART::GetMovingspeed (unsigned short *speed)
{
	return ReadWord (MOVING_SPEED_W, speed);
}

bool RobotisDynamixelUART::GetTorquelimit (unsigned short *torque)
{
	return ReadWord (TORQUE_LIMIT_W, torque);
}

bool RobotisDynamixelUART::GetPresentposition(unsigned short *angle)
{
	return ReadWord (PRESENT_POSITION_W, angle);
}

bool RobotisDynamixelUART::GetPresentspeed (unsigned short *speed)
{
	unsigned short val;
	if (ReadWord (PRESENT_SPEED_W, &val)) {
		// bit 10이 방향을 나타냄 (0 ~ 1023)
		*speed = (val & 0x0400)? -(val & 0x03FF) : (val & 0x03FF);
		return true;
	}
	return false;
}

bool RobotisDynamixelUART::GetPresentload (unsigned short *torque)
{
	unsigned short val;
	if (ReadWord (PRESENT_LOAD_W, &val)) {
		// bit 10이 방향을 나타냄 (0 ~ 1023)
		*torque = (val & 0x0400)? -(val & 0x03FF) : (val & 0x03FF);
		return true;
	}
	return false;
}

bool RobotisDynamixelUART::GetPresentvoltage (unsigned char *voltage)
{
	// 전압의 10배 값
	return ReadByte (PRESENT_VOLTAGE, voltage);
}

bool RobotisDynamixelUART::GetPresenttemperature (unsigned char *temperature)
{
	return ReadByte (PRESETN_TEMPERATURE, temperature);
}

unsigned char RobotisDynamixelUART::Checksum(unsigned char *buf, int dataSize)
{
	unsigned char result = 0;
	for(int i = 0; i < dataSize; ++i) {
		result += *(buf + i);
	}
	return ~result;
}

int RobotisDynamixelUART::SendPacket (unsigned char *data, int dataSize)
{
	return uart->Write (data, dataSize);
}

int RobotisDynamixelUART::ReceivePacket (unsigned char *data, int dataSize)
{
	assert (4 < dataSize);

	int n;
	int readDataSize = 0;
	OprosTimer timer;
	timer.StartTimeTick();

	while (readDataSize < 4) {
		n = uart->Read (data + readDataSize, dataSize - readDataSize);
		if (0 < n) {
			readDataSize += n;
		}
		else if (n < 0) {
			return -1;
		}
		if (timer.GetTimeTick() > (unsigned long)(TRANSACTION_TIMEOUT*(dataSize/10 + 1))) {
			break;
		}
	}
	if (4 <= readDataSize && data[0] == (unsigned char)0xFF && data[1] == (unsigned char)0xFF) {
		int packetSize = 4 + data[3];
		if (dataSize < packetSize) {
			return -1;
		}

		while (readDataSize < packetSize) {
			n = uart->Read (data + readDataSize, packetSize - readDataSize);
			if (0 < n) {
				readDataSize += n;
			}
			else if (n < 0) {
				return -1;
			}
			if (timer.GetTimeTick() > (unsigned long)(TRANSACTION_TIMEOUT*(dataSize/10 + 1))) {
				break;
			}
		}
		if (packetSize == readDataSize) {
			unsigned char cs = Checksum (&data[2], packetSize - 3);
			if (data[packetSize - 1] == cs) {
				return packetSize;
			}
		}
	}
	
	return -1;
}

bool RobotisDynamixelUART::Transaction (unsigned char *sendPacket, int sendPacketSize)
{
	uart->Lock();

	int ret = -1;
	for (int i=0; i < RETRY_COUNT; ++i) {
		ret = SendPacket (sendPacket, sendPacketSize);
		if(0 <= ret) {
			OprosSleep (TRANSACTION_WRITE_DELAY);
			uart->Unlock();
			return true;
		}
	}

	uart->Unlock();

	return false;
}

bool RobotisDynamixelUART::Transaction (unsigned char *sendPacket, int sendPacketSize, unsigned char *receivePacket, int receivePacketSize)
{
	uart->Lock();

	int ret;
	for (int i=0; i < RETRY_COUNT; ++i) {
		ret = SendPacket (sendPacket, sendPacketSize);
		if(0 <= ret) {
			OprosSleep(TRANSACTION_READ_DELAY);

			ret = ReceivePacket (receivePacket, receivePacketSize);
			if (0 <= ret) {
				_deviceStatus = receivePacket[4];
				if (_deviceStatus) {
					
				}
				uart->Unlock();
				return true;
			}
		}
	}

	uart->Unlock();

	return false;
}

bool RobotisDynamixelUART::Ping ()
{
	unsigned char sendPacket[6] = { 0xFF, 0xFF, nodeID, 2, PING, 0 };
	sendPacket[5] = Checksum (&sendPacket[2], 3);
	unsigned char recvPacket[6];

	return Transaction(sendPacket, 6, recvPacket, 6);
}

bool RobotisDynamixelUART::ResetMemory ()
{
	//!!! 주의: ID를 1로 재설정한다. 
	unsigned char sendPacket[6] = { 0xFF, 0xFF, nodeID, 2, RESET, 0 };
	sendPacket[5] = Checksum (&sendPacket[2], 3);
	unsigned char recvPacket[6];

	return Transaction(sendPacket, 6, recvPacket, 6);
}

bool RobotisDynamixelUART::WriteByte(unsigned char index, unsigned char data)
{
	unsigned char sendPacket[8] = { 0xFF, 0xFF, nodeID, 4, WRITE_DATA, index, data };
	sendPacket[7] = Checksum (&sendPacket[2], 5);

	return Transaction(sendPacket, 8);
}

//len은 한 모터당 보내는 데이터의 길이
bool RobotisDynamixelUART::WriteBytes (unsigned char index, unsigned char *data, int dataSize, int len, bool sync_flag)
{
	assert (dataSize + 7 <= MAX_PACKET_SIZE);

	unsigned char sendPacket[MAX_PACKET_SIZE] = { 0xFF, 0xFF, 254, dataSize + 4, (sync_flag)? SYNC_WRITE : WRITE_DATA, index , len};
	memcpy (&sendPacket[7], data, dataSize);
	sendPacket[dataSize + 7] = Checksum (&sendPacket[2], dataSize + 5);

	return Transaction (sendPacket, dataSize + 8);
}

bool RobotisDynamixelUART::WriteWord (unsigned char index, unsigned short data)
{
	unsigned char sendPacket[9] = { 0xFF, 0xFF, nodeID, 5, WRITE_DATA, index, (unsigned char)(data >> 0), (unsigned char)(data >> 8), 0 };
	sendPacket[8] = Checksum (&sendPacket[2], 6);

	return Transaction(sendPacket, 9);
}

bool RobotisDynamixelUART::WriteReg (unsigned char index, unsigned short data)
{
	unsigned char sendPacket[9] = { 0xFF, 0xFF, nodeID, 5, REG_WRITE, index, (unsigned char)(data >> 0), (unsigned char)(data >> 8), 0 };
	sendPacket[8] = Checksum (&sendPacket[2], 6);

	return Transaction(sendPacket, 9);
}

bool RobotisDynamixelUART::ReadByte (unsigned char index, unsigned char *data)
{
	unsigned char sendPacket[8] = { 0xFF, 0xFF, nodeID, 4, READ_DATA, index, 1, 0 };
	sendPacket[7] = Checksum (&sendPacket[2], 5);
	unsigned char recvPacket[7];

	if (Transaction (sendPacket, 8, recvPacket, 7)) {
		*data = *(unsigned char *)&recvPacket[5];
		return true;
	}
	return false;
}

bool RobotisDynamixelUART::ReadBytes (unsigned char index, unsigned char *data, int dataSize)
{
	assert (dataSize + 6 <= MAX_PACKET_SIZE);

	unsigned char sendPacket[8] = { 0xFF, 0xFF, nodeID, 4, READ_DATA, index, dataSize, 0 };
	sendPacket[7] = Checksum (&sendPacket[2], 5);
	unsigned char recvPacket[MAX_PACKET_SIZE];

	if (Transaction (sendPacket, 8, recvPacket, 6+dataSize)) {
		memcpy (data, &recvPacket[5], dataSize);
		return true;
	}
	return false;
}

bool RobotisDynamixelUART::ReadWord (unsigned char index, unsigned short *data)
{
	unsigned char sendPacket[8] = { 0xFF, 0xFF, nodeID, 4, READ_DATA, index, 2, 0 };
	sendPacket[7] = Checksum (&sendPacket[2], 5);
	unsigned char recvPacket[8];

	if (Transaction (sendPacket, 8, recvPacket, 8)) {
		*data = *(unsigned short *)&recvPacket[5];
		return true;
	}
	return false;
}

bool RobotisDynamixelUART::SetGoalpositionSync_Broadcast(int size, unsigned short *position, unsigned char *id)
{
	unsigned char sendPacket[MAX_SYNCPACKET_SIZE];
	memset(sendPacket, 0x00, sizeof(sendPacket));

	for(int i = 0, index = 0;i < size; i++, index += 3)
	{
		sendPacket[index] = (unsigned char)id[i];
		sendPacket[index+1] = (unsigned char)((*position) >> 0);
		sendPacket[index+2] = (unsigned char)((*position) >> 8);
	}
		
	return WriteBytes (GOAL_POSITION_W, sendPacket, 3*size, 2, true);
}
