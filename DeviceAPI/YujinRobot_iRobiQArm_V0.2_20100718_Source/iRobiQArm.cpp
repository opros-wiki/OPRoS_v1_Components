#include "iRobiQArm.h"

#include "OprosPrintMessage.h"
#include <map>

#define	IROBIQ_CONNECTION_DELAY		(5000)
#define	IROBIQ_COMMAND_DELAY		(1000)
#define	IROBIQ_LEFT_ARM				(0)
#define	IROBIQ_RIGHT_ARM			(1)

class iRobiQEvent
{
public:
	bool result;
	HANDLE connectionEvent;
	HANDLE commandEvent;
};

static map<LPROBOTINTERFACE, iRobiQEvent> iRobiQEventInfo;
static WORD cmdID = 0;

iRobiQArm::iRobiQArm(void)
{
	pRI = NULL;
	isConnected = false;
}

iRobiQArm::~iRobiQArm(void)
{
	iRobiQ_Finalize();
}

bool iRobiQArm::iRobiQ_Initialize(void)
{
	if(YJCI_CreateInstance(&pRI) == YJERR_SUCCESS) {
		YJCI_RegAcknowledgeProc(pRI, AckMsgProc);
		YJCI_RegResponseProc(pRI, ResponseMsgProc);
		YJCI_RegEventProc(pRI, EventMsgProc);

		iRobiQEventInfo[pRI].connectionEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		iRobiQEventInfo[pRI].commandEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	}
	else {
		PrintMessage("ERROR : iRobiQArm::iRobiQ_Initialize() -> iRobiQArm isn't intialized.\n");
		pRI = NULL;
	}

	return true;
}

bool iRobiQArm::iRobiQ_Finalize(void)
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

	return true;
}

bool iRobiQArm::iRobiQ_Connect(std::string ip, unsigned int port, unsigned short serviceId)
{
	if(isConnected == true) {
		PrintMessage("INFO : iRobiQArm::iRobiQ_Connect() -> iRobiQArm is already connected.\n");
		return true;
	}

	if(pRI == NULL || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("ERROR : iRobiQArm::iRobiQ_Connect() -> iRobiQArm is initialized.\n");
		return false;
	}

	isConnected = false;
	if(YJCI_InitInterface(pRI, serviceId, ip.c_str(), port) == YJERR_SUCCESS) {
		if(WaitForSingleObject(iRobiQEventInfo[pRI].connectionEvent, IROBIQ_CONNECTION_DELAY) == WAIT_OBJECT_0) {
			if((isConnected = iRobiQEventInfo[pRI].result) == true) {
				PrintMessage("SUCCESS : iRobiQArm::iRobiQ_Connect() -> iRobiQArm is connected.\n");
			}
		}
		ResetEvent(iRobiQEventInfo[pRI].connectionEvent);
	}

	if(isConnected == false) {
		PrintMessage("ERROR : iRobiQArm::iRobiQ_Connect() -> Can't connect to iRobiQ\n");
	}

	return isConnected;
}

bool iRobiQArm::iRobiQ_Disconnect(void)
{
	if(isConnected == false) {
		return true;
	}

	if(YJCI_UnInitInterface(pRI) != YJERR_SUCCESS) {
		PrintMessage("ERROR : iRobiQArm::iRobiQ_Disconnect() -> iRobiQArm isn't disconnected.\n");
		return false;
	}
	isConnected = false;
	PrintMessage("SUCCESS : iRobiQArm::iRobiQ_Disconnect() -> iRobiQArm is disconnected.\n");

	return true;
}

bool iRobiQArm::iRobiQ_SetLeftArm(double degree, int time)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	ARMACTIONPARAMS armActionParam = {0,};
	unsigned short executeTime = (time < 1000) ? 1 : (unsigned short)(time / 1000);

	armActionParam.wTemplateCode = 0x0001;
	armActionParam.wLeftExecuteTime = executeTime;
	armActionParam.wLeftRepeatNum = 1;
	armActionParam.shLeftAngle = (SHORT)degree;
	
	if(YJBH_MoveArm(pRI, cmdID++, &armActionParam, FALSE, FALSE) != YJERR_SUCCESS) {
		return false;
	}

	return true;
}

bool iRobiQArm::iRobiQ_GetLeftArm(double *degree)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	iRobiQ_CalculateAngle(IROBIQ_LEFT_ARM, degree);

	return true;
}

bool iRobiQArm::iRobiQ_SetRightArm(double degree, int time)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	ARMACTIONPARAMS armActionParam = {0,};
	unsigned short executeTime = (time < 1000) ? 1 : (unsigned short)(time / 1000);

	armActionParam.wTemplateCode = 0x0004;
	armActionParam.wRightExecuteTime = executeTime;
	armActionParam.wRightRepeatNum = 1;
	armActionParam.shRightAngle = (SHORT)degree;
	
	if(YJBH_MoveArm(pRI, cmdID++, &armActionParam, FALSE, FALSE) != YJERR_SUCCESS) {
		return false;
	}

	return true;
}

bool iRobiQArm::iRobiQ_GetRightArm(double *degree)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	iRobiQ_CalculateAngle(IROBIQ_RIGHT_ARM, degree);

	return true;
}

void iRobiQArm::iRobiQ_CalculateAngle(int index, double *degree)
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

void iRobiQArm::EventMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	if(iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("INFO : iRobiQArm::EventMsgProc() -> Event Messsage : %8x\t%4x\n", dwTaskID, wParam);
		return;
	}

	switch (dwTaskID) {
		//	Connect Event
		case TASK_SYS_CONN:
			iRobiQEventInfo[pRI].result = false;
			switch(wParam) {
				case YJERR_CONN_SUCCESS:
					iRobiQEventInfo[pRI].result = true;
					PrintMessage("SUCCESS : iRobiQArm::EventMsgProc() -> Connected to Robot successfully \n");
					break;

				case YJERR_CONN_CLOSED:
					PrintMessage("ERROR : iRobiQArm::EventMsgProc() -> Connection was closed \n");
					break;

				case YJERR_CONN_HOSTUNREACH:
					PrintMessage("ERROR : iRobiQArm::EventMsgProc() -> Unreachable host \n");
					break;

				case YJERR_CONN_TIMEDOUT:
					PrintMessage("ERROR : iRobiQArm::EventMsgProc() -> Connection was timed out \n");
					break;

				case YJERR_CONN_CONNREFUSED:
					PrintMessage("ERROR : iRobiQArm::EventMsgProc() -> Connection was refused \n");
					break;

				default:
					PrintMessage("ERROR : iRobiQArm::EventMsgProc() -> Unknown error \n");
					break;
			}
			SetEvent(iRobiQEventInfo[pRI].connectionEvent);
			break;

		default:
			break;
	}
}

void iRobiQArm::ResponseMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	DWORD dwResultCode = (DWORD)wParam;

	if(iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return;
	}
}

void iRobiQArm::AckMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	//	YujinRobot_iRobiQPanTilt API에서는 사용하지 않음.
}