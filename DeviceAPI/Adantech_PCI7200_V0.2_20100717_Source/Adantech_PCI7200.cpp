#include "Adantech_PCI7200.h"
#include "OprosPrintMessage.h"

#include "./Windows/Dask.h"

#define PCI7200_PORT_COUNT		32

Adantech_PCI7200::Adantech_PCI7200(void)
{
	_handle = -1;
	_channel = 0;
	_inputPortCount = 0;
	_outputPortCount = 0;
}

Adantech_PCI7200::~Adantech_PCI7200(void)
{
	Finalize();
}

int Adantech_PCI7200::Initialize(Property parameter)
{
	if(SetParameter(parameter) == API_ERROR) {
		return API_ERROR;
	}

	if(_handle = Register_Card(PCI_7200, _channel) < 0) {
		PrintMessage("ERROR : Adantech_PCI7200::Initialize() -> ");
		PCI7200_PrintErrorMessage(_handle);
		PrintMessage("\n");
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Adantech_PCI7200::Finalize(void)
{
	if(_handle >= 0) {
		Release_Card(_handle);
		_handle = -1;
		_channel = -1;
	}

	return API_SUCCESS;
}

int Adantech_PCI7200::Enable(void)
{
	if(_handle < 0) {
		return API_ERROR;
	}

	short err;
	if((err = DO_7200_Config(_handle, TRIG_INT_PACER, OREQ_DISABLE, OTRIG_LOW)) != NoError) {		
		PrintMessage("ERROR : Adantech_PCI7200::Enable() -> ");
		PCI7200_PrintErrorMessage(err);
		PrintMessage("\n");
		return API_ERROR;
	}

	if((err = DI_7200_Config(_handle, TRIG_INT_PACER, DI_NOWAITING, DI_TRIG_FALLING, IREQ_FALLING)) != NoError) {	
		PrintMessage("ERROR : Adantech_PCI7200::Enable() -> ");
		PCI7200_PrintErrorMessage(err);
		PrintMessage("\n");
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Adantech_PCI7200::Disable(void)
{
	return API_SUCCESS;
}

int Adantech_PCI7200::SetParameter(Property parameter)
{
	if(parameter.FindName("DigitalInputPortSize") == false)	{
		return API_ERROR;
	}
	_inputPortCount = atoi(parameter.GetValue("DigitalInputPortSize").c_str());
	if(_inputPortCount > PCI7200_PORT_COUNT || _inputPortCount < 0) {
		return API_ERROR;
	}

	if(parameter.FindName("DigitalOutputPortSize") == false) {
		return API_ERROR;
	}
	_outputPortCount = atoi(parameter.GetValue("DigitalOutputPortSize").c_str());
	if(_outputPortCount > PCI7200_PORT_COUNT || _outputPortCount < 0) {
		return API_ERROR;
	}

	this->parameter = parameter;

	return API_SUCCESS;
}

int Adantech_PCI7200::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int Adantech_PCI7200::SetDigitalOutputData(vector<bool> digitalOutputData)
{
	if(digitalOutputData.size() != (size_t)_outputPortCount) {
		return API_ERROR;
	}

	unsigned long data = 0;
	for(size_t i = 0; i < digitalOutputData.size(); i++) {
		if(digitalOutputData[0] == true) {
			data = data | (1 << i);
		}
	}

	if(Adantech_PCI7200_WritePort(data) < 0) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Adantech_PCI7200::GetDigitalInputData(vector<bool> &digitalInputData)
{
	if(_inputPortCount < 0) {
		return API_ERROR;
	}
	digitalInputData.resize(_inputPortCount);

	unsigned long data;
	if(Adantech_PCI7200_ReadPort(&data) < 0) {
		return API_ERROR;
	}

	for(int i = 0; i < _inputPortCount; i++) {
		if(((data >> i) & 0x1) == 0x1) {
			digitalInputData[i] = true;
		}
		else {
			digitalInputData[i] = false;
		}
	}

	return API_SUCCESS;
}

int Adantech_PCI7200::Adantech_PCI7200_WritePort(unsigned long data)
{
	if(_handle < 0) {
		return -1;
	}

	short err;
	if((err = DO_WritePort(_handle, 0, data)) != NoError) {
		PrintMessage("ERROR : Adantech_PCI7200::Adantech_PCI7200_WritePort() -> ");
		PCI7200_PrintErrorMessage(err);
		PrintMessage("\n");
		return -1;
	}

	return 0;
}

int Adantech_PCI7200::Adantech_PCI7200_ReadPort(unsigned long *data)
{
	if(_handle < 0) {
		return -1;
	}

	short err;
	if((err = DI_ReadPort(_handle, 0, data)) != NoError) {
		PrintMessage("ERROR : Adantech_PCI7200::Adantech_PCI7200_ReadPort() -> ");
		PCI7200_PrintErrorMessage(err);
		PrintMessage("\n");
		return -1;
	}

	return 0;
}

void Adantech_PCI7200::PCI7200_PrintErrorMessage(short errorCode)
{
	switch(errorCode) {
		case ErrorUnknownCardType :
			PrintMessage("The CardType argument is not valid.");
			break;

		case ErrorInvalidCardNumber :
			PrintMessage("The CardNumber argument is out of range (larger than 31).");
			break;

		case ErrorTooManyCardRegistered :
			PrintMessage("32 cards have been registered.");
			break;

		case ErrorCardNotRegistered :
			PrintMessage("No card registered as id CardNumber.");
			break;

		case ErrorFuncNotSupport :
			PrintMessage("The function called is not supported by this type of card.");
			break;

		case ErrorInvalidIoChannel :
			PrintMessage("The specified Channel or Port argument is out of range.");
			break;

		case ErrorContIoNotAllowed :
			PrintMessage("The specified continuous IO operation is not supported by this type of card.");
			break;

		case ErrorDiffRangeNotSupport :
			PrintMessage("All the analog input ranges must be the same for multichannel analog input.");
			break;

		case ErrorLastChannelNotZero :
			PrintMessage("The channels for multi-channel analog input must end with or start from zero.");
			break;

		case ErrorChannelNotDescending :
			PrintMessage("The channels for multi-channel analog input must be contiguous and in descending order.");
			break;

		case ErrorChannelNotAscending :
			PrintMessage("The channels for multi-channel analog input must be contiguous and in ascending order.");
			break;

		case ErrorOpenDriverFailed :
			PrintMessage("Failed to open the device driver.");
			break;

		case ErrorOpenEventFailed :
			PrintMessage("Open event failed in device driver.");
			break;

		case ErrorTransferCountTooLarge :
			PrintMessage("The size of transfer is larger than the size of initially allocated memory in driver.");
			break;

		case ErrorNotDoubleBufferMode :
			PrintMessage("Double buffer mode is disabled.");
			break;

		case ErrorInvalidSampleRate :
			PrintMessage("The specified sampling rate is out of range.");
			break;

		case ErrorInvalidCounterMode :
			PrintMessage("The value of the Mode argument is invalid.");
			break;

		case ErrorInvalidCounter :
			PrintMessage("The value of the Ctr argument is out of range.");
			break;

		case ErrorInvalidCounterState :
			PrintMessage("The value of the State argument is out of range.");
			break;

		case ErrorInvalidBinBcdParam :
			PrintMessage("The value of the BinBcd argument is invalid.");
			break;

		case ErrorBadCardType :
			PrintMessage("The value of Card Type argument is invalid.");
			break;

		case ErrorInvalidDaRefVoltage :
			PrintMessage("The value of DA reference voltage argument is invalid.");
			break;

		case ErrorAdTimeOut :
			PrintMessage("AD operation timed-out.");
			break;

		case ErrorNoAsyncAI :
			PrintMessage("Continuous AI is not set to asynchronous mode.");
			break;

		case ErrorNoAsyncAO :
			PrintMessage("Continuous AO is not set to asynchronous mode.");
			break;

		case ErrorNoAsyncDI :
			PrintMessage("Continuous DI is not set to asynchronous mode.");
			break;

		case ErrorNoAsyncDO :
			PrintMessage("Continuous DO is not set to asynchronous mode.");
			break;

		case ErrorNotInputPort :
			PrintMessage("The value of AI/DI port argument is invalid.");
			break;

		case ErrorNotOutputPort :
			PrintMessage("The value of AO/DO argument is invalid.");
			break;

		case ErrorInvalidDioPort :
			PrintMessage("The value of DI/O port argument is invalid.");
			break;

		case ErrorInvalidDioLine :
			PrintMessage("The value of DI/O line argument is invalid.");
			break;

		case ErrorContIoActive :
			PrintMessage("Continuous IO operation is not active.");
			break;

		case ErrorDblBufModeNotAllowed :
			PrintMessage("Double Buffer mode is not allowed.");
			break;

		case ErrorConfigFailed :
			PrintMessage("The specified function configuration failed.");
			break;

		case ErrorInvalidPortDirection :
			PrintMessage("The value of DIO port direction argument is invalid.");
			break;

		case ErrorBeginThreadError :
			PrintMessage("Failed to create thread.");
			break;

		case ErrorInvalidPortWidth :
			PrintMessage("Port width setting for PCI-7300A/cPCI-7300A is not allowed.");
			break;

		case ErrorInvalidCtrSource :
			PrintMessage("The clock source setting is invalid.");
			break;

		case ErrorOpenFile :
			PrintMessage("Failed to open file");
			break;

		case ErrorAllocateMemory :
			PrintMessage("The memory allocation failed.");
			break;

		case ErrorDaVoltageOutOfRange :
			PrintMessage("The value of DA voltage argument is out of range.");
			break;

		case ErrorInvalidCounterValue :
			PrintMessage("The value of count for a counter is invalid.");
			break;

		case ErrorInvalidEventHandle :
			PrintMessage("The event handle is invalid.");
			break;

		case ErrorNoMessageAvailable :
			PrintMessage("No event message can be added.");
			break;

		case ErrorEventMessgaeNotAdded :
			PrintMessage("The specified event message does not exist.");
			break;

		case ErrorCalibrationTimeOut :
			PrintMessage("Auto-calibration has timed-out.");
			break;

		case ErrorUndefinedParameter :
			PrintMessage("Parameter(s) is not defined.");
			break;

		case ErrorInvalidBufferID :
			PrintMessage("Buffer ID is invalid.");
			break;

		case ErrorConfigIoctl :
			PrintMessage("The configuration API failed.");
			break;

		case ErrorAsyncSetIoctl :
			PrintMessage("The async. mode API failed.");
			break;

		case ErrorDBSetIoctl :
			PrintMessage("The double-buffer setting API failed.");
			break;

		case ErrorDBHalfReadyIoctl :
			PrintMessage("The half-ready API failed.");
			break;

		case ErrorContOPIoctl :
			PrintMessage("The continuous data acquisition API failed.");
			break;

		case ErrorContStatusIoctl :
			PrintMessage("Continuous data acquisition status API setting failed.");
			break;

		case ErrorPIOIoctl :
			PrintMessage("The polling data API failed.");
			break;

		case ErrorDIntSetIoctl :
			PrintMessage("The dual-interrupt setting API failed.");
			break;

		case ErrorWaitEvtIoctl :
			PrintMessage("The wait event API failed.");
			break;

		case ErrorOpenEvtIoctl :
			PrintMessage("The open event API failed.");
			break;

		case ErrorCOSIntSetIoctl :
			PrintMessage("The COS interrupt setting API failed.");
			break;

		case ErrorMemMapIoctl :
			PrintMessage("The memory mapping API failed.");
			break;

		case ErrorMemUMapSetIoctl :
			PrintMessage("The memory unmapping API failed.");
			break;

		case ErrorCTRIoctl :
			PrintMessage("The counter API failed.");
			break;

		default :
			PrintMessage("Error Unknown.");
			break;
	}
}

#if !defined(DEVICE_TEST)
#if defined(WIN32)
extern "C"
{
__declspec(dllexport) OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new Adantech_PCI7200();
}
#endif
#endif
