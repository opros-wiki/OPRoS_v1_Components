#ifndef _PositionSensorComp_COMPONENT_H
#define _PositionSensorComp_COMPONENT_H
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

#include "PositionSensorServiceProvided.h"
#include "PositionSensor.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif
	
class PositionSensorComp : public Component, public IPositionSensorService
{
protected:
	// data
	OutputDataPort< vector<ObjectPosition> > positionData;

public:
	PositionSensorComp();
	PositionSensorComp(const std::string &compId);
	virtual ~PositionSensorComp();
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
	virtual vector<ObjectPosition> GetPositionSensorData();

private:
	/**
	*	OPRoS API 라이브러리의 핸들 변수이다.
	*/
#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	PositionSensor *positionSensor;
	int error;
};

#endif

