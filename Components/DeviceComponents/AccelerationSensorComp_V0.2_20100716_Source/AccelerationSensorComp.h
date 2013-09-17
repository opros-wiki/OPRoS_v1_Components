
#ifndef _AccelerationSensorComp_COMPONENT_H
#define _AccelerationSensorComp_COMPONENT_H
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

#include "AccelerationSensorServiceProvided.h"
#include "AccelerationSensor.h"
#include "OprosLock.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

class AccelerationSensorComp: public Component
	,public IAccelerationSensorService
{
protected:
	OutputDataPort< vector<double> > accelerationData;

public:
	AccelerationSensorComp();
	AccelerationSensorComp(const std::string &compId);
	virtual ~AccelerationSensorComp();
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
	virtual vector<double> GetAccelerationData();

private:
#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	AccelerationSensor *accelerationSensor;
	int error;
	OprosLock lock;
};

#endif

