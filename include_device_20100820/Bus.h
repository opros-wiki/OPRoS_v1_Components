#ifndef	_BUS_H_
#define	_BUS_H_

#include "Device.h"

class Bus : public Device
{
public:
	Bus(void) { };
	virtual ~Bus(void) { };

public:
	virtual int Lock(void) { return API_NOT_SUPPORTED; }
	virtual int Unlock(void) { return API_NOT_SUPPORTED; }
};

#endif	//	_BUS_H_