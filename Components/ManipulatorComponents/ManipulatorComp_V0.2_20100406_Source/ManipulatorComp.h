#ifndef _ManipulatorComp_COMPONENT_H
#define _ManipulatorComp_COMPONENT_H
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

#include "Manipulator.h"
#include "ManipulatorServiceProvided.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif
	
class ManipulatorComp: public Component, public IManipulatorService
{
protected:


public:
	ManipulatorComp();
	ManipulatorComp(const std::string &compId);
	virtual ~ManipulatorComp();
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
	virtual bool Stop();
	virtual bool SetPower(vector<double> power,vector<unsigned long> time);
	virtual vector<double> GetPower();
	virtual bool SetVelocity(vector<double> velocity,vector<unsigned long> time);
	virtual vector<double> GetVelocity();
	virtual bool SetPosition(vector<double> position,vector<unsigned long> time);
	virtual vector<double> GetPosition();

private:
	/**
	*	OPRoS API ���̺귯���� �ڵ� �����̴�.
	*/
#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	Manipulator *manipulator;
	int error;
};

#endif

