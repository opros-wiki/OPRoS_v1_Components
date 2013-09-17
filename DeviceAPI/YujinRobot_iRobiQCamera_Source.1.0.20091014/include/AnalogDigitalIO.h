#ifndef	_ANALOG_DIGITAL_INPUT_OUTPUT_H_
#define	_ANALOG_DIGITAL_INPUT_OUTPUT_H_

#include "AnalogIO.h"
#include "DigitalIO.h"

namespace OPRoS
{

class AnalogDigitalIO : public AnalogIO, public DigitalIO
{
public:
	AnalogDigitalIO(void) { };
	virtual ~AnalogDigitalIO(void) { };
};

};


#endif	//	_ANALOG_DIGITAL_INPUT_OUTPUT_H_