#pragma once

#include "OprosLock.h"

class AdvantechCanImpl
{
public:
	AdvantechCanImpl(int channel, long bitRate, long acceptanceMask, long acceptanceCode, int mode, unsigned long timeOut);
	virtual ~AdvantechCanImpl(void);

private:
	int _channel;
	unsigned short _port;
	long _bitRate;
	long _acceptanceMask;
	long _acceptanceCode;
	int _mode;
	unsigned long _timeOut;

	bool _isOpened;

	OprosLock lock;

public:
	int Open(void);
	int Close(void);
	int Write(long id, unsigned char *data, int size);
	int Read(long &id, unsigned char *data, int size);
	void Lock(void);
	void Unlock(void);
};
