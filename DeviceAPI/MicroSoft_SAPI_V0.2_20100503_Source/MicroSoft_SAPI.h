#pragma once

#include "Speech.h"
#include "sapi.h"

class MicroSoft_SAPI : public Speech
{
public:
	MicroSoft_SAPI(void);
	virtual ~MicroSoft_SAPI(void);

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);

	int PlaySpeech(string speechData, int mode);
	int StopSpeech(void);

private:
	ISpVoice *pVoice;
	HRESULT hr;
	Property parameter;

	int SAPI_Initialize(void);
	int SAPI_Uninitialize(void);
	int SAPI_Enable(void);
	int SAPI_Disable(void);
	int SAPI_Play(string text);
	int SAPI_Pause(void);
	int SAPI_Resume(void);
	int SAPI_Stop(void);
};
