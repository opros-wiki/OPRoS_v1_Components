#ifndef	_DIGITAL_OUTPUT_H_
#define	_DIGITAL_OUTPUT_H_

#include "Device.h"

namespace OPRoS
{

class DigitalOutput : virtual public Device
{
public:
	DigitalOutput(void) { };
	virtual ~DigitalOutput(void) { };

public:
	virtual int setState(int index, valarray<bool> state) = 0;
};

};

#endif	//	_DIGITAL_OUTPUT_H_