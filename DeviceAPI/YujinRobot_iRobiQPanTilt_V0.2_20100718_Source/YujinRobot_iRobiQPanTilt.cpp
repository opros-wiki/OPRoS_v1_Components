#include "YujinRobot_iRobiQPanTilt.h"
#include "OprosPrintMessage.h"

YujinRobot_iRobiQPanTilt::YujinRobot_iRobiQPanTilt(void)
{
	panTilt = NULL;
}

YujinRobot_iRobiQPanTilt::~YujinRobot_iRobiQPanTilt(void)
{
	Finalize();
}

int YujinRobot_iRobiQPanTilt::Initialize(Property parameter)
{
	panTilt = new iRobiQPanTilt();

	if(panTilt->iRobiQ_Initialize() == false) {
		Finalize();
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQPanTilt::Finalize(void)
{
	Disable();

	if(panTilt != NULL) {
		panTilt->iRobiQ_Finalize();
		delete panTilt;
		panTilt = NULL;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQPanTilt::Enable(void)
{
	if(panTilt == NULL) {
		return API_ERROR;
	}

	if(panTilt->iRobiQ_Connect(ip, port, serviceId) == false) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQPanTilt::Disable(void)
{
	if(panTilt == NULL) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQPanTilt::SetParameter(Property parameter)
{
	if(parameter.FindName("Size") == false)				return API_ERROR;
	int size = atoi(parameter.GetValue("Size").c_str());

	if(size != 2) {
		return API_ERROR;
	}

	char name[128];
	ManipulatorProfile tempProfile;
	_profile.clear();

	for(int i = 0; i < size; i++) {
		sprintf(name, "MaximumPower%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQPanTilt_SetParameter;
		tempProfile.maximumPower = atof(parameter.GetValue(name).c_str());

		sprintf(name, "LinePerRevolution%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQPanTilt_SetParameter;
		tempProfile.linePerRevolution = atof(parameter.GetValue(name).c_str());

		sprintf(name, "ReductionRatio%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQPanTilt_SetParameter;
		tempProfile.reductionRatio = atof(parameter.GetValue(name).c_str());

		sprintf(name, "MaximumVelocity%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQPanTilt_SetParameter;
		tempProfile.maximumVelocity = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Acceleration%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQPanTilt_SetParameter;
		tempProfile.acceleration = atof(parameter.GetValue(name).c_str());

		sprintf(name, "MinimumPositionLimit%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQPanTilt_SetParameter;
		tempProfile.minimumPositionLimit = atof(parameter.GetValue(name).c_str());

		sprintf(name, "MaximumPositionLimit%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQPanTilt_SetParameter;
		tempProfile.maximumPositionLimit = atof(parameter.GetValue(name).c_str());
		
		_profile.push_back(tempProfile);
	}

	if(parameter.FindName("IP") == false)						goto ERROR_YujinRobot_iRobiQPanTilt_SetParameter;
	ip = parameter.GetValue("IP");
	
	if(parameter.FindName("Port") == false)						goto ERROR_YujinRobot_iRobiQPanTilt_SetParameter;
	port = (unsigned int)atoi(parameter.GetValue("Port").c_str());
	
	if(parameter.FindName("ServiceID") == false)				goto ERROR_YujinRobot_iRobiQPanTilt_SetParameter;
	serviceId = (unsigned short)atoi(parameter.GetValue("ServiceID").c_str());

	this->parameter = parameter;

	return API_SUCCESS;

ERROR_YujinRobot_iRobiQPanTilt_SetParameter :
	PrintMessage("ERROR : YujinRobot_iRobiQPanTilt::SetParameter() -> Can't find parameters\n");
	_profile.clear();
	return API_ERROR;
}

int YujinRobot_iRobiQPanTilt::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int YujinRobot_iRobiQPanTilt::StartHoming(void)
{
	if(panTilt == NULL) {
		return API_ERROR;
	}

	if(panTilt->iRobiQ_SetPan(0.0, 1) == false) {
		return API_ERROR;
	}
	if(panTilt->iRobiQ_SetTilt(0.0, 1) == false) {
		return API_ERROR;
	}

	for(int i = 0; i < 2; i++) {
		panTilt->startTime[i] = 0;
		panTilt->runTime[i] = 0;
		panTilt->startAngle[i] = 0.0;
		panTilt->targetAngle[i] = 0.0;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQPanTilt::Stop(void)
{
	if(panTilt == NULL) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQPanTilt::EmergencyStop(void)
{
	if(panTilt == NULL) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQPanTilt::SetPower(vector<double> power, vector<unsigned long> time)
{
	return API_NOT_SUPPORTED;
}

int YujinRobot_iRobiQPanTilt::GetPower(vector<double> &power)
{
	return API_NOT_SUPPORTED;
}

int YujinRobot_iRobiQPanTilt::SetVelocity(vector<double> velocity, vector<unsigned long> time)
{
	return API_NOT_SUPPORTED;
}

int YujinRobot_iRobiQPanTilt::GetVelocity(vector<double> &velocity)
{
	return API_NOT_SUPPORTED;
}

int YujinRobot_iRobiQPanTilt::SetPosition(vector<double> position, vector<unsigned long> time)
{
	if(panTilt == NULL) {
		return API_ERROR;
	}

	if(position.size() != 2 || time.size() != 2 || _profile.size() != 2) {
		return API_ERROR;
	}

	for(size_t i = 0; i < position.size(); i++) {
		if(position[i] > _profile[i].maximumPositionLimit || position[i] < _profile[i].minimumPositionLimit) {
			return API_ERROR;
		}
	}

	if(panTilt->iRobiQ_SetPan(position[0], (int)time[0]) == true) {
		return API_ERROR;
	}

	if(panTilt->iRobiQ_SetTilt(position[1], (int)time[1]) == false) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQPanTilt::GetPosition(vector<double> &position)
{
	if(panTilt == NULL) {
		return API_ERROR;
	}

	position.resize(2);

	if(panTilt->iRobiQ_GetPan(&position[0]) == false) {
		position.clear();
		return API_ERROR;
	}
	if(panTilt->iRobiQ_GetTilt(&position[1]) == false) {
		position.clear();
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
	return new YujinRobot_iRobiQPanTilt();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new YujinRobot_iRobiQPanTilt();
}

#endif
#endif