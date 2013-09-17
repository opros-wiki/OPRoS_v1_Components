#pragma once

#include "InertiaMeasurementUnit.h"
#include "UART.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

class MicroInfinity_A3350M : public InertiaMeasurementUnit
{
public:
	MicroInfinity_A3350M(void);
	virtual ~MicroInfinity_A3350M(void);

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);
	int GetInertiaMeasurementUnitData(vector<ObjectPosture> &inertiaMeasurementUnitData);

private:
	Property parameter;
	UART *_uart;

#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	int InitializeUART(Property parameter);

	int A3350_RecvPacket(vector<unsigned char> *data);
	int A3350_ParsingData(vector<unsigned char> data, vector<double> *value);
	int A3350_GetValue(vector<double> *value);
};
