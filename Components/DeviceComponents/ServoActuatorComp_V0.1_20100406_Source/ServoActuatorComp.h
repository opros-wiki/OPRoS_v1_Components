#ifndef _ServoActuatorComp_COMPONENT_H
#define _ServoActuatorComp_COMPONENT_H
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

#include "ServoActuator.h"
#include "ServoActuatorServiceProvided.h"

class ServoActuatorComp: public Component, public IServoActuatorService
{
public:
	ServoActuatorComp();
	ServoActuatorComp(const std::string &compId);
	virtual ~ServoActuatorComp();
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
	virtual bool SetVelocity(double velocity,unsigned long time);
	virtual double GetVelocity();
	virtual bool SetPosition(double position,unsigned long time);
	virtual double GetPosition();

private:
#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	ServoActuator *servoActuator;
	int error;
};

#endif

