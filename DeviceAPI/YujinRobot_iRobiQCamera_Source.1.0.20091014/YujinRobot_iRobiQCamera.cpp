#include "YujinRobot_iRobiQCamera.h"
#include "OprosPrintMessage.h"

#include <map>

using namespace std;

#define	IROBIQ_CONNECTION_DELAY		(5000)
#define	IROBIQ_COMMAND_DELAY		(10000)

#define	IROBIQ_CAMERA_176_144	0x01
#define	IROBIQ_CAMERA_320_240	0x02
#define	IROBIQ_CAMERA_640_480	0x03

#define	IROBIQ_CAMERA_BITMAP	0x01
#define	IROBIQ_CAMERA_JPEG		0x02

class iRobiQEvent
{
public:
	bool result;
	HANDLE connectionEvent;
	HANDLE commandEvent;
};

static map<LPROBOTINTERFACE, iRobiQEvent> iRobiQEventInfo;
static WORD cmdID = 0;
std::valarray<unsigned char> captureImage;

YujinRobot_iRobiQCamera::YujinRobot_iRobiQCamera(void)
:pRI(NULL), isConnected(false), isEnabled(false), isStarted(false), width(0), height(0), pixelBytes(0), flip(0), period(0)
{
}

YujinRobot_iRobiQCamera::~YujinRobot_iRobiQCamera(void)
{
	iRobiQ_Finalize();
}

bool YujinRobot_iRobiQCamera::initialize(OPRoS::Property parameter)
{
	if(setParameter(parameter) == false) {
		return false;
	}

	if(parameter.findIndex("IP") == false) {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::initialize() -> Can't get the IP Address from parameter.\n");
		return false;
	}
	std::string ip = parameter.getValue("IP");

	if(parameter.findIndex("port") == false) {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::initialize() -> Can't get the Port Number from parameter.\n");
		return false;
	}
	unsigned int port = (unsigned int)atoi(parameter.getValue("port").c_str());

	if(parameter.findIndex("serviceID") == false) {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::initialize() -> Can't get the Service ID from parameter.\n");
		return false;
	}
	unsigned short serviceId = (unsigned short)atoi(parameter.getValue("serviceID").c_str());

	if(iRobiQ_Initialize() == false) {
		return false;
	}

	if(iRobiQ_Connect(ip, port, serviceId) == false) {
		iRobiQ_Finalize();
	}

	return true;
}

bool YujinRobot_iRobiQCamera::enable(void)
{
	short resolution;
	if(width == 176 && height == 144) {
		resolution = IROBIQ_CAMERA_176_144;
	}
	else if(width == 320 && height == 240) {
		resolution = IROBIQ_CAMERA_320_240;
	}
	else {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::enable() -> Unsupported Resolution.\n");
		return false;
	}

	short format;
	if(pixelBytes == 0) {		//	JPEG
		format = IROBIQ_CAMERA_JPEG;
	}
	else if(pixelBytes == 3) {	//	RGB
		format = IROBIQ_CAMERA_BITMAP;
	}
	else {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::enable() -> Unsupported Image Format.\n");
	}

	if(iRobiQ_EnableCamera(resolution) == false) {
		return false;
	}
	
	if(iRobiQ_StartCapture(period, resolution, format) == false) {
		iRobiQ_DisableCamera();
		return false;
	}

	return true;
}

bool YujinRobot_iRobiQCamera::disable(void)
{
	return iRobiQ_DisableCamera();
}

bool YujinRobot_iRobiQCamera::finalize(void)
{
	return iRobiQ_Finalize();
}

bool YujinRobot_iRobiQCamera::setParameter(OPRoS::Property parameter)
{
	if(parameter.findIndex("width") == false) {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::setParameter() -> Can't find Image Information(widht).\n");
		return false;
	}
	width = atoi(parameter.getValue("width").c_str());

	if(parameter.findIndex("height") == false) {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::setParameter() -> Can't find Image Information(height).\n");
		return false;
	}
	height = atoi(parameter.getValue("height").c_str());

	if(parameter.findIndex("pixelBytes") == false) {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::setParameter() -> Can't find Image Information(pixelBytes).\n");
		return false;
	}
	pixelBytes = atoi(parameter.getValue("pixelBytes").c_str());

	if(parameter.findIndex("flip") == false) {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::setParameter() -> Can't find Image Information(flip).\n");
		return false;
	}
	flip = atoi(parameter.getValue("flip").c_str());

	if(parameter.findIndex("period") == false) {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::setParameter() -> Can't find Image Information(peroid).\n");
		return false;
	}
	period = atoi(parameter.getValue("period").c_str());

	this->parameter = parameter;

	captureImage.resize(width * height * pixelBytes);

	return true;
}

OPRoS::Property YujinRobot_iRobiQCamera::getParameter(void)
{
	return parameter;
}

DEVICE_STATUS YujinRobot_iRobiQCamera::getStatus(void)
{
	return status;
}

bool YujinRobot_iRobiQCamera::getImage(unsigned char *image)
{
	return true;
}

bool YujinRobot_iRobiQCamera::iRobiQ_Initialize(void)
{
	if(pRI != NULL) {
		PrintMessage("INFO : YujinRobot_iRobiQCamera::iRobiQ_Initialize() -> iRobiQCamera already is initialized.\n");
		return true;
	}

	if(YJCI_CreateInstance(&pRI) == YJERR_SUCCESS) {
		if(YJCI_RegAcknowledgeProc(pRI, AckMsgProc) != YJERR_SUCCESS) {
			PrintMessage("ERROR : YujinRobot_iRobiQCamera::iRobiQ_Initialize() -> Can't register the Acknowledge Procedure\n");
			YJCI_DeleteInstance(&pRI);
			return false;
		}
		if(YJCI_RegResponseProc(pRI, ResponseMsgProc) != YJERR_SUCCESS) {
			PrintMessage("ERROR : YujinRobot_iRobiQCamera::iRobiQ_Initialize() -> Can't register the Response Procedure\n");
			YJCI_DeleteInstance(&pRI);
			return false;
		}
		if(YJCI_RegEventProc(pRI, EventMsgProc) != YJERR_SUCCESS) {
			PrintMessage("ERROR : YujinRobot_iRobiQCamera::iRobiQ_Initialize() -> Can't register the Event Procedure\n");
			YJCI_DeleteInstance(&pRI);
			return false;
		}

		iRobiQEventInfo[pRI].connectionEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		iRobiQEventInfo[pRI].commandEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		isConnected = false;

		PrintMessage("SUCCESS : YujinRobot_iRobiQCamera::iRobiQ_Initialize() -> iRobiQCamera is initialized.\n");
	}
	else {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::iRobiQ_Initialize() -> iRobiQCamera isn't intialized.\n");
		pRI = NULL;
		return false;
	}

	return true;
}

bool YujinRobot_iRobiQCamera::iRobiQ_Finalize(void)
{
	if(pRI != NULL)	{
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

		PrintMessage("SUCCESS : YujinRobot_iRobiQCamera::iRobiQ_Finalize() -> iRobiQCamera is finalized.\n");
	}
	else {
		PrintMessage("INFO : YujinRobot_iRobiQCamera::iRobiQ_Finalize() -> iRobiQCamera already is finalized.\n");
	}

	return true;
}

bool YujinRobot_iRobiQCamera::iRobiQ_Connect(std::string ip, unsigned int port, unsigned short serviceId)
{
	if(pRI == NULL || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::iRobiQ_Connect() -> iRobiQCamera is not initialized.\n");
		return false;
	}

	if(isConnected == true) {
		PrintMessage("INFO : YujinRobot_iRobiQCamera::iRobiQ_Connect() -> iRobiQCamera already is connected.\n");
		return true;
	}

	PrintMessage("INFO : YujinRobot_iRobiQCamera::iRobiQ_Connect() -> IP : %s, Port : %d, Serivce ID : %d\n", ip.c_str(), port, serviceId);

	if(YJCI_InitInterface(pRI, serviceId, ip.c_str(), port) == YJERR_SUCCESS) {
		if(WaitForSingleObject(iRobiQEventInfo[pRI].connectionEvent, IROBIQ_CONNECTION_DELAY) == WAIT_OBJECT_0) {
			isConnected = iRobiQEventInfo[pRI].result;
		}
		ResetEvent(iRobiQEventInfo[pRI].connectionEvent);
	}
	else {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::iRobiQ_Connect() -> iRobiQCamera is not connected.\n");
	}

	return isConnected;
}

bool YujinRobot_iRobiQCamera::iRobiQ_Disconnect(void)
{
	if(pRI == NULL || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::iRobiQ_Disconnect() -> iRobiQCamera is not initialized.\n");
		return false;
	}

	if(isConnected == false) {
		PrintMessage("INFO : YujinRobot_iRobiQCamera::iRobiQ_Disconnect() -> iRobiQCamera already is disconnected.\n");
		return true;
	}

	if(YJCI_UnInitInterface(pRI) != YJERR_SUCCESS) {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::iRobiQ_Disconnect() -> iRobiQCamera isn't disconnected.\n");
		return false;
	}
	else {
		isConnected = false;
		PrintMessage("SUCCESS : YujinRobot_iRobiQCamera::iRobiQ_Disconnect() -> iRobiQCamera is disconnected.\n");
	}

	return true;
}

bool YujinRobot_iRobiQCamera::iRobiQ_EnableCamera(short resolution)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::iRobiQ_EnableCamera() -> iRobiQCamera isn't connected.\n");
		return false;
	}

	if(isEnabled == true) {
		return true;
	}

	if(YJVS_ReleaseCamera(pRI, cmdID++, FALSE) != YJERR_SUCCESS) {
		return false;
	}
	if(WaitForSingleObject(iRobiQEventInfo[pRI].commandEvent, IROBIQ_COMMAND_DELAY) != WAIT_OBJECT_0) {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::iRobiQ_EnableCamera() -> Can't enable the Camera\n");
		return false;
	}
	ResetEvent(iRobiQEventInfo[pRI].commandEvent);
	if(iRobiQEventInfo[pRI].result == false) {
		return false;
	}

	CAMERAOPENPARAMSEX cameraParam;
	cameraParam.wShowPreview = 0x00;
	cameraParam.hPreviewWindow = NULL;
	cameraParam.nLeft = 0;
	cameraParam.nTop = 0;
	cameraParam.nWidth = 0;
	cameraParam.nHeight = 0;
	cameraParam.wResolution = resolution;
	cameraParam.dwReserved = 0;

	if(YJRI_OpenCameraEx(pRI, cmdID++, &cameraParam, FALSE) != YJERR_SUCCESS) {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::iRobiQ_EnableCamrea() -> Occur a error in YJRI_OpenCameraEx().\n");
		return false;
	}

	if(WaitForSingleObject(iRobiQEventInfo[pRI].commandEvent, IROBIQ_COMMAND_DELAY) != WAIT_OBJECT_0) {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::iRobiQ_EnableCamrea() -> Can't enable the Camera\n");
		return false;
	}
	ResetEvent(iRobiQEventInfo[pRI].commandEvent);

	return (isEnabled = iRobiQEventInfo[pRI].result);
}

bool YujinRobot_iRobiQCamera::iRobiQ_StartCapture(int period, short resolution, short format)
{
	if(pRI == NULL || isConnected == false || isEnabled == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::iRobiQ_StartCapture() -> Can't start the capture.\n");
		return false;
	}

	if(isStarted == true) {
		return true;
	}

	CAPIMGPERIODPARAMS captureParam;
	captureParam.nPeriod = period;
	captureParam.wResolution = resolution;
	captureParam.wFormat = format;

	if(YJRI_StartCapImgPeriod(pRI, cmdID++, &captureParam, FALSE) != YJERR_SUCCESS) {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::iRobiQ_StartCapture() -> Occur a error in YJRI_StartCapImgPeriod.\n");
		return false;
	}

	if(WaitForSingleObject(iRobiQEventInfo[pRI].commandEvent, IROBIQ_COMMAND_DELAY) != WAIT_OBJECT_0) {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::iRobiQ_StartCapture() -> Can't start the capture.\n");
		return false;
	}
	ResetEvent(iRobiQEventInfo[pRI].commandEvent);

	return (isStarted = iRobiQEventInfo[pRI].result);
}

bool YujinRobot_iRobiQCamera::iRobiQ_StopCapture(void)
{
	if(pRI == NULL || isConnected == false || isEnabled == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	if(isStarted== false) {
		return true;
	}

	if(YJRI_StopCapImgPeriod(pRI, cmdID++, FALSE) != YJERR_SUCCESS) {
		return false;
	}
	if(WaitForSingleObject(iRobiQEventInfo[pRI].commandEvent, IROBIQ_COMMAND_DELAY) != WAIT_OBJECT_0) {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::iRobiQ_StopCapture() -> Can't stop the capture\n");
		return false;
	}
	ResetEvent(iRobiQEventInfo[pRI].commandEvent);

	if(iRobiQEventInfo[pRI].result == true) {
		isStarted = false;
	}

	return iRobiQEventInfo[pRI].result;
}
	
bool YujinRobot_iRobiQCamera::iRobiQ_DisableCamera(void)
{
	if(pRI == NULL || isConnected == false || iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return false;
	}

	if(isStarted == true) {
		if(iRobiQ_StopCapture() == false) {
			return false;
		}
	}

	if(YJRI_CloseCamera(pRI, cmdID++, FALSE) != YJERR_SUCCESS) {
		return false;
	}
	if(WaitForSingleObject(iRobiQEventInfo[pRI].commandEvent, IROBIQ_COMMAND_DELAY) != WAIT_OBJECT_0) {
		PrintMessage("ERROR : YujinRobot_iRobiQCamera::iRobiQ_StopCapture() -> Can't enable the Camera\n");
		return false;
	}
	ResetEvent(iRobiQEventInfo[pRI].commandEvent);
	if(iRobiQEventInfo[pRI].result == false) {
		return false;
	}

	return (isEnabled = false);
}

void YujinRobot_iRobiQCamera::EventMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	CAPIMGRESULT *camera = NULL;

	if(iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		PrintMessage("INFO : YujinRobot_iRobiQCamera::EventMsgProc() -> Event Messsage : %8x\t%4x\n", dwTaskID, wParam);
		return;
	}

	switch (dwTaskID) {
		//	Connection Event
		case TASK_SYS_CONN:
			iRobiQEventInfo[pRI].result = false;
			switch(wParam) {
				case YJERR_CONN_SUCCESS:
					iRobiQEventInfo[pRI].result = true;
					PrintMessage("SUCCESS : YujinRobot_iRobiQCamera::EventMsgProc() -> Connected to Robot successfully \n");
					break;

				case YJERR_CONN_CLOSED:
					PrintMessage("ERROR : YujinRobot_iRobiQCamera::EventMsgProc() -> Connection was closed \n");
					break;

				case YJERR_CONN_HOSTUNREACH:
					PrintMessage("ERROR : YujinRobot_iRobiQCamera::EventMsgProc() -> Unreachable host \n");
					break;

				case YJERR_CONN_TIMEDOUT:
					PrintMessage("ERROR : YujinRobot_iRobiQCamera::EventMsgProc() -> Connection was timed out \n");
					break;

				case YJERR_CONN_CONNREFUSED:
					PrintMessage("ERROR : YujinRobot_iRobiQCamera::EventMsgProc() -> Connection was refused \n");
					break;

				default:
					PrintMessage("ERROR : YujinRobot_iRobiQCamera::EventMsgProc() -> Unknown error \n");
					break;
			}
			SetEvent(iRobiQEventInfo[pRI].connectionEvent);

			break;
		//	Camera Event
		case TASK_RI_START_CAPIMG_PERIOD :
			switch(wParam) {
				case YJERR_SUCCESS :
					camera = (CAPIMGRESULT *)lParam;
					if((int)captureImage.size() != camera->dwFileLength) {
						captureImage.resize(camera->dwFileLength);
					}
					memcpy(&captureImage[0], camera->lpFileBuffer, camera->dwFileLength);
					break;
				default:
					PrintMessage("ERROR : YujinRobot_iRobiQCamera::EventMsgProc() -> Can't get the Image\n");
					break;
			}
			break;

		default:
			break;
	}
}

void YujinRobot_iRobiQCamera::ResponseMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	DWORD dwResultCode = (DWORD)wParam;

	if(iRobiQEventInfo.find(pRI) == iRobiQEventInfo.end()) {
		return;
	}
	
	switch (dwTaskID) {
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Camera
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case TASK_RI_OPEN_CAMERA_EX :
			switch (dwResultCode) {
				case YJERR_SUCCESS:
					PrintMessage("SUCCESS : YujinRobot_iRobiQCamera::EventMsgProc() -> YJRI_OpenCameraEx is succeeded\n");
					iRobiQEventInfo[pRI].result = true;
					break;
				default:
					iRobiQEventInfo[pRI].result = false;
					PrintMessage("ERROR : YujinRobot_iRobiQCamera::EventMsgProc() -> YJRI_OpenCameraEx is failed : %x\n", dwResultCode);
					break;
			}
			SetEvent(iRobiQEventInfo[pRI].commandEvent);
			break;

		case TASK_RI_CLOSE_CAMERA :
			switch (dwResultCode) {
				case YJERR_SUCCESS:
					PrintMessage("SUCCESS : YujinRobot_iRobiQCamera::EventMsgProc() -> YJRI_CloseCamera is succeeded\n");
					iRobiQEventInfo[pRI].result = true;
					break;
				default:
					iRobiQEventInfo[pRI].result = false;
					PrintMessage("ERROR : YujinRobot_iRobiQCamera::EventMsgProc() -> YJRI_CloseCamera is failed : %x\n", dwResultCode);
					break;
			}
			SetEvent(iRobiQEventInfo[pRI].commandEvent);
			break;

		case TASK_RI_START_CAPIMG_PERIOD:
			switch (dwResultCode) {
				case YJERR_SUCCESS:
					PrintMessage("SUCCESS : YujinRobot_iRobiQCamera::EventMsgProc() -> YJRI_StartCapImgPeriod is succeeded\n");
					iRobiQEventInfo[pRI].result = true;
					break;
				default:
					PrintMessage("ERROR : YujinRobot_iRobiQCamera::EventMsgProc() -> YJRI_StartCapImgPeriod is failed : %x\n", dwResultCode);
					iRobiQEventInfo[pRI].result = false;
					break;
			}
			SetEvent(iRobiQEventInfo[pRI].commandEvent);
			break;

		case TASK_RI_STOP_CAPIMG_PERIOD:
			switch (dwResultCode) {
				case YJERR_SUCCESS:
					PrintMessage("SUCCESS : YujinRobot_iRobiQCamera::EventMsgProc() -> YJRI_StartCapImgPeriod is succeeded\n");
					iRobiQEventInfo[pRI].result = true;
					break;
				default:
					PrintMessage("ERROR : YujinRobot_iRobiQCamera::EventMsgProc() -> YJRI_StartCapImgPeriod is failed : %x\n", dwResultCode);
					iRobiQEventInfo[pRI].result = false;
					break;
			}
			SetEvent(iRobiQEventInfo[pRI].commandEvent);
			break;

		case TASK_VS_RELEASE_CAMERA:
			switch (dwResultCode) {
				case YJERR_SUCCESS:
					PrintMessage("SUCCESS : YujinRobot_iRobiQCamera::EventMsgProc() -> YJVS_ReleaseCamera is succeeded\n");
					iRobiQEventInfo[pRI].result = true;
					break;
				default:
					PrintMessage("ERROR : YujinRobot_iRobiQCamera::EventMsgProc() -> YJVS_ReleaseCamera is failed\n");
					iRobiQEventInfo[pRI].result = false;
					break;
			}
			SetEvent(iRobiQEventInfo[pRI].commandEvent);
			break;

		default:
			break;
	}
}

void YujinRobot_iRobiQCamera::AckMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam)
{
	//	iRobiQSpeech API에서는 사용하지 않음.
}

extern "C"
{
__declspec(dllexport) OprosApi *getAPI();
}

OprosApi *getAPI()
{
	return new YujinRobot_iRobiQCamera();
}
