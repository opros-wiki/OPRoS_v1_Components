#include "Robotis_DynamixelCAN.h"
#include "OprosPrintMessage.h"

#define	OFFSET_ANGLE	150.0

Robotis_DynamixelCAN::Robotis_DynamixelCAN(void)
{
	dynamixel = NULL;
	can = NULL;
	hOprosAPI = NULL;
}

Robotis_DynamixelCAN::~Robotis_DynamixelCAN(void)
{
	Finalize();
}

int Robotis_DynamixelCAN::Initialize(Property parameter)
{
	if(InitializeCAN(parameter) < 0) {
		PrintMessage("ERROR : Robotis_DynamixelCAN::Initialize() -> Occur a error in InitializeCAN().\n");
		return API_ERROR;
	}

	if(SetParameter(parameter) < 0) {
		Finalize();
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Robotis_DynamixelCAN::Finalize(void)
{
	if(dynamixel != NULL) {
		dynamixel->SetTorqueEnable(0);

		delete dynamixel;
		dynamixel = NULL;
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

int Robotis_DynamixelCAN::Enable(void)
{
	if(dynamixel == NULL) {
		return API_ERROR;
	}

	if(dynamixel->SetTorqueEnable(1) == false) {
		PrintMessage("ERROR : Robotis_DynamixelCAN::Enable() -> Occur a error in SetTorqueEnable().\n");
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Robotis_DynamixelCAN::Disable(void)
{
	if(dynamixel == NULL) {
		return API_ERROR;
	}

	if(dynamixel->SetTorqueEnable(0) == false) {
		PrintMessage("ERROR : Robotis_DynamixelCAN::Disable() -> Occur a error in SetTorqueEnable().\n");
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Robotis_DynamixelCAN::SetParameter(Property parameter)
{
	long id;

	if(parameter.FindName("ID") == false)						goto ERROR_Robotis_DynamixelCAN_SetParameter;
	id = atol(parameter.GetValue("ID").c_str());

	if(parameter.FindName("MaximumPower") == false)				goto ERROR_Robotis_DynamixelCAN_SetParameter;
	_profile.maximumPower = atof(parameter.GetValue("MaximumPower").c_str());

	if(parameter.FindName("LinePerRevolution") == false)		goto ERROR_Robotis_DynamixelCAN_SetParameter;
	_profile.linePerRevolution = atof(parameter.GetValue("LinePerRevolution").c_str());
	//	엔코더가 고정되어 있기 때문에 강제로 값을 설정
	_profile.linePerRevolution = 360.0 * 1023.0 / 300.0;

	if(parameter.FindName("ReductionRatio") == false)			goto ERROR_Robotis_DynamixelCAN_SetParameter;
	_profile.reductionRatio = atof(parameter.GetValue("ReductionRatio").c_str());

	if(parameter.FindName("MaximumVelocity") == false)			goto ERROR_Robotis_DynamixelCAN_SetParameter;
	_profile.maximumVelocity = atof(parameter.GetValue("MaximumVelocity").c_str());

	if(parameter.FindName("Acceleration") == false)				goto ERROR_Robotis_DynamixelCAN_SetParameter;
	_profile.acceleration = atof(parameter.GetValue("Acceleration").c_str());

	if(parameter.FindName("MinimumPositionLimit") == false)		goto ERROR_Robotis_DynamixelCAN_SetParameter;
	_profile.minimumPositionLimit = atof(parameter.GetValue("MinimumPositionLimit").c_str());

	if(parameter.FindName("MaximumPositionLimit") == false)		goto ERROR_Robotis_DynamixelCAN_SetParameter;
	_profile.maximumPositionLimit = atof(parameter.GetValue("MaximumPositionLimit").c_str());

	if(dynamixel == NULL) {
		if(can == NULL) {
			return API_ERROR;
		}

		dynamixel = new DynamixelCAN(id, can);
	}

	if(dynamixel->SetTorqueLimit((unsigned short)(_profile.maximumPower)) == false) {
		PrintMessage("ERROR : Robotis_DynamixelUART::SetParameter() -> Occur a error in SetTorqueLimit().\n");
		return API_ERROR;
	}

	if(dynamixel->SetMovingSpeed((unsigned short)(_profile.maximumVelocity * 60 * _profile.reductionRatio / 360.0)) == false) {
		PrintMessage("ERROR : Robotis_DynamixelUART::SetParameter() -> Occur a error in SetMovingSpeed().\n");
		return API_ERROR;
	}

	this->parameter = parameter;

	return API_SUCCESS;

ERROR_Robotis_DynamixelCAN_SetParameter :
	PrintMessage("ERROR : Robotis_DynamixelCAN::SetParameter() -> Can't find parameters\n");
	return API_ERROR;
}

int Robotis_DynamixelCAN::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int Robotis_DynamixelCAN::SetPower(double power, unsigned long time)
{
	return API_NOT_SUPPORTED;
}

int Robotis_DynamixelCAN::GetPower(double &power)
{
	return API_NOT_SUPPORTED;
}

int Robotis_DynamixelCAN::SetVelocity(double velocity, unsigned long time)
{
	return API_NOT_SUPPORTED;
}

int Robotis_DynamixelCAN::GetVelocity(double &velocity)
{
	return API_NOT_SUPPORTED;
}

int Robotis_DynamixelCAN::SetPosition(double position, unsigned long time)
{
	if(dynamixel == NULL) {
		return API_ERROR;
	}

	if(position > _profile.maximumPositionLimit || position < _profile.minimumPositionLimit) {
		return API_ERROR;
	}

	//	Angle -> Pulse
	unsigned short tmp = (unsigned short)(position * (_profile.linePerRevolution * _profile.reductionRatio) / 360.0 + OFFSET_ANGLE);

	if(dynamixel->SetGoalPosition(tmp) == false) {
		PrintMessage("ERROR : Robotis_DynamixelCAN::SetPosition() -> Occur a error in SetGoalPosition()\n");
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Robotis_DynamixelCAN::GetPosition(double &position)
{
	if(dynamixel == NULL) {
		return API_ERROR;
	}

	unsigned short tmp;
	if(dynamixel->GetPresentPosition(&tmp) == false) {
		PrintMessage("ERROR : Robotis_DynamixelCAN::GetPosition() -> Occur a error in GetPresentPosition()\n");
		position = 0;
		return API_ERROR;
	}

	//	Pulse -> Angle
	position = (double)(tmp) * 360.0 / (_profile.linePerRevolution * _profile.reductionRatio) - OFFSET_ANGLE;

	return API_SUCCESS;
}

int Robotis_DynamixelCAN::InitializeCAN(Property parameter)
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


#if !defined(DEVICE_TEST)
#if defined(WIN32)
extern "C"
{
	__declspec(dllexport) OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new Robotis_DynamixelCAN();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new Robotis_DynamixelCAN();
}

#endif
#endif