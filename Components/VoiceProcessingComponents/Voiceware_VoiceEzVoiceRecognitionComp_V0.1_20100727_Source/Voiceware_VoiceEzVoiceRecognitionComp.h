#ifndef _Voiceware_VoiceEzVoiceRecognitionComp_COMPONENT_H
#define _Voiceware_VoiceEzVoiceRecognitionComp_COMPONENT_H
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

#include "VoiceRecDlg.h"
#include "VoiceRecognition.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif


class Voiceware_VoiceEzVoiceRecognitionComp: public Component
{
protected:
// data
	OutputDataPort< std::string > wordData;

public:
	Voiceware_VoiceEzVoiceRecognitionComp();
	Voiceware_VoiceEzVoiceRecognitionComp(const std::string &compId);
	virtual ~Voiceware_VoiceEzVoiceRecognitionComp();
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

public:
	VoiceRecDlg	*voiceRecDlg;
};

#endif

