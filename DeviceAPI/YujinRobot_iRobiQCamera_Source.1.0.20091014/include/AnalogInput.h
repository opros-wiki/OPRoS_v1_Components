#ifndef	_ANALOG_INPUT_H_
#define	_ANALOG_INPUT_H_

#include "Device.h"

namespace OPRoS
{

class AnalogInput : virtual public Device
{
public:
	AnalogInput(void) { };
	virtual ~AnalogInput(void) { };

public:
	virtual int getValue(int index, valarray<double> *value) = 0;
};

};

#endif	//	_ANALOG_INPUT_H_