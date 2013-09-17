#ifndef	_ANALOG_INPUT_OUTPUT_H_
#define	_ANALOG_INPUT_OUTPUT_H_

#include "AnalogInput.h"
#include "AnalogOutput.h"

namespace OPRoS
{

class AnalogIO : public AnalogInput, public AnalogOutput
{
public:
	AnalogIO(void) { };
	virtual ~AnalogIO(void) { };
};

};


#endif	//	_ANALOG_INPUT_OUTPUT_H_