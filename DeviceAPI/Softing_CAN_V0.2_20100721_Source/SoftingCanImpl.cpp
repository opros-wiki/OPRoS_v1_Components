#include <stdio.h>

#include "SoftingCanImpl.h"
#include "Can_def.h"
#include "canl2.h"

SoftingCanImpl::SoftingCanImpl(int channel, long bitRate, long acceptanceMask, long acceptanceCode, int mode, unsigned long timeOut)
{
	_channel = channel;
	_bitRate = bitRate;
	_acceptanceMask = acceptanceMask;
	_acceptanceCode = acceptanceCode;
	_mode = mode;
	
	_handle = -1;
	_readTimeout = timeOut;
	_writeTimeout = timeOut; 
}

SoftingCanImpl::~SoftingCanImpl(void)
{
	Close();
}

int SoftingCanImpl::Open(void)
{
	if(_handle != -1) {
		return 0;
	}

	char channelName[20];
	sprintf_s(channelName, sizeof(channelName), "CAN-ACx-PCI_%d", _channel);
	int ret = INIL2_initialize_channel(&_handle, channelName);
	if(ret < 0) {
		goto ERROR_RET;
	}
	
	double bitRate;
	int	presc, sjw, tseg1, tseg2, sample;
	switch(_bitRate) {
	case 1000000:		bitRate = 1000.;	presc = 1;   sjw = 2;   tseg1 = 4;   tseg2 = 3;	sample = 0;	break;
	case 500000:		bitRate = 500.;		presc = 1;   sjw = 4;   tseg1 = 8;   tseg2 = 7;	sample = 0;	break;
	case 250000:		bitRate = 250.;		presc = 2;   sjw = 4;   tseg1 = 8;   tseg2 = 7;	sample = 0;	break;
	case 125000:		bitRate = 125.;		presc = 4;   sjw = 4;   tseg1 = 8;   tseg2 = 7;	sample = 0;	break;
	case 100000:		bitRate = 100.;		presc = 4;   sjw = 4;   tseg1 = 11;  tseg2 = 8;	sample = 0;	break;
	case 50000:			bitRate = 50.;		presc = 8;   sjw = 4;   tseg1 = 11;  tseg2 = 8;	sample = 0;	break;
	default: {
		goto ERROR_RET;
		}
	}

	_readAcEventHandle[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
	_readAcEventHandle[1] = CreateEvent(NULL, FALSE, FALSE, NULL);

	L2CONFIG L2Config;

	L2Config.fBaudrate = bitRate;
	L2Config.bEnableAck = 0;
	L2Config.bEnableErrorframe = 0;
	if(_mode == 0) {
		L2Config.s32AccCodeStd = _acceptanceCode;
		L2Config.s32AccMaskStd = _acceptanceMask;
		L2Config.s32AccCodeXtd = 0x00000000;
		L2Config.s32AccMaskXtd = 0x00000000;
	}
	else {
		L2Config.s32AccCodeStd = 0x00000000;
		L2Config.s32AccMaskStd = 0x00000000;
		L2Config.s32AccCodeXtd = _acceptanceCode;
		L2Config.s32AccMaskXtd = _acceptanceMask;
	}
	L2Config.s32OutputCtrl = GET_FROM_SCIM;
	L2Config.s32Prescaler = presc;
	L2Config.s32Sam = sample;
	L2Config.s32Sjw = sjw;
	L2Config.s32Tseg1 = tseg1;
	L2Config.s32Tseg2 = tseg2;
	L2Config.hEvent = _readAcEventHandle[0];

	ret = CANL2_initialize_fifo_mode(_handle, &L2Config);
	if(ret < 0) {
		goto ERROR_RET;
	}

	return 0;

ERROR_RET:
	INIL2_close_channel(_handle);
	_handle = -1;
	
	if (_readAcEventHandle[0]) CloseHandle(_readAcEventHandle[0]);
	if (_readAcEventHandle[1]) CloseHandle(_readAcEventHandle[1]);

	_readAcEventHandle[0] = 0;
	_readAcEventHandle[1] = 0;
	return -1;
}

int SoftingCanImpl::Close(void)
{
	if (_handle == -1) return 0;

	INIL2_close_channel(_handle);
	_handle = -1;

	if (_readAcEventHandle[0]) CloseHandle(_readAcEventHandle[0]);
	if (_readAcEventHandle[1]) CloseHandle(_readAcEventHandle[1]);

	_readAcEventHandle[0] = 0;
	_readAcEventHandle[1] = 0;

	return 0;
}

int SoftingCanImpl::Write(long id, unsigned char *data, int size)
{
	if (_handle == -1) return -1;

	if(size < 0) {
		return -1;
	}
	else if(size > 8) {
		size = 8;
	}

	int ret = CANL2_send_data(_handle, id, _mode, size, (BYTE *)data);
	if(ret < 0) {
		// -1  - transmit fifo full
		// -11 - wrong parameter
		return -1;
	}
	return size;
}

int SoftingCanImpl::Read(long &id, unsigned char *data, int size)
{
	if (_handle == -1) return -1;

REPEAT_READ:
	PARAM_STRUCT param;
	int ret = CANL2_read_ac(_handle, &param);
	switch( ret ) {
	case CANL2_RA_NO_DATA: {		// no new data received
		// 데이터가 없을 때는 데이터가 들어올 때까지 기다렸다가 다시 읽는다(goto REPEAT_READ).
		int ret2 = WaitForMultipleObjects (2, _readAcEventHandle, FALSE, _readTimeout);
		switch (ret2) {
		case WAIT_OBJECT_0:
			goto REPEAT_READ;
		case WAIT_OBJECT_0+1:		// End event
			return -1;
		case WAIT_TIMEOUT:
			return 0;
			break;
		}
		}
		break;
	case CANL2_RA_DATAFRAME:		// std. data frame received
	case CANL2_RA_XTD_DATAFRAME:	// xtd. data frame received
		id = param.Ident;
		size = min(size, (int)param.DataLength);
		memcpy(data, param.RCV_data, size);
		return size;
	
	case CANL2_RA_REMOTEFRAME:		// std. remote frame received
	case CANL2_RA_TX_DATAFRAME:     // transmission of std. data-frame is confirmed  
	case CANL2_RA_TX_FIFO_OVR:      // remote tx fifo overrun   
	case CANL2_RA_CHG_BUS_STATE:    // change of bus status   
	case CANL2_RA_ERR_ADD:          // additional error causes   
	case CANL2_RA_TX_REMOTEFRAME:   // transmission of std. data-frame is confirmed 
	case CANL2_RA_XTD_TX_DATAFRAME:    // transmission of xtd. data-frame is confirmed
	case CANL2_RA_XTD_TX_REMOTEFRAME:  // transmission of xtd. remote-frame is confirmed
	case CANL2_RA_XTD_REMOTEFRAME:     // xtd. remote frame received(only CANcard)
	case CANL2_RA_ERRORFRAME:          // error frame detected(only CANcard)
		break;
	default:
		break;
	}
	return 0;
}

int SoftingCanImpl::Flush(void)
{
	if (_handle == -1) return -1;

	CANL2_reset_xmt_fifo(_handle);
	CANL2_reset_rcv_fifo(_handle);

	return 0;
}

void SoftingCanImpl::Lock(void)
{
	lock.Lock();
}

void SoftingCanImpl::Unlock(void)
{
	lock.Unlock();
}
