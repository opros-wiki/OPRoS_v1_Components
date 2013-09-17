#include "iRobiQWheelController.h"
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

static long gLeftEncoder = 0;
static long gRightEncoder = 0;

iRobiQWheelController::iRobiQWheelController(void)
{
	pRI = NULL;
	isConnected = false;
	isRunning = false;
	startTime = 0;
	runTime = 0;
}

iRobiQWheelController::~iRobiQWheelController(void)
{
	iRobiQ_Finalize();
}

bool iRobiQWheelController::iRobiQ_Initialize(void)
{
	if(pRI != NULL) {
		PrintMessage("INFO : iRobiQWheelController::iRobiQ_Initialize() -> iRobiQMobility already is initialized.\n");
		return true;
	}

	if(YJCI_CreateInstance(&pRI) == YJERR_SUCCESS) {
		if(YJCI_RegAcknowledgeProc(pRI, AckMsgProc) != YJERR_SUCCESS) {
			PrintMessage("ERROR : iRobiQWheelController::iRobiQ_Initialize() -> Can't register the Acknowledge Procedure\n");
			YJCI_DeleteInstance(&pRI);
			return false;
		}
		if(YJCI_RegResponseProc(pRI, ResponseMsgProc) != YJERR_SUCCESS) {
			PrintMessage("ERROR : iRobiQWheelController::iRobiQ_Initialize() -> Can't register the Response Procedure\n");
			YJCI_DeleteInstance(&pRI);
			return false;
		}
		if(YJCI_RegEventProc(pRI, EventMsgProc) != YJERR_SUCCESS) {
			PrintMessage("ERROR : iRobiQWheelController::iRobiQ_Initialize() -> Can't register the Event Procedure\n");
			YJCI_DeleteInstance(&pRI);
			return false;
		}

		iRobiQEventInfo[pRI].connectionEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		iRobiQEventInfo[pRI].commandEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		isConnected = false;
	}
	else {
		PrintMessage("ERROR : iRobiQWheelController::iRobiQ_Initialize() -> iRobiQMobility isn't intialized.\n");
		pRI = NULL;
		return false;
	}

	return true;
}

bool iRobiQWheelController::iRobiQ_Finalize(void)
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
	}
	else {
		PrintMessage("INFO : iRobiQWheelController::iRobiQ_Finalize() -> iRobiQMobility already is finalized.\n");
	}

	return true;
}

bool iRobiQWheelController::iRobiQ_Connect(std::string ip, unsigned int port, unsigned short serviceId)
{
	if(pRI == NULL || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("ERROR : iRobiQWheelController::iRobiQ_Connect() -> iRobiQMobility is not initialized.\n");
		return false;
	}

	if(isConnected == true) {
		return true;
	}

	PrintMessage("INFO : iRobiQWheelController::iRobiQ_Connect() -> IP : %s, Port : %d, Serivce ID : %d\n", ip.c_str(), port, serviceId);

	if(YJCI_InitInterface(pRI, serviceId, ip.c_str(), port) == YJERR_SUCCESS) {
		if(WaitForSingleObject(iRobiQEventInfo[pRI].connectionEvent, IROBIQ_CONNECTION_DELAY) == WAIT_OBJECT_0) {
			isConnected = iRobiQEventInfo[pRI].result;
		}
		ResetEvent(iRobiQEventInfo[pRI].connectionEvent);
	}
	else {
		PrintMessage("ERROR : iRobiQWheelController::iRobiQ_Connect() -> iRobiQMobility is not connected.\n");
	}

	return isConnected;
}

bool iRobiQWheelController::iRobiQ_Disconnect(void)
{
	if(pRI == NULL || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("ERROR : iRobiQWheelController::iRobiQ_Disconnect() -> iRobiQMobility is not initialized.\n");
		return false;
	}

	if(isConnected == false) {
		PrintMessage("INFO : iRobiQWheelController::iRobiQ_Disconnect() -> iRobiQMobility already is disconnected.\n");
		return true;
	}

	if(YJCI_UnInitInterface(pRI) != YJERR_SUCCESS) {
		PrintMessage("ERROR : iRobiQWheelController::iRobiQ_Disconnect() -> iRobiQMobility isn't disconnected.\n");
		return false;
	}
	else {
		isConnected = false;
		PrintMessage("SUCCESS : iRobiQWheelController::iRobiQ_Disconnect() -> iRobiQMobility is disconnected.\n");
	}

	return true;
}

bool iRobiQWheelController::iRobiQ_MoveWheel(double distance, int time)
{
	if(pRI == NULL || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("ERROR : iRobiQWheelController::iRobiQ_MoveWheel() -> iRobiQMobility is not initialized.\n");
		return false;
	}

	if(isConnected == false) {
		PrintMessage("ERROR : iRobiQWheelController::iRobiQ_MoveWheel() -> iRobiQMobility is not connected.\n");
		return true;
	}

	WHEELACTIONPARAMS stWheelActionParam = {0,};

	if(distance >= 0.0) {
		stWheelActionParam.wTemplateCode = 0x0001;
	}
	else {
		stWheelActionParam.wTemplateCode = 0x0002;
		distance = -distance;
	}

	stWheelActionParam.wExecuteTime = time;
	stWheelActionParam.wRepeatNum = 1;
	stWheelActionParam.shDistance = (short)(distance * 100.0);
	
	if(YJBH_MoveWheel(pRI, cmdID++, &stWheelActionParam, FALSE, FALSE) == YJERR_SUCCESS) {
		if(WaitForSingleObject(iRobiQEventInfo[pRI].commandEvent, (time + 1) * 1000) == WAIT_OBJECT_0) {
			if(iRobiQEventInfo[pRI].result == true) {
				startTime = GetTickCount();
				runTime = time;
				isRunning = true;
				PrintMessage("SUCCESS : iRobiQWheelController::iRobiQ_MoveWheel()\n");
			}
			else {
				PrintMessage("ERROR : iRobiQWheelController::iRobiQ_MoveWheel() -> iRobiQMobility can't move.\n");
				ResetEvent(iRobiQEventInfo[pRI].commandEvent);
				return false;
			}
		}
		else {
			PrintMessage("ERROR : iRobiQWheelController::iRobiQ_MoveWheel() -> Response Event is not received.\n");
			ResetEvent(iRobiQEventInfo[pRI].commandEvent);
			return false;
		}
		ResetEvent(iRobiQEventInfo[pRI].commandEvent);
	}
	else {
		PrintMessage("ERROR : iRobiQWheelController::iRobiQ_MoveWheel() -> Occur the error in YJBH_MoveWheel function.\n");
		return true;
	}

	return true;
}

bool iRobiQWheelController::iRobiQ_RotateWheel(double degree, int time)
{
	if(pRI == NULL || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("ERROR : iRobiQWheelController::iRobiQ_RotateWheel() -> iRobiQMobility is not initialized.\n");
		return false;
	}

	if(isConnected == false) {
		PrintMessage("ERROR : iRobiQWheelController::iRobiQ_RotateWheel() -> iRobiQMobility is not connected.\n");
		return true;
	}

	WHEELACTIONPARAMS stWheelActionParam = {0,};

	if(degree >= 0) {
		stWheelActionParam.wTemplateCode = 0x0104;
	}
	else {
		stWheelActionParam.wTemplateCode = 0x0103;
		degree = -degree;
	}

	stWheelActionParam.wExecuteTime = time;
	stWheelActionParam.wRepeatNum = 1;
	stWheelActionParam.shAngle = (short)(degree);
	
	if(YJBH_MoveWheel(pRI, cmdID++, &stWheelActionParam, FALSE, FALSE) == YJERR_SUCCESS) {
		if(WaitForSingleObject(iRobiQEventInfo[pRI].commandEvent, (time + 1) * 1000) == WAIT_OBJECT_0) {
			if(iRobiQEventInfo[pRI].result == true) {
				startTime = GetTickCount();
				runTime = time;
				isRunning = true;
				PrintMessage("SUCCESS : iRobiQWheelController::iRobiQ_RotateWheel()\n");
			}
			else {
				PrintMessage("ERROR : iRobiQWheelController::iRobiQ_RotateWheel() -> iRobiQMobility can't rotate.\n");
				ResetEvent(iRobiQEventInfo[pRI].commandEvent);
				return false;
			}
		}
		else {
			PrintMessage("ERROR : iRobiQWheelController::iRobiQ_RotateWheel() -> Response Event is not received.\n");
			ResetEvent(iRobiQEventInfo[pRI].commandEvent);
			return false;
		}
		ResetEvent(iRobiQEventInfo[pRI].commandEvent);
	}
	else {
		PrintMessage("ERROR : iRobiQWheelController::iRobiQ_RotateWheel() -> Occur the error in YJBH_MoveWheel function.\n");
		return true;
	}

	return true;
}

bool iRobiQWheelController::iRobiQ_StopWheel(void)
{
	if(pRI == NULL || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("ERROR : iRobiQWheelController::iRobiQ_StopWheel() -> iRobiQMobility is not initialized.\n");
		return false;
	}

	if(isConnected == false) {
		PrintMessage("ERROR : iRobiQWheelController::iRobiQ_StopWheel() -> iRobiQMobility is not connected.\n");
		return true;
	}

	WHEELACTIONPARAMS stWheelActionParam = {0,};
	stWheelActionParam.wTemplateCode = 0x0001;
	stWheelActionParam.wExecuteTime = 1;
	stWheelActionParam.wRepeatNum = 1;
	stWheelActionParam.shDistance = 0;
	
	if(YJBH_MoveWheel(pRI, cmdID++, &stWheelActionParam, FALSE, FALSE) == YJERR_SUCCESS) {
		if(WaitForSingleObject(iRobiQEventInfo[pRI].commandEvent, IROBIQ_COMMAND_DELAY) == WAIT_OBJECT_0) {
			if(iRobiQEventInfo[pRI].result == true) {
				PrintMessage("SUCCESS : iRobiQWheelController::iRobiQ_StopWheel()\n");
				isRunning = false;
			}
			else {
				PrintMessage("ERROR : iRobiQWheelController::iRobiQ_StopWheel() -> iRobiQMobility is not stopped.\n");
				ResetEvent(iRobiQEventInfo[pRI].commandEvent);
				return false;
			}
		}
		else {
			PrintMessage("ERROR : iRobiQWheelController::iRobiQ_StopWheel() -> Response Event is not received.\n");
			ResetEvent(iRobiQEventInfo[pRI].commandEvent);
			return false;
		}
		ResetEvent(iRobiQEventInfo[pRI].commandEvent);
	}
	else {
		PrintMessage("ERROR : iRobiQWheelController::iRobiQ_StopWheel() -> Occur the error in YJBH_MoveWheel function.\n");
		return false;
	}

	return true;
}

bool iRobiQWheelController::iRobiQ_CheckRunningState(void)
{
	if(isRunning == true) {
		if((GetTickCount() - startTime) >= runTime) {
			isRunning = false;
		}
	}
	
	return isRunning;
}

void iRobiQWheelController::EventMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	if(iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("INFO : iRobiQWheelController::EventMsgProc() -> Event Messsage : %8x\t%4x\n", dwTaskID, wParam);
		return;
	}

	switch (dwTaskID) {
		//	Connect Event
		case TASK_SYS_CONN:
			iRobiQEventInfo[pRI].result = false;
			switch(wParam) {
				case YJERR_CONN_SUCCESS:
					iRobiQEventInfo[pRI].result = true;
					PrintMessage("SUCCESS : iRobiQWheelController::EventMsgProc() -> Connected to Robot successfully \n");
					break;

				case YJERR_CONN_CLOSED:
					PrintMessage("ERROR : iRobiQWheelController::EventMsgProc() -> Connection was closed \n");
					break;

				case YJERR_CONN_HOSTUNREACH:
					PrintMessage("ERROR : iRobiQWheelController::EventMsgProc() -> Unreachable host \n");
					break;

				case YJERR_CONN_TIMEDOUT:
					PrintMessage("ERROR : iRobiQWheelController::EventMsgProc() -> Connection was timed out \n");
					break;

				case YJERR_CONN_CONNREFUSED:
					PrintMessage("ERROR : iRobiQWheelController::EventMsgProc() -> Connection was refused \n");
					break;

				default:
					PrintMessage("ERROR : iRobiQWheelController::EventMsgProc() -> Unknown error \n");
					break;
			}
			SetEvent(iRobiQEventInfo[pRI].connectionEvent);
			break;

		default:
			break;
	}
}

void iRobiQWheelController::ResponseMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	DWORD dwResultCode = (DWORD)wParam;
	WHEEL_VELOCITY *encoder = NULL;

	if(iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("INFO : iRobiQWheelController::ResponseMsgProc() -> Response Messsage : %8x\t%4x\n", dwTaskID, dwResultCode);
		return;
	}

	PrintMessage("INFO : iRobiQWheelController::ResponseMsgProc() -> Response Messsage : %8x\t%4x\n", dwTaskID, dwResultCode);
	
	switch (dwTaskID) {
		case TASK_BH_WHEEL :
			if(dwResultCode == YJERR_SUCCESS) {
				iRobiQEventInfo[pRI].result = true;
			}
			else {
				iRobiQEventInfo[pRI].result = false;
			}
			SetEvent(iRobiQEventInfo[pRI].commandEvent);
			break;

		default:
			break;
	}
}

void iRobiQWheelController::AckMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	//	YujinRobot_iRobiQMobility API에서는 사용하지 않음.
}