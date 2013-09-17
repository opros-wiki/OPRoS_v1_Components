#include <string.h>
#include "MicroInfinity_A3350M.h"

#include "OprosTimer.h"
#include "OprosPrintMessage.h"

#define	A3350M_PACKET_SIZE	(42)
#define	A3350M_RETRY_COUNT	(3)
#define	A3350M_DELAY		(30)

MicroInfinity_A3350M::MicroInfinity_A3350M(void)
{
	_uart = NULL;
}

MicroInfinity_A3350M::~MicroInfinity_A3350M(void)
{
	Finalize();
}

int MicroInfinity_A3350M::Initialize(Property parameter)
{
	if(InitializeUART(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : MicroInfinity_A3350M::Initialize() -> Occur a error in InitializeUART().\n");
		return API_ERROR;
	}

	if(SetParameter(parameter) != API_SUCCESS) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int MicroInfinity_A3350M::Finalize(void)
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

int MicroInfinity_A3350M::Enable(void)
{
	return API_SUCCESS;
}

int MicroInfinity_A3350M::Disable(void)
{
	return API_SUCCESS;
}

int MicroInfinity_A3350M::SetParameter(Property parameter)
{
	if(parameter.FindName("Size") == false)				return API_ERROR;
	int size = atoi(parameter.GetValue("Size").c_str());

	if(size < 0) {
		return API_ERROR;
	}

	char name[128];
	for(int i = 0; i < size; i++) {
		sprintf(name, "X%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_MicroInfinity_A3350M_SetParameter;
		
		sprintf(name, "Y%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_MicroInfinity_A3350M_SetParameter;
		
		sprintf(name, "Z%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_MicroInfinity_A3350M_SetParameter;
		
		sprintf(name, "Roll%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_MicroInfinity_A3350M_SetParameter;
		
		sprintf(name, "Pitch%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_MicroInfinity_A3350M_SetParameter;
		
		sprintf(name, "Yaw%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_MicroInfinity_A3350M_SetParameter;
	}

	this->parameter = parameter;

	return API_SUCCESS;

ERROR_MicroInfinity_A3350M_SetParameter :
	PrintMessage("ERROR : MicroInfinity_A3350M::SetParameter -> Can't find a property in parameter.\n");
	return API_ERROR;
}

int MicroInfinity_A3350M::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int MicroInfinity_A3350M::GetInertiaMeasurementUnitData(vector<ObjectPosture> &inertiaMeasurementUnitData)
{
	vector<double> data(9);
	if(A3350_GetValue(&data) < 0) {
		inertiaMeasurementUnitData.clear();
		
		return API_ERROR;
	}
	else {
		inertiaMeasurementUnitData.resize(1);

		inertiaMeasurementUnitData[0].pRate = data[0];
		inertiaMeasurementUnitData[0].qRate = data[1];
		inertiaMeasurementUnitData[0].rRate = data[2];
		inertiaMeasurementUnitData[0].xAcceleration = data[3];
		inertiaMeasurementUnitData[0].yAcceleration = data[4];
		inertiaMeasurementUnitData[0].zAcceleration = data[5];
		inertiaMeasurementUnitData[0].roll = data[6];
		inertiaMeasurementUnitData[0].pitch = data[7];
		inertiaMeasurementUnitData[0].yaw = data[8];
	}
	

	return API_SUCCESS;
}

int MicroInfinity_A3350M::InitializeUART(Property parameter)
{
	Property uartParameter;
	char *error = NULL;

	if(parameter.FindName("UARTAPIName") == false)	goto ERROR_MicroInfinity_A3350M_InitializeUART;
	if(parameter.FindName("PortName") == false)		goto ERROR_MicroInfinity_A3350M_InitializeUART;
	else	uartParameter.SetValue("PortName", parameter.GetValue("PortName"));
	if(parameter.FindName("TimeOut") == false)		goto ERROR_MicroInfinity_A3350M_InitializeUART;
	else	uartParameter.SetValue("TimeOut", parameter.GetValue("TimeOut"));
	if(parameter.FindName("BaudRate") == false)		goto ERROR_MicroInfinity_A3350M_InitializeUART;
	else	uartParameter.SetValue("BaudRate", parameter.GetValue("BaudRate"));
	if(parameter.FindName("DataBits") == false)		goto ERROR_MicroInfinity_A3350M_InitializeUART;
	else	uartParameter.SetValue("DataBits", parameter.GetValue("DataBits"));
	if(parameter.FindName("StopBits") == false)		goto ERROR_MicroInfinity_A3350M_InitializeUART;
	else	uartParameter.SetValue("StopBits", parameter.GetValue("StopBits"));
	if(parameter.FindName("Parity") == false)		goto ERROR_MicroInfinity_A3350M_InitializeUART;
	else	uartParameter.SetValue("Parity", parameter.GetValue("Parity"));
	if(parameter.FindName("FlowControl") == false)	goto ERROR_MicroInfinity_A3350M_InitializeUART;
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

ERROR_MicroInfinity_A3350M_InitializeUART :
	PrintMessage("ERROR : MicroInfinity_A3350M::InitializeUART() -> Can't find a property in parameter.\n");
	return API_ERROR;
}

int MicroInfinity_A3350M::A3350_RecvPacket(vector<unsigned char> *data)
{
	if(_uart == NULL || data == NULL) {
		return -1;
	}

	if(data->size() < A3350M_PACKET_SIZE) {
		data->resize(A3350M_PACKET_SIZE);
	}

	OprosTimer timer;
	unsigned char *buf = &(*data)[0];
	int ret;
	int index = 0;
	timer.StartTimeTick();

	//	헤더를 찾음
	while(1) {
		ret = _uart->Read(&buf[index], 1);
		if(ret < 0) {
			return -1;
		}
		if(ret == 1) {
			if(index == 0) {
				if(buf[index] == 0xFF) {
					index++;
				}
			}
			else if(index == 1) {
				if(buf[index] == 0xFF) {
					break;
				}
				else {
					return -1;
				}
			}
		}

		if(timer.GetTimeTick() > A3350M_DELAY) {
			return false;
		}
	}
	
	//	나머지 40바이트의 데이터를 받음
	for(; index < A3350M_PACKET_SIZE; index += ret) {
		ret = _uart->Read(&buf[index], A3350M_PACKET_SIZE - index);
		if(ret < 0) {
			return -1;
		}
		else if(ret == 0) {
			if(timer.GetTimeTick() > A3350M_DELAY) {
				return -1;
			}
		}
	}

	return 0;
}

int MicroInfinity_A3350M::A3350_ParsingData(vector<unsigned char> data, vector<double> *value)
{
	unsigned long checkSum = 0;
	unsigned long lTmp;

	if(data.size() != A3350M_PACKET_SIZE) {
		return -1;
	}

	if(value->size() < 9) {
		value->resize(9);
	}
	
	for(int i = 0; i < 9; i++) {
		memcpy((unsigned char *)&lTmp, (unsigned char *)&data[i * 4 + 2], 4);
		checkSum ^= lTmp;
	}
	
	unsigned long cs;
	memcpy((unsigned char *)&cs, (unsigned char *)&data[38], 4);

	if (cs != checkSum) {
		return -1;
	}
	else{
		float fTmp;
		for(int i = 0; i < 9; i++) {
			memcpy(&fTmp, &data[i * 4], 4);
			(*value)[i] = (double)fTmp;
		}
	}

	return 0;
}

int MicroInfinity_A3350M::A3350_GetValue(vector<double> *value)
{
	vector<unsigned char> data(A3350M_PACKET_SIZE);

	if(A3350_RecvPacket(&data) == -1) {
		return -1;
	}

	if(A3350_ParsingData(data, value) == -1) {
		return -1;
	}

	return 0;
}