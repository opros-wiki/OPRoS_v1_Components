#ifndef _ActuatorComp_COMPONENT_H
#define _ActuatorComp_COMPONENT_H
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

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

#include "Actuator.h"
#include "ActuatorServiceProvided.h"
	
class ActuatorComp: public Component, public IActuatorService
{
protected:

public:
	ActuatorComp();
	ActuatorComp(const std::string &compId);
	virtual ~ActuatorComp();
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
	virtual bool SetPower(double power,unsigned long time);
	virtual double GetPower();

private:
#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	Actuator *actuator;
	int error;
};

#endif

