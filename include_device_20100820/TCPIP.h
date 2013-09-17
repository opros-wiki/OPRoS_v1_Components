#ifndef	_TCP_IP_H_
#define	_TCP_IP_H_

#include "Bus.h"

class TCPIP : public Bus
{
public:
	TCPIP(void) { };
	virtual ~TCPIP(void) { };

public:
	virtual int Write(unsigned char *data, int size) { return API_NOT_SUPPORTED; }
	virtual int Read(unsigned char *data, int size) { return API_NOT_SUPPORTED; }
};


#endif	//	_TCP_IP_H_
