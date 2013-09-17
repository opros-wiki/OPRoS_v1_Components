#include "iRobiQPanTilt.h"

#include "OprosPrintMessage.h"
#include <map>

#define	IROBIQ_CONNECTION_DELAY		(5000)
#define	IROBIQ_COMMAND_DELAY		(1000)
#define	IROBIQ_PAN					(0)
#define	IROBIQ_TILT					(1)

class iRobiQEvent
{
public:
	bool result;
	HANDLE connectionEvent;
	HANDLE commandEvent;
};

static map<LPROBOTINTERFACE, iRobiQEvent> iRobiQEventInfo;
static WORD cmdID = 0;

iRobiQPanTilt::iRobiQPanTilt(void)
{
	pRI = NULL;
	isConnected = false;
}

iRobiQPanTilt::~iRobiQPanTilt(void)
{
	iRobiQ_Finalize();
}

bool iRobiQPanTilt::iRobiQ_Initialize(void)
{
	if(YJCI_CreateInstance(&pRI) == YJERR_SUCCESS) {
		YJCI_RegAcknowledgeProc(pRI, AckMsgProc);
		YJCI_RegResponseProc(pRI, ResponseMsgProc);
		YJCI_RegEventProc(pRI, EventMsgProc);

		iRobiQEventInfo[pRI].connectionEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		iRobiQEventInfo[pRI].commandEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	}
	else {
		PrintMessage("ERROR : iRobiQPanTilt::iRobiQ_Initialize() -> iRobiQPanTilt isn't intialized.\n");
		pRI = NULL;
	}

	return true;
}

bool iRobiQPanTilt::iRobiQ_Finalize(void)
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

		PrintMessage("SUCCESS : iRobiQPanTilt::iRobiQ_Finalize() -> iRobiQPanTilt is finalized.\n");
	}

	return true;
}

bool iRobiQPanTilt::iRobiQ_Connect(std::string ip, unsigned int port, unsigned short serviceId)
{
	if(isConnected == true) {
		PrintMessage("INFO : iRobiQPanTilt::iRobiQ_Connect() -> iRobiQPanTilt is already connected.\n");
		return true;
	}

	if(pRI == NULL || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("ERROR : iRobiQPanTilt::iRobiQ_Connect() -> iRobiQPanTilt is initialized.\n");
		return false;
	}

	PrintMessage("INFO : iRobiQPanTilt::iRobiQ_Connect() -> IP : %s, Port : %d, Serivce ID : %d\n", ip.c_str(), port, serviceId);

	isConnected = false;
	if(YJCI_InitInterface(pRI, serviceId, ip.c_str(), port) == YJERR_SUCCESS) {
		if(WaitForSingleObject(iRobiQEventInfo[pRI].connectionEvent, IROBIQ_CONNECTION_DELAY) == WAIT_OBJECT_0) {
			if((isConnected = iRobiQEventInfo[pRI].result) == true) {
				PrintMessage("SUCCESS : iRobiQPanTilt::iRobiQ_Connect() -> iRobiQPanTilt is connected.\n");
			}
		}
		ResetEvent(iRobiQEventInfo[pRI].connectionEvent);
	}

	if(isConnected == false) {
		PrintMessage("ERROR : iRobiQPanTilt::iRobiQ_Connect() -> Can't connect to iRobiQ\n");
	}

	return isConnected;
}

bool iRobiQPanTilt::iRobiQ_Disconnect(void)
{
	if(isConnected == false) {
		return true;
	}

	if(YJCI_UnInitInterface(pRI) != YJERR_SUCCESS) {
		PrintMessage("ERROR : iRobiQPanTilt::iRobiQ_Disconnect() -> iRobiQPanTilt isn't disconnected.\n");
		return false;
	}
	isConnected = false;
	
	return true;
}

bool iRobiQPanTilt::iRobiQ_SetPan(double degree, int time)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	HEADACTIONPARAMS stHeadActionParam = {0,};
	unsigned short executeTime = (time < 1000) ? 1 : (unsigned short)(time / 1000);

	stHeadActionParam.wTemplateCode = 0x0009;
	stHeadActionParam.wPanExecuteTime = executeTime;
	stHeadActionParam.wPanRepeatNum = 1;
	stHeadActionParam.shPanAngle = (SHORT)degree;
	
	if(YJBH_MoveHead(pRI, cmdID++, &stHeadActionParam, FALSE, FALSE) != YJERR_SUCCESS) {
		return false;
	}

	return true;
}

bool iRobiQPanTilt::iRobiQ_GetPan(double *degree)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	iRobiQ_CalculateAngle(IROBIQ_PAN, degree);

	return true;
}

bool iRobiQPanTilt::iRobiQ_SetTilt(double degree, int time)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	HEADACTIONPARAMS stHeadActionParam = {0,};
	unsigned short executeTime = (time < 1000) ? 1 : (unsigned short)(time / 1000);

	stHeadActionParam.wTemplateCode = 0x000C;
	stHeadActionParam.wTiltExecuteTime = executeTime;
	stHeadActionParam.wTiltRepeatNum = 1;
	stHeadActionParam.shTiltAngle = (SHORT)degree;
	
	if(YJBH_MoveHead(pRI, cmdID++, &stHeadActionParam, FALSE, FALSE) != YJERR_SUCCESS) {
		return false;
	}

	return true;
}

bool iRobiQPanTilt::iRobiQ_GetTilt(double *degree)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	iRobiQ_CalculateAngle(IROBIQ_TILT, degree);

	return true;
}

void iRobiQPanTilt::iRobiQ_CalculateAngle(int index, double *degree)
{
	if(startAngle[index] == targetAngle[index]) {
		*degree = targetAngle[index];
	}
	else if((GetTickCount() - startTime[index]) >= runTime[index]) {
		*degree = startAngle[index] = targetAngle[index];
	}
	else {
		*degree = startAngle[index] + (targetAngle[index] - startAngle[index]) / (GetTickCount() - startTime[index]);
	}
}

void iRobiQPanTilt::EventMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	if(iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("INFO : iRobiQPanTilt::EventMsgProc() -> Event Messsage : %8x\t%4x\n", dwTaskID, wParam);
		return;
	}

	switch (dwTaskID) {
		//	Connect Event
		case TASK_SYS_CONN:
			iRobiQEventInfo[pRI].result = false;
			switch(wParam) {
				case YJERR_CONN_SUCCESS:
					iRobiQEventInfo[pRI].result = true;
					PrintMessage("SUCCESS : iRobiQPanTilt::EventMsgProc() -> Connected to Robot successfully \n");
					break;

				case YJERR_CONN_CLOSED:
					PrintMessage("ERROR : iRobiQPanTilt::EventMsgProc() -> Connection was closed \n");
					break;

				case YJERR_CONN_HOSTUNREACH:
					PrintMessage("ERROR : iRobiQPanTilt::EventMsgProc() -> Unreachable host \n");
					break;

				case YJERR_CONN_TIMEDOUT:
					PrintMessage("ERROR : iRobiQPanTilt::EventMsgProc() -> Connection was timed out \n");
					break;

				case YJERR_CONN_CONNREFUSED:
					PrintMessage("ERROR : iRobiQPanTilt::EventMsgProc() -> Connection was refused \n");
					break;

				default:
					PrintMessage("ERROR : iRobiQPanTilt::EventMsgProc() -> Unknown error \n");
					break;
			}
			SetEvent(iRobiQEventInfo[pRI].connectionEvent);
			break;

		default:
			break;
	}
}

void iRobiQPanTilt::ResponseMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	DWORD dwResultCode = (DWORD)wParam;

	if(iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return;
	}
}

void iRobiQPanTilt::AckMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	//	YujinRobot_iRobiQPanTilt API에서는 사용하지 않음.
}
