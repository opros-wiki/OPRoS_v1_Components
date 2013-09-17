#ifndef	_CAN_H_
#define	_CAN_H_

#include "Bus.h"

namespace OPRoS
{

class CAN : public Bus
{
public:
	CAN(void) { };
	virtual ~CAN(void) { };

public:
	virtual int write(long id, valarray<unsigned char> data) = 0;
	virtual int read(long *id, valarray<unsigned char> *data) = 0;
};

};

#endif	//	_CAN_H_