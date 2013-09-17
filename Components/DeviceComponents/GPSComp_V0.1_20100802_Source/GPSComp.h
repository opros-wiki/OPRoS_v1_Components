#ifndef _GPSComp_COMPONENT_H
#define _GPSComp_COMPONENT_H
/*
 *  Generated sources by OPRoS Component Generator (OCG V2)
 *   
 */
#include <Component.h>
#include <InputDataPort.h>
#include <OutputDataPort.h>
#include <InputEventPort.h>
#include <OutputEventPort.h>
#include <Event.h>
#include <OPRoSTypes.h>

#include "GPSServiceProvided.h"
#include "GPS.h"
#include "OprosLock.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

class GPSComp: public Component
	,public IGPSService
{
protected:
	OutputDataPort< GPSData > gpsData;

#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	GPS *gps;
	int error;
	OprosLock lock;

public:
	GPSComp();
	GPSComp(const std::string &compId);
	virtual ~GPSComp();
	virtual void portSetup();

protected:
	virtual ReturnType onInitialize();
	virtual ReturnType onStart();
	virtual ReturnType onStop();
	virtual ReturnType onReset();
	virtual ReturnType onError();
	virtual ReturnType onRecover();
	virtual ReturnType onDestroy();

public:
	virtual ReturnType onEvent(Event *evt);
	virtual ReturnType onExecute();
	virtual ReturnType onUpdated();
	virtual ReturnType onPeriodChanged();

	virtual bool SetParameter(Property parameter);
	virtual Property GetParameter();
	virtual int GetError();
	virtual GPSData GetGPSData();
};

#endif

