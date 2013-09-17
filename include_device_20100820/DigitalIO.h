#ifndef	_DIGITAL_IO_H_
#define	_DIGITAL_IO_H_

#include "Device.h"

class DigitalIO : public Device
{
public:
	DigitalIO(void) { };
	virtual ~DigitalIO(void) { };

public:
	virtual int SetDigitalOutputData(vector<bool> digitalOutputData) { return API_NOT_SUPPORTED; }
	virtual int GetDigitalInputData(vector<bool> &digitalInputData) { return API_NOT_SUPPORTED; }
};

#endif	//	_DIGITAL_IO_H_