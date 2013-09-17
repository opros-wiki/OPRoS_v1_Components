#ifndef	_CAN_H_
#define	_CAN_H_

#include "Bus.h"

class CANProfile {
public:
	CANProfile(void)
	{
		timeOut = 0;

		channel = -1;
		bitRate = 0;
		acceptanceMask = 0;
		acceptanceCode = 0;
		isExtended = false;
	}

	virtual ~CANProfile(void) { }

	unsigned long timeOut;
	int channel;
	unsigned long bitRate;
	unsigned long acceptanceMask;
	unsigned long acceptanceCode;
	bool isExtended;
};

class CAN : public Bus
{
public:
	CAN(void) { };
	virtual ~CAN(void) { };

public:
	virtual int Write(long id, unsigned char *data, int size) { return API_NOT_SUPPORTED; }
	virtual int Read(long &id, unsigned char *data, int size) { return API_NOT_SUPPORTED; }
};

#endif	//	_CAN_H_