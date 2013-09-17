
#ifndef _DigitalIOComp_COMPONENT_H
#define _DigitalIOComp_COMPONENT_H
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

#include "DigitalIOServiceProvided.h"
#include "DigitalIO.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

class DigitalIOComp: public Component
	,public IDigitalIOService
{
protected:
	OutputDataPort< vector<bool> > digitalInputData;
	InputDataPort< vector<bool> > digitalOutputData;

public:
	DigitalIOComp();
	DigitalIOComp(const std::string &compId);
	virtual ~DigitalIOComp();
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
	virtual bool SetDigitalOutputData(vector<bool> digitalOutputData);
	virtual vector<bool> GetDigitalInputData();

private:
	#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif

	DigitalIO *digitalIO;
	int error;
};

#endif

