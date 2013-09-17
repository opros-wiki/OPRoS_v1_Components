#pragma once

#include <string>

using namespace std;

class UDPSocketImpl
{
public:
	UDPSocketImpl(string ip, short port, unsigned long timeOut)
	{
		this->ip = ip;
		this->port = port;
		this->timeOut = timeOut;
	};
	virtual ~UDPSocketImpl(void) { };

protected:
	string ip;
	short port;
	unsigned long timeOut;

public:
	virtual int OpenUDPSocket(void) = 0;
	virtual int CloseUDPSocket(void) = 0;
	virtual int WriteUDPSocket(unsigned char *data, int size) = 0;
	virtual int ReadUDPSOcket(unsigned char *data, int size) = 0;
	virtual int SetParameter(string ip, short port, unsigned long timeOut) = 0;
};
