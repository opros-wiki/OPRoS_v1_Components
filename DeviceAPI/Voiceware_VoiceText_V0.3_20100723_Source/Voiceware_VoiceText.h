#pragma once

#include "Windows.h"
#include "Speech.h"

enum eLanguage{
	KOREAN = 0,
	ENGLISH = 100,
	JAPANESE = 200,
	CHINESE = 300,
};

class Voiceware_VoiceText : public Speech
{
public:
	Voiceware_VoiceText(void);
	virtual ~Voiceware_VoiceText(void);

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);

	int PlaySpeech(string speechData, int mode);
	int StopSpeech(void);

	int SpeakerName2ID (const char *speaker);
	const char *SpeakerID2Name (int id);
	void SetVoice (const char *speaker);
	void SetProperty (int pitch, int speed, int volume, int pause);


private:
	HRESULT hr;
	Property parameter;

	int _speakerID;
	int _pitch; 
	int _speed; 
	int _volume;
	int _pause; 

private:
	int _option;
	bool _init;
	HWND _hWnd;
	int _msg;

	int _startWord;
	int _endWord;

	int VT_Initialize(void);
	int VT_Uninitialize(void);
	int VT_Enable(void);
	int VT_Disable(void);
	int VT_Play(string text);
	int VT_Pause(void);
	int VT_Resume(void);
	int VT_Stop(void);

	virtual eLanguage SpeakerLanguage(int speakerID);
	int   VT_GetTTSInfo(int request, char *licensefile, void *value, int valuesize);
	short VT_LOADTTS(HWND hWnd, int nSpeakerID, char *db_path, char *licensefile);
	void  VT_UNLOADTTS(int nSpeakerID);
	short VT_TextToFile(int fmt, char *tts_text, char *filename, int nSpeakerID, int pitch, int speed, int volume, int pause, int dictidx, int texttype);
	short VT_PLAYTTS(HWND hcaller, UINT umsg, char *text_buff, int nSpeakerID, int pitch, int speed, int volume, int pause, int dictidx, int texttype);
	void  VT_STOPTTS();
};
