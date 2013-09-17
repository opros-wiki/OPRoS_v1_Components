#ifndef _BatteryManagementSystemComp_COMPONENT_H
#define _BatteryManagementSystemComp_COMPONENT_H
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

#include "BatteryManagementSystemServiceProvided.h"
#include "BatteryManagementSystem.h"
#include "OprosLock.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

class BatteryManagementSystemComp: public Component
	,public IBatteryManagementSystemService
{
protected:
	OutputDataPort<double> voltageData;
#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	BatteryManagementSystem *bms;
	int error;
	OprosLock lock;

public:
	BatteryManagementSystemComp();
	BatteryManagementSystemComp(const std::string &compId);
	virtual ~BatteryManagementSystemComp();
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
	virtual double GetBatteryVoltage();
	virtual vector<double> GetCellVoltage();
};

#endif

