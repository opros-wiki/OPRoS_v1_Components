#pragma once

#include "CAN.h"

class Kvaser_CAN : public CAN
{
public:
	Kvaser_CAN(void);
	virtual ~Kvaser_CAN(void);

private:
	Property parameter;

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);

	int Lock(void);
	int Unlock(void);

	int Write(long id, unsigned char *data, int size);
	int Read(long &id, unsigned char *data, int size);

private:
	int channel;
	bool isOpened;

	int OpenKvaserCAN(void);
	int CloseKvaserCAN(void);
	int WriteKvaserCAN(long id, unsigned char *data, int size);
	int ReadKvaserCAN(long &id, unsigned char *data);
};
