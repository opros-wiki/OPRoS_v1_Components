#pragma once

#include "Nican.h"
#include "OprosLock.h"

class NiCanImpl
{
public:
	NiCanImpl(int channel, long bitRate, long acceptanceMask, long acceptanceCode, int mode, unsigned long timeOut);
	virtual ~NiCanImpl(void);

private:
	int _channel;
	long _bitRate;
	long _acceptanceMask;
	long _acceptanceCode;
	int _mode;
	unsigned long _timeOut;

	NCTYPE_OBJH _handle;
	
	OprosLock lock;

public:
	int Open(void);
	int Close(void);
	int Write(long id, unsigned char *data, int size);
	int Read(long &id, unsigned char *data, int size);
	void Lock(void);
	void Unlock(void);
};
