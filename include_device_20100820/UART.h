#ifndef	_UART_H_
#define	_UART_H_

#include "Bus.h"

class UART : public Bus
{
public:
	UART(void) { };
	virtual ~UART(void) { };

public:
	virtual int Write(unsigned char *data, int size) { return API_NOT_SUPPORTED; }
	virtual int Read(unsigned char *data, int size) { return API_NOT_SUPPORTED; }
};

#endif	//	_UART_H_