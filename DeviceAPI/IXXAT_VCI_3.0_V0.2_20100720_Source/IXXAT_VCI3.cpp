#include "IXXAT_VCI3.h"

#include "vcinpl.h"
#include "OprosLock.h"
#include "OprosTimer.h"
#include "OprosPrintMessage.h"

#pragma comment (lib,"./windows/vcisdk.lib") 

class IXXATInfo {
public:
	IXXATInfo(void)
	{
		vciDeviceHandle = INVALID_HANDLE_VALUE;
		canChannelHandle = INVALID_HANDLE_VALUE;
		canControlHandle = INVALID_HANDLE_VALUE;
		nOpened = 0;
		timeOut = 10;
		bitRate = 1000000;
		acceptanceCode = 0;
		acceptanceMask = 0;
		canExtended = false;
	}
	virtual ~IXXATInfo(void) { };

	VCIDEVICEINFO deviceInfo;
	HANDLE vciDeviceHandle;
	HANDLE canChannelHandle;
	HANDLE canControlHandle;
	int nOpened;
	DWORD timeOut;
	unsigned long bitRate;
	unsigned long acceptanceCode;
	unsigned long acceptanceMask;
	bool canExtended;
	OprosLock lock;
};

static vector<IXXATInfo> hIXXATCAN;
static bool isInitialized = false;

IXXAT_VCI3::IXXAT_VCI3(void)
{
	isOpened = false;

	if(isInitialized == false) {
		HANDLE enumDeviceHandle;

		HRESULT hResult = vciEnumDeviceOpen(&enumDeviceHandle);
		if(hResult != VCI_OK) {
			return;
		}

		isInitialized = true;

		IXXATInfo ixxatInfo;
		for(int i = 0; ;i++) {
			hResult = vciEnumDeviceNext(enumDeviceHandle, &ixxatInfo.deviceInfo);
			if(hResult != VCI_OK) {
				break;
			}

			hIXXATCAN.push_back(ixxatInfo);
		}
		vciEnumDeviceClose(enumDeviceHandle);

		PrintMessage("INFO -> IXXAT_VCI3::IXXAT_VCI3() -> Number of device : %d.\n", hIXXATCAN.size());
	}
}

IXXAT_VCI3::~IXXAT_VCI3(void)
{
	Finalize();
}

int IXXAT_VCI3::Initialize(Property parameter)
{
	PrintMessage("INFO -> IXXAT_VCI3::Initialize() -> Start.\n");

	if(SetParameter(parameter) == API_ERROR) {
		PrintMessage("ERROR -> IXXAT_VCI3::Initialize() -> Occur a error in SetParameter()\n");
		return API_ERROR;
	}

	PrintMessage("SUCCESS -> IXXAT_VCI3::Initialize()\n");

	return API_SUCCESS;
}

int IXXAT_VCI3::Finalize(void)
{
	Disable();
	return API_SUCCESS;
}

int IXXAT_VCI3::Enable(void)
{
	Lock();

	if(hIXXATCAN[channel].nOpened != 0) {
		hIXXATCAN[channel].nOpened++;
		isOpened = true;
		Unlock();
		PrintMessage("SUCCESS -> IXXAT_VCI3::Enable()\n");
		return API_SUCCESS;
	}

	//	Open a device
	if(vciDeviceOpen((REFVCIID)(hIXXATCAN[channel].deviceInfo.VciObjectId), &hIXXATCAN[channel].vciDeviceHandle) != VCI_OK) {
		PrintMessage("ERROR : IXXAT_VCI3::Enable() -> Can't open the device.\n");
		goto IXXAT_VCI3_ENABLE_ERROR;
	}

	//	Open a channel
	if(canChannelOpen(hIXXATCAN[channel].vciDeviceHandle, (DWORD)channel, FALSE, &hIXXATCAN[channel].canChannelHandle) != VCI_OK) {
		PrintMessage("ERROR : IXXAT_VCI3::Enable() -> Can't open the channel.\n");
		goto IXXAT_VCI3_ENABLE_ERROR;
	}

	//	Initialize a channel
	WORD wRxFifoSize  = 1024;
	WORD wRxThreshold = 1;
	WORD wTxFifoSize  = 128;
	WORD wTxThreshold = 1;

	if(canChannelInitialize(hIXXATCAN[channel].canChannelHandle, wRxFifoSize, wRxThreshold, wTxFifoSize, wTxThreshold) != VCI_OK) {
		goto IXXAT_VCI3_ENABLE_ERROR;
	}

	// Activate the CAN channel
	if(canChannelActivate(hIXXATCAN[channel].canChannelHandle, TRUE) != VCI_OK) {
		goto IXXAT_VCI3_ENABLE_ERROR;
	}

	//	Open the CAN Controller
	if(canControlOpen(hIXXATCAN[channel].vciDeviceHandle, channel, &hIXXATCAN[channel].canControlHandle) != VCI_OK) {
		goto IXXAT_VCI3_ENABLE_ERROR;
	}

	//	Initialize the CAN Controller
	BYTE mode;
	BOOL bMode;
	if (hIXXATCAN[channel].canExtended) {
		mode = CAN_OPMODE_EXTENDED;	
		bMode = TRUE;	
	}
	else {
		mode = CAN_OPMODE_STANDARD;	
		bMode = FALSE;	
	}

	BYTE bit0, bit1;
	switch(hIXXATCAN[channel].bitRate) {
	case 1000000:	bit0 = CAN_BT0_1000KB;	bit1 = CAN_BT1_1000KB;	break;
	case 500000:	bit0 = CAN_BT0_500KB;	bit1 = CAN_BT1_500KB;	break;
	case 250000:	bit0 = CAN_BT0_250KB;	bit1 = CAN_BT1_250KB;	break;
	case 125000:	bit0 = CAN_BT0_125KB;	bit1 = CAN_BT1_125KB;	break;
	case 100000:	bit0 = CAN_BT0_100KB;	bit1 = CAN_BT1_100KB;	break;
	case 50000:		bit0 = CAN_BT0_50KB;	bit1 = CAN_BT1_50KB;	break;
	default: {
		goto IXXAT_VCI3_ENABLE_ERROR;
		}
	}

	if(canControlInitialize(hIXXATCAN[channel].canControlHandle, mode, bit0, bit1) != VCI_OK) {
		goto IXXAT_VCI3_ENABLE_ERROR;
	}

	if(canControlSetAccFilter(hIXXATCAN[channel].canControlHandle, bMode, hIXXATCAN[channel].acceptanceCode, hIXXATCAN[channel].acceptanceMask) != VCI_OK) {
		goto IXXAT_VCI3_ENABLE_ERROR;
	}

	//	Start the CAN Controller
	if(canControlStart(hIXXATCAN[channel].canControlHandle, TRUE) != VCI_OK) {
		goto IXXAT_VCI3_ENABLE_ERROR;
	}

	isOpened = true;
	hIXXATCAN[channel].nOpened++;

	Unlock();

	PrintMessage("SUCCESS -> IXXAT_VCI3::Enable()\n");
	
	return API_SUCCESS;

IXXAT_VCI3_ENABLE_ERROR:
	if (hIXXATCAN[channel].canControlHandle) canControlClose(hIXXATCAN[channel].canControlHandle);
	if (hIXXATCAN[channel].canChannelHandle) canChannelClose(hIXXATCAN[channel].canChannelHandle);
	if (hIXXATCAN[channel].vciDeviceHandle) vciDeviceClose(hIXXATCAN[channel].vciDeviceHandle);

	hIXXATCAN[channel].canControlHandle = INVALID_HANDLE_VALUE;
	hIXXATCAN[channel].canChannelHandle = INVALID_HANDLE_VALUE;
	hIXXATCAN[channel].vciDeviceHandle  = INVALID_HANDLE_VALUE;

	Unlock();
	PrintMessage("ERROR -> IXXAT_VCI3::Enable() ->Can't enable a IXXAT.\n");
	return API_ERROR;
}

int IXXAT_VCI3::Disable(void)
{
	Lock();

	if(isOpened == false || hIXXATCAN[channel].nOpened == 0) {
		Unlock();	return API_SUCCESS;
	}

	hIXXATCAN[channel].nOpened--;
	if(hIXXATCAN[channel].nOpened == 0) {
		if (hIXXATCAN[channel].canControlHandle) canControlClose(hIXXATCAN[channel].canControlHandle);
		if (hIXXATCAN[channel].canChannelHandle) canChannelClose(hIXXATCAN[channel].canChannelHandle);
		if (hIXXATCAN[channel].vciDeviceHandle) vciDeviceClose(hIXXATCAN[channel].vciDeviceHandle);

		hIXXATCAN[channel].canControlHandle = INVALID_HANDLE_VALUE;
		hIXXATCAN[channel].canChannelHandle = INVALID_HANDLE_VALUE;
		hIXXATCAN[channel].vciDeviceHandle  = INVALID_HANDLE_VALUE;
	}

	Unlock();

	return API_SUCCESS;
}

int IXXAT_VCI3::SetParameter(Property parameter)
{
	if(parameter.FindName("Channel") == false) return API_ERROR;
	channel = atoi(parameter.GetValue("Channel").c_str());

	if(channel < 0 || channel >= (int)hIXXATCAN.size()) {
		return API_ERROR;
	}

	if(hIXXATCAN[channel].nOpened > 0) {
		return API_SUCCESS;
	}

	if(parameter.FindName("TimeOut") == false)				return API_ERROR;
	hIXXATCAN[channel].timeOut = atol(parameter.GetValue("TimeOut").c_str());

	if(parameter.FindName("BitRate") == false)				return API_ERROR;
	hIXXATCAN[channel].bitRate = atol(parameter.GetValue("BitRate").c_str());

	if(parameter.FindName("AcceptanceCode") == false)	return API_ERROR;
	hIXXATCAN[channel].acceptanceCode = atol(parameter.GetValue("AcceptanceCode").c_str());

	if(parameter.FindName("AcceptanceMask") == false)		return API_ERROR;
	hIXXATCAN[channel].acceptanceMask = atol(parameter.GetValue("AcceptanceMask").c_str());

	int mode = atoi(parameter.GetValue("Mode").c_str());
	if(mode == 0)	hIXXATCAN[channel].canExtended = false;
	else			hIXXATCAN[channel].canExtended = true;

	return API_SUCCESS;
}

int IXXAT_VCI3::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int IXXAT_VCI3::Lock(void)
{
	if(channel < 0 || channel >= (int)hIXXATCAN.size()) {
		return API_ERROR;
	}

	hIXXATCAN[channel].lock.Lock();

	return API_SUCCESS;
}

int IXXAT_VCI3::Unlock(void)
{
	if(channel < 0 || channel >= (int)hIXXATCAN.size()) {
		return API_ERROR;
	}

	hIXXATCAN[channel].lock.Unlock();

	return API_SUCCESS;
}

int IXXAT_VCI3::Write(long id, unsigned char *data, int size)
{
	if(channel < 0 || channel >= (int)hIXXATCAN.size()) {
		return API_ERROR;
	}

	CANMSG  canMsg;
	canMsg.dwMsgId = id;
	canMsg.dwTime = 0;
	memcpy(canMsg.abData, data, size);
	canMsg.uMsgInfo.Bytes.bType  = CAN_MSGTYPE_DATA;
	canMsg.uMsgInfo.Bytes.bFlags = CAN_MAKE_MSGFLAGS(size, 0, 0, 0, hIXXATCAN[channel].canExtended);

	if(canChannelSendMessage(hIXXATCAN[channel].canChannelHandle, hIXXATCAN[channel].timeOut, &canMsg) != VCI_OK) {
		return -1;
	}

	if(canChannelWaitTxEvent(hIXXATCAN[channel].canChannelHandle, hIXXATCAN[channel].timeOut) != VCI_OK) {
		return -1;
	}

	return size;
}

int IXXAT_VCI3::Read(long &id, unsigned char *data, int size)
{
	if(channel < 0 || channel >= (int)hIXXATCAN.size()) {
		return API_ERROR;
	}

	while(1) {
		CANMSG canMsg;

		if(canChannelWaitRxEvent(hIXXATCAN[channel].canChannelHandle, hIXXATCAN[channel].timeOut) != VCI_OK) {
			return -1;
		}
		if(canChannelReadMessage(hIXXATCAN[channel].canChannelHandle, hIXXATCAN[channel].timeOut, &canMsg) != VCI_OK) {
			return -1;
		}

		if(canMsg.uMsgInfo.Bytes.bType == CAN_MSGTYPE_DATA) {
			id = canMsg.dwMsgId;
			size = min (size, (int)canMsg.uMsgInfo.Bits.dlc);
			memcpy(data, canMsg.abData, size);
			break;
		}
		OprosSleep (0);
	}

	return size;
}

#if !defined(DEVICE_TEST)
#if defined(WIN32)
extern "C"
{
	__declspec(dllexport) OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new IXXAT_VCI3();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new IXXAT_VCI3();
}

#endif
#endif