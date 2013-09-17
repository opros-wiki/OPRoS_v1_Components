#include "DasaRobot_MobilityUltrasonic.h"
#include "OprosPrintMessage.h"
#include "OprosTimer.h"

// Protocol Packet
#define STX				0x05
#define ETX             0x03
#define ACK             0x06
#define NAK             0x15
#define RST             0x12

#define	FLAG_OK			0x30 // Processing Success
#define	FLAG_ERROR		0x31 // Protocol Error
#define FLAG_FAIL		0x32 // Processing Fail
#define	FLAG_NO			0x33 // No Processing
#define	FLAG_END		0x34 // End of Packet
#define	FLAG_PASS		0x35 // Pass through

#define READ_MODE	'U'
#define	WRITE_MODE	'u'

#define	SENSOR1		'1'
#define	SENSOR2		'2'
#define	SENSOR3		'3'
#define	SENSOR4		'4'
#define	SENSOR5		'5'
#define	SENSOR6		'6'
#define	SENSOR7		'7'
#define	SENSOR8		'8'
#define	SENSOR_ALL	'A'

#define	SIMUL		'A'
#define	SEQUEN		'a'
#define	CONT		'u'
#define	STOP		'U'

#define	DASA_ROBOT_ULTRASONIC_SINGLE_MODE	(0)
#define	DASA_ROBOT_ULTRASONIC_MULTI_MODE	(1)
#define	DASA_ROBOT_ULTRASONIC_CONT_MODE		(2)
#define	DASA_ROBOT_ULTRASONIC_STOP_MODE		(3)

#define	MAX_PACK_SIZE					(255)
#define	DASA_ROBOT_ULTRASONIC_DELAY		(100)	//	단위 : ms

#define	DASA_ROBOT_ULTRASONIC_SENSOR_COUNT	8

DasaRobot_MobilityUltrasonic::DasaRobot_MobilityUltrasonic(void)
{
	hOprosAPI = NULL;
	uart = NULL;
}

DasaRobot_MobilityUltrasonic::~DasaRobot_MobilityUltrasonic(void)
{
	Finalize();
}

int DasaRobot_MobilityUltrasonic::Initialize(Property parameter)
{
	if(InitializeUART(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : DasaRobot_MobilityUltrasonic::Initialize() -> Occur a error in InitializeUART().\n");
		return API_ERROR;
	}

	if(SetParameter(parameter) != API_SUCCESS) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int DasaRobot_MobilityUltrasonic::Finalize(void)
{
	if(uart != NULL) {
		delete uart;
		uart = NULL;
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

int DasaRobot_MobilityUltrasonic::Enable(void)
{
	if(DasaRobot_Ultrasonic_SetMode(DASA_ROBOT_ULTRASONIC_CONT_MODE) < 0) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int DasaRobot_MobilityUltrasonic::Disable(void)
{
	if(DasaRobot_Ultrasonic_SetMode(DASA_ROBOT_ULTRASONIC_STOP_MODE) < 0) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int DasaRobot_MobilityUltrasonic::SetParameter(Property parameter)
{
	if(parameter.FindName("Size") == false)				return API_ERROR;
	int size = atoi(parameter.GetValue("Size").c_str());

	if(size != 8) {
		return API_ERROR;
	}

	char name[128];
	for(int i = 0; i < size; i++) {
		sprintf(name, "X%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_DasaRobot_MobilityUltrasonic_SetParameter;
		
		sprintf(name, "Y%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_DasaRobot_MobilityUltrasonic_SetParameter;
		
		sprintf(name, "Z%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_DasaRobot_MobilityUltrasonic_SetParameter;
		
		sprintf(name, "Roll%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_DasaRobot_MobilityUltrasonic_SetParameter;
		
		sprintf(name, "Pitch%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_DasaRobot_MobilityUltrasonic_SetParameter;
		
		sprintf(name, "Yaw%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_DasaRobot_MobilityUltrasonic_SetParameter;
	}

	this->parameter = parameter;

	return API_SUCCESS;

ERROR_DasaRobot_MobilityUltrasonic_SetParameter :
	PrintMessage("ERROR : DasaRobot_MobilityUltrasonic::SetParameter -> Can't find a property in parameter.\n");
	return API_ERROR;
}

int DasaRobot_MobilityUltrasonic::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int DasaRobot_MobilityUltrasonic::GetUltrasonicSensorData(vector<double> &ultrasonicSensorData)
{
	ultrasonicSensorData.resize(DASA_ROBOT_ULTRASONIC_SENSOR_COUNT);

	if(DasaRobot_Ultrasonic_GetSensorValue(&ultrasonicSensorData[0], DASA_ROBOT_ULTRASONIC_SENSOR_COUNT) < 0) {
		ultrasonicSensorData.clear();
		return API_ERROR;
	}

	return API_SUCCESS;
}

int DasaRobot_MobilityUltrasonic::InitializeUART(Property parameter)
{
	Property uartParameter;
	char *error = NULL;

	if(parameter.FindName("UARTAPIName") == false)	goto ERROR_DasaRobot_MobilityUltrasonic_InitializeUART;
	if(parameter.FindName("PortName") == false)		goto ERROR_DasaRobot_MobilityUltrasonic_InitializeUART;
	else	uartParameter.SetValue("PortName", parameter.GetValue("PortName"));
	if(parameter.FindName("TimeOut") == false)		goto ERROR_DasaRobot_MobilityUltrasonic_InitializeUART;
	else	uartParameter.SetValue("TimeOut", parameter.GetValue("TimeOut"));
	if(parameter.FindName("BaudRate") == false)		goto ERROR_DasaRobot_MobilityUltrasonic_InitializeUART;
	else	uartParameter.SetValue("BaudRate", parameter.GetValue("BaudRate"));
	if(parameter.FindName("DataBits") == false)		goto ERROR_DasaRobot_MobilityUltrasonic_InitializeUART;
	else	uartParameter.SetValue("DataBits", parameter.GetValue("DataBits"));
	if(parameter.FindName("StopBits") == false)		goto ERROR_DasaRobot_MobilityUltrasonic_InitializeUART;
	else	uartParameter.SetValue("StopBits", parameter.GetValue("StopBits"));
	if(parameter.FindName("Parity") == false)		goto ERROR_DasaRobot_MobilityUltrasonic_InitializeUART;
	else	uartParameter.SetValue("Parity", parameter.GetValue("Parity"));
	if(parameter.FindName("FlowControl") == false)	goto ERROR_DasaRobot_MobilityUltrasonic_InitializeUART;
	else	uartParameter.SetValue("FlowControl", parameter.GetValue("FlowControl"));

	if(uart != NULL) {
		delete uart;
		uart = NULL;
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

	uart = (UART *)getOprosAPI();
	if(uart == NULL) {
		Finalize();
		return API_ERROR;
	}

	//	API 초기화
	if(uart->Initialize(uartParameter) < 0) {
		Finalize();
		return API_ERROR;
	}

	if(uart->Enable() < 0) {
		Finalize();
		return API_ERROR;
	}

	return API_SUCCESS;

ERROR_DasaRobot_MobilityUltrasonic_InitializeUART :
	PrintMessage("ERROR : DasaRobot_MobilityUltrasonic::InitializeUART() -> Can't find a property in parameter.\n");
	return API_ERROR;
}

unsigned char DasaRobot_MobilityUltrasonic::DasaRobot_Ultrasonic_MakeLrc(unsigned char data[], int size)
{
	unsigned char tmp = 0;
	int i;

	for(i = 0; i < size; i++)
		tmp ^= data[i];

	return tmp;
}

unsigned long DasaRobot_MobilityUltrasonic::DasaRobot_Ultrasonic_Pow(int i, int j)
{
	unsigned long result = 1;
	int k;

	for(k = 0; k < j; k++)
		result *= i;

	return result;
}

void DasaRobot_MobilityUltrasonic::DasaRobot_Ultrasonic_Str2Int(unsigned char data[], unsigned int distance[])
{
	int i, j, k, index;
	char tmp[10];

	i = j = k = index = 0;
	while(1) {
		if('0' <= data[i] && data[i] <= '9')
			tmp[j++] = data[i];
		else if(data[i] == ';' || data[i] == ETX) {
			for(k = 0; k < j; k++) {
				distance[index] += (tmp[k] - '0') * DasaRobot_Ultrasonic_Pow(10, j - k - 1);
			}
			j = 0;
			index++;
		}
		
		if(data[i] == ETX)
			break;
		i++;
	}
}

int DasaRobot_MobilityUltrasonic::DasaRobot_Ultrasonic_SendPack(unsigned char data[], int size)
{
	int ret;
	OprosTimer timer;
	timer.StartTimeTick();

	if(uart == NULL) {
		return -1;
	}

	if(size <= 0) {
		return 0;
	}
	

	for(int i = 0; i < size; ) {
		ret = uart->Write(&data[i], size - i);
		if(ret < 0) {
			return -1;
		}
		if(ret == 0) {
			if(timer.GetTimeTick() > DASA_ROBOT_ULTRASONIC_DELAY) {
				return -1;
			}
		}
		i += ret;
	}

	return size;
}

int DasaRobot_MobilityUltrasonic::DasaRobot_Ultrasonic_RecvPack(unsigned char data[])
{
	int index;
	int ret;
	OprosTimer timer;
	timer.StartTimeTick();
	
	for(data[0] = 0; data[0] != STX;) {
		ret = uart->Read(data, 1);
		
		if(timer.GetTimeTick() > DASA_ROBOT_ULTRASONIC_DELAY) {
			return -1;
		}
	}
		
	for(index = 1; ;) {
		ret = uart->Read(&data[index], 1);
		
		if(ret == 1) {
			index++;
			if(data[index - 2] == ETX) {
				break;
			}
		}
		else {
			if(timer.GetTimeTick() > DASA_ROBOT_ULTRASONIC_DELAY) {
				return -1;
			}
		}
	}

	if(data[1] != FLAG_OK) {
		return -1;
	}
	else if(data[index - 1] != DasaRobot_Ultrasonic_MakeLrc(&data[1], index - 2)) {
		return -1;
	}
	else
	{
		unsigned char tmp = ACK;
		while(1) {
			ret = uart->Write(&tmp, 1);
			if(ret < 0) {
				return -1;
			}
			else if(ret == 1) {
				return index;
			}
			else {
				if(timer.GetTimeTick() > DASA_ROBOT_ULTRASONIC_DELAY) {
					return -1;
				}
			}
		}
	}

	return -1;
}

int DasaRobot_MobilityUltrasonic::DasaRobot_Ultrasonic_SetMode(int mode)
{
	unsigned char data[MAX_PACK_SIZE] = {STX, 0x00, 0x00, ETX, 0x00};
	
	switch(mode) {
		case DASA_ROBOT_ULTRASONIC_SINGLE_MODE :
			/*
			data[1] = 'U';
			if((m_id < 0) || (m_id > 9)) {
				return -1;
			}
			data[2] = (char)(m_id) + '0';
			*/

			break;
		case DASA_ROBOT_ULTRASONIC_MULTI_MODE :
			data[1] = 'U';
			data[2] = 'A';
			break;
		case DASA_ROBOT_ULTRASONIC_CONT_MODE :
			data[1] = 'u';
			data[2] = 'u';
			break;
		case DASA_ROBOT_ULTRASONIC_STOP_MODE :
			data[1] = 'U';
			data[2] = 'U';
			break;
		default:
			return -1;
	}

	data[4] = DasaRobot_Ultrasonic_MakeLrc(&data[1], 3);

	if(DasaRobot_Ultrasonic_SendPack(data, 5) < 0) {
		return -1;
	}

	if(DasaRobot_Ultrasonic_RecvPack(data) < 0) {
		return -1;
	}

	return 0;
}

int DasaRobot_MobilityUltrasonic::DasaRobot_Ultrasonic_GetSensorValue(double value[], int size)
{
	unsigned int tmp[8], i;
	unsigned char packet_buf[MAX_PACK_SIZE] = {STX, READ_MODE, 'A', ETX};
	
	packet_buf[4] = DasaRobot_Ultrasonic_MakeLrc(&packet_buf[1], 3);
	if(DasaRobot_Ultrasonic_SendPack(packet_buf, 5) < 0) {
		return -1;
	}

	if(DasaRobot_Ultrasonic_RecvPack(packet_buf) < 0) {
		return -1;
	}
	
	memset(tmp, 0, 8*sizeof(unsigned int));
	DasaRobot_Ultrasonic_Str2Int(packet_buf, tmp);
	
	for(i = 0; i < 8; i++)
		value[i] = (double)(tmp[i]) * (double)0.01;
	
	return 0;
}

#if !defined(DEVICE_TEST)
#if defined(WIN32)
extern "C"
{
	__declspec(dllexport) OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new DasaRobot_MobilityUltrasonic();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new DasaRobot_MobilityUltrasonic();
}

#endif
#endif