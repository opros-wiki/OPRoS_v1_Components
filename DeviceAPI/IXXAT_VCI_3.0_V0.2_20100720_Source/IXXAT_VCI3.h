#pragma once

#include "CAN.h"

class IXXAT_VCI3 : public CAN
{
public:
	IXXAT_VCI3(void);
	virtual ~IXXAT_VCI3(void);

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
	Property parameter;
};
