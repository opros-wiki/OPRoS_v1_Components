#pragma once

#include "CAN.h"

class ESD_CAN : public CAN
{
public:
	ESD_CAN(void);
	virtual ~ESD_CAN(void);

private:
	Property parameter;
	int channel;
	bool isInitialized;
	bool isOpened;

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
};
