#ifndef _HCILab_PowerSTTVoiceRecognitionComp_COMPONENT_H
#define _HCILab_PowerSTTVoiceRecognitionComp_COMPONENT_H
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

#include "VoiceRecognition.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif


class HCILab_PowerSTTVoiceRecComp: public Component
{
protected:
// data
	OutputDataPort< std::string > wordData;

public:
	HCILab_PowerSTTVoiceRecComp();
	HCILab_PowerSTTVoiceRecComp(const std::string &compId);
	virtual ~HCILab_PowerSTTVoiceRecComp();
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

private:
	char strModulePath [256];
	string strList1;
	BOOL LoadList1(char * fileName);
	void SetModulePath();
};

#endif

