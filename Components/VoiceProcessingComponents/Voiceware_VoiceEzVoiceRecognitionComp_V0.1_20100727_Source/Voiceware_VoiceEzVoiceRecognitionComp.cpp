
/*
 *  Generated sources by OPRoS Component Generator (OCG V2)
 *  
 */
#include <Component.h>
#include <InputDataPort.h>
#include <OutputDataPort.h>
#include <InputEventPort.h>
#include <OutputEventPort.h>
#include <OPRoSTypes.h>
#include <EventData.h>

#include "Voiceware_VoiceEzVoiceRecognitionComp.h"

#include "OprosPrintMessage.h"

UINT VoiceEZDlgThreadProc(LPVOID pParam);
VoiceRecDlg *voiceDlg;

//
// constructor declaration
//
Voiceware_VoiceEzVoiceRecognitionComp::Voiceware_VoiceEzVoiceRecognitionComp()
{
	AfxBeginThread(VoiceEZDlgThreadProc, this);

	portSetup();
}

//
// constructor declaration (with name)
//
Voiceware_VoiceEzVoiceRecognitionComp::Voiceware_VoiceEzVoiceRecognitionComp(const std::string &name):Component(name)
{
	AfxBeginThread(VoiceEZDlgThreadProc, this);

	portSetup();
}

//
// destructor declaration
//

Voiceware_VoiceEzVoiceRecognitionComp::~Voiceware_VoiceEzVoiceRecognitionComp() {
	onDestroy();
}

void Voiceware_VoiceEzVoiceRecognitionComp::portSetup() {
	// data port setup
	addPort("WordData", &wordData);
}

// Call back Declaration
ReturnType Voiceware_VoiceEzVoiceRecognitionComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	return OPROS_SUCCESS;
}

ReturnType Voiceware_VoiceEzVoiceRecognitionComp::onStart()
{
	if( voiceRecDlg->StartVoiceEZ() ) {
		PrintMessage("Success:Voiceware_VoiceEZ::Enable()\n");
		return OPROS_SUCCESS;
	}
	else {
		PrintMessage("Error:Voiceware_VoiceEZ::Enable()\n");
		return OPROS_INTERNAL_FAULT;
	}
}
	
ReturnType Voiceware_VoiceEzVoiceRecognitionComp::onStop()
{
	if( voiceRecDlg->StopVoiceEZ() ) {
		PrintMessage("Success:Voiceware_VoiceEZ::Disable()\n");
		return OPROS_SUCCESS;
	}
	else {
		PrintMessage("Error:Voiceware_VoiceEZ::Disable()\n");
		return OPROS_INTERNAL_FAULT;
	}
}

ReturnType Voiceware_VoiceEzVoiceRecognitionComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType Voiceware_VoiceEzVoiceRecognitionComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType Voiceware_VoiceEzVoiceRecognitionComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType Voiceware_VoiceEzVoiceRecognitionComp::onDestroy()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType Voiceware_VoiceEzVoiceRecognitionComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType Voiceware_VoiceEzVoiceRecognitionComp::onExecute()
{

	std::string result;
	voiceRecDlg->GetVoiceResult(&result);

	if( strlen(result.c_str()) > 0 ) {
		wordData.push(result);
	}
	return OPROS_SUCCESS;
}
	
ReturnType Voiceware_VoiceEzVoiceRecognitionComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType Voiceware_VoiceEzVoiceRecognitionComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}



#ifdef MAKE_COMPONENT_DLL
#ifdef WIN32

extern "C"
{
__declspec(dllexport) Component *getComponent();
__declspec(dllexport) void releaseComponent(Component *pcom);
}

Component *getComponent()
{
	return new Voiceware_VoiceEzVoiceRecognitionComp();
}

void releaseComponent(Component *com)
{
	delete com;
}

UINT VoiceEZDlgThreadProc(LPVOID pParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());	

	Voiceware_VoiceEzVoiceRecognitionComp *pcom = (Voiceware_VoiceEzVoiceRecognitionComp *)pParam;
	VoiceRecDlg dlg(::AfxGetMainWnd());
	voiceDlg = &dlg;

	pcom->voiceRecDlg =  &dlg;

	dlg.DoModal();

	pcom->voiceRecDlg = NULL;

	return 0;
}

#else
extern "C"
{
	Component *getComponent();
	void releaseComponent(Component *com);
}
Component *getComponent()
{
	return new Voiceware_VoiceEzVoiceRecognitionComp();
}

void releaseComponent(Component *com)
{
	delete com;
}

#endif
#endif

