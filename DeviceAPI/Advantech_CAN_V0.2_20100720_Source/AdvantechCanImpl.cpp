#include "AdvantechCanImpl.h"

#include "CanBus2.0.h"

#pragma comment (lib,"AdsCAN.lib")

typedef struct
{
    unsigned char rtr;
    unsigned long id;
    unsigned char dLen;
    unsigned char data[8];

} CAN_MSG_T, *PCAN_MSG_T;

static int advantechCanHandleCount = 0;
static PCAN_MSG_T advantechCanBuffer;
static PCAN_MSG_T gBuffer;

AdvantechCanImpl::AdvantechCanImpl(int channel, long bitRate, long acceptanceMask, long acceptanceCode, int mode, unsigned long timeOut)
{
	if(advantechCanHandleCount++ == 0) {
		advantechCanBuffer = (PCAN_MSG_T)GlobalAlloc(GPTR, 16*sizeof(CAN_MSG_T));
	}

	_channel = channel;
	_port = 0;
	_bitRate;
	_acceptanceMask = acceptanceMask;
	_acceptanceCode = acceptanceCode;
	_mode = mode;
	_timeOut = timeOut;

	_isOpened = false;
}

AdvantechCanImpl::~AdvantechCanImpl(void)
{
	Close();

	if(--advantechCanHandleCount == 0) {
		GlobalFree(advantechCanBuffer);
	}
}

int AdvantechCanImpl::Open(void)
{
	unsigned short nHostID;
	unsigned short nPreBaudRate;
		
	if(CANPortOpen((unsigned short)_channel, &_port, &nHostID, &nPreBaudRate) != SUCCESS) {
		return -1;
	}

	if(CANHwReset(_port) != SUCCESS) {
		CANPortClose(_port);
		return -1;
	}

	unsigned char mask = 0x00;
	unsigned char bit0, bit1;
	switch(_bitRate) {
		case 1000000:
			bit0 = 0x00;	bit1 = 0x05;	break;
		case 500000:
			bit0 = 0x00;	bit1 = 0x1C;	break;
		case 250000:
			bit0 = 0x01;	bit1 = 0x1C;	break;
		case 125000:
			bit0 = 0x03;	bit1 = 0x1C;	break;
		default:
			CANPortClose(_port);
			return -1;
	}

	//	CAN 모드 설정
	if(_mode == 0) {
		if(CANSetProtocolType(_port, CANBUS_PROTOCOL_20A) != SUCCESS) {
			CANPortClose(_port);
			return -1;
		}

		unsigned short outCtrlCode = 250;
		if(CANSetOutCtrl(_port, outCtrlCode) != SUCCESS) {
			CANPortClose(_port);
			return -1;
		}

		_acceptanceMask = ~_acceptanceMask;
		if(CANSetAcp(_port, (unsigned short)_acceptanceCode, (unsigned short)_acceptanceMask) != SUCCESS) {
			CANPortClose(_port);
			return -1;
		}
	}
	else if(_mode == 1) {
		if(CANSetProtocolType(_port, CANBUS_PROTOCOL_20B) != SUCCESS) {
			CANPortClose(_port);
			return -1;
		}

		unsigned short outCtrlCode = 250;
		if(CANSetOutCtrl(_port, outCtrlCode) != SUCCESS) {
			CANPortClose(_port);
			return -1;
		}

		unsigned char tmp[13] = {8, 0, 0, 0};
		memcpy(&tmp[4], &_acceptanceCode, 4);
		_acceptanceMask = ~_acceptanceMask;
		memcpy(&tmp[8], &_acceptanceMask, 4);

		if(CANSetAcpEx(_port, (LPT_FilterSetting)tmp) != SUCCESS) {
			CANPortClose(_port);
			return -1;
		}
	}
	else {
		CANPortClose(_port);
		return -1;
	}

	_isOpened = false;

	return 0;
}

int AdvantechCanImpl::Close(void)
{
	if(_isOpened == true) {
		CANPortClose(_port);
		_isOpened = false;
	}

	return 0;
}

int AdvantechCanImpl::Write(long id, unsigned char *data, int size)
{
	if(_isOpened == false) {
		return -1;
	}

	if(size < 0) {
		return -1;
	}
	else if(size > 8) {
		size = 8;
	}

	BOOL bReady;
	CAN_MSG_T msg;
	msg.rtr = 0x00;
	msg.id = (unsigned long)id;
	msg.dLen = (unsigned char)size;
	memcpy(msg.data, data, size);

	if(CANWriteFile(_port, &bReady, (void *)&msg) != SUCCESS) {
		return -1;
	}
	if(bReady == FALSE) {
		return -1;
	}

	return size;
}

int AdvantechCanImpl::Read(long &id, unsigned char *data, int size)
{
	if(_isOpened == false) {
		return -1;
	}

	BOOL bReady;
	if(CANWaitForFIFOEvent(_port, _timeOut, &bReady) != SUCCESS) {
		return -1;
	}
	if(bReady == TRUE) {
		id = (long)gBuffer[0].id;
		memcpy(data, gBuffer[0].data, gBuffer[0].dLen);
	}
	else {
		return -1;
	}

	return gBuffer[0].dLen;
}

void AdvantechCanImpl::Lock(void)
{
	lock.Lock();
}

void AdvantechCanImpl::Unlock(void)
{
	lock.Unlock();
}
