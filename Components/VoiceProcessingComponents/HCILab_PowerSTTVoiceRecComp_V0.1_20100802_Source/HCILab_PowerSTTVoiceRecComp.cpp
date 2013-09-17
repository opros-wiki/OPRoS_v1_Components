
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

#include "afxwin.h"
#include "resource.h"
#include "afxcmn.h"

#include "HCILab_PowerSTTVoiceRecComp.h"
#include "PowerSTT.h"

#include "OprosPrintMessage.h"

UINT PowerSTTThreadProc(LPVOID pParam);
BOOL   g_bStop = TRUE;
string recResult;

//
// constructor declaration
//
HCILab_PowerSTTVoiceRecComp::HCILab_PowerSTTVoiceRecComp()
{
	portSetup();
}

//
// constructor declaration (with name)
//
HCILab_PowerSTTVoiceRecComp::HCILab_PowerSTTVoiceRecComp(const std::string &name):Component(name)
{
	portSetup();
}

//
// destructor declaration
//

HCILab_PowerSTTVoiceRecComp::~HCILab_PowerSTTVoiceRecComp() {
	onDestroy();
}

void HCILab_PowerSTTVoiceRecComp::portSetup() {
	// data port setup
	addPort("WordData", &wordData);
}

// Call back Declaration
ReturnType HCILab_PowerSTTVoiceRecComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	if(parameter.FindName("WordList") == false) {
		PrintMessage("ERROR : HCILab_PowerSTTVoiceRecComp::onInitialize() -> Can't find the WordList in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	SetModulePath();
	int err = power_stt_kor_create(strModulePath);
	if( err != 1 )
		PrintMessage("Error:HCILab_PowerSTTVoiceRecComp::power_stt_kor_create ()\n");

	if( LoadList1((char *)parameter.GetValue("WordList").c_str()) ) {
		PrintMessage("INFO:HCILab_PowerSTTVoiceRecComp::onInitialize() %s -> %s\n", parameter.GetValue("WordList").c_str(), strList1.c_str());
		power_stt_kor_set_vocab((char *)strList1.c_str(), "");
	}

	PrintMessage("Success : HCILab_PowerSTTVoiceRecComp::onInitialize()\n");
	return OPROS_SUCCESS;
}

ReturnType HCILab_PowerSTTVoiceRecComp::onStart()
{
	g_bStop = false;
	AfxBeginThread(PowerSTTThreadProc, this);
	PrintMessage("Success:HCILab_PowerSTTVoiceRecComp::Enable()\n");
	return OPROS_SUCCESS;
}
	
ReturnType HCILab_PowerSTTVoiceRecComp::onStop()
{
	g_bStop = true;
	Sleep(100);
	PrintMessage("Success:HCILab_PowerSTTVoiceRecComp::Disable()\n");
	return OPROS_SUCCESS;
}

ReturnType HCILab_PowerSTTVoiceRecComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType HCILab_PowerSTTVoiceRecComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType HCILab_PowerSTTVoiceRecComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType HCILab_PowerSTTVoiceRecComp::onDestroy()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType HCILab_PowerSTTVoiceRecComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType HCILab_PowerSTTVoiceRecComp::onExecute()
{
	if( strlen(recResult.c_str()) ) {
		wordData.push(recResult);
		recResult.clear();
	}
	return OPROS_SUCCESS;
}
	
ReturnType HCILab_PowerSTTVoiceRecComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType HCILab_PowerSTTVoiceRecComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

BOOL HCILab_PowerSTTVoiceRecComp::LoadList1(char * fileName)
{
	FILE *fp = fopen (fileName, "rb");
	int numStr, i, len;
	char Buf [255];
	
	strList1 = "";

	if (!fp)
	{
		return FALSE;
	}

	numStr = 0;
	while(!feof(fp)) {
		if (fgets(Buf,255,fp)==NULL) break;
		if (strlen(Buf) > 2) numStr++;		
	}
	if (numStr <= 0) {
		fclose(fp);
		return FALSE;
	}
	fseek (fp, 0, SEEK_SET);

	for(i=0; i<numStr; i++) {
		if (fgets(Buf,255,fp)==NULL) break;
		Buf [strlen (Buf) -2] = NULL;
		len = strlen(Buf);
		
		if (len > 1) {
			strList1 += Buf;
			strList1 += "/";
		}
	}
	fclose(fp);


	return TRUE;
}

void HCILab_PowerSTTVoiceRecComp::SetModulePath()
{
	char szPath[MAX_PATH]= {0,};
	GetModuleFileName(NULL, szPath, MAX_PATH);
	
	int Len, i;	
	Len = (int)strlen(szPath);
	
	for (i = Len-1; i > 0; i--)
	{
		if (szPath[i] == '\\' || szPath[i] == '/') break;
	}
	
	memset (strModulePath, NULL, MAX_PATH);
	strncpy (strModulePath, szPath, i + 1);
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
	return new HCILab_PowerSTTVoiceRecComp();
}

void releaseComponent(Component *com)
{
	delete com;
}

UINT PowerSTTThreadProc(LPVOID pParam)
{
	short FrameBuff [1600];
	short res;
	RESULT_API_t asrResult;

	while( !g_bStop ) {
		power_stt_kor_start_record ();
		power_stt_kor_init_voice ();

		while(TRUE) {
			while (!g_bStop && !power_stt_kor_get_frame(FrameBuff, FALSE) ) {
				if (!power_stt_kor_decod_proc() )
					Sleep (10);
			}
			if (g_bStop) break;
			res = power_stt_kor_frame_proc(FrameBuff);						
			if (g_bStop) break;	

			switch (res)
			{
				case -1 : // 너무 긴 발성구간
				case -2 : // 크게 말씀해 주세요.
				case -3 : // 작게 말씀해 주세요.
					power_stt_kor_init_voice ();
					break;			
				case 1 :
					break;
				case 0 :
					break;
			}
			if (res == 1) break;
			if (g_bStop) break;
		}

		power_stt_kor_stop_record();
		if (g_bStop) break;
		res = power_stt_kor_get_result (&asrResult);
	
		if( res > 0 ) {
			recResult = asrResult.OutString[0];
//			PrintMessage("INFO:HCILab_PowerSTTVoiceRecComp::[Recog] %s\n", asrResult.OutString[0]);
		}
	}

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
	return new HCILab_PowerSTTVoiceRecComp();
}

void releaseComponent(Component *com)
{
	delete com;
}

#endif
#endif

