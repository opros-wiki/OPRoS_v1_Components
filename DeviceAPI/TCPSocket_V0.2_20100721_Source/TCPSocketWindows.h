#ifndef	_TCP_SOCKET_WINDOWS_H_
#define	_TCP_SOCKET_WINDOWS_H_

#if defined(WIN32)
#include <Winsock.h>

#include "TCPSocketImpl.h"

class TCPSocketWindows : public TCPSocketImpl
{
public:
	TCPSocketWindows(string ip, short port, unsigned long timeOut);
	virtual ~TCPSocketWindows(void);

public:
	int OpenTCPSocket(void);
	int CloseTCPSocket(void);
	int WriteTCPSocket(unsigned char *data, int size);
	int ReadTCPSOcket(unsigned char *data, int size);
	int SetParameter(string ip, short port, unsigned long timeOut);

private:
	WSADATA wsaData;
	SOCKET hSocket;
	bool isInitialized;
};

#endif

#endif	//	_TCP_SOCKET_WINDOWS_H_
