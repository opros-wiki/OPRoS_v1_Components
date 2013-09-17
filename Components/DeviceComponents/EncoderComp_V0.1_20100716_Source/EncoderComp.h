#ifndef _EncoderComp_COMPONENT_H
#define _EncoderComp_COMPONENT_H
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
		
#include "EncoderServiceProvided.h"
#include "Encoder.h"

#include "OprosLock.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

class EncoderComp: public Component
	,public IEncoderService
{
protected:
	OutputDataPort< vector<double> > encoderData;

public:
	EncoderComp();
	EncoderComp(const std::string &compId);
	virtual ~EncoderComp();
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
	virtual vector<double> GetEncoderData();

private:
#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	Encoder *encoder;
	int error;
	OprosLock lock;
};

#endif

