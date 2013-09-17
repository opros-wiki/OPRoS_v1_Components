#ifndef	_DEVICE_H_
#define	_DEVICE_H_

#include "OprosApi.h"

namespace OPRoS
{

class Device : public OprosApi
{
public:
	Device(void) { };
	virtual ~Device(void) { };

protected:

	DEVICE_STATUS status;

public:
	virtual DEVICE_STATUS getStatus(void) = 0;
};

};

#endif	//	_DEVICE_H_