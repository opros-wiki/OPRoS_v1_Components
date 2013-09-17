#include "iRobiQSonar.h"
#include "OprosPrintMessage.h"

#include <map>

using namespace std;

#define	IROBIQ_CONNECTION_DELAY		(5000)
#define	IROBIQ_COMMAND_DELAY		(1000)
#define	IROBIQ_SONAR_SIZE			(4)

class iRobiQEvent
{
public:
	bool result;
	HANDLE connectionEvent;
	HANDLE commandEvent;
};

static map<LPROBOTINTERFACE, iRobiQEvent> iRobiQEventInfo;
static WORD cmdID = 0;
static double sonarValue[IROBIQ_SONAR_SIZE] = {0.0, };

iRobiQSonar::iRobiQSonar(void)
{
	pRI = NULL;
	isConnected = false;
}

iRobiQSonar::~iRobiQSonar(void)
{
	iRobiQ_Finalize();
}

bool iRobiQSonar::iRobiQ_Initialize(void)
{
	if(YJCI_CreateInstance(&pRI) == YJERR_SUCCESS) {
		YJCI_RegAcknowledgeProc(pRI, AckMsgProc);
		YJCI_RegResponseProc(pRI, ResponseMsgProc);
		YJCI_RegEventProc(pRI, EventMsgProc);

		iRobiQEventInfo[pRI].connectionEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		iRobiQEventInfo[pRI].commandEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

		PrintMessage("SUCCESS : iRobiQSonar::iRobiQ_Initialize() -> iRobiQSonar is initialized.\n");
	}
	else {
		PrintMessage("ERROR : iRobiQSonar::iRobiQ_Initialize() -> iRobiQSonar isn't intialized.\n");
		pRI = NULL;
	}

	return true;
}

bool iRobiQSonar::iRobiQ_Finalize(void)
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

		PrintMessage("SUCCESS : iRobiQSonar::iRobiQ_Finalize() -> iRobiQSonar is finalized.\n");
	}

	return true;
}

bool iRobiQSonar::iRobiQ_Connect(std::string ip, unsigned int port, unsigned short serviceId)
{
	if(isConnected == true) {
		PrintMessage("INFO : iRobiQSonar::iRobiQ_Connect() -> iRobiQSonar is already connected.\n");
		return true;
	}

	if(pRI == NULL || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("ERROR : iRobiQSonar::iRobiQ_Connect() -> iRobiQSonar is initialized.\n");
		return false;
	}

	PrintMessage("INFO : iRobiQSonar::iRobiQ_Connect() -> IP : %s, Port : %d, Serivce ID : %d\n", ip.c_str(), port, serviceId);

	isConnected = false;
	if(YJCI_InitInterface(pRI, serviceId, ip.c_str(), port) == YJERR_SUCCESS) {
		if(WaitForSingleObject(iRobiQEventInfo[pRI].connectionEvent, IROBIQ_CONNECTION_DELAY) == WAIT_OBJECT_0) {
			if((isConnected = iRobiQEventInfo[pRI].result) == true) {
				PrintMessage("SUCCESS : iRobiQSonar::iRobiQ_Connect() -> iRobiQSonar is connected.\n");
			}
		}
		ResetEvent(iRobiQEventInfo[pRI].connectionEvent);
	}

	if(isConnected == false) {
		PrintMessage("ERROR : iRobiQSonar::iRobiQ_Connect() -> Can't connect to iRobiQ\n");
	}

	return isConnected;
}

bool iRobiQSonar::iRobiQ_Disconnect(void)
{
	if(isConnected == false) {
		return true;
	}

	if(YJCI_UnInitInterface(pRI) != YJERR_SUCCESS) {
		PrintMessage("ERROR : iRobiQSonar::iRobiQ_Disconnect() -> iRobiQSonar isn't disconnected.\n");
		return false;
	}
	isConnected = false;
	PrintMessage("SUCCESS : iRobiQSonar::iRobiQ_Disconnect() -> iRobiQSonar is disconnected.\n");

	return true;
}

bool iRobiQSonar::iRobiQ_EnableSonar(void)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	if(YJRI_SetHWEventFilter(pRI, cmdID++, 0xFFFFFFFF, FALSE) != YJERR_SUCCESS) {
		PrintMessage("ERROR : iRobiQSonar::iRobiQ_EnableSonar() -> Can't enable the Hardware Event Filter for Touch\n");
		return false;
	}

	if(WaitForSingleObject(iRobiQEventInfo[pRI].commandEvent, IROBIQ_COMMAND_DELAY) != WAIT_OBJECT_0) {
		PrintMessage("ERROR : iRobiQSonar::iRobiQ_EnableSonar() -> Can't enable the Hardware Event Filter for Touch\n");
		return false;
	}
	ResetEvent(iRobiQEventInfo[pRI].commandEvent);

	return iRobiQEventInfo[pRI].result;
}

bool iRobiQSonar::iRobiQ_DisableSonar(void)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	if(YJRI_SetHWEventFilter(pRI, cmdID++, 0x00000000, FALSE) != YJERR_SUCCESS) {
		PrintMessage("ERROR : iRobiQSonar::iRobiQ_DisableSonar() -> Can't disable the Hardware Event Filter for Touch\n");
		return false;
	}

	if(WaitForSingleObject(iRobiQEventInfo[pRI].commandEvent, IROBIQ_COMMAND_DELAY) != WAIT_OBJECT_0) {
		PrintMessage("ERROR : iRobiQSonar::iRobiQ_DisableSonar() -> Can't disable the Hardware Event Filter for Touch\n");
		return false;
	}
	ResetEvent(iRobiQEventInfo[pRI].commandEvent);

	return iRobiQEventInfo[pRI].result;
}

bool iRobiQSonar::iRobiQ_GetSonarSensorData(vector<double> &data)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	data.resize(IROBIQ_SONAR_SIZE);

	for(int i = 0; i < (int)data.size(); i++) {
		data[i] = sonarValue[i];
	}

	return true;
}

void iRobiQSonar::EventMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	SONARSENSORPARAMS *sonar = NULL;

	if(iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("INFO : iRobiQSonar::EventMsgProc() -> Event Messsage : %8x\t%4x\n", dwTaskID, wParam);
		return;
	}

	switch (dwTaskID) {
		//	Connect Event
		case TASK_SYS_CONN:
			iRobiQEventInfo[pRI].result = false;
			switch(wParam) {
				case YJERR_CONN_SUCCESS:
					iRobiQEventInfo[pRI].result = true;
					PrintMessage("SUCCESS : iRobiQSonar::EventMsgProc() -> Connected to Robot successfully \n");
					break;

				case YJERR_CONN_CLOSED:
					PrintMessage("ERROR : iRobiQSonar::EventMsgProc() -> Connection was closed \n");
					break;

				case YJERR_CONN_HOSTUNREACH:
					PrintMessage("ERROR : iRobiQSonar::EventMsgProc() -> Unreachable host \n");
					break;

				case YJERR_CONN_TIMEDOUT:
					PrintMessage("ERROR : iRobiQSonar::EventMsgProc() -> Connection was timed out \n");
					break;

				case YJERR_CONN_CONNREFUSED:
					PrintMessage("ERROR : iRobiQSonar::EventMsgProc() -> Connection was refused \n");
					break;

				default:
					PrintMessage("ERROR : iRobiQSonar::EventMsgProc() -> Unknown error \n");
					break;
			}
			SetEvent(iRobiQEventInfo[pRI].connectionEvent);

			break;

		//	Touch Event
		case TASK_RI_HW_E_SONAR:	//	초음파센서 이벤트
			switch(wParam) {
				case 0x00000000 :
					sonar = (SONARSENSORPARAMS *)lParam;
					sonarValue[sonar->dwSonarID - 1] = sonar->fdistance * 0.1;
					PrintMessage("INFO : iRobiQSonar::EventMsgProc() -> Sonar Event(%d) : %.3f\n", sonar->dwSonarID - 1, sonarValue[sonar->dwSonarID - 1]);
					break;

				default :
					break;
			}
			break;

		default:
			break;
	}
}

void iRobiQSonar::ResponseMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	DWORD dwResultCode = (DWORD)wParam;

	if(iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return;
	}
	
	switch (dwTaskID) {
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Hardware Filter
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case TASK_RI_SET_HW_EVENT_FILTER :
			switch(dwResultCode) {
				case YJERR_SUCCESS :
					PrintMessage("SUCCESS : iRobiQSonar::ResponseMsgProc() -> Setting HW Event Filter is succeeded\n");
					iRobiQEventInfo[pRI].result = true;
					break;
				default :
					PrintMessage("ERROR : iRobiQSonar::ResponseMsgProc() -> Setting HW Event Filter is failed\n");
					iRobiQEventInfo[pRI].result = false;
					break;
			}
			SetEvent(iRobiQEventInfo[pRI].commandEvent);
			break;

		default:
			break;
	}
}

void iRobiQSonar::AckMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	//	YujinRobot_iRobiQSonar API에서는 사용하지 않음.
}