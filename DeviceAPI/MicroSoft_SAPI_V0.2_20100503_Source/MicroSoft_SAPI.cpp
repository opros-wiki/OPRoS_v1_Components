#include "MicroSoft_SAPI.h"
#include "OprosPrintMessage.h"

MicroSoft_SAPI::MicroSoft_SAPI(void)
{
	pVoice = NULL;
}

MicroSoft_SAPI::~MicroSoft_SAPI(void)
{
	Finalize();
}

int MicroSoft_SAPI::Initialize(Property parameter)
{
	SetParameter(parameter);

	return SAPI_Initialize();
}

int MicroSoft_SAPI::Finalize(void)
{
	return SAPI_Uninitialize();
}

int MicroSoft_SAPI::Enable(void)
{
	return SAPI_Enable();
}

int MicroSoft_SAPI::Disable(void)
{
	return SAPI_Disable();
}

int MicroSoft_SAPI::SetParameter(Property parameter)
{
	this->parameter = parameter;

	return 0;
}

int MicroSoft_SAPI::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return 0;
}

int MicroSoft_SAPI::PlaySpeech(string speechData, int mode)
{
	if(mode != SPEECH_TEXT_STREAM) {
		return -1;
	}

	return SAPI_Play(speechData);
}

int MicroSoft_SAPI::StopSpeech(void)
{
	return SAPI_Stop();
}

int MicroSoft_SAPI::SAPI_Initialize(void)
{
	if (FAILED(::CoInitialize(NULL))) {
		PrintMessage("ERROR : MicorSoft_SAPI::SAPI_Initialize() -> Can't intialize the MicorSoft_SAPI\n");
		return -1;
	}

	return 0;
}

int MicroSoft_SAPI::SAPI_Uninitialize(void)
{
	if(pVoice != NULL) {
		pVoice->Release();
		pVoice = NULL;
	}

	::CoUninitialize();

	return 0;
}

int MicroSoft_SAPI::SAPI_Enable(void)
{
	if(pVoice != NULL) {
		return -1;
	}

	hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);

    if(!SUCCEEDED(hr)) {
		PrintMessage("ERROR : MicorSoft_SAPI::SAPI_Initialize() -> Can't enable the MicorSoft_SAPI\n");
		return -1;
    }

	return 0;
}

int MicroSoft_SAPI::SAPI_Disable(void)
{
	if(pVoice == NULL) {
		return 0;
	}

	pVoice->Release();
	pVoice = NULL;

	return 0;
}

int MicroSoft_SAPI::SAPI_Play(string text)
{
	if (FAILED(::CoInitialize(NULL))) {
		PrintMessage("ERROR : MicorSoft_SAPI::SAPI_Initialize() -> Can't intialize the MicorSoft_SAPI\n");
		return -1;
	}

	if(text.size() < 1) {
		return 0;
	}

	PrintMessage("INFO : MicorSoft_SAPI::SAPI_Play() -> Text : %s\n", text.c_str());

	WCHAR *wText = new WCHAR[text.size()];
	MultiByteToWideChar(CP_ACP, MB_COMPOSITE, text.c_str(), -1, wText, text.size());

	hr = pVoice->Speak(wText, 0, NULL);

	if(text.size() == 1) {
		delete wText;
	}
	else {
		delete [] wText;
	}

	if (!SUCCEEDED(hr)) {
		PrintMessage("ERROR : MicorSoft_SAPI::SAPI_Play() -> Can't speak.\n");
		return -1;
	}

	return 0;
}

int MicroSoft_SAPI::SAPI_Pause(void)
{
	if(pVoice == NULL) {
		return -1;
	}

	if(pVoice->Pause() != S_OK) {
		return -1;
	}

	return 0;
}

int MicroSoft_SAPI::SAPI_Resume(void)
{
	if(pVoice == NULL) {
		return -1;
	}

	if(pVoice->Resume() != S_OK) {
		return -1;
	}

	return 0;
}

int MicroSoft_SAPI::SAPI_Stop(void)
{
	if(pVoice == NULL) {
		return -1;
	}
	
	unsigned long temp;
	if(pVoice->Skip(L"SENTENCE", 0, &temp) != S_OK) {
		return -1;
	}

	return 0;
}


#if defined(WIN32)
extern "C"
{
__declspec(dllexport) OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new MicroSoft_SAPI();
}
#endif