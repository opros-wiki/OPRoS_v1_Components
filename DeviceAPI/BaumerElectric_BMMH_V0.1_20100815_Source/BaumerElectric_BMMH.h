#pragma once

#include "Encoder.h"
#include "CANOpen.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif


class BMMHProfile : public EncoderProfile
{
public:
	BMMHProfile(void)
	{
		id = -1;
	}
	virtual ~BMMHProfile(void)
	{
	}

public:
	long id;
};

class BaumerElectric_BMMH : public Encoder
{
public:
	BaumerElectric_BMMH(void);
	virtual ~BaumerElectric_BMMH(void);

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);
	int GetEncoderData(vector<double> &encoderData);

private:
	Property parameter;
	CAN *can;
	CANOpen *canOpen;

	vector<BMMHProfile> _profile;

#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif

	int InitializeCAN(Property parameter);

	int BMMH_GetError(long id, unsigned char *error);
	int BMMH_SetPosition(long id, long position);
	int BMMH_GetPosition(long id, long *position);
	int BMMH_SaveToEEPROM(long id);
};
