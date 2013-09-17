#ifndef	_ANALOG_IO_H_
#define	_ANALOG_IO_H_

#include "Device.h"

class AnalogIO : public Device
{
public:
	AnalogIO(void) { };
	virtual ~AnalogIO(void) { };

public:
	virtual int SetAnalogOutputData(vector<double> analogOutputData) { return API_NOT_SUPPORTED; }
	virtual int GetAnalogInputData(vector<double> &analogInputData) { return API_NOT_SUPPORTED; }
};

#endif	//	_ANALOG_IO_H_