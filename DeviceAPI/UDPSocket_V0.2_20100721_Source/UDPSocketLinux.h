#pragma once

#if !defined(WIN32)

#include "UDPSocketImpl.h"

class UDPSocketLinux : public UDPSocketImpl
{
public:
	UDPSocketLinux(string ip, short port, unsigned long timeOut);
	virtual ~UDPSocketLinux(void);

private:
	int _socket;

public:
	int OpenUDPSocket(void);
	int CloseUDPSocket(void);
	int WriteUDPSocket(unsigned char *data, int size);
	int ReadUDPSOcket(unsigned char *data, int size);
	int SetParameter(string ip, short port, unsigned long timeOut);
};

#endif
