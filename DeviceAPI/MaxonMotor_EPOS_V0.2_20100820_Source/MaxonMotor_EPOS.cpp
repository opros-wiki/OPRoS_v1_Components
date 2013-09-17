#include "MaxonMotor_EPOS.h"
#include "OprosPrintMessage.h"

MaxonMotor_EPOS::MaxonMotor_EPOS(void)
{
	epos = NULL;
	canOpen = NULL;
	can = NULL;
	hOprosAPI = NULL;

	isActive = false;
}

MaxonMotor_EPOS::~MaxonMotor_EPOS(void)
{
	Finalize();
}

int MaxonMotor_EPOS::Initialize(Property parameter)
{
	if(InitializeCAN(parameter) < 0) {
		PrintMessage("ERROR : MaxonMotor_EPOS::Initialize() -> Occur a error in InitializeCAN().\n");
		return API_ERROR;
	}

	if(SetParameter(parameter) < 0) {
		Finalize();
		return API_ERROR;
	}

	return API_SUCCESS;
}

int MaxonMotor_EPOS::Finalize(void)
{
	Disable();

	isActive = false;

	if(epos != NULL) {
		delete epos;
		epos = NULL;
	}

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

int MaxonMotor_EPOS::Enable(void)
{
	if(epos == NULL)	return API_ERROR;

	if(epos->EPOS_FaultReset() < 0) {
		PrintMessage("ERROR : MaxonMotor_EPOS::Enable() -> Occur a error in EPOS_FaultReset().\n");
		return API_ERROR;
	}

	if(epos->EPOS_SetHomePosition(0) < 0) {
		PrintMessage("ERROR : MaxonMotor_EPOS::Enable() -> Occur a error in EPOS_SetHomePosition().\n");
		return API_ERROR;
	}

	if(epos->EPOS_EnableOperation() < 0) {
		PrintMessage("ERROR : MaxonMotor_EPOS::Enable() -> Occur a error in EPOS_EnableOperation().\n");
		return API_ERROR;
	}

	isActive = true;

	return API_SUCCESS;
}

int MaxonMotor_EPOS::Disable(void)
{
	if(epos == NULL)	return API_ERROR;

	if(epos->EPOS_ShutDown() < 0) {
		PrintMessage("ERROR : MaxonMotor_EPOS::Disable() -> Occur a error in EPOS_ShutDown().\n");
	}

	isActive = false;

	return API_SUCCESS;
}

int MaxonMotor_EPOS::SetParameter(Property parameter)
{
	if(can == NULL || canOpen == NULL) {
		PrintMessage("ERROR : MaxonMotor_EPOS::SetParameter() -> A handle of CAN API is NULL.\n");
		return API_ERROR;
	}

	if(epos == NULL) {
		if(parameter.FindName("ID") == false)						goto ERROR_MaxonMotor_EPOS_Set_Parameter;
		epos = new EPOS(atol(parameter.GetValue("ID").c_str()), canOpen);
	}
	else {
		if(isActive == false) {
			if(epos->EPOS_ShutDown() < 0) {
				PrintMessage("ERROR : MaxonMotor_EPOS::SetParameter() -> Occur a error in EPOS_ShutDown().\n");
			}
		}
	}

	if(parameter.FindName("MaximumPower") == false)				goto ERROR_MaxonMotor_EPOS_Set_Parameter;
	profile.maximumPower = atof(parameter.GetValue("MaximumPower").c_str());

	if(parameter.FindName("LinePerRevolution") == false)		goto ERROR_MaxonMotor_EPOS_Set_Parameter;
	profile.linePerRevolution = atof(parameter.GetValue("LinePerRevolution").c_str());

	if(parameter.FindName("ReductionRatio") == false)			goto ERROR_MaxonMotor_EPOS_Set_Parameter;
	profile.reductionRatio = atof(parameter.GetValue("ReductionRatio").c_str());

	if(parameter.FindName("MaximumVelocity") == false)			goto ERROR_MaxonMotor_EPOS_Set_Parameter;
	profile.maximumVelocity = atof(parameter.GetValue("MaximumVelocity").c_str());

	if(parameter.FindName("Acceleration") == false)				goto ERROR_MaxonMotor_EPOS_Set_Parameter;
	profile.acceleration = atof(parameter.GetValue("Acceleration").c_str());

	if(parameter.FindName("MinimumPositionLimit") == false)		goto ERROR_MaxonMotor_EPOS_Set_Parameter;
	profile.minimumPositionLimit = atof(parameter.GetValue("MinimumPositionLimit").c_str());

	if(parameter.FindName("MaximumPositionLimit") == false)		goto ERROR_MaxonMotor_EPOS_Set_Parameter;
	profile.maximumPositionLimit = atof(parameter.GetValue("MaximumPositionLimit").c_str());

	if(parameter.FindName("MotorType") == false)		goto ERROR_MaxonMotor_EPOS_Set_Parameter;
	profile.motorType = (unsigned short)atoi(parameter.GetValue("MotorType").c_str());

	if(parameter.FindName("PolePair") == false)		goto ERROR_MaxonMotor_EPOS_Set_Parameter;
	profile.polePair = (unsigned char)atoi(parameter.GetValue("PolePair").c_str());

	if(parameter.FindName("PositionSensorType") == false)		goto ERROR_MaxonMotor_EPOS_Set_Parameter;
	profile.positionSensorType = (unsigned short)atoi(parameter.GetValue("PositionSensorType").c_str());

	if(epos->EPOS_SetMotorType(profile.motorType) < 0) {
		PrintMessage("ERROR : MaxonMotor_EPOS::SetParameter() -> Occur a error in EPOS_SetMotorType().\n");
		delete epos;	epos = NULL;	isActive = false;
		return API_ERROR;
	}

	if(epos->EPOS_SetPolePair(profile.polePair) < 0) {
		PrintMessage("ERROR : MaxonMotor_EPOS::SetParameter() -> Occur a error in EPOS_SetPolePair().\n");
		delete epos;	epos = NULL;	isActive = false;
		return API_ERROR;
	}

	if(epos->EPOS_SetPositionSensorType(profile.positionSensorType) < 0) {
		PrintMessage("ERROR : MaxonMotor_EPOS::SetParameter() -> Occur a error in EPOS_SetPositionSensorType().\n");
		delete epos;	epos = NULL;	isActive = false;
		return API_ERROR;
	}

	if(epos->EPOS_SetContinuousCurrent((unsigned short)abs(profile.maximumPower)) < 0) {
		PrintMessage("ERROR : MaxonMotor_EPOS::SetParameter() -> Occur a error in EPOS_SetContinuousCurrent().\n");
		delete epos;	epos = NULL;	isActive = false;
		return API_ERROR;
	}

	if(epos->EPOS_SetOutputCurrent((unsigned short)abs(profile.maximumPower * 1.5)) < 0) {
		PrintMessage("ERROR : MaxonMotor_EPOS::SetParameter() -> Occur a error in EPOS_SetOutputCurrent().\n");
		delete epos;	epos = NULL;	isActive = false;
		return API_ERROR;
	}

	if(epos->EPOS_SetEncoderCount((unsigned long)abs(profile.linePerRevolution)) < 0) {
		PrintMessage("ERROR : MaxonMotor_EPOS::SetParameter() -> Occur a error in EPOS_SetEncoderCount().\n");
		delete epos;	epos = NULL;	isActive = false;
		return API_ERROR;
	}

	if(epos->EPOS_SetProMaxVel((unsigned long)abs(profile.maximumVelocity * 60.0 * profile.reductionRatio / 360.0)) < 0) {
		delete epos;	epos = NULL;	isActive = false;
		PrintMessage("ERROR : MaxonMotor_EPOS::SetParameter() -> Occur a error in EPOS_SetProMaxVel().\n");
		return API_ERROR;
	}

	if(epos->EPOS_SetProAccel((unsigned long)abs(profile.acceleration * 60.0 * profile.reductionRatio / 360.0)) < 0) {
		delete epos;	epos = NULL;	isActive = false;
		PrintMessage("ERROR : MaxonMotor_EPOS::SetParameter() -> Occur a error in EPOS_SetProAccel().\n");
		return API_ERROR;
	}

	if(epos->EPOS_SetProDecel((unsigned long)abs(profile.acceleration * 60.0 * profile.reductionRatio / 360.0)) < 0) {
		delete epos;	epos = NULL;	isActive = false;
		PrintMessage("ERROR : MaxonMotor_EPOS::SetParameter() -> Occur a error in EPOS_SetProDecel().\n");
		return API_ERROR;
	}

	if(epos->EPOS_SetQuickStopDecel((unsigned long)abs(profile.acceleration * 60.0 * profile.reductionRatio / 360.0 * 2.0)) < 0) {
		delete epos;	epos = NULL;	isActive = false;
		PrintMessage("ERROR : MaxonMotor_EPOS::SetParameter() -> Occur a error in EPOS_SetQuickStopDecel().\n");
		return API_ERROR;
	}

	if(isActive == false) {
		if(epos->EPOS_EnableOperation() < 0) {
			PrintMessage("ERROR : MaxonMotor_EPOS::SetParameter() -> Occur a error in EPOS_EnableOperation().\n");
			delete epos;	epos = NULL;	isActive = false;
			return API_ERROR;
		}
	}

	this->parameter = parameter;

	return API_SUCCESS;

ERROR_MaxonMotor_EPOS_Set_Parameter :
	delete epos;	epos = NULL;	isActive = false;
	PrintMessage("ERROR : MaxonMotor_EPOS::SetParameter() -> Can't find parameters\n");
	return API_ERROR;
}

int MaxonMotor_EPOS::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int MaxonMotor_EPOS::SetPower(double power, unsigned long time)
{
	if(epos == NULL)	return API_ERROR;

	if(epos->EPOS_SetTargetCurrent((short)(power * 1000.0)) < 0) {
		PrintMessage("ERROR : MaxonMotor_EPOS::SetPower() -> Occur a error in EPOS_SetTargetCurrent().\n");
		return API_ERROR;
	}

	return API_SUCCESS;
}

int MaxonMotor_EPOS::GetPower(double &power)
{
	if(epos == NULL)	return API_ERROR;
	
	short actualCurrent;
	if(epos->EPOS_GetActualCurrent(&actualCurrent) < 0) {
		PrintMessage("ERROR : MaxonMotor_EPOS::GetPower() -> Occur a error in EPOS_GetActualCurrent().\n");
		return API_ERROR;
	}

	power = (double)actualCurrent / 1000.0;

	return API_SUCCESS;
}

int MaxonMotor_EPOS::SetVelocity(double velocity, unsigned long time)
{
	if(epos == NULL)	return API_ERROR;

	if(velocity > profile.maximumVelocity) {
		velocity = profile.maximumVelocity;
	}
	else if(velocity < -profile.maximumVelocity) {
		velocity = -profile.maximumVelocity;
	}
	
	//	Degree/s -> RPM
	if(epos->EPOS_SetTargetVelocity((long)(velocity * 60.0 * profile.reductionRatio / 360.0)) < 0) {
		PrintMessage ("ERROR : MaxonMotor_EPOS::SetVelocity() -> Occur a error int EPOS_SetTargetVelocity().\n");
		return API_ERROR;
	}

	return API_SUCCESS;
}

int MaxonMotor_EPOS::GetVelocity(double &velocity)
{
	if(epos == NULL)	return API_ERROR;

	long actualVelocity;
	if(epos->EPOS_GetActualVelocity(&actualVelocity) < 0) {
		PrintMessage ("ERROR : MaxonMotor_EPOS::GetVelocity() -> Occur a error int EPOS_GetActualVelocity().\n");
		return API_ERROR;
	}

	velocity = (double)(actualVelocity) * 360.0 / 60.0 / profile.reductionRatio;

	return API_SUCCESS;
}

int MaxonMotor_EPOS::SetPosition(double position, unsigned long time)
{
	if(epos == NULL)	return API_ERROR;

	if(position > profile.maximumPositionLimit) {
		position = profile.maximumPositionLimit;
	}
	else if(position < profile.minimumPositionLimit) {
		position = profile.minimumPositionLimit;
	}

	if(epos->EPOS_SetTargetPosition((long)(position * (profile.linePerRevolution * profile.reductionRatio) / 360.0)) < 0) {
		PrintMessage ("ERROR : MaxonMotor_EPOS::SetPosition() -> Occur a error int EPOS_SetTargetPosition().\n");
		return API_ERROR;
	}

	return API_SUCCESS;
}

int MaxonMotor_EPOS::GetPosition(double &position)
{
	if(epos == NULL)	return API_ERROR;

	long actualPosition;
	if(epos->EPOS_GetActualPosition(&actualPosition) < 0) {
		PrintMessage ("ERROR : MaxonMotor_EPOS::GetPosition() -> Occur a error int EPOS_GetActualPosition().\n");
		return API_ERROR;
	}

	position = (double)(actualPosition) * 360.0 / (profile.linePerRevolution * profile.reductionRatio);

	return API_SUCCESS;
}

int MaxonMotor_EPOS::InitializeCAN(Property parameter)
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

	if(canOpen != NULL) {
		delete canOpen;
		canOpen = NULL;
	}
	canOpen = new CANOpen(can);

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
	return new MaxonMotor_EPOS();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new MaxonMotor_EPOS();
}

#endif
#endif