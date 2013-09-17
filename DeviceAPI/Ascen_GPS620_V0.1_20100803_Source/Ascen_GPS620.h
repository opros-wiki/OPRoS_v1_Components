#pragma once

//#if defined(WIN32)
//#include <Windows.h>
//#else
//#include <dlfcn.h>
//#endif

#include "NMEAParser.h"
#include "GPS.h"
#include "UART.h"

class Ascen_GPS620 : public GPS
{
public:
	Ascen_GPS620(void);
	virtual ~Ascen_GPS620(void);

public:
	virtual int Initialize(Property parameter);
	virtual int Finalize(void);
	virtual int Enable(void);
	virtual int Disable(void);
	virtual int SetParameter(Property parameter);
	virtual int GetParameter(Property &parameter);
	virtual int GetGPSData(GPSData &gpsData);

private:
	int	_com;
	UART *uart;
	CNMEAParser _nmeaParser;

	Property parameter;

#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif

	int InitializeUART(Property parameter);
	int FinalizeUART(void);

};
