#include "Ascen_GPS620.h"
#include "OprosPrintMessage.h"

#if defined(WIN32)
#pragma warning(disable : 4996)
#endif

Ascen_GPS620::Ascen_GPS620(void)
{
	hOprosAPI = NULL;
	uart = NULL;
}

Ascen_GPS620::~Ascen_GPS620(void)
{
	if(uart != NULL) {
		delete uart;
	}
}

int Ascen_GPS620::Initialize(Property parameter)
{
	if(InitializeUART(parameter) != API_SUCCESS) {
		PrintMessage("SUCCESS : Ascen_GPS620::Initialize() -> Fail to initialize UART.\n");
		return API_ERROR;
	}

	if( SetParameter(parameter) == API_ERROR ) {
		PrintMessage("SUCCESS : Ascen_GPS620::Initialize() -> Fail to SetParameter.\n");
		return API_ERROR;
	}
	return API_SUCCESS;
}

int Ascen_GPS620::Enable(void)
{
	return API_SUCCESS;
}

int Ascen_GPS620::Disable(void)
{
	return API_SUCCESS;
}

int Ascen_GPS620::Finalize(void)
{
	FinalizeUART();

	return API_SUCCESS;
}

int Ascen_GPS620::SetParameter(Property parameter)
{
	this->parameter = parameter;

	return API_SUCCESS;
}

int Ascen_GPS620::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int Ascen_GPS620::GetGPSData(GPSData &gpsData)
{
	int len = 256;
	BYTE buff[256];
	char time[256];

	if( uart ) {
		uart->Lock();
		int readSize = uart->Read(buff, len);
		uart->Unlock();
		if (0 < readSize && readSize < 256) {
			_nmeaParser.ParseBuffer (buff, readSize);

			gpsData.latitude = _nmeaParser.m_dGGALatitude;
			gpsData.longitude = _nmeaParser.m_dGGALongitude;
			sprintf(time, "%02d:%02d:%02d",
				_nmeaParser.m_btGGAHour,
				_nmeaParser.m_btGGAMinute,
				_nmeaParser.m_btGGASecond);
			gpsData.time = time;
			gpsData.velocity = 0.0;

			return API_SUCCESS;
		}
		else {
			PrintMessage("ERROR:Ascen_GPS620::GetGPSData() -> Can't get GPS data.\n");
		}
	}
	else {
		PrintMessage("ERROR:Ascen_GPS620::GetGPSData() -> Can't use uart port.\n");
	}
	return API_ERROR;
}

int Ascen_GPS620::InitializeUART(Property parameter)
{
	Property uartParameter;

	if(parameter.FindName("UARTAPIName") == false)	return API_ERROR;
	if(parameter.FindName("PortName") == false)		return API_ERROR;	uartParameter.SetValue("PortName", parameter.GetValue("PortName"));
	if(parameter.FindName("TimeOut") == false)		return API_ERROR;	uartParameter.SetValue("TimeOut", parameter.GetValue("TimeOut"));
	if(parameter.FindName("BaudRate") == false)		return API_ERROR;	uartParameter.SetValue("BaudRate", parameter.GetValue("BaudRate"));
	if(parameter.FindName("DataBits") == false)		return API_ERROR;	uartParameter.SetValue("DataBits", parameter.GetValue("DataBits"));
	if(parameter.FindName("StopBits") == false)		return API_ERROR;	uartParameter.SetValue("StopBits", parameter.GetValue("StopBits"));
	if(parameter.FindName("Parity") == false)		return API_ERROR;	uartParameter.SetValue("Parity", parameter.GetValue("Parity"));
	if(parameter.FindName("FlowControl") == false)	return API_ERROR;	uartParameter.SetValue("FlowControl", parameter.GetValue("FlowControl"));

	if(uart != NULL) {
		delete uart;
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
		PrintMessage("ERROR : InitializeUART() -> dlopen (%s)\n",parameter.GetValue("UARTAPIName").c_str());
		return API_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage ("ERROR -> %s\n", error);
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return API_ERROR;
	}
#endif

	uart = (UART *)getOprosAPI();
	if(uart == NULL) {
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return API_ERROR;
	}

	//	API 초기화
	if(uart->Initialize(uartParameter) < 0) {
		FinalizeUART();
		return API_ERROR;
	}

	if(uart->Enable() < 0) {
		FinalizeUART();
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Ascen_GPS620::FinalizeUART(void)
{
	if(uart != NULL) {
		uart->Disable();
		uart->Finalize();
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

#if defined(WIN32)
extern "C"
{
__declspec(dllexport) OprosApi *GetAPI();
__declspec(dllexport) void ReleaseAPI(OprosApi *api);
}

OprosApi *GetAPI()
{
	return new Ascen_GPS620();
}

void ReleaseAPI(OprosApi *api)
{
	delete api;
}
#endif
