
#ifndef _AnalogDigitalIOComp_COMPONENT_H
#define _AnalogDigitalIOComp_COMPONENT_H
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
		
#include "AnalogDigitalIOServiceProvided.h"
#include "AnalogDigitalIO.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif
	

class AnalogDigitalIOComp: public Component
	,public IAnalogDigitalIOService
{
protected:
	OutputDataPort< vector<double> > analogInputData;
	InputDataPort< vector<double> > analogOutputData;
	OutputDataPort< vector<bool> > digitalInputData;
	InputDataPort< vector<bool> > digitalOutputData;

public:
	AnalogDigitalIOComp();
	AnalogDigitalIOComp(const std::string &compId);
	virtual ~AnalogDigitalIOComp();
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
	virtual bool SetDigitalOutputData(vector<bool> digitalOutputData);
	virtual vector<bool> GetDigitalInputData();

private:
	#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif

	AnalogDigitalIO *analogDigitalIO;
	int error;
};

#endif

