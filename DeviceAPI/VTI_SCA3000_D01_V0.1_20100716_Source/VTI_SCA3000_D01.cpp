#include "VTI_SCA3000_D01.h"

#include "OprosPrintMessage.h"
#include "OprosTimer.h"

#include "boost/tokenizer.hpp"

#define	VTI_RECEIVE_TIMEOUT			5
#define VTI_MAX_DATA				3
#define VTI_DATA_SAMPLE				10		//request할때 몇개의 data sample을 요구할 것인가
#define VTI_SENSITIVITY				1333	//1333 count/g
#define GRAVITY_ACCEL				9.80665

using namespace boost;

VTI_SCA3000_D01::VTI_SCA3000_D01(void)
{
	_uart = NULL;

	_offset[0] = _offset[1] = _offset[2] = 0;
}

VTI_SCA3000_D01::~VTI_SCA3000_D01(void)
{
	Finalize();
}

int VTI_SCA3000_D01::Initialize(Property parameter)
{
	if(InitializeUART(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : VTI_SCA3000_D01::Initialize() -> Occur a error in InitializeUART().\n");
		return API_ERROR;
	}

	if(SetParameter(parameter) != API_SUCCESS) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int VTI_SCA3000_D01::Finalize(void)
{
	if(_uart != NULL) {
		delete _uart;
		_uart = NULL;
	}

	if(hOprosAPI != NULL) {
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
	}

	return API_SUCCESS;
}

int VTI_SCA3000_D01::Enable(void)
{
	Initialize();
	//약간의 sleep 필요.
	OprosSleep(10);
	//초기화를 하면 보드에서 결과를 리턴하는데.. 이걸 강제로 읽어서 처리한다.
	unsigned char trashData[1024] = {0,};
	ReceivePacket(trashData, sizeof(trashData));

	return API_SUCCESS;
}

int VTI_SCA3000_D01::Disable(void)
{
	return API_SUCCESS;
}

int VTI_SCA3000_D01::SetParameter(Property parameter)
{
	if(parameter.FindName("Size") == false)				return API_ERROR;
	int size = atoi(parameter.GetValue("Size").c_str());

	if(size != 3) {
		return API_ERROR;
	}

	char name[128];
	for(int i = 0; i < size; i++) {
		sprintf(name, "X%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_VTI_SCA3000_D01_SetParameter;
		
		sprintf(name, "Y%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_VTI_SCA3000_D01_SetParameter;
		
		sprintf(name, "Z%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_VTI_SCA3000_D01_SetParameter;
		
		sprintf(name, "Roll%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_VTI_SCA3000_D01_SetParameter;
		
		sprintf(name, "Pitch%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_VTI_SCA3000_D01_SetParameter;
		
		sprintf(name, "Yaw%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_VTI_SCA3000_D01_SetParameter;
	}

	this->parameter = parameter;

	return API_SUCCESS;

ERROR_VTI_SCA3000_D01_SetParameter :
	PrintMessage("ERROR : VTI_SCA3000_D01::SetParameter -> Can't find a property in parameter.\n");
	return API_ERROR;
}

int VTI_SCA3000_D01::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int VTI_SCA3000_D01::GetAccelerationSensorData(vector<double> &accelerationSensorData)
{
	unsigned char rcvData[VTI_DATA_SAMPLE*50] = {0,};
	int readByte = 0;

	if(RequestData(VTI_DATA_SAMPLE)>0) 
	{
		OprosSleep(17);
		readByte = ReceivePacket(rcvData, sizeof(rcvData));

		if(readByte<=0)		return API_ERROR;
		else {
			vector<double> data;
			if(DecodePacket(rcvData, readByte, data)) {
				accelerationSensorData.resize(3);
				accelerationSensorData[0] = data[0];
				accelerationSensorData[1] = data[1];
				accelerationSensorData[2] = data[2];
			}
		}
	}
	else {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int VTI_SCA3000_D01::InitializeUART(Property parameter)
{
	Property uartParameter;
	char *error = NULL;

	if(parameter.FindName("UARTAPIName") == false)	goto ERROR_VTI_SCA3000_D01_InitializeUART;
	if(parameter.FindName("PortName") == false)		goto ERROR_VTI_SCA3000_D01_InitializeUART;
	else	uartParameter.SetValue("PortName", parameter.GetValue("PortName"));
	if(parameter.FindName("TimeOut") == false)		goto ERROR_VTI_SCA3000_D01_InitializeUART;
	else	uartParameter.SetValue("TimeOut", parameter.GetValue("TimeOut"));
	if(parameter.FindName("BaudRate") == false)		goto ERROR_VTI_SCA3000_D01_InitializeUART;
	else	uartParameter.SetValue("BaudRate", parameter.GetValue("BaudRate"));
	if(parameter.FindName("DataBits") == false)		goto ERROR_VTI_SCA3000_D01_InitializeUART;
	else	uartParameter.SetValue("DataBits", parameter.GetValue("DataBits"));
	if(parameter.FindName("StopBits") == false)		goto ERROR_VTI_SCA3000_D01_InitializeUART;
	else	uartParameter.SetValue("StopBits", parameter.GetValue("StopBits"));
	if(parameter.FindName("Parity") == false)		goto ERROR_VTI_SCA3000_D01_InitializeUART;
	else	uartParameter.SetValue("Parity", parameter.GetValue("Parity"));
	if(parameter.FindName("FlowControl") == false)	goto ERROR_VTI_SCA3000_D01_InitializeUART;
	else	uartParameter.SetValue("FlowControl", parameter.GetValue("FlowControl"));

	if(_uart != NULL) {
		delete _uart;
		_uart = NULL;
	}
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("UARTAPIName").c_str());
	if(hOprosAPI == NULL) {
		return API_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return API_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("UARTAPIName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		return API_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	error = dlerror();
	if(error != NULL) {
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return API_ERROR;
	}
#endif

	_uart = (UART *)getOprosAPI();
	if(_uart == NULL) {
		Finalize();
		return API_ERROR;
	}

	//	API 초기화
	if(_uart->Initialize(uartParameter) < 0) {
		Finalize();
		return API_ERROR;
	}

	if(_uart->Enable() < 0) {
		Finalize();
		return API_ERROR;
	}

	return API_SUCCESS;

ERROR_VTI_SCA3000_D01_InitializeUART :
	PrintMessage("ERROR : VTI_SCA3000_D01::InitializeUART() -> Can't find a property in parameter.\n");
	return API_ERROR;
}

void VTI_SCA3000_D01::Initialize()
{
	//X-Y-Z순서
	unsigned char data[] = 
		"*29A#*21,3axis,SENDSTR,@;spi,8,0x14,16,0xffff;send,hex,r0,16;spi,8,0x1C,16,0xffff;send,hex,r0,16;spi,8,0x24,16,0xffff;send,hex,r0,16;#*20#*22,3axis#";
	_uart->Write(data, sizeof(data));
}

int VTI_SCA3000_D01::RequestData(int nSample)
{
	unsigned char sendData[16];
	int nSend = sprintf((char *)sendData, "*10,c%d#",nSample);

	return _uart->Write(sendData, nSend);
}

int VTI_SCA3000_D01::ReceivePacket(unsigned char *rcvBufferdata, int rcvBufferdataSize)
{
	int readByte = _uart->Read(rcvBufferdata, rcvBufferdataSize);
	
	if(readByte>0) return readByte;
	else return 0;
}

bool VTI_SCA3000_D01::DecodePacket(unsigned char *data, int dataSize, vector<double> &convData)
{
	if(dataSize<(VTI_DATA_SAMPLE*24+10)) 
	{
		PrintMessage("ERROR : VTI_SCA3000_D01::decodePacket() -> VTI Sensor receive error occurred!(size:%d)",dataSize);
		return false;
	}

	string str = (char*)data;
	vector<double> accelvector;
	vector<double> averageaccel;
	unsigned int index = 0;
	typedef tokenizer< char_separator<char> > datatokenizer;
	char_separator<char> sep(" @,DONE");
	datatokenizer token(str, sep);

	accelvector.resize(0);
	averageaccel.resize(3);

	//수신된 데이터를 모두 잘라서 변환
	for(datatokenizer::iterator itr = token.begin();itr!=token.end();++itr)
	{
		double tmp_accel = 0.;	//가속도(m/s^2)변환 데이터
		string in = itr->c_str();

		if(in.size()>=6)
		{
			long tmp = strtol(in.c_str(), NULL, 16);
			if(tmp>=32768)		tmp = -(65536-tmp);
			tmp_accel = ((double)tmp/8/VTI_SENSITIVITY)*GRAVITY_ACCEL;
			accelvector.push_back(tmp_accel);
			index++;

			if(index>2) index=0;
		}
	}

	//sampling된 data의 average
	if(accelvector.size()==3*VTI_DATA_SAMPLE)
	{
		double sumx=0, sumy=0, sumz=0;

		for(unsigned int i=0;i<accelvector.size();i+=3)
		{
			sumx += accelvector[i];
			sumy += accelvector[i+1];
			sumz += accelvector[i+2];
		}
		averageaccel[0] = sumx/VTI_DATA_SAMPLE - _offset[0];
		averageaccel[1] = sumy/VTI_DATA_SAMPLE - _offset[1];
		averageaccel[2] = sumz/VTI_DATA_SAMPLE - _offset[2];

	}
	else return false;

	//calibration
	if(!_isCalibrated)
	{
		_offset[0] = averageaccel[0];
		_offset[1] = averageaccel[1];
		_offset[2] = 0;
		_isCalibrated = true;
		return false;
	}

	convData = averageaccel;

	return true;
}

#if !defined(DEVICE_TEST)
#if defined(WIN32)
extern "C"
{
__declspec(dllexport) OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new VTI_SCA3000_D01();
}
#endif
#endif
