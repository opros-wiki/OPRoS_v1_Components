#ifndef	_I2C_H_
#define	_I2C_H_

#include "Bus.h"

class I2C : public Bus
{
public:
	I2C(void) { };
	virtual ~I2C(void) { };

public:
	virtual int Write(unsigned long address, unsigned char *data, int size) { return API_NOT_SUPPORTED; }
	virtual int Read(unsigned long address, unsigned char *data, int size) { return API_NOT_SUPPORTED; }
};

#endif	//	_I2C_H_