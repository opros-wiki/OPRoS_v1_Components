#pragma once

#include "Speech.h"

#include "taskdef.h"
#include "errdef.h"
#include "yjrobotdef.h"
#include "yjrobotapi.h"

class YujinRobot_iRobiQSpeech : public Speech
{
public:
	YujinRobot_iRobiQSpeech(void);
	virtual ~YujinRobot_iRobiQSpeech(void);

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
	Property parameter;
	LPROBOTINTERFACE pRI;
	bool isConnected;
	VC_SPEECHTYPE type;
	
	bool iRobiQ_Initialize(void);
	bool iRobiQ_Finalize(void);
	bool iRobiQ_Connect(std::string ip, unsigned int port, unsigned short serviceId);
	bool iRobiQ_Disconnect(void);
	bool iRobiQSpeech_LoadTTS(VC_SPEECHTYPE type);
	bool iRobiQSpeech_UnloadTTS(VC_SPEECHTYPE type);
	bool iRobiQSpeech_PlayTTS(std::string text);
	bool iRobiQSpeech_StopTTS(void);

	static void CALLBACK EventMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam);
	static void CALLBACK ResponseMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam);
	static void CALLBACK AckMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam);
};
