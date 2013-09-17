
#ifndef _UltrasonicSensorComp_COMPONENT_H
#define _UltrasonicSensorComp_COMPONENT_H
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

#include "UltrasonicSensorServiceProvided.h"
#include "UltrasonicSensor.h"
	
class UltrasonicSensorComp: public Component
	,public IUltrasonicSensorService
{
protected:
	OutputDataPort< vector<double> > ultrasonicData;

public:
	UltrasonicSensorComp();
	UltrasonicSensorComp(const std::string &compId);
	virtual ~UltrasonicSensorComp();
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
	virtual vector<double> GetUltrasonicSensorData();

private:
	/**
	*	OPRoS API 라이브러리의 핸들 변수이다.
	*/
#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	UltrasonicSensor *ultrasonicSensor;
	int error;
};

#endif

