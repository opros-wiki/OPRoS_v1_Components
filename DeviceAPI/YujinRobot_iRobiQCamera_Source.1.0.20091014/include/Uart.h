#ifndef	_UART_H_
#define	_UART_H_

#include "Bus.h"

namespace OPRoS
{

class UART : public Bus
{
public:
	UART(void) { };
	virtual ~UART(void) { };

public:
	virtual int write(unsigned char *data, int size) = 0;
	virtual int read(unsigned char *data, int size) = 0;
};

};

#endif	//	_BUS_H_