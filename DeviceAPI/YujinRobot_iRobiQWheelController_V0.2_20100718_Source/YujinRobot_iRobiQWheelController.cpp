#include "YujinRobot_iRobiQWheelController.h"
#include "OprosPrintMessage.h"

YujinRobot_iRobiQWheelController::YujinRobot_iRobiQWheelController(void)
{
	wheelController = NULL;
}

YujinRobot_iRobiQWheelController::~YujinRobot_iRobiQWheelController(void)
{
	Finalize();
}

int YujinRobot_iRobiQWheelController::Initialize(Property parameter)
{
	if(SetParameter(parameter) == API_ERROR) {
		return API_ERROR;
	}

	wheelController = new iRobiQWheelController();

	if(wheelController->iRobiQ_Initialize() == false) {
		Finalize();
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQWheelController::Finalize(void)
{
	Disable();

	if(wheelController != NULL) {
		wheelController->iRobiQ_Finalize();
		delete wheelController;
		wheelController = NULL;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQWheelController::Enable(void)
{
	if(wheelController == NULL) {
		return API_ERROR;
	}

	wheelController->location.x = wheelController->location.y = wheelController->location.theta = 0.0;

	if(wheelController->iRobiQ_Connect(ip, port, serviceId) == false) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQWheelController::Disable(void)
{
	if(wheelController == NULL) {
		return API_ERROR;
	}

	if(wheelController->iRobiQ_Disconnect() == false) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQWheelController::SetParameter(Property parameter)
{
	if (parameter.FindName("WheelDiameter") == false)		goto ERROR_YujinRobot_iRobiQWheelController_SetParameter;
	if (parameter.FindName("AxleDistance") == false)		goto ERROR_YujinRobot_iRobiQWheelController_SetParameter;
	if (parameter.FindName("VarianceDistance") == false)	goto ERROR_YujinRobot_iRobiQWheelController_SetParameter;
	if (parameter.FindName("VarianceDirection") == false)	goto ERROR_YujinRobot_iRobiQWheelController_SetParameter;
	if (parameter.FindName("SafeRadius") == false)			goto ERROR_YujinRobot_iRobiQWheelController_SetParameter;
	if (parameter.FindName("MaximumVelocity") == false)		goto ERROR_YujinRobot_iRobiQWheelController_SetParameter;
	if (parameter.FindName("Acceleration") == false)		goto ERROR_YujinRobot_iRobiQWheelController_SetParameter;
	
	_profile.wheelDiameter = atof (parameter.GetValue("WheelDiameter").c_str());
	_profile.axleDistance = atof (parameter.GetValue("AxleDistance").c_str());
	_profile.varianceDistance = atof (parameter.GetValue("VarianceDistance").c_str());
	_profile.varianceDirection = DEG2RAD (atof (parameter.GetValue("VarianceDirection").c_str()));
	_profile.safeRadius = atof (parameter.GetValue("SafeRadius").c_str());
	_profile.maximumVelocity = atof (parameter.GetValue("MaximumVelocity").c_str());
	_profile.acceleration = atof (parameter.GetValue("Acceleration").c_str());

	this->parameter = parameter;

	return API_SUCCESS;

ERROR_YujinRobot_iRobiQWheelController_SetParameter :
	PrintMessage("ERROR : YujinRobot_iRobiQWheelController::SetParameter() -> Can't find parameters\n");

	return API_ERROR;
}

int YujinRobot_iRobiQWheelController::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int YujinRobot_iRobiQWheelController::Move(double distance)
{
	if(wheelController == NULL) {
		return API_ERROR;
	}

	int time;
	if(abs(distance) < 0.2) {
		time = 1;
	}
	else {
		time = (int)(distance * 5.0);
	}

	if(wheelController->iRobiQ_MoveWheel(distance, time) == false) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQWheelController::Rotate(double degree)
{
	if(wheelController == NULL) {
		return API_ERROR;
	}

	int time;
	if(abs(degree) < 30.0) {
		time = 1;
	}
	else {
		time = (int)(degree / 30.0);
	}

	if(wheelController->iRobiQ_RotateWheel(degree, time) == false) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQWheelController::Drive(double forwardVelocity, double angularVelocity)
{
	return API_NOT_SUPPORTED;
}

int YujinRobot_iRobiQWheelController::Stop(void)
{
	if(wheelController == NULL) {
		return API_ERROR;
	}

	if(wheelController->iRobiQ_StopWheel() == false) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQWheelController::EmergencyStop(void)
{
	return API_NOT_SUPPORTED;
}

int YujinRobot_iRobiQWheelController::SetPosition(ObjectLocation position)
{
	if(wheelController == NULL) {
		return API_ERROR;
	}

	wheelController->location = position;

	return API_NOT_SUPPORTED;
}

int YujinRobot_iRobiQWheelController::GetPosition(ObjectLocation &position)
{
	if(wheelController == NULL) {
		return API_ERROR;
	}

	position = wheelController->location;

	return API_NOT_SUPPORTED;
}

#if !defined(DEVICE_TEST)
#if defined(WIN32)
extern "C"
{
	__declspec(dllexport) OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new YujinRobot_iRobiQWheelController();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new YujinRobot_iRobiQWheelController();
}
#endif
#endif
