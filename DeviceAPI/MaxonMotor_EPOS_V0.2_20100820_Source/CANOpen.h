#pragma once

#include "CAN.h"

class CANOpen
{
public:
	CANOpen(CAN *can);
	virtual ~CANOpen(void);

private:
	CAN *can;

public:
	int WriteData(long id, unsigned char *data, int size);
	int ReadData(long &id, unsigned char *data, int size);
	int Lock(void);
	int Unlock(void);

	int WriteObject(long id, unsigned short index, unsigned char subIndex, unsigned char *data, int size, unsigned long timeOut = 0);
	int WriteObject(long id, unsigned short index, unsigned char subIndex, char data, unsigned long timeOut = 0);
	int WriteObject(long id, unsigned short index, unsigned char subIndex, unsigned char data, unsigned long timeOut = 0);
	int WriteObject(long id, unsigned short index, unsigned char subIndex, short data, unsigned long timeOut = 0);
	int WriteObject(long id, unsigned short index, unsigned char subIndex, unsigned short data, unsigned long timeOut = 0);
	int WriteObject(long id, unsigned short index, unsigned char subIndex, long data, unsigned long timeOut = 0);
	int WriteObject(long id, unsigned short index, unsigned char subIndex, unsigned long data, unsigned long timeOut = 0);

	int ReadObject(long id, unsigned short index, unsigned char subIndex, unsigned char *data, int size, unsigned long timeOut = 0);
	int ReadObject(long id, unsigned short index, unsigned char subIndex, char *data, unsigned long timeOut = 0);
	int ReadObject(long id, unsigned short index, unsigned char subIndex, unsigned char *data, unsigned long timeOut = 0);
	int ReadObject(long id, unsigned short index, unsigned char subIndex, short *data, unsigned long timeOut = 0);
	int ReadObject(long id, unsigned short index, unsigned char subIndex, unsigned short *data, unsigned long timeOut = 0);
	int ReadObject(long id, unsigned short index, unsigned char subIndex, long *data, unsigned long timeOut = 0);
	int ReadObject(long id, unsigned short index, unsigned char subIndex, unsigned long *data, unsigned long timeOut = 0);
};
