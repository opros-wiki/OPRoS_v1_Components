#ifndef _TouchSensorComp_COMPONENT_H
#define _TouchSensorComp_COMPONENT_H
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

#include "TouchSensorServiceProvided.h"
#include "TouchSensor.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

class TouchSensorComp : public Component, public ITouchSensorService
{
protected:
	OutputDataPort< vector<bool> > touchData;

public:
	TouchSensorComp();
	TouchSensorComp(const std::string &compId);
	virtual ~TouchSensorComp();
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
	virtual vector<bool> GetTouchSensorData();

private:
	/**
	*	OPRoS API 라이브러리의 핸들 변수이다.
	*/
#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	TouchSensor *touchSensor;
	int error;
};

#endif

