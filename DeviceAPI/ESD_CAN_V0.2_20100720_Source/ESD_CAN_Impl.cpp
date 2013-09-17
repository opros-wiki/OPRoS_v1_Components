#include "ESD_CAN_Impl.h"

#if defined(WIN32)
#pragma comment(lib, "./windows/ntcan.lib")
#endif

#define	ESD_CAN_TX_FIFO_SIZE		32
#define	ESD_CAN_RX_FIFO_SIZE		32

#define	ESD_CAN_STD_END_ID			(0x7FF - 1)

ESD_CAN_Impl::ESD_CAN_Impl(int channel, long bitRate, long acceptanceMask, long acceptanceCode, bool isExtended, long timeOut)
{
	handle = INVALID_HANDLE_VALUE;

	this->channel = channel;
	this->bitRate = bitRate;
	this->acceptanceMask = acceptanceMask;
	this->acceptanceCode = acceptanceCode;
	this->isExtended = isExtended;
	this->timeOut = timeOut;
}

ESD_CAN_Impl::~ESD_CAN_Impl(void)
{
	Close();
}

int ESD_CAN_Impl::Open(void)
{
	if(handle != INVALID_HANDLE_VALUE) {
		return -1;
	}

	//	Open the channel
	if(canOpen(channel, NTCAN_MODE_NO_INTERACTION, ESD_CAN_TX_FIFO_SIZE, ESD_CAN_RX_FIFO_SIZE, timeOut, timeOut, &handle) != NTCAN_SUCCESS) {
		return -1;
	}

	Flush();

	//	Set the bitrate
	switch(bitRate) {
		case 1000000 :	bitRate = NTCAN_BAUD_1000;	break;
		case 50000 :	bitRate = NTCAN_BAUD_500;	break;
		case 25000 :	bitRate = NTCAN_BAUD_250;	break;
		case 12500 :	bitRate = NTCAN_BAUD_125;	break;
		case 10000 :	bitRate = NTCAN_BAUD_100;	break;
		case 5000 :		bitRate = NTCAN_BAUD_50;	break;
	}
	if(canSetBaudrate(handle, bitRate) != NTCAN_SUCCESS) {
		Close();
		return -1;
	}

	if(isExtended == true) {
		//	Set the Acceptance Code
		acceptanceCode = acceptanceCode & 0x1FFFFFF | NTCAN_20B_BASE;
		if(canIdAdd(handle, acceptanceCode) != NTCAN_SUCCESS) {
			Close();
			return -1;
		}

		//	Set the Acceptance Mask
		if(canIoctl(handle, NTCAN_IOCTL_SET_20B_HND_FILTER, (void *)&acceptanceMask) != NTCAN_SUCCESS) {
			Close();
			return -1;
		}
	}
	else {
		for(int i = 0; i < ESD_CAN_STD_END_ID; i++) {
			if(canIdAdd(handle, i) != NTCAN_SUCCESS) {
				Close();
				return -1;
			}
		}
	}
	
	return 0;
}

int ESD_CAN_Impl::Close(void)
{
	if(handle == INVALID_HANDLE_VALUE) {
		return 0;
	}

	canClose(handle);

	handle = INVALID_HANDLE_VALUE;

	return 0;
}

int ESD_CAN_Impl::Write(long id, unsigned char *data, int size)
{
	CMSG canMsg;
	long len = 1;

	if(isExtended == true) {
		canMsg.id = id | NTCAN_20B_BASE;
	}
	else {
		canMsg.id = id;
	}
	if(size < 0 ) {
		return -1;
	}
	else if(size > 8) {
		size = 8;
	}

	canMsg.len = size;
	memcpy(canMsg.data, data, size);

	if(canWrite(handle, &canMsg, &len, NULL) != NTCAN_SUCCESS) {
		return -1;
	}

	return (int)len;
}

int ESD_CAN_Impl::Read(long *id, unsigned char *data, int size)
{
	CMSG canMsg;
	long len = 1;

	if(canRead(handle, &canMsg, &len, NULL) != NTCAN_SUCCESS) {
		Flush();
		return -1;
	}

	if(isExtended == true) {
		*id = canMsg.id & (NTCAN_20B_BASE - 1);
	}
	else {
		*id = canMsg.id;
	}

	if(canMsg.len < size) {
		len = canMsg.len;
	}
	memcpy(data, canMsg.data, len);

	return (int)len;
}

int ESD_CAN_Impl::Flush(void)
{
	if(canIoctl(handle, NTCAN_IOCTL_FLUSH_RX_FIFO, NULL) != NTCAN_SUCCESS) {
		return -1;
	}

	return 0;
}

int ESD_CAN_Impl::SetTimeOut(long readTimeOut, long writeTimeOut)
{
	if(canIoctl(handle, NTCAN_IOCTL_SET_RX_TIMEOUT, (void *)&readTimeOut) != NTCAN_SUCCESS) {
		return -1;
	}

	if(canIoctl(handle, NTCAN_IOCTL_SET_TX_TIMEOUT, (void *)&writeTimeOut) != NTCAN_SUCCESS) {
		return -1;
	}
	
	return 0;
}
