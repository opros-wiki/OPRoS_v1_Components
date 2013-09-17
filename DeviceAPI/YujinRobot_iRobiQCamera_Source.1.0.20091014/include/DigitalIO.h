#ifndef	_DIGITAL_INPUT_OUTPUT_H_
#define	_DIGITAL_INPUT_OUTPUT_H_

#include "DigitalInput.h"
#include "DigitalOutput.h"

namespace OPRoS
{

class DigitalIO : public DigitalInput, public DigitalOutput
{
public:
	DigitalIO(void) { };
	virtual ~DigitalIO(void) { };
};

};


#endif	//	_DIGITAL_INPUT_OUTPUT_H_