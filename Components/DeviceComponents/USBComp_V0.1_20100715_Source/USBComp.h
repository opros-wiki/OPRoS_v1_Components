
#ifndef _USBComp_COMPONENT_H
#define _USBComp_COMPONENT_H
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

#include "USBServiceProvided.h"
#include "USB.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

class USBComp: public Component
	,public IUSBService
{
public:
	USBComp();
	USBComp(const std::string &compId);
	virtual ~USBComp();
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
	virtual int WriteData(vector<unsigned char> data);
	virtual vector<unsigned char> ReadData(int size);
	virtual bool Lock();
	virtual bool Unlock();

private:
#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif

	USB *usb;
	int error;
};

#endif

