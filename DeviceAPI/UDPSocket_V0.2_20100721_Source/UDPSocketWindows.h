#pragma once

#if defined(WIN32)
#include "UDPSocketImpl.h"
#include <Winsock.h>

class UDPSocketWindows : public UDPSocketImpl
{
public:
	UDPSocketWindows(string ip, short port, unsigned long timeOut);
	virtual ~UDPSocketWindows(void);

private:
	WSADATA wsaData;
	SOCKET hSocket;

public:
	int OpenUDPSocket(void);
	int CloseUDPSocket(void);
	int WriteUDPSocket(unsigned char *data, int size);
	int ReadUDPSOcket(unsigned char *data, int size);
	int SetParameter(string ip, short port, unsigned long timeOut);
};

#endif
