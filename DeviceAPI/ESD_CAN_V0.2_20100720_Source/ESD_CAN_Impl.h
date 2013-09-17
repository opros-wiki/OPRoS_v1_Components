#pragma once

#include "ntcan.h"

class ESD_CAN_Impl
{
public:
	ESD_CAN_Impl(int channel, long bitRate, long acceptanceMask, long acceptanceCode, bool isExtended, long timeOut);
	virtual ~ESD_CAN_Impl(void);

private:
	HANDLE handle;
	int channel;
	unsigned long bitRate;
	long acceptanceMask;
	long acceptanceCode;
	bool isExtended;
	long timeOut;

public:
	int Open(void);
	int Close(void);
	int Write(long id, unsigned char *data, int size);
	int Read(long *id, unsigned char *data, int size);
	int Flush(void);
	int SetTimeOut(long readTimeOut, long writeTimeOut);
};
