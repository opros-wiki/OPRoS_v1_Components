#ifndef _InfraredSensorComp_COMPONENT_H
#define _InfraredSensorComp_COMPONENT_H
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

#include "InfraredSensorServiceProvided.h"
#include "InfraredSensor.h"

#include "OprosLock.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif
	

class InfraredSensorComp: public Component
	,public IInfraredSensorService
{
protected:
	OutputDataPort< vector<double> > infraredData;

public:
	InfraredSensorComp();
	InfraredSensorComp(const std::string &compId);
	virtual ~InfraredSensorComp();
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
	virtual vector<double> GetInfraredData();

private:
#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	InfraredSensor *infraredSensor;
	int error;
	OprosLock lock;
};

#endif

