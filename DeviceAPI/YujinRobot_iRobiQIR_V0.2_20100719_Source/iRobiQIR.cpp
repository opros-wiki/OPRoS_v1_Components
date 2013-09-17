#include "iRobiQIR.h"
#include "OprosPrintMessage.h"

#include <map>

using namespace std;

#define	IROBIQ_CONNECTION_DELAY		(5000)
#define	IROBIQ_COMMAND_DELAY		(1000)
#define	IROBIQ_IR_SIZE				(2)

class iRobiQEvent
{
public:
	bool result;
	HANDLE connectionEvent;
	HANDLE commandEvent;
};

static map<LPROBOTINTERFACE, iRobiQEvent> iRobiQEventInfo;
static WORD cmdID = 0;
static bool irValue[IROBIQ_IR_SIZE] = {false, };

iRobiQIR::iRobiQIR(void)
{
	pRI = NULL;
	isConnected = false;
}

iRobiQIR::~iRobiQIR(void)
{
	iRobiQ_Finalize();
}

bool iRobiQIR::iRobiQ_Initialize(void)
{
	if(YJCI_CreateInstance(&pRI) == YJERR_SUCCESS) {
		YJCI_RegAcknowledgeProc(pRI, AckMsgProc);
		YJCI_RegResponseProc(pRI, ResponseMsgProc);
		YJCI_RegEventProc(pRI, EventMsgProc);

		iRobiQEventInfo[pRI].connectionEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		iRobiQEventInfo[pRI].commandEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

		PrintMessage("SUCCESS : iRobiQIR::iRobiQ_Initialize() -> iRobiQTouch is initialized.\n");
	}
	else {
		PrintMessage("ERROR : iRobiQIR::iRobiQ_Initialize() -> iRobiQTouch isn't intialized.\n");
		pRI = NULL;
	}

	return true;
}

bool iRobiQIR::iRobiQ_Finalize(void)
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

		PrintMessage("SUCCESS : iRobiQIR::iRobiQ_Finalize() -> iRobiQTouch is finalized.\n");
	}

	return true;
}

bool iRobiQIR::iRobiQ_Connect(std::string ip, unsigned int port, unsigned short serviceId)
{
	if(isConnected == true) {
		PrintMessage("INFO : iRobiQIR::iRobiQ_Connect() -> iRobiQ Touch is already connected.\n");
		return true;
	}

	if(pRI == NULL || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("ERROR : iRobiQIR::iRobiQ_Connect() -> iRobiQ Touch is initialized.\n");
		return false;
	}

	PrintMessage("INFO : iRobiQIR::iRobiQ_Connect() -> IP : %s, Port : %d, Serivce ID : %d\n", ip.c_str(), port, serviceId);

	isConnected = false;
	if(YJCI_InitInterface(pRI, serviceId, ip.c_str(), port) == YJERR_SUCCESS) {
		if(WaitForSingleObject(iRobiQEventInfo[pRI].connectionEvent, IROBIQ_CONNECTION_DELAY) == WAIT_OBJECT_0) {
			if((isConnected = iRobiQEventInfo[pRI].result) == true) {
				PrintMessage("SUCCESS : iRobiQIR::iRobiQ_Connect() -> iRobiQ Touch is connected.\n");
			}
		}
		ResetEvent(iRobiQEventInfo[pRI].connectionEvent);
	}

	if(isConnected == false) {
		PrintMessage("ERROR : iRobiQIR::iRobiQ_Connect() -> Can't connect to iRobiQ\n");
	}

	return isConnected;
}

bool iRobiQIR::iRobiQ_Disconnect(void)
{
	if(isConnected == false) {
		return true;
	}

	if(YJCI_UnInitInterface(pRI) != YJERR_SUCCESS) {
		PrintMessage("ERROR : iRobiQIR::iRobiQ_Disconnect() -> iRobiQTouch isn't disconnected.\n");
		return false;
	}
	isConnected = false;
	PrintMessage("SUCCESS : iRobiQIR::iRobiQ_Disconnect() -> iRobiQTouch is disconnected.\n");

	return true;
}

bool iRobiQIR::iRobiQ_EnableIR(void)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	if(YJRI_SetHWEventFilter(pRI, cmdID++, 0xFFFFFFFF, FALSE) != YJERR_SUCCESS) {
		PrintMessage("ERROR : iRobiQIR::iRobiQTouch_Enable() -> Can't enable the Hardware Event Filter for Touch\n");
		return false;
	}

	if(WaitForSingleObject(iRobiQEventInfo[pRI].commandEvent, IROBIQ_COMMAND_DELAY) != WAIT_OBJECT_0) {
		PrintMessage("ERROR : iRobiQIR::iRobiQTouch_Enable() -> Can't enable the Hardware Event Filter for Touch\n");
		return false;
	}
	ResetEvent(iRobiQEventInfo[pRI].commandEvent);

	return iRobiQEventInfo[pRI].result;
}

bool iRobiQIR::iRobiQ_DisableIR(void)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	if(YJRI_SetHWEventFilter(pRI, cmdID++, 0x00000000, FALSE) != YJERR_SUCCESS) {
		PrintMessage("ERROR : iRobiQIR::iRobiQTouch_Enable() -> Can't disable the Hardware Event Filter for Touch\n");
		return false;
	}

	if(WaitForSingleObject(iRobiQEventInfo[pRI].commandEvent, IROBIQ_COMMAND_DELAY) != WAIT_OBJECT_0) {
		PrintMessage("ERROR : iRobiQIR::iRobiQTouch_Enable() -> Can't disable the Hardware Event Filter for Touch\n");
		return false;
	}
	ResetEvent(iRobiQEventInfo[pRI].commandEvent);

	return iRobiQEventInfo[pRI].result;
}

bool iRobiQIR::iRobiQ_GetIRSensorData(vector<double> &data)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	data.resize(IROBIQ_IR_SIZE);

	for(int i = 0; i < (int)data.size(); i++) {
		data[i] = (irValue[i] == true) ? 0.04 : 0.05;
	}

	return true;
}

void iRobiQIR::EventMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	TOUCHSENSORPARAMS *touch = NULL;
	if(iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("INFO : iRobiQIR::EventMsgProc() -> Event Messsage : %8x\t%4x\n", dwTaskID, wParam);
		return;
	}

	switch (dwTaskID) {
		//	Connect Event
		case TASK_SYS_CONN:
			iRobiQEventInfo[pRI].result = false;
			switch(wParam) {
				case YJERR_CONN_SUCCESS:
					iRobiQEventInfo[pRI].result = true;
					PrintMessage("SUCCESS : iRobiQIR::EventMsgProc() -> Connected to Robot successfully \n");
					break;

				case YJERR_CONN_CLOSED:
					PrintMessage("ERROR : iRobiQIR::EventMsgProc() -> Connection was closed \n");
					break;

				case YJERR_CONN_HOSTUNREACH:
					PrintMessage("ERROR : iRobiQIR::EventMsgProc() -> Unreachable host \n");
					break;

				case YJERR_CONN_TIMEDOUT:
					PrintMessage("ERROR : iRobiQIR::EventMsgProc() -> Connection was timed out \n");
					break;

				case YJERR_CONN_CONNREFUSED:
					PrintMessage("ERROR : iRobiQIR::EventMsgProc() -> Connection was refused \n");
					break;

				default:
					PrintMessage("ERROR : iRobiQIR::EventMsgProc() -> Unknown error \n");
					break;
			}
			SetEvent(iRobiQEventInfo[pRI].connectionEvent);

			break;

		//	전방 IR센서 이벤트
		case TASK_RI_HW_E_PRXIR :
			switch(wParam) {
				case 0x00000000 :
					irValue[0] = true;
					PrintMessage("INFO : iRobiQIR::EventMsgProc() -> Front IR Event\n");
					break;
				default :
					break;
			}
			break;

		//	후방 IR센서 이벤트
		case TASK_RI_HW_E_BOTTOM :
			switch(wParam) {
				case 0x00000000 :
					irValue[1] = true;
					PrintMessage("INFO : iRobiQIR::EventMsgProc() -> Bottom IR Event\n");
					break;
				default :
					break;
			}
			break;

		default:
			break;
	}
}

void iRobiQIR::ResponseMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
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
					PrintMessage("SUCCESS : iRobiQIR::ResponseMsgProc() -> Setting HW Event Filter is succeeded\n");
					iRobiQEventInfo[pRI].result = true;
					break;
				default :
					PrintMessage("ERROR : iRobiQIR::ResponseMsgProc() -> Setting HW Event Filter is failed\n");
					iRobiQEventInfo[pRI].result = false;
					break;
			}
			SetEvent(iRobiQEventInfo[pRI].commandEvent);
			break;

		default:
			break;
	}
}

void iRobiQIR::AckMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	//	YujinRobot_iRobiQIR API에서는 사용하지 않음.
}