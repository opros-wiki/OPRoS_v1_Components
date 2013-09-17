/*************************************************************

 file: iRobiQTouch.cpp
 author: E.C. Shin
 begin: January 30 2010
 copyright: (c) 2010 KITECH, OPRoS
 email: unchol@kitech.re.kr

***************************************************************

OPRoS source code is provided under a dual license mode:
 LGPL and OPRoS individually.

LGPL: You can redistribute it and/or modify it under the terms
 of the Less GNU General Public License as published by the Free
 Software Foundation, either version 3 of the License.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of 
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 Less GNU General Public License for more details. 

 You should have received a copy of the Less GNU General Public
 License along with this program. If not, see 
 <http://www.gnu.org/licenses/>.

OPRoS individual license: An individual license is a license for
 modifying the source code of OPRoS and distiributing it in a
 closed format for commercial purposes.

 If you are interested in this option, please see 
 <http://www.opros.or.kr>.

This license policy may be changed without prior notice.

***************************************************************/

#include "iRobiQTouch.h"
#include "OprosPrintMessage.h"

#include <map>

using namespace std;

#define	IROBIQ_CONNECTION_DELAY		(5000)
#define	IROBIQ_COMMAND_DELAY		(1000)
#define	IROBIQ_TOUCH_SIZE			(6)

class iRobiQEvent
{
public:
	bool result;
	HANDLE connectionEvent;
	HANDLE commandEvent;
};

static map<LPROBOTINTERFACE, iRobiQEvent> iRobiQEventInfo;
static WORD cmdID = 0;
static bool touchState[IROBIQ_TOUCH_SIZE] = {false, };

iRobiQTouch::iRobiQTouch(void)
{
	pRI = NULL;
	isConnected = false;
}

iRobiQTouch::~iRobiQTouch(void)
{
	iRobiQ_Finalize();
}

bool iRobiQTouch::iRobiQ_Initialize(void)
{
	if(YJCI_CreateInstance(&pRI) == YJERR_SUCCESS) {
		YJCI_RegAcknowledgeProc(pRI, AckMsgProc);
		YJCI_RegResponseProc(pRI, ResponseMsgProc);
		YJCI_RegEventProc(pRI, EventMsgProc);

		iRobiQEventInfo[pRI].connectionEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		iRobiQEventInfo[pRI].commandEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

		PrintMessage("SUCCESS : iRobiQTouch::iRobiQ_Initialize() -> iRobiQTouch is initialized.\n");
	}
	else {
		PrintMessage("ERROR : iRobiQTouch::iRobiQ_Initialize() -> iRobiQTouch isn't intialized.\n");
		pRI = NULL;
	}

	return true;
}

bool iRobiQTouch::iRobiQ_Finalize(void)
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

		PrintMessage("SUCCESS : iRobiQTouch::iRobiQ_Finalize() -> iRobiQTouch is finalized.\n");
	}

	return true;
}

bool iRobiQTouch::iRobiQ_Connect(std::string ip, unsigned int port, unsigned short serviceId)
{
	if(isConnected == true) {
		PrintMessage("INFO : iRobiQTouch::iRobiQ_Connect() -> iRobiQ Touch is already connected.\n");
		return true;
	}

	if(pRI == NULL || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("ERROR : iRobiQTouch::iRobiQ_Connect() -> iRobiQ Touch is initialized.\n");
		return false;
	}

	PrintMessage("INFO : iRobiQTouch::iRobiQ_Connect() -> IP : %s, Port : %d, Serivce ID : %d\n", ip.c_str(), port, serviceId);

	isConnected = false;
	if(YJCI_InitInterface(pRI, serviceId, ip.c_str(), port) == YJERR_SUCCESS) {
		if(WaitForSingleObject(iRobiQEventInfo[pRI].connectionEvent, IROBIQ_CONNECTION_DELAY) == WAIT_OBJECT_0) {
			if((isConnected = iRobiQEventInfo[pRI].result) == true) {
				PrintMessage("SUCCESS : iRobiQTouch::iRobiQ_Connect() -> iRobiQ Touch is connected.\n");
			}
		}
		ResetEvent(iRobiQEventInfo[pRI].connectionEvent);
	}

	if(isConnected == false) {
		PrintMessage("ERROR : iRobiQTouch::iRobiQ_Connect() -> Can't connect to iRobiQ\n");
	}

	return isConnected;
}

bool iRobiQTouch::iRobiQ_Disconnect(void)
{
	if(isConnected == false) {
		return true;
	}

	if(YJCI_UnInitInterface(pRI) != YJERR_SUCCESS) {
		PrintMessage("ERROR : iRobiQTouch::iRobiQ_Disconnect() -> iRobiQTouch isn't disconnected.\n");
		return false;
	}
	isConnected = false;
	PrintMessage("SUCCESS : iRobiQTouch::iRobiQ_Disconnect() -> iRobiQTouch is disconnected.\n");

	return true;
}

bool iRobiQTouch::iRobiQTouch_Enable(void)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	if(YJRI_SetHWEventFilter(pRI, cmdID++, 0xFFFFFFFF, FALSE) != YJERR_SUCCESS) {
		PrintMessage("ERROR : iRobiQTouch::iRobiQTouch_Enable() -> Can't enable the Hardware Event Filter for Touch\n");
		return false;
	}

	if(WaitForSingleObject(iRobiQEventInfo[pRI].commandEvent, IROBIQ_COMMAND_DELAY) != WAIT_OBJECT_0) {
		PrintMessage("ERROR : iRobiQTouch::iRobiQTouch_Enable() -> Can't enable the Hardware Event Filter for Touch\n");
		return false;
	}
	ResetEvent(iRobiQEventInfo[pRI].connectionEvent);

	return iRobiQEventInfo[pRI].result;
}

bool iRobiQTouch::iRobiQTouch_Disable(void)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	if(YJRI_SetHWEventFilter(pRI, cmdID++, 0x00000000, FALSE) != YJERR_SUCCESS) {
		PrintMessage("ERROR : iRobiQTouch::iRobiQTouch_Enable() -> Can't disable the Hardware Event Filter for Touch\n");
		return false;
	}

	if(WaitForSingleObject(iRobiQEventInfo[pRI].commandEvent, IROBIQ_COMMAND_DELAY) != WAIT_OBJECT_0) {
		PrintMessage("ERROR : iRobiQTouch::iRobiQTouch_Enable() -> Can't disable the Hardware Event Filter for Touch\n");
		return false;
	}
	ResetEvent(iRobiQEventInfo[pRI].connectionEvent);

	return iRobiQEventInfo[pRI].result;
}

bool iRobiQTouch::iRobiQ_GetTouchSensorData(vector<bool> &data)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	data.resize(IROBIQ_TOUCH_SIZE);

	for(int i = 0; i < (int)data.size(); i++) {
		data[i] = touchState[i];
	}

	return false;
}

void iRobiQTouch::EventMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	TOUCHSENSORPARAMS *touch = NULL;
	if(iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("INFO : iRobiQTouch::EventMsgProc() -> Event Messsage : %8x\t%4x\n", dwTaskID, wParam);
		return;
	}

	switch (dwTaskID) {
		//	Connect Event
		case TASK_SYS_CONN:
			iRobiQEventInfo[pRI].result = false;
			switch(wParam) {
				case YJERR_CONN_SUCCESS:
					iRobiQEventInfo[pRI].result = true;
					PrintMessage("SUCCESS : iRobiQTouch::EventMsgProc() -> Connected to Robot successfully \n");
					break;

				case YJERR_CONN_CLOSED:
					PrintMessage("ERROR : iRobiQTouch::EventMsgProc() -> Connection was closed \n");
					break;

				case YJERR_CONN_HOSTUNREACH:
					PrintMessage("ERROR : iRobiQTouch::EventMsgProc() -> Unreachable host \n");
					break;

				case YJERR_CONN_TIMEDOUT:
					PrintMessage("ERROR : iRobiQTouch::EventMsgProc() -> Connection was timed out \n");
					break;

				case YJERR_CONN_CONNREFUSED:
					PrintMessage("ERROR : iRobiQTouch::EventMsgProc() -> Connection was refused \n");
					break;

				default:
					PrintMessage("ERROR : iRobiQTouch::EventMsgProc() -> Unknown error \n");
					break;
			}
			SetEvent(iRobiQEventInfo[pRI].connectionEvent);

			break;

		//	Touch Event
		case TASK_RI_HW_E_TOUCH :
			switch(wParam) {
				case 0x00000000 :
					touch = (TOUCHSENSORPARAMS *)lParam;
					if(touch->dwStatus == 1) {
						touchState[touch->dwButtonID] = true;
					}
					else {
						touchState[touch->dwButtonID] = false;
					}
					PrintMessage("INFO : iRobiQTouch::EventMsgProc() -> Touch Event\n");
					break;
				default :
					break;
			}
			break;

		default:
			break;
	}
}

void iRobiQTouch::ResponseMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
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
					PrintMessage("SUCCESS : iRobiQTouch::ResponseMsgProc() -> Setting HW Event Filter is succeeded\n");
					iRobiQEventInfo[pRI].result = true;
					break;
				default :
					PrintMessage("ERROR : iRobiQTouch::ResponseMsgProc() -> Setting HW Event Filter is failed\n");
					iRobiQEventInfo[pRI].result = false;
					break;
			}
			SetEvent(iRobiQEventInfo[pRI].commandEvent);
			break;

		default:
			break;
	}
}

void iRobiQTouch::AckMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	//	iRobiQSpeech API에서는 사용하지 않음.
}