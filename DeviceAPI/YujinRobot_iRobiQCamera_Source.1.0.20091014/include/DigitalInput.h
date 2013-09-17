#ifndef	_DIGITAL_INPUT_H_
#define	_DIGITAL_INPUT_H_

#include "Device.h"

namespace OPRoS
{

class DigitalInput : virtual public Device
{
public:
	DigitalInput(void) { };
	virtual ~DigitalInput(void) { };

public:
	virtual int getState(int index, valarray<bool> *state) = 0;
};

};

#endif	//	_DIGITAL_INPUT_H_