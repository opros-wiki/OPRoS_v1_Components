#include "iRobiQBumper.h"

#include "OprosPrintMessage.h"

#include <map>

using namespace std;

#define	IROBIQ_CONNECTION_DELAY		(5000)
#define	IROBIQ_COMMAND_DELAY		(1000)
#define	IROBIQ_BUMPER_SIZE			(1)

class iRobiQBumperEvent
{
public:
	bool result;
	HANDLE connectionEvent;
	HANDLE commandEvent;
};

static map<LPROBOTINTERFACE, iRobiQBumperEvent> iRobiQBumperInfo;
static WORD cmdID = 0;
static bool bumperState[IROBIQ_BUMPER_SIZE] = {false, };

iRobiQBumper::iRobiQBumper(void)
{
	pRI = NULL;
	isConnected = false;
}

iRobiQBumper::~iRobiQBumper(void)
{
	iRobiQ_Finalize();
}

bool iRobiQBumper::iRobiQ_Initialize(void)
{
	if(YJCI_CreateInstance(&pRI) == YJERR_SUCCESS) {
		YJCI_RegAcknowledgeProc(pRI, AckMsgProc);
		YJCI_RegResponseProc(pRI, ResponseMsgProc);
		YJCI_RegEventProc(pRI, EventMsgProc);

		iRobiQBumperInfo[pRI].connectionEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		iRobiQBumperInfo[pRI].commandEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

		PrintMessage("SUCCESS : iRobiQBumper::iRobiQ_Initialize() -> iRobiQBumper is initialized.\n");
	}
	else {
		PrintMessage("ERROR : iRobiQBumper::iRobiQ_Initialize() -> iRobiQBumper isn't intialized.\n");
		pRI = NULL;
	}

	return true;
}

bool iRobiQBumper::iRobiQ_Finalize(void)
{
	if(pRI != NULL)
	{
		if(isConnected == true) {
			iRobiQ_Disconnect();
		}

		if(iRobiQBumperInfo.find(pRI) != iRobiQBumperInfo.end()) {
			if(iRobiQBumperInfo[pRI].connectionEvent != INVALID_HANDLE_VALUE) {
				CloseHandle(iRobiQBumperInfo[pRI].connectionEvent);
				iRobiQBumperInfo[pRI].connectionEvent = INVALID_HANDLE_VALUE;
			}

			if(iRobiQBumperInfo[pRI].commandEvent != INVALID_HANDLE_VALUE) {
				CloseHandle(iRobiQBumperInfo[pRI].commandEvent);
				iRobiQBumperInfo[pRI].commandEvent = INVALID_HANDLE_VALUE;
			}

			iRobiQBumperInfo.erase(pRI);
		}

		YJCI_DeleteInstance(&pRI);
		pRI = NULL;

		PrintMessage("SUCCESS : iRobiQBumper::iRobiQ_Finalize() -> iRobiQBumper is finalized.\n");
	}

	return true;
}

bool iRobiQBumper::iRobiQ_Connect(std::string ip, unsigned int port, unsigned short serviceId)
{
	if(isConnected == true) {
		PrintMessage("INFO : iRobiQBumper::iRobiQ_Connect() -> iRobiQ Bumper is already connected.\n");
		return true;
	}

	if(pRI == NULL || iRobiQBumperInfo.find(pRI) == iRobiQBumperInfo.end()) {
		PrintMessage("ERROR : iRobiQBumper::iRobiQ_Connect() -> iRobiQ Bumper is initialized.\n");
		return false;
	}

	PrintMessage("INFO : iRobiQBumper::iRobiQ_Connect() -> IP : %s, Port : %d, Serivce ID : %d\n", ip.c_str(), port, serviceId);

	isConnected = false;
	if(YJCI_InitInterface(pRI, serviceId, ip.c_str(), port) == YJERR_SUCCESS) {
		if(WaitForSingleObject(iRobiQBumperInfo[pRI].connectionEvent, IROBIQ_CONNECTION_DELAY) == WAIT_OBJECT_0) {
			if((isConnected = iRobiQBumperInfo[pRI].result) == true) {
				PrintMessage("SUCCESS : YujinRobot_iRobiQBumper::iRobiQ_Connect() -> iRobiQ Bumper is connected.\n");
			}
		}
		ResetEvent(iRobiQBumperInfo[pRI].connectionEvent);
	}

	if(isConnected == false) {
		PrintMessage("ERROR : iRobiQBumper::iRobiQ_Connect() -> Can't connect to iRobiQ\n");
	}

	return isConnected;
}

bool iRobiQBumper::iRobiQ_Disconnect(void)
{
	if(isConnected == false) {
		return true;
	}

	if(YJCI_UnInitInterface(pRI) != YJERR_SUCCESS) {
		PrintMessage("ERROR : iRobiQBumper::iRobiQ_Disconnect() -> iRobiQBumper isn't disconnected.\n");
		return false;
	}
	isConnected = false;
	PrintMessage("SUCCESS : iRobiQBumper::iRobiQ_Disconnect() -> iRobiQBumper is disconnected.\n");

	return true;
}

bool iRobiQBumper::iRobiQBumper_Enable(void)
{
	if(pRI == NULL || isConnected == false || iRobiQBumperInfo.find(pRI) == iRobiQBumperInfo.end()) {
		return false;
	}

	if(YJRI_SetHWEventFilter(pRI, cmdID++, 0xFFFFFFFF, FALSE) != YJERR_SUCCESS) {
		PrintMessage("ERROR : iRobiQBumper::iRobiQBumper_Enable() -> Can't enable the Hardware Event Filter for Bumper\n");
		return false;
	}

	if(WaitForSingleObject(iRobiQBumperInfo[pRI].commandEvent, IROBIQ_COMMAND_DELAY) != WAIT_OBJECT_0) {
		PrintMessage("ERROR : iRobiQBumper::iRobiQBumper_Enable() -> Can't enable the Hardware Event Filter for Bumper\n");
		return false;
	}
	ResetEvent(iRobiQBumperInfo[pRI].connectionEvent);

	return iRobiQBumperInfo[pRI].result;
}

bool iRobiQBumper::iRobiQBumper_Disable(void)
{
	if(pRI == NULL || isConnected == false || iRobiQBumperInfo.find(pRI) == iRobiQBumperInfo.end()) {
		return false;
	}

	if(YJRI_SetHWEventFilter(pRI, cmdID++, 0x00000000, FALSE) != YJERR_SUCCESS) {
		PrintMessage("ERROR : iRobiQBumper::iRobiQBumper_Enable() -> Can't disable the Hardware Event Filter for Bumper\n");
		return false;
	}

	if(WaitForSingleObject(iRobiQBumperInfo[pRI].commandEvent, IROBIQ_COMMAND_DELAY) != WAIT_OBJECT_0) {
		PrintMessage("ERROR : iRobiQBumper::iRobiQBumper_Enable() -> Can't disable the Hardware Event Filter for Bumper\n");
		return false;
	}
	ResetEvent(iRobiQBumperInfo[pRI].connectionEvent);

	return iRobiQBumperInfo[pRI].result;
}

bool iRobiQBumper::iRobiQBumper_GetBumperState()
{
	return bumperState[0];
}

void iRobiQBumper::EventMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	if(iRobiQBumperInfo.find(pRI) == iRobiQBumperInfo.end()) {
		PrintMessage("INFO : iRobiQBumper::EventMsgProc() -> Event Messsage : %8x\t%4x\n", dwTaskID, wParam);
		return;
	}

	switch (dwTaskID) {
		//	Connect Event
		case TASK_SYS_CONN:
			iRobiQBumperInfo[pRI].result = false;
			switch(wParam) {
				case YJERR_CONN_SUCCESS:
					iRobiQBumperInfo[pRI].result = true;
					PrintMessage("SUCCESS : iRobiQBumper::EventMsgProc() -> Connected to Robot successfully \n");
					break;

				case YJERR_CONN_CLOSED:
					PrintMessage("ERROR : iRobiQBumper::EventMsgProc() -> Connection was closed \n");
					break;

				case YJERR_CONN_HOSTUNREACH:
					PrintMessage("ERROR : iRobiQBumper::EventMsgProc() -> Unreachable host \n");
					break;

				case YJERR_CONN_TIMEDOUT:
					PrintMessage("ERROR : iRobiQBumper::EventMsgProc() -> Connection was timed out \n");
					break;

				case YJERR_CONN_CONNREFUSED:
					PrintMessage("ERROR : iRobiQBumper::EventMsgProc() -> Connection was refused \n");
					break;

				default:
					PrintMessage("ERROR : iRobiQBumper::EventMsgProc() -> Unknown error \n");
					break;
			}
			SetEvent(iRobiQBumperInfo[pRI].connectionEvent);

			break;

		//	Bumper Event
		case TASK_RI_HW_E_BUMPER :
			switch(wParam) {
				case 0x00000000 :
					bumperState[0] = true;
					PrintMessage("INFO : iRobiQBumper::EventMsgProc() -> Bumper Event\n");
					break;
				default :
					break;
			}
			break;

		default:
			break;
	}
}

void iRobiQBumper::ResponseMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	DWORD dwResultCode = (DWORD)wParam;

	if(iRobiQBumperInfo.find(pRI) == iRobiQBumperInfo.end()) return;
	
	switch (dwTaskID) {
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Hardware Filter
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case TASK_RI_SET_HW_EVENT_FILTER :
			switch(dwResultCode) {
				case YJERR_SUCCESS :
					PrintMessage("SUCCESS : iRobiQBumper::ResponseMsgProc() -> Setting HW Event Filter is succeeded\n");
					iRobiQBumperInfo[pRI].result = true;
					break;
				default :
					PrintMessage("ERROR : iRobiQBumper::ResponseMsgProc() -> Setting HW Event Filter is failed\n");
					iRobiQBumperInfo[pRI].result = false;
					break;
			}
			SetEvent(iRobiQBumperInfo[pRI].commandEvent);
			break;

		default:
			break;
	}
}

void iRobiQBumper::AckMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	//	iRobiQSpeech API에서는 사용하지 않음.
}