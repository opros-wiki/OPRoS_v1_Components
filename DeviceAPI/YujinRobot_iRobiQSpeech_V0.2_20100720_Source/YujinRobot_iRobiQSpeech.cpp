#include "YujinRobot_iRobiQSpeech.h"
#include "OprosPrintMessage.h"
#include <map>

using namespace std;

#define	IROBIQ_CONNECTION_DELAY		(5000)
#define	IROBIQ_COMMAND_DELAY		(1000)

class iRobiQEvent
{
public:
	bool result;
	HANDLE connectionEvent;
	HANDLE commandEvent;
};

static map<LPROBOTINTERFACE, iRobiQEvent> iRobiQEventInfo;
static WORD cmdID = 0;

YujinRobot_iRobiQSpeech::YujinRobot_iRobiQSpeech(void)
{
	pRI = NULL;
	isConnected = false;
}

YujinRobot_iRobiQSpeech::~YujinRobot_iRobiQSpeech(void)
{
	Finalize();
}

int YujinRobot_iRobiQSpeech::Initialize(Property parameter)
{
	if(SetParameter(parameter) == false) {
		return false;
	}

	if(parameter.FindName("IP") == false) {
		PrintMessage("ERROR : YujinRobot_iRobiQSpeech::initialize() -> Can't find the IP Address\n");
		return false;
	}
	std::string ip = parameter.GetValue("IP");

	if(parameter.FindName("Port") == false) {
		PrintMessage("ERROR : YujinRobot_iRobiQSpeech::initialize() -> Can't find the Port Number\n");
		return false;
	}
	unsigned int port = (unsigned int)atoi(parameter.GetValue("Port").c_str());

	if(parameter.FindName("ServiceID") == false) {
		PrintMessage("ERROR : YujinRobot_iRobiQSpeech::initialize() -> Can't find the Service ID\n");
		return false;
	}
	unsigned short serviceId = (unsigned short)atoi(parameter.GetValue("ServiceID").c_str());

	if(iRobiQ_Initialize() == false) {
		return false;
	}

	if(iRobiQ_Connect(ip, port, serviceId) == false) {
		iRobiQ_Finalize();
	}

	return true;
}

int YujinRobot_iRobiQSpeech::Finalize(void)
{
	if(iRobiQ_Finalize() == false) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQSpeech::Enable(void)
{
	if(iRobiQ_Finalize() == false) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQSpeech::Disable(void)
{
	return API_SUCCESS;
}

int YujinRobot_iRobiQSpeech::SetParameter(Property parameter)
{
	this->parameter = parameter;

	return API_SUCCESS;
}

int YujinRobot_iRobiQSpeech::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int YujinRobot_iRobiQSpeech::PlaySpeech(string speechData, int mode)
{
	if(iRobiQSpeech_PlayTTS(speechData) == false) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQSpeech::StopSpeech(void)
{
	if(iRobiQSpeech_StopTTS() == false) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

bool YujinRobot_iRobiQSpeech::iRobiQ_Initialize(void)
{
	if(YJCI_CreateInstance(&pRI) == YJERR_SUCCESS) {
		YJCI_RegAcknowledgeProc(pRI, AckMsgProc);
		YJCI_RegResponseProc(pRI, ResponseMsgProc);
		YJCI_RegEventProc(pRI, EventMsgProc);

		iRobiQEventInfo[pRI].connectionEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		iRobiQEventInfo[pRI].commandEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

		PrintMessage("SUCCESS : YujinRobot_iRobiQSpeech::iRobiQ_Initialize() -> iRobiQSpeech is initialized.\n");
	}
	else {
		PrintMessage("ERROR : YujinRobot_iRobiQSpeech::iRobiQ_Initialize() -> iRobiQSpeech isn't intialized.\n");
		pRI = NULL;
	}

	return true;
}

bool YujinRobot_iRobiQSpeech::iRobiQ_Finalize(void)
{
	if(pRI != NULL)
	{
		if(isConnected == true) {
			iRobiQ_Disconnect();
		}

		if(iRobiQEventInfo.find(pRI) != iRobiQEventInfo.end()) {
			if(iRobiQEventInfo[pRI].connectionEvent != INVALID_HANDLE_VALUE) {
				CloseHandle(iRobiQEventInfo[pRI].connectionEvent);
				iRobiQEventInfo[pRI].connectionEvent = INVALID_HANDLE_VALUE;
			}

			if(iRobiQEventInfo[pRI].commandEvent != INVALID_HANDLE_VALUE) {
				CloseHandle(iRobiQEventInfo[pRI].commandEvent);
				iRobiQEventInfo[pRI].commandEvent = INVALID_HANDLE_VALUE;
			}

			iRobiQEventInfo.erase(pRI);
		}

		YJCI_DeleteInstance(&pRI);
		pRI = NULL;

		PrintMessage("SUCCESS : YujinRobot_iRobiQSpeech::iRobiQ_Finalize() -> iRobiQSpeech is finalized.\n");
	}

	return true;
}

bool YujinRobot_iRobiQSpeech::iRobiQ_Connect(std::string ip, unsigned int port, unsigned short serviceId)
{
	if(isConnected == true) {
		PrintMessage("INFO : YujinRobot_iRobiQSpeech::iRobiQ_Connect() -> iRobiQSpeech is already connected.\n");
		return true;
	}

	if(pRI == NULL || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("ERROR : YujinRobot_iRobiQSpeech::iRobiQ_Connect() -> iRobiQSpeech is initialized.\n");
		return false;
	}

	PrintMessage("INFO : YujinRobot_iRobiQSpeech::iRobiQ_Connect() -> IP : %s, Port : %d, Serivce ID : %d\n", ip.c_str(), port, serviceId);

	isConnected = false;
	if(YJCI_InitInterface(pRI, serviceId, ip.c_str(), port) == YJERR_SUCCESS) {
		if(WaitForSingleObject(iRobiQEventInfo[pRI].connectionEvent, IROBIQ_CONNECTION_DELAY) == WAIT_OBJECT_0) {
			if((isConnected = iRobiQEventInfo[pRI].result) == true) {
				PrintMessage("SUCCESS : YujinRobot_iRobiQSpeech::iRobiQ_Connect() -> iRobiQSpeech is connected.\n");
			}
		}
		ResetEvent(iRobiQEventInfo[pRI].connectionEvent);
	}

	if(isConnected == false) {
		PrintMessage("ERROR : YujinRobot_iRobiQSpeech::iRobiQ_Connect() -> Can't connect to iRobiQ\n");
	}

	return isConnected;
}

bool YujinRobot_iRobiQSpeech::iRobiQ_Disconnect(void)
{
	if(isConnected == false) {
		return true;
	}

	if(YJCI_UnInitInterface(pRI) != YJERR_SUCCESS) {
		PrintMessage("ERROR : YujinRobot_iRobiQSpeech::iRobiQ_Disconnect() -> iRobiQSpeech isn't disconnected.\n");
		return false;
	}
	isConnected = false;
	PrintMessage("SUCCESS : YujinRobot_iRobiQSpeech::iRobiQ_Disconnect() -> iRobiQSpeech is disconnected.\n");

	return true;
}

bool YujinRobot_iRobiQSpeech::iRobiQSpeech_LoadTTS(VC_SPEECHTYPE type)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	if(YJVC_LoadTTS(pRI, cmdID++, type, FALSE) != YJERR_SUCCESS) {
		return false;
	}

	if(WaitForSingleObject(iRobiQEventInfo[pRI].commandEvent, IROBIQ_COMMAND_DELAY) != WAIT_OBJECT_0) {
		return false;
	}
	ResetEvent(iRobiQEventInfo[pRI].commandEvent);
	
	return iRobiQEventInfo[pRI].result;
}

bool YujinRobot_iRobiQSpeech::iRobiQSpeech_UnloadTTS(VC_SPEECHTYPE type)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	if(YJVC_UnloadTTS(pRI, cmdID, type, FALSE) != YJERR_SUCCESS) {
		return false;
	}

	if(WaitForSingleObject(iRobiQEventInfo[pRI].commandEvent, IROBIQ_COMMAND_DELAY) != WAIT_OBJECT_0) {
		return false;
	}
	ResetEvent(iRobiQEventInfo[pRI].commandEvent);

	return iRobiQEventInfo[pRI].result;
}

bool YujinRobot_iRobiQSpeech::iRobiQSpeech_PlayTTS(std::string text)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	if(YJVC_PlayTTS(pRI, cmdID++, text.c_str(), type) != YJERR_SUCCESS) {
		return false;
	}

	if(WaitForSingleObject(iRobiQEventInfo[pRI].commandEvent, IROBIQ_COMMAND_DELAY) != WAIT_OBJECT_0) {
		return false;
	}
	ResetEvent(iRobiQEventInfo[pRI].commandEvent);

	return iRobiQEventInfo[pRI].result;
}

bool YujinRobot_iRobiQSpeech::iRobiQSpeech_StopTTS(void)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	if(YJVC_StopTTS(pRI, cmdID++, FALSE) != YJERR_SUCCESS) {
		return false;
	}

	if(WaitForSingleObject(iRobiQEventInfo[pRI].commandEvent, IROBIQ_COMMAND_DELAY) != WAIT_OBJECT_0) {
		return false;
	}
	ResetEvent(iRobiQEventInfo[pRI].commandEvent);

	return iRobiQEventInfo[pRI].result;
}

void YujinRobot_iRobiQSpeech::EventMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	if(iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("INFO : YujinRobot_iRobiQSpeech::EventMsgProc() -> Event Messsage : %8x\t%4x\n", dwTaskID, wParam);
		return;
	}

	switch (dwTaskID) {
		//	Connect Event
		case TASK_SYS_CONN:
			iRobiQEventInfo[pRI].result = false;
			switch(wParam) {
				case YJERR_CONN_SUCCESS:
					iRobiQEventInfo[pRI].result = true;
					PrintMessage("SUCCESS : YujinRobot_iRobiQSpeech::EventMsgProc() -> Connected to Robot successfully \n");
					break;

				case YJERR_CONN_CLOSED:
					PrintMessage("ERROR : YujinRobot_iRobiQSpeech::EventMsgProc() -> Connection was closed \n");
					break;

				case YJERR_CONN_HOSTUNREACH:
					PrintMessage("ERROR : YujinRobot_iRobiQSpeech::EventMsgProc() -> Unreachable host \n");
					break;

				case YJERR_CONN_TIMEDOUT:
					PrintMessage("ERROR : YujinRobot_iRobiQSpeech::EventMsgProc() -> Connection was timed out \n");
					break;

				case YJERR_CONN_CONNREFUSED:
					PrintMessage("ERROR : YujinRobot_iRobiQSpeech::EventMsgProc() -> Connection was refused \n");
					break;

				default:
					PrintMessage("ERROR : YujinRobot_iRobiQSpeech::EventMsgProc() -> Unknown error \n");
					break;
			}
			SetEvent(iRobiQEventInfo[pRI].connectionEvent);
			break;

		default:
			break;
	}
}

void YujinRobot_iRobiQSpeech::ResponseMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	DWORD dwResultCode = (DWORD)wParam;

	if(iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return;
	}
	
	switch (dwTaskID) {
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Voice
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case TASK_VC_LOAD_TTS :
			switch(dwResultCode) {
				case YJERR_SUCCESS :
					PrintMessage("SUCCESS : YujinRobot_iRobiQSpeech::ResponseMsgProc() -> YJVC_LoadTTS is succeeded\n");
					iRobiQEventInfo[pRI].result = true;
					break;

				default :
					PrintMessage("ERROR : YujinRobot_iRobiQSpeech::ResponseMsgProc() ->  YJVC_LoadTTS is failed : %x\n", dwResultCode);
					iRobiQEventInfo[pRI].result = false;
					break;
			}
			SetEvent(iRobiQEventInfo[pRI].commandEvent);
			break;

		case TASK_VC_UNLOAD_TTS :
			switch(dwResultCode) {
				case YJERR_SUCCESS :
					PrintMessage("SUCCESS : YujinRobot_iRobiQSpeech::ResponseMsgProc() ->  YJVC_UnloadTTS is succeeded\n");
					iRobiQEventInfo[pRI].result = true;
					break;

				default :
					PrintMessage("ERROR : YujinRobot_iRobiQSpeech::ResponseMsgProc() ->  YJVC_UnloadTTS is failed : %x\n", dwResultCode);
					iRobiQEventInfo[pRI].result = false;
					break;
			}
			SetEvent(iRobiQEventInfo[pRI].commandEvent);
			break;

		case TASK_VC_TTS_START :
			switch(dwResultCode) {
				case YJERR_SUCCESS :
					PrintMessage("SUCCESS : YujinRobot_iRobiQSpeech::ResponseMsgProc() ->  YJVC_PlayTTS is succeeded\n");
					iRobiQEventInfo[pRI].result = true;
					break;

				default :
					PrintMessage("ERROR : YujinRobot_iRobiQSpeech::ResponseMsgProc() ->  YJVC_PlayTTS is failed : \n", dwResultCode);
					iRobiQEventInfo[pRI].result = false;
					break;
			}
			SetEvent(iRobiQEventInfo[pRI].commandEvent);
			break;

		case TASK_VC_TTS_STOP :
			switch(dwResultCode) {
				case YJERR_SUCCESS :
					PrintMessage("SUCCESS : YujinRobot_iRobiQSpeech::ResponseMsgProc() ->  YJVC_StopTTS is succeeded\n");
					iRobiQEventInfo[pRI].result = true;
					break;

				default :
					PrintMessage("ERROR : YujinRobot_iRobiQSpeech::ResponseMsgProc() ->  YJVC_StopTTS is failed : \n", dwResultCode);
					iRobiQEventInfo[pRI].result = false;
					break;
			}
			SetEvent(iRobiQEventInfo[pRI].commandEvent);
			break;

		default:
			break;
	}
}

void YujinRobot_iRobiQSpeech::AckMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	//	iRobiQSpeech API에서는 사용하지 않음.
}

#if !defined(DEVICE_TEST)
#if defined(WIN32)
extern "C"
{
	__declspec(dllexport) OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new YujinRobot_iRobiQSpeech();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new YujinRobot_iRobiQSpeech();
}

#endif
#endif
