#include <string.h>
#include "CANOpen.h"
#include "OprosPrintMessage.h"
#include "OprosTimer.h"

enum eSDO_COMMAND {
	WRITE_REQUEST			= 0x22,
	WRITE_REQUEST_4BYTE		= 0x23,
	WRITE_REQUEST_2BYTE		= 0x2B,
	WRITE_REQUEST_1BYTE		= 0x2F,
	WRITE_RESPONSE			= 0x60,

	READ_REQUEST			= 0x40,
	READ_RESPONSE_MAX4BYTE	= 0x42,
	READ_RESPONSE_4BYTE		= 0x43,
	READ_RESPONSE_2BYTE		= 0x4B,
	READ_RESPONSE_1BYTE		= 0x4F,

	ABORT_MESSAGE1			= 0x80,	// BMMX Absolute encoder
	ABORT_MESSAGE2			= 0xC0,	// EPOS, UCMC
};

enum eFC_PTP_ID {
	FC_EMERGENCY		= 0x80,
	FC_SDO1_RX			= 0x580,
	FC_SDO1_TX			= 0x600,
	FC_Heartbeat		= 0x700,
};

CANOpen::CANOpen(CAN *can)
{
	this->can = can;
}

CANOpen::~CANOpen(void)
{
	can = NULL;
}

int CANOpen::WriteData(long id, unsigned char *data, int size)
{
	if(can == NULL) {
		return -1;
	}

	return can->Write(id, data, size);
}

int CANOpen::ReadData(long &id, unsigned char *data, int size)
{
	if(can == NULL) {
		return -1;
	}

	return can->Read(id, data, size);
}

int CANOpen::Lock(void)
{
	if(can == NULL) {
		return -1;
	}

	can->Lock();

	return 0;
}

int CANOpen::Unlock(void)
{
	if(can == NULL) {
		return -1;
	}

	can->Unlock();

	return 0;
}

int CANOpen::WriteObject(long id, unsigned short index, unsigned char subIndex, unsigned char *data, int size, unsigned long timeOut)
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

int CANOpen::WriteObject(long id, unsigned short index, unsigned char subIndex, char data, unsigned long timeOut)
{
	return WriteObject(id, index, subIndex, (unsigned char *)&data, 1, timeOut);
}

int CANOpen::WriteObject(long id, unsigned short index, unsigned char subIndex, unsigned char data, unsigned long timeOut)
{
	return WriteObject(id, index, subIndex, (unsigned char *)&data, 1, timeOut);
}

int CANOpen::WriteObject(long id, unsigned short index, unsigned char subIndex, short data, unsigned long timeOut)
{
	return WriteObject(id, index, subIndex, (unsigned char *)&data, 2, timeOut);
}

int CANOpen::WriteObject(long id, unsigned short index, unsigned char subIndex, unsigned short data, unsigned long timeOut)
{
	return WriteObject(id, index, subIndex, (unsigned char *)&data, 2, timeOut);
}

int CANOpen::WriteObject(long id, unsigned short index, unsigned char subIndex, long data, unsigned long timeOut)
{
	return WriteObject(id, index, subIndex, (unsigned char *)&data, 4, timeOut);
}

int CANOpen::WriteObject(long id, unsigned short index, unsigned char subIndex, unsigned long data, unsigned long timeOut)
{
	return WriteObject(id, index, subIndex, (unsigned char *)&data, 4, timeOut);
}

int CANOpen::ReadObject(long id, unsigned short index, unsigned char subIndex, unsigned char *data, int size, unsigned long timeOut)
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

int CANOpen::ReadObject(long id, unsigned short index, unsigned char subIndex, char *data, unsigned long timeOut)
{
	return ReadObject(id, index, subIndex, (unsigned char *)data, 1, timeOut);
}

int CANOpen::ReadObject(long id, unsigned short index, unsigned char subIndex, unsigned char *data, unsigned long timeOut)
{
	return ReadObject(id, index, subIndex, (unsigned char *)data, 1, timeOut);
}

int CANOpen::ReadObject(long id, unsigned short index, unsigned char subIndex, short *data, unsigned long timeOut)
{
	return ReadObject(id, index, subIndex, (unsigned char *)data, 2, timeOut);
}

int CANOpen::ReadObject(long id, unsigned short index, unsigned char subIndex, unsigned short *data, unsigned long timeOut)
{
	return ReadObject(id, index, subIndex, (unsigned char *)data, 2, timeOut);
}

int CANOpen::ReadObject(long id, unsigned short index, unsigned char subIndex, long *data, unsigned long timeOut)
{
	return ReadObject(id, index, subIndex, (unsigned char *)data, 4, timeOut);
}

int CANOpen::ReadObject(long id, unsigned short index, unsigned char subIndex, unsigned long *data, unsigned long timeOut)
{
	return ReadObject(id, index, subIndex, (unsigned char *)data, 4, timeOut);
}