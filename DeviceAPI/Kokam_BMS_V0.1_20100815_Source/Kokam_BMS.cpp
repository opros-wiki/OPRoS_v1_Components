#include "Kokam_BMS.h"
#include "OprosPrintMessage.h"
#include "OprosTimer.h"

using namespace boost::posix_time;

// Data range
// Cell Voltage      :	0 ~5000 mV
// Cell Temperature  :	0 ~ 90 C
// Cell SOC          :	0 ~ 100 %
// Discharge current :	0 ~ 450 A

#define BMS_TRANSACTION_DELAY		20
#define BMS_TRANSACTION_TIMEOUT		1000

#define LF		0x0A
#define CR		0x0D

Kokam_BMS::Kokam_BMS(void)
{
	uart = NULL;
	pThread = NULL;
	threadOn = false;

	minimumVoltageLimit = 0.0;
	maximumVoltageLimit = 0.0;
	minimumCellVoltageLimit = 0.0;
	maximumCellVoltageLimit = 0.0;
}

Kokam_BMS::~Kokam_BMS(void)
{
	Finalize();
}

int Kokam_BMS::Initialize(Property parameter)
{
	cellsVoltage.clear();

	if(InitializeUART(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : Kokam_BMS::Initialize() -> Occur a error in InitializeUART().\n");
		return API_ERROR;
	}

	if(SetParameter(parameter) != API_SUCCESS) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Kokam_BMS::Finalize(void)
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

int Kokam_BMS::Enable(void)
{
	if((threadOn == false) && (pThread == NULL)) {
		pThread = new boost::thread(boost::bind(&Kokam_BMS::ThreadFunc, this));
		threadOn = true;
	}
	else {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Kokam_BMS::Disable(void)
{
	if((threadOn == true) && pThread) {
		threadOn = false;
		pThread->join();
		delete pThread;
		pThread = NULL;
	}
	else {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Kokam_BMS::SetParameter(Property parameter)
{
	if(parameter.FindName("CellCount") == false) {
		PrintMessage("ERROR : Kokam_BMS::SetParameter() -> Can't find a CellCount in parameter.\n");
		return API_ERROR;
	}
	cellsVoltage.resize(atoi(parameter.GetValue("CellCount").c_str()));

	if(parameter.FindName("MinimumVoltageLimit") == false) {
		PrintMessage("ERROR : Kokam_BMS::SetParameter() -> Can't find a MinimumVoltageLimit in parameter.\n");
		return API_ERROR;
	}
	minimumVoltageLimit = atof(parameter.GetValue("MinimumVoltageLimit").c_str());

	if(parameter.FindName("MaximumVoltageLimit") == false) {
		PrintMessage("ERROR : Kokam_BMS::SetParameter() -> Can't find a MaximumVoltageLimit in parameter.\n");
		return API_ERROR;
	}
	maximumVoltageLimit = atof(parameter.GetValue("MaximumVoltageLimit").c_str());

	if(parameter.FindName("MinimumCellVoltageLimit") == false) {
		PrintMessage("ERROR : Kokam_BMS::SetParameter() -> Can't find a MinimumCellVoltageLimit in parameter.\n");
		return API_ERROR;
	}
	minimumCellVoltageLimit = atof(parameter.GetValue("MinimumCellVoltageLimit").c_str());

	if(parameter.FindName("MaximumCellVoltageLimit") == false) {
		PrintMessage("ERROR : Kokam_BMS::SetParameter() -> Can't find a MaximumCellVoltageLimit in parameter.\n");
		return API_ERROR;
	}
	maximumCellVoltageLimit = atof(parameter.GetValue("MaximumCellVoltageLimit").c_str());

	return API_SUCCESS;
}

int Kokam_BMS::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int Kokam_BMS::GetBatteryVoltage(double &batteryVoltage)
{
	lock.Lock();

	batteryVoltage = 0.0;
	for(size_t i = 0; i < cellsVoltage.size(); i++) {
		batteryVoltage += cellsVoltage[i];
	}

	lock.Unlock();

	return API_SUCCESS;
}

int Kokam_BMS::GetCellVoltage(vector<double> &cellVoltage)
{
	lock.Lock();

	cellVoltage = cellsVoltage;

	lock.Unlock();

	return API_SUCCESS;
}

void Kokam_BMS::ThreadFunc()
{
	int index = 0;

	while(threadOn) {
		//	시작 시간
		ptime beginTime(microsec_clock::local_time());

		// 실행
		double rawData[3];

		int ret = GetRawValue(index, rawData);
		lock.Lock();
		if(ret > 0) {
			cellsVoltage[index] = rawData[0] / 1000.0;	//	Voltage;
			//cellsTmperature[index] = rawData[1]] / 1000.0;	//	Temperature
			if(++index >= (int)cellsVoltage.size()) {
				index = 0;
			}
		}
		lock.Unlock();

		// 완료 시간
		ptime endTime(microsec_clock::local_time());

		// 실행시간을 계산해서 sleep할 시간을 계산한다.
		time_period elapsedTime(beginTime, endTime);	// 경과 시간
		long elapsedMicrosec = (long)elapsedTime.length().total_microseconds();  // elapsed micro sec
		long sleepTime = (long)(BMS_TRANSACTION_TIMEOUT * 1000) - elapsedMicrosec;

		// 주기를 over해서 실행한 경우로써 warning을 report해야함.
		if(sleepTime < 0) {
		}
		else {
			boost::posix_time::microsec sleepBoostTime(sleepTime); // sleep 시간 설정 (microsec)
			boost::this_thread::sleep<boost::posix_time::microsec>(sleepBoostTime);
		}
	}
}

int Kokam_BMS::InitializeUART(Property parameter)
{
	Property uartParameter;
	char *error = NULL;

	if(parameter.FindName("UARTAPIName") == false)	goto ERROR_Kokam_BMS_InitializeUART;
	if(parameter.FindName("PortName") == false)		goto ERROR_Kokam_BMS_InitializeUART;
	else	uartParameter.SetValue("PortName", parameter.GetValue("PortName"));
	if(parameter.FindName("TimeOut") == false)		goto ERROR_Kokam_BMS_InitializeUART;
	else	uartParameter.SetValue("TimeOut", parameter.GetValue("TimeOut"));
	if(parameter.FindName("BaudRate") == false)		goto ERROR_Kokam_BMS_InitializeUART;
	else	uartParameter.SetValue("BaudRate", parameter.GetValue("BaudRate"));
	if(parameter.FindName("DataBits") == false)		goto ERROR_Kokam_BMS_InitializeUART;
	else	uartParameter.SetValue("DataBits", parameter.GetValue("DataBits"));
	if(parameter.FindName("StopBits") == false)		goto ERROR_Kokam_BMS_InitializeUART;
	else	uartParameter.SetValue("StopBits", parameter.GetValue("StopBits"));
	if(parameter.FindName("Parity") == false)		goto ERROR_Kokam_BMS_InitializeUART;
	else	uartParameter.SetValue("Parity", parameter.GetValue("Parity"));
	if(parameter.FindName("FlowControl") == false)	goto ERROR_Kokam_BMS_InitializeUART;
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

ERROR_Kokam_BMS_InitializeUART :
	PrintMessage("ERROR : Kokam_BMS::InitializeUART() -> Can't find a property in parameter.\n");
	return API_ERROR;
}

unsigned char Kokam_BMS::ChkSum (unsigned char *pBuff, int size)
{
	unsigned char ChkSum = 0;

	for (int i=0; i<size; ++i) {
		ChkSum += pBuff[i];
	}
	return ChkSum^0xFF;
}

int Kokam_BMS::recv_packet (unsigned char *rbuff, int len)
{
	int recv_bytes = 0;
	unsigned char *recv_p = rbuff;
	OprosTimer timer;
	timer.StartTimeTick();

	if(uart == NULL) {
		return -1;
	}

	while (0 < len) {
		int n = uart->Read (recv_p, len);
		if (0 < n) {
			recv_p += n;
			len -= n;
			recv_bytes += n;
		}
		else if (n < 0) {
			return -1;
		}
		else {
			OprosSleep (1);
		}
		
		if (timer.GetTimeTick() > BMS_TRANSACTION_TIMEOUT) {
			break;
		}
	}

	return recv_bytes;
}

int Kokam_BMS::FourAscii2Int (unsigned char *ascii)
{
	return (ascii[0] - '0') * 1000 + 
		(ascii[1] - '0') * 100 + 
		(ascii[2] - '0') * 10 + 
		(ascii[3] - '0') * 1 ;
}

int Kokam_BMS::GetRawValue (int cell, double *measure)
{
	assert (0 <= cell);

	if(uart == NULL) {
		return -1;
	}

	uart->Lock();

	unsigned char sbuff[16] = { 0x02,	0x32,	'0',	'0',	'0' + cell,		0,	0x03 };
	sbuff[5] = ChkSum (sbuff, 5);
	uart->Write(sbuff, 7);

	OprosSleep(BMS_TRANSACTION_DELAY);

	unsigned char rbuff[16] = {0,};
	int n = uart->Read(rbuff, 15);
	if (0 < n) {
		if (n == 15 && 
			rbuff[0] == (unsigned char)0x02 && 
			rbuff[13]== ChkSum (rbuff, 13) &&
			rbuff[14]== (unsigned char)0x03 ){ 
															// cell 0 ~ 5			, 6
			measure[0] = (double)FourAscii2Int(&rbuff[1]);	// cell voltage			, charge current
			measure[1] = (double)FourAscii2Int(&rbuff[5]);	// cell temperature		, discharge current
			measure[2] = (double)FourAscii2Int(&rbuff[9]);	// cell SOC				, reserved
			uart->Unlock();
			return n;
		}
		else {
			uart->Unlock();
			return 0;
		}
	}
	else {
		uart->Unlock();
		return -1;
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
	return new Kokam_BMS();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new Kokam_BMS();
}

#endif
#endif