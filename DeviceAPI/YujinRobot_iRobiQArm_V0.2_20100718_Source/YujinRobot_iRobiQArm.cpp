#include "YujinRobot_iRobiQArm.h"
#include "OprosPrintMessage.h"

YujinRobot_iRobiQArm::YujinRobot_iRobiQArm(void)
{
	arm = NULL;
}

YujinRobot_iRobiQArm::~YujinRobot_iRobiQArm(void)
{
	Finalize();
}

int YujinRobot_iRobiQArm::Initialize(Property parameter)
{
	arm = new iRobiQArm();

	if(arm->iRobiQ_Initialize() == false) {
		Finalize();
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQArm::Finalize(void)
{
	Disable();

	if(arm != NULL) {
		arm->iRobiQ_Finalize();
		delete arm;
		arm = NULL;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQArm::Enable(void)
{
	if(arm == NULL) {
		return API_ERROR;
	}

	if(arm->iRobiQ_Connect(ip, port, serviceId) == false) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQArm::Disable(void)
{
	if(arm == NULL) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQArm::SetParameter(Property parameter)
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
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQArm_SetParameter;
		tempProfile.maximumPower = atof(parameter.GetValue(name).c_str());

		sprintf(name, "LinePerRevolution%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQArm_SetParameter;
		tempProfile.linePerRevolution = atof(parameter.GetValue(name).c_str());

		sprintf(name, "ReductionRatio%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQArm_SetParameter;
		tempProfile.reductionRatio = atof(parameter.GetValue(name).c_str());

		sprintf(name, "MaximumVelocity%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQArm_SetParameter;
		tempProfile.maximumVelocity = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Acceleration%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQArm_SetParameter;
		tempProfile.acceleration = atof(parameter.GetValue(name).c_str());

		sprintf(name, "MinimumPositionLimit%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQArm_SetParameter;
		tempProfile.minimumPositionLimit = atof(parameter.GetValue(name).c_str());

		sprintf(name, "MaximumPositionLimit%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQArm_SetParameter;
		tempProfile.maximumPositionLimit = atof(parameter.GetValue(name).c_str());
		
		_profile.push_back(tempProfile);
	}

	if(parameter.FindName("IP") == false)						goto ERROR_YujinRobot_iRobiQArm_SetParameter;
	ip = parameter.GetValue("IP");
	
	if(parameter.FindName("Port") == false)						goto ERROR_YujinRobot_iRobiQArm_SetParameter;
	port = (unsigned int)atoi(parameter.GetValue("Port").c_str());
	
	if(parameter.FindName("ServiceID") == false)				goto ERROR_YujinRobot_iRobiQArm_SetParameter;
	serviceId = (unsigned short)atoi(parameter.GetValue("ServiceID").c_str());

	this->parameter = parameter;

	return API_SUCCESS;

ERROR_YujinRobot_iRobiQArm_SetParameter :
	PrintMessage("ERROR : YujinRobot_iRobiQArm::SetParameter() -> Can't find parameters\n");
	_profile.clear();
	return API_ERROR;
}

int YujinRobot_iRobiQArm::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int YujinRobot_iRobiQArm::StartHoming(void)
{
	if(arm == NULL) {
		return API_ERROR;
	}

	if(arm->iRobiQ_SetLeftArm(0.0, 1) == false) {
		return false;
	}
	if(arm->iRobiQ_SetRightArm(0.0, 1) == false) {
		return false;
	}

	for(int i = 0; i < 2; i++) {
		arm->startTime[i] = 0;
		arm->runTime[i] = 0;
		arm->startAngle[i] = 0.0;
		arm->targetAngle[i] = 0.0;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQArm::Stop(void)
{
	if(arm == NULL) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQArm::EmergencyStop(void)
{
	if(arm == NULL) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQArm::SetPower(vector<double> power, vector<unsigned long> time)
{
	return API_NOT_SUPPORTED;
}

int YujinRobot_iRobiQArm::GetPower(vector<double> &power)
{
	return API_NOT_SUPPORTED;
}

int YujinRobot_iRobiQArm::SetVelocity(vector<double> velocity, vector<unsigned long> time)
{
	return API_NOT_SUPPORTED;
}

int YujinRobot_iRobiQArm::GetVelocity(vector<double> &velocity)
{
	return API_NOT_SUPPORTED;
}

int YujinRobot_iRobiQArm::SetPosition(vector<double> position, vector<unsigned long> time)
{
	if(arm == NULL) {
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

	if(arm->iRobiQ_SetLeftArm(position[0], (int)time[0]) == true) {
		return API_ERROR;
	}

	if(arm->iRobiQ_SetRightArm(position[1], (int)time[1]) == false) {
		return API_ERROR;
	}
	
	return API_SUCCESS;
}

int YujinRobot_iRobiQArm::GetPosition(vector<double> &position)
{
	if(arm == NULL) {
		return API_ERROR;
	}

	position.resize(2);

	if(arm->iRobiQ_GetLeftArm(&position[0]) == false) {
		position.clear();
		return API_ERROR;
	}
	if(arm->iRobiQ_GetRightArm(&position[1]) == false) {
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
	return new YujinRobot_iRobiQArm();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new YujinRobot_iRobiQArm();
}

#endif
#endif