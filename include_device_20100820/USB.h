#ifndef	_USB_H_
#define	_USB_H_

#include "Bus.h"

class USB : public Bus
{
public:
	USB(void) { };
	virtual ~USB(void) { };

public:
	virtual int Write(unsigned char *data, int size) { return API_NOT_SUPPORTED; }
	virtual int Read(unsigned char *data, int size) { return API_NOT_SUPPORTED; }
};


#endif	//	_USB_H_