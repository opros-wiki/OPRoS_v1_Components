#ifndef	_TCP_IP_SOCKET_H_
#define	_TCP_IP_SOCKET_H_

#include "Bus.h"

namespace OPRoS
{

class TcpIpSocket : public Bus
{
public:
	TcpIpSocket(void) { };
	virtual ~TcpIpSocket(void) { };

public:
	virtual int write(valarray<unsigned char> data) = 0;
	virtual int read(valarray<unsigned char> *data) = 0;
};

};

#endif	//	_TCP_IP_SOCKET_H_