#pragma once

#include "Bus.h"
#include "OprosLock.h"

#if defined(WIN32)
#include "TCPSocketWindows.h"

#else
#include "TCPSocketLinux.h"

#endif

class TCPSocket : public Bus
{
public:
	TCPSocket(void);
	virtual ~TCPSocket(void);

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);

	int Lock(void);
	int Unlock(void);

	int Write(unsigned char *data, int size);
	int Read(unsigned char *data, int size);

private:
	Property parameter;
	TCPSocketImpl *tcpSocket;
	OprosLock lock;
};
