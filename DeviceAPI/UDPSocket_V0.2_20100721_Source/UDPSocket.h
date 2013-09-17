#pragma once

#include "Bus.h"
#include "OprosLock.h"

#if defined(WIN32)
#include "UDPSocketWindows.h"

#else
#include "UDPSocketLinux.h"

#endif

class UDPSocket : public Bus
{
public:
	UDPSocket(void);
	virtual ~UDPSocket(void);

private:
	Property parameter;
	UDPSocketImpl *udpSocket;
	OprosLock lock;

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
};
