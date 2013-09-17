#ifndef	_ANALOG_DIGITAL_IO_H_
#define	_ANALOG_DIGITAL_IO_H_

#include "Device.h"

class AnalogDigitalIO : public Device
{
public:
	AnalogDigitalIO(void) { };
	virtual ~AnalogDigitalIO(void) { };

public:
	virtual int SetAnalogOutputData(vector<double> analogOutputData) { return API_NOT_SUPPORTED; }
	virtual int GetAnalogInputData(vector<double> &analogInputData) { return API_NOT_SUPPORTED; }
	virtual int SetDigitalOutputData(vector<bool> digitalOutputData) { return API_NOT_SUPPORTED; }
	virtual int GetDigitalInputData(vector<bool> &digitalInputData) { return API_NOT_SUPPORTED; }
};

#endif	//	_ANALOG_DIGITAL_IO_H_