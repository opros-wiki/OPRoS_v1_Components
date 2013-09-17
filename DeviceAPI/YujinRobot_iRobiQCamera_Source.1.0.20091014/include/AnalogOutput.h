#ifndef	_ANALOG_OUTPUT_H_
#define	_ANALOG_OUTPUT_H_

#include "Device.h"

namespace OPRoS
{

class AnalogOutput : virtual public Device
{
public:
	AnalogOutput(void) { };
	virtual ~AnalogOutput(void) { };

public:
	virtual int setValue(int index, valarray<double> value) = 0;
};

};

#endif	//	_ANALOG_OUTPUT_H_