
#ifndef _AnalogIOComp_COMPONENT_H
#define _AnalogIOComp_COMPONENT_H
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
		
#include "AnalogIOServiceProvided.h"
#include "AnalogIO.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif
	
class AnalogIOComp: public Component
	,public IAnalogIOService
{
protected:
	OutputDataPort< vector<double> > analogInputData;
	InputDataPort< vector<double> > analogOutputData;

public:
	AnalogIOComp();
	AnalogIOComp(const std::string &compId);
	virtual ~AnalogIOComp();
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
	virtual bool SetAnalogOutputData(vector<double> analogOutputData);
	virtual vector<double> GetAnalogInputData();

private:
	#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif

	AnalogIO *analogIO;
	int error;
};

#endif

