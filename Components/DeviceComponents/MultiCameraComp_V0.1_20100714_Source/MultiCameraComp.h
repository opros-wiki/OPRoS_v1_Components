
#ifndef _MultiCameraComp_COMPONENT_H
#define _MultiCameraComp_COMPONENT_H
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

#include "MultiCameraServiceProvided.h"
#include "MultiCamera.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

class MultiCameraComp: public Component
	,public IMultiCameraService
{
protected:
	OutputDataPort< vector< vector<unsigned char> > > multiImageData;

public:
	MultiCameraComp();
	MultiCameraComp(const std::string &compId);
	virtual ~MultiCameraComp();
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
	virtual vector< vector<unsigned char> > GetImageData();

private:
	int error;
	int count;
	MultiCamera *multiCamera;
#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	
	vector< vector<unsigned char> > imageBuffer;
};

#endif

