#ifndef	_BUS_H_
#define	_BUS_H_

#include "Device.h"

namespace OPRoS
{ 

class Bus : public Device
{
public:
	Bus(void) { };
	virtual ~Bus(void) { };

public:
	virtual void lock(void) = 0;
	virtual void unlock(void) = 0;
};

};


#endif	//	_BUS_H_