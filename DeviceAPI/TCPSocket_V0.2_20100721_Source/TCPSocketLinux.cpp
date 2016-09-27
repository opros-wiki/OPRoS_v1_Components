#if !defined(WIN32)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "TCPSocketLinux.h"

TCPSocketLinux::TCPSocketLinux(string ip, short port, unsigned long timeOut)
: TCPSocketImpl(ip, port, timeOut)
{
	_socket = -1;
}

TCPSocketLinux::~TCPSocketLinux(void)
{
	CloseTCPSocket();
}

int TCPSocketLinux::OpenTCPSocket(void)
{
	struct sockaddr_in socket_addr;

	_socket = socket(PF_INET, SOCK_STREAM, 0);
	if(_socket == -1) {
		return -1;
	}

	memset(&socket_addr, 0, sizeof(socket_addr));
	socket_addr.sin_family = AF_INET;
	socket_addr.sin_addr.s_addr = inet_addr(ip.c_str());
	socket_addr.sin_port = htons((short)port);

	if(connect(_socket, (struct sockaddr *)&socket_addr, sizeof(socket_addr)) == -1) {
		CloseTCPSocket();
		return -1;
	}

	struct timeval tv;
	tv.tv_usec = timeOut * 1000;

	if(setsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *)&tv, sizeof(struct timeval)) == -1) {
		CloseTCPSocket();
		return -1;
	}

	if(setsockopt(_socket, SOL_SOCKET, SO_SNDTIMEO, (struct timeval *)&tv, sizeof(struct timeval)) == -1) {
		CloseTCPSocket();
		return -1;
	}

	return 0;
}

int TCPSocketLinux::CloseTCPSocket(void)
{
	if(_socket == -1) {
		return 0;
	}

	close(_socket);
	_socket = -1;

	return 0;
}

int TCPSocketLinux::WriteTCPSocket(unsigned char *data, int size)
{
	if(_socket == -1) {
		return -1;
	}

	return write(_socket, data, size);
}

int TCPSocketLinux::ReadTCPSOcket(unsigned char *data, int size)
{
	if(_socket == -1) {
		return -1;
	}

	return read(_socket, data, size);
}

int TCPSocketLinux::SetParameter(string ip, short port, unsigned long timeOut)
{
	CloseTCPSocket();

	this->ip = ip;
	this->port = port;
	this->timeOut = timeOut;

	return OpenTCPSocket();
}

#endif

