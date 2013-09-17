#include "Devantech_SRF08.h"
#include "OprosPrintMessage.h"

Devantech_SRF08::Devantech_SRF08(void)
{
	_i2c = NULL;
}

Devantech_SRF08::~Devantech_SRF08(void)
{
	Finalize();
}

int Devantech_SRF08::Initialize(Property parameter)
{
	if(InitializeI2C(parameter) < 0) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Devantech_SRF08::Finalize(void)
{
	if(_i2c != NULL) {
		delete _i2c;
		_i2c = NULL;
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

int Devantech_SRF08::Enable(void)
{
	return API_SUCCESS;
}

int Devantech_SRF08::Disable(void)
{
	return API_SUCCESS;
}

int Devantech_SRF08::SetParameter(Property parameter)
{
	if(parameter.FindName("Size") == false)				return API_ERROR;
	int size = atoi(parameter.GetValue("Size").c_str());

	if(size < 0) {
		return API_ERROR;
	}

	char name[128];
	for(int i = 0; i < size; i++) {
		sprintf(name, "X%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_Devantech_SRF08_SetParameter;
		
		sprintf(name, "Y%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_Devantech_SRF08_SetParameter;
		
		sprintf(name, "Z%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_Devantech_SRF08_SetParameter;
		
		sprintf(name, "Roll%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_Devantech_SRF08_SetParameter;
		
		sprintf(name, "Pitch%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_Devantech_SRF08_SetParameter;
		
		sprintf(name, "Yaw%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_Devantech_SRF08_SetParameter;
	}

	this->parameter = parameter;

	return API_SUCCESS;

ERROR_Devantech_SRF08_SetParameter :
	PrintMessage("ERROR : Devantech_SRF08::SetParameter -> Can't find a property in parameter.\n");
	return API_ERROR;
}

int Devantech_SRF08::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int Devantech_SRF08::GetUltrasonicSensorData(vector<double> &ultrasonicSensorData)
{
	if(_i2c == NULL) {
		return API_ERROR;
	}

	unsigned char buf[4];
	if(_i2c->Read(0xE0, buf, 4) < 0) {
		return API_ERROR;
	}

	int distance;
	distance = buf[2] << 8;
	distance |= buf[3];
	ultrasonicSensorData.resize(1);
	ultrasonicSensorData[0] = (double)distance * 0.01 / 58.0;

	PrintMessage("INFO : Devantech_SRF08::GetUltrasonicSensorData() -> %.3f\n", ultrasonicSensorData[0]);

	buf[0] = 0x52;
	if(_i2c->Write(0xE0, buf, 1) != 1) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Devantech_SRF08::InitializeI2C(Property parameter)
{
	if(parameter.FindName("I2CAPIName") == false)	return API_ERROR;
	
	if(_i2c != NULL) {
		delete _i2c;
		_i2c = NULL;
	}
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("I2CAPIName").c_str());
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
	hOprosAPI = dlopen(parameter.GetValue("I2CAPIName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		return API_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return API_ERROR;
	}
#endif

	_i2c = (I2C *)getOprosAPI();
	if(_i2c == NULL) {
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return API_ERROR;
	}

	//	API 초기화
	if(_i2c->Initialize(parameter) < 0) {
		FinalizeI2C();
		return API_ERROR;
	}

	if(_i2c->Enable() < 0) {
		FinalizeI2C();
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Devantech_SRF08::FinalizeI2C(void)
{
	if(_i2c != NULL) {
		delete _i2c;
		_i2c = NULL;
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

#if !defined(DEVICE_TEST)
#if defined(WIN32)
extern "C"
{
__declspec(dllexport) OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new Devantech_SRF08();
}
#endif
#endif