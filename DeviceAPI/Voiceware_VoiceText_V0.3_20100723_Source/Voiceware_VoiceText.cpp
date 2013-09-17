#include "Voiceware_VoiceText.h"

#include "vt/vt_kor.h"
#include "vt/vt_eng.h"
#include "OprosPrintMessage.h"

Voiceware_VoiceText::Voiceware_VoiceText(void)
{
}

Voiceware_VoiceText::~Voiceware_VoiceText(void)
{
	Finalize();
}

int Voiceware_VoiceText::Initialize(Property parameter)
{
	SetParameter(parameter);

	return VT_Initialize();
}

int Voiceware_VoiceText::Finalize(void)
{
	return VT_Uninitialize();
}

int Voiceware_VoiceText::Enable(void)
{
	return VT_Enable();
}

int Voiceware_VoiceText::Disable(void)
{
	return VT_Disable();
}

int Voiceware_VoiceText::SetParameter(Property parameter)
{
	this->parameter = parameter;

	return 0;
}

int Voiceware_VoiceText::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return 0;
}

int Voiceware_VoiceText::PlaySpeech(string speechData, int mode)
{
	if(mode != SPEECH_TEXT_STREAM) {
		return -1;
	}

	return VT_Play(speechData);
}

int Voiceware_VoiceText::StopSpeech(void)
{
	return VT_Stop();
}

int Voiceware_VoiceText::VT_Initialize(void)
{
	const char *speaker = "Junwoo";
	_startWord = 0;
	_endWord = -1;
	_speakerID = SpeakerName2ID (speaker);

	int infoval = 0;

	VT_GetTTSInfo(VT_LOAD_SUCCESS_CODE, NULL, &infoval, sizeof(int));

	int ret = VT_LOADTTS(NULL, _speakerID, NULL, NULL);
	if (ret != infoval) {
		PrintMessage ("WARNING: 지정한 화자 %s를 로딩하지 못하였습니다. 기본 화자 로딩을 시도합니다.", speaker);

		// 지정한 화자(_speakerID)를 로딩 하지 못한 경우 기본 값(-1)로 기본 화자를 로딩 한다.
		_speakerID = -1;
		ret = VT_LOADTTS(NULL, _speakerID, NULL, NULL);
		if (ret != infoval) {
			PrintMessage ("ERROR: VT_LOADTTS_KOR() or VT_LOADTTS_ENG() failed");
			return -1;
		}
		VT_GetTTSInfo(VT_DEF_SPEAKER, NULL, &infoval, sizeof(int));
		PrintMessage ("INFO: 기본 화자 %s를 로딩하였습니다.", SpeakerID2Name (infoval));
	}

	_init = true;
	PrintMessage ("Voiceware TTS initialized");

	if ( !_init ) {
		PrintMessage("ERROR : Voiceware_VoiceText::VT_Initialize() -> Can't intialize the Voiceware_VoiceText\n");
		return -1;
	}

	return 0;
}

int Voiceware_VoiceText::VT_Uninitialize(void)
{
	if (_init) {
		VT_UNLOADTTS (-1);
	}

	return 0;
}

int Voiceware_VoiceText::VT_Enable(void)
{
	SetProperty(100, 100, 100, 100);

	return 0;
}

int Voiceware_VoiceText::VT_Disable(void)
{

	return 0;
}

int Voiceware_VoiceText::VT_Play(string text)
{
	if (!_init) return -1;

	VT_STOPTTS ();

	_startWord = 0;
	_endWord = 0;

	VT_PLAYTTS (_hWnd, _msg, (char *)text.c_str(), _speakerID, _pitch, _speed, _volume, _pause, -1, -1);

	return 0;
}

int Voiceware_VoiceText::VT_Pause(void)
{
	return -1;
}

int Voiceware_VoiceText::VT_Resume(void)
{
	return -1;
}

int Voiceware_VoiceText::VT_Stop(void)
{
	if (!_init) return -1;

	VT_STOPTTS ();

	_startWord = 0;
	_endWord = -1;

	return 0;
}



int Voiceware_VoiceText::SpeakerName2ID (const char *speaker)
{
	if (stricmp ("junwoo", speaker) == 0) return 3;
	else if (stricmp ("sujin", speaker) == 0) return 8;
	else if (stricmp ("yumi", speaker) == 0) return 10;
	else if (stricmp ("gyuri", speaker) == 0) return 11;
	else if (stricmp ("dayoung", speaker) == 0) return 12;
	else if (stricmp ("paul", speaker) == 0) return 101;
	else return -1;
}

const char *Voiceware_VoiceText::SpeakerID2Name (int id)
{
	switch (id) {
	case 3: return "junwoo"; 
	case 8: return "sujin";
	case 10: return "yumi";
	case 11: return "gyuri";
	case 12: return "dayoung";
	case 101: return "paul";
	default: return "[unknown]";
	}
}

void Voiceware_VoiceText::SetVoice (const char *speaker)
{
	if (!_init) return;

	VT_UNLOADTTS (_speakerID);
	
	_speakerID = SpeakerName2ID (speaker);

	int infoval = 0;
	VT_GetTTSInfo(VT_LOAD_SUCCESS_CODE, NULL, &infoval, sizeof(int));

	int ret = VT_LOADTTS(_hWnd, _speakerID, NULL, NULL);
	if (ret != infoval) {
		PrintMessage ("WARNING: 지정한 화자 %s를 로딩하지 못하였습니다. 기본 화자 로딩을 시도합니다.", speaker);

		// 지정한 화자(_speakerID)를 로딩 하지 못한 경우 기본 값(-1)로 기본 화자를 로딩 한다.
		_speakerID = -1;
		ret = VT_LOADTTS(_hWnd, _speakerID, NULL, NULL);
		if (ret != infoval) {
			PrintMessage ("ERROR: VT_LOADTTS_KOR() or VT_LOADTTS_ENG() failed");
			return;
		}
		VT_GetTTSInfo(VT_DEF_SPEAKER, NULL, &infoval, sizeof(int));
		PrintMessage ("INFO: 기본 화자 %s를 로딩하였습니다.", SpeakerID2Name (infoval));
	}
}

void Voiceware_VoiceText::SetProperty (int pitch, int speed, int volume, int pause)
{
	// Pitch: 합성 음의 높낮이를 설정
	// 기본값은 100이고, 0으로 세팅했을 때 기본값인 100으로 세팅됨
	// 유효 범위는 0 ~ 200
	pitch = bound (pitch, 0, 200);
	_pitch = pitch;

	// Speed: 합성 속도를 설정
	// 기본값은 100이고, 0으로 세팅했을 때 기본값인 100으로 세팅됨
	// 유효 범위는 25 ~ 400
	speed = bound (speed, 25, 400);
	_speed = speed;

	// Volume: 음량을 설정
	// 기본값은 100이고, 0으로 세팅했을 때 기본 값인 100으로 세팅됨
	// 유효 범위는 0 ~ 500
	_volume = volume;	// 200 이상은 쓰지 않는다.

	_pause = pause;
}

eLanguage Voiceware_VoiceText::SpeakerLanguage(int speakerID)
{
	eLanguage language = KOREAN;

	if( 0 <= speakerID && speakerID < 100 )
		language = KOREAN;
	else if( 100 <= speakerID && speakerID < 200 )
		language = ENGLISH;
	else if( 200 <= speakerID && speakerID < 300 )
		language = JAPANESE;
	else if( 300 <= speakerID && speakerID < 400 )
		language = CHINESE;

	return language;
}

int Voiceware_VoiceText::VT_GetTTSInfo(int request, char *licensefile, void *value, int valuesize)
{
	if( SpeakerLanguage(_speakerID) == ENGLISH )
		return VT_GetTTSInfo_ENG(request, licensefile, value, valuesize);
	else
		return VT_GetTTSInfo_KOR(request, licensefile, value, valuesize);
}

short Voiceware_VoiceText::VT_LOADTTS(HWND hWnd, int nSpeakerID, char *db_path, char *licensefile)
{
	if( SpeakerLanguage(_speakerID) == ENGLISH )
		return VT_LOADTTS_ENG(hWnd, nSpeakerID-ENGLISH, db_path, licensefile);
	else
		return VT_LOADTTS_KOR(hWnd, nSpeakerID, db_path, licensefile);
}

void Voiceware_VoiceText::VT_UNLOADTTS(int nSpeakerID)
{
	if( SpeakerLanguage(_speakerID) == ENGLISH )
		VT_UNLOADTTS_ENG(nSpeakerID);
	else
		VT_UNLOADTTS_KOR(nSpeakerID);
}

short Voiceware_VoiceText::VT_TextToFile(int fmt, char *tts_text, char *filename, int nSpeakerID, int pitch, int speed, int volume, int pause, int dictidx, int texttype)
{
	if( SpeakerLanguage(_speakerID) == ENGLISH )
		return VT_TextToFile_ENG(fmt, tts_text, filename, nSpeakerID, pitch, speed, volume, pause, dictidx, texttype);
	else
		return VT_TextToFile_KOR(fmt, tts_text, filename, nSpeakerID, pitch, speed, volume, pause, dictidx, texttype);
}

void Voiceware_VoiceText::VT_STOPTTS()
{
	if( SpeakerLanguage(_speakerID) == ENGLISH )
		VT_STOPTTS_ENG();
	else
		VT_STOPTTS_KOR();
}

short Voiceware_VoiceText::VT_PLAYTTS(HWND hcaller, UINT umsg, char *text_buff, int nSpeakerID, int pitch, int speed, int volume, int pause, int dictidx, int texttype)
{
	if( SpeakerLanguage(_speakerID) == ENGLISH )
		return VT_PLAYTTS_ENG(hcaller, umsg, text_buff, nSpeakerID, pitch, speed, volume, pause, dictidx, texttype);
	else
		return VT_PLAYTTS_KOR(hcaller, umsg, text_buff, nSpeakerID, pitch, speed, volume, pause, dictidx, texttype);
}

#if defined(WIN32)
extern "C"
{
__declspec(dllexport) OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new Voiceware_VoiceText();
}
#endif