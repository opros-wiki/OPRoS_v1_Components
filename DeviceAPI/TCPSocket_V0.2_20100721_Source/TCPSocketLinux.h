#pragma once
#include "TCPSocketImpl.h"

#if !defined(WIN32)

class TCPSocketLinux : public TCPSocketImpl
{
public:
	TCPSocketLinux(string ip, short port, unsigned long timeOut);
	virtual ~TCPSocketLinux(void);

private:
	int _socket;

public:
	int OpenTCPSocket(void);
	int CloseTCPSocket(void);
	int WriteTCPSocket(unsigned char *data, int size);
	int ReadTCPSOcket(unsigned char *data, int size);
	int SetParameter(string ip, short port, unsigned long timeOut);
};

#endif
