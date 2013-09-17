#include "BaumerElectric_BMMH.h"
#include "OprosPrintMessage.h"

#define	BMMH_ERROR				0x1001
#define	BMMH_STORE_PARAMS		0x1010
	#define	BMMH_ALL_PARAMS			0x01
	#define	BMMH_COMM_PARAMS		0x02
	#define	BMMH_APP_PARAMS			0x03
	#define	BMMH_MANUF_PARAMS		0x04
#define	BMMH_SET_POSITION		0x6003
#define	BMMH_GET_POSITION		0x6004

BaumerElectric_BMMH::BaumerElectric_BMMH(void)
{
	can = NULL;
	canOpen = NULL;
	hOprosAPI = NULL;
}

BaumerElectric_BMMH::~BaumerElectric_BMMH(void)
{
	Finalize();
}

int BaumerElectric_BMMH::Initialize(Property parameter)
{
	if(InitializeCAN(parameter) < 0) {
		PrintMessage("ERROR : BaumerElectric_BMMH::Initialize() -> Occur a error in InitializeCAN().\n");
		return API_ERROR;
	}
	canOpen = new CANOpen(can);

	if(SetParameter(parameter) < 0) {
		Finalize();
		return API_ERROR;
	}

	return API_SUCCESS;
}

int BaumerElectric_BMMH::Finalize(void)
{
	_profile.clear();

	if(canOpen != NULL) {
		delete canOpen;
		canOpen = NULL;
	}

	if(can != NULL) {
		delete can;
		can = NULL;
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

int BaumerElectric_BMMH::Enable(void)
{
	if(_profile.size() == 0) {
		return API_ERROR;
	}

	for(size_t i = 0; i < _profile.size(); i++) {
		unsigned char error;

		if(BMMH_GetError(_profile[i].id, &error) < 0) {
			return API_ERROR;
		}

		if(error != 0x00) {
			return API_ERROR;
		}
	}

	return API_SUCCESS;
}

int BaumerElectric_BMMH::Disable(void)
{
	if(_profile.size() == 0) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int BaumerElectric_BMMH::SetParameter(Property parameter)
{
	if(parameter.FindName("Size") == false)				return API_ERROR;
	int size = atoi(parameter.GetValue("Size").c_str());

	if(size < 0) {
		return API_ERROR;
	}

	_profile.resize(size);

	char name[128];
	for(int i = 0; i < size; i++) {
		sprintf(name, "ID%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_BaumerElectric_BMMH_SetParameter;
		_profile[i].id = atol(parameter.GetValue(name).c_str());
		
		sprintf(name, "LinePerRevolution%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_BaumerElectric_BMMH_SetParameter;
		_profile[i].linePerRevolution = atof(parameter.GetValue(name).c_str());
		
		sprintf(name, "ReductionRatio%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_BaumerElectric_BMMH_SetParameter;
		_profile[i].reductionRatio = atof(parameter.GetValue(name).c_str());
	}

	this->parameter = parameter;

	return API_SUCCESS;

ERROR_BaumerElectric_BMMH_SetParameter :
	PrintMessage("ERROR : BaumerElectric_BMMH::SetParameter -> Can't find a property in parameter.\n");
	return API_ERROR;

	return API_SUCCESS;
}

int BaumerElectric_BMMH::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int BaumerElectric_BMMH::GetEncoderData(vector<double> &encoderData)
{
	encoderData.clear();

	for(size_t i = 0; i < _profile.size(); i++) {
		long position;

		if(BMMH_GetPosition(_profile[i].id, &position) < 0) {
			return API_ERROR;
		}

		encoderData.push_back((double)(position) * 360.0 / (_profile[i].linePerRevolution * _profile[i].reductionRatio));
	}

	return API_SUCCESS;
}

int BaumerElectric_BMMH::InitializeCAN(Property parameter)
{
	char *error = NULL;

	//	CAN API 초기화
	if(parameter.FindName("CANAPIName") == false) {
		return API_ERROR;
	}

	Property canParameter;
	if(parameter.FindName("TimeOut") == false)				return API_ERROR;
	canParameter.SetValue("TimeOut", parameter.GetValue("TimeOut"));

	if(parameter.FindName("Channel") == false)				return API_ERROR;
	canParameter.SetValue("Channel", parameter.GetValue("Channel"));
	
	if(parameter.FindName("BitRate") == false)				return API_ERROR;
	canParameter.SetValue("BitRate", parameter.GetValue("BitRate"));

	if(parameter.FindName("AcceptanceMask") == false)		return API_ERROR;
	canParameter.SetValue("AcceptanceMask", parameter.GetValue("AcceptanceMask"));

	if(parameter.FindName("AcceptanceCode") == false)		return API_ERROR;
	canParameter.SetValue("AcceptanceCode", parameter.GetValue("AcceptanceCode"));

	if(parameter.FindName("Mode") == false)				return API_ERROR;
	canParameter.SetValue("Mode", parameter.GetValue("Mode"));

	if(can != NULL) {
		delete can;
		can = NULL;
	}
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("CANAPIName").c_str());
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
	hOprosAPI = dlopen(parameter.GetValue("CANAPIName").c_str(), RTLD_LAZY);
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

	can = (CAN *)getOprosAPI();
	if(can == NULL) {
		Finalize();
		return API_ERROR;
	}

	//	API 초기화
	if(can->Initialize(canParameter) < 0) {
		Finalize();
		return API_ERROR;
	}

	if(can->Enable() < 0) {
		Finalize();
		return API_ERROR;
	}

	return API_SUCCESS;
}

int BaumerElectric_BMMH::BMMH_GetError(long id, unsigned char *error)
{
	if(canOpen == NULL) {
		return -1;
	}

	return canOpen->ReadObject(id, BMMH_ERROR, 0x00, error);
}

int BaumerElectric_BMMH::BMMH_SetPosition(long id, long position)
{
	if(canOpen == NULL) {
		return -1;
	}

	return canOpen->WriteObject(id, BMMH_SET_POSITION, 0x00, position);
}

int BaumerElectric_BMMH::BMMH_GetPosition(long id, long *position)
{
	if(canOpen == NULL) {
		return -1;
	}

	if(canOpen->ReadObject(id, BMMH_GET_POSITION, 0x00, (unsigned long *)position) < 0) {
		return -1;
	}
	*position = (*position << 2) >> 2;

	return 0;
}

int BaumerElectric_BMMH::BMMH_SaveToEEPROM(long id)
{
	if(canOpen == NULL) {
		return -1;
	}

	if(canOpen->WriteObject(id, BMMH_STORE_PARAMS, BMMH_APP_PARAMS, (unsigned long)0x65766173) < 0) {
		return -1;
	}
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
	return new BaumerElectric_BMMH();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new BaumerElectric_BMMH();
}

#endif
#endif