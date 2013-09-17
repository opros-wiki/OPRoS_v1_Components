#pragma once

#include "Windows.h"
#include "OprosLock.h"

class SoftingCanImpl
{
public:
	SoftingCanImpl(int channel, long bitRate, long acceptanceMask, long acceptanceCode, int mode, unsigned long timeOut);
	virtual ~SoftingCanImpl(void);

private:
	int _channel;
	long _bitRate;
	long _acceptanceMask;
	long _acceptanceCode;
	int _mode;
	
	bool _isOpened;
	OprosLock lock;

	unsigned long _handle;
	unsigned long _readTimeout;
	unsigned long _writeTimeout;
	HANDLE _readAcEventHandle[2];

public:
	int Open(void);
	int Close(void);
	int Write(long id, unsigned char *data, int size);
	int Read(long &id, unsigned char *data, int size);
	int Flush(void);
	void Lock(void);
	void Unlock(void);
};
