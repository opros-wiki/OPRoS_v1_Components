#include "CNRobot_HRB_MTC_B10.h"

#include "OprosPrintMessage.h"

CNRobot_HRB_MTC_B10::CNRobot_HRB_MTC_B10(void)
{
	_hcr01 = NULL;
	isOpened = false;
}

CNRobot_HRB_MTC_B10::~CNRobot_HRB_MTC_B10(void)
{
	Finalize();
}

int CNRobot_HRB_MTC_B10::Initialize(Property parameter)
{
	if(SetParameter(parameter) < 0) {
		return API_ERROR;
	}

	_hcr01 = new HRC01();

	return 0;
}

int CNRobot_HRB_MTC_B10::Finalize(void)
{
	Disable();

	if(_hcr01 != NULL) {
		delete _hcr01;
		_hcr01 = NULL;
	}

	return 0;
}

int CNRobot_HRB_MTC_B10::Enable(void)
{
	if(_hcr01 == NULL) {
		return API_ERROR;
	}

	Disable();

	if(_hcr01->Open() < 0) {
		PrintMessage("ERROR : CNRobot_HRB_MTC_B10::Enable() -> Occur a error in _hcr01->Open()\n");
		return API_ERROR;
	}

	if(_hcr01->Reset() < 0) {
		PrintMessage("ERROR : CNRobot_HRB_MTC_B10::Enable() -> Occur a error in _hcr01->Reset()\n");
		_hcr01->Close();
		return API_ERROR;
	}

	if(SetupParameters() < 0) {
		PrintMessage("ERROR : CNRobot_HRB_MTC_B10::Enable() -> Occur a error in SetupParameters()\n");
		_hcr01->Close();
		return API_ERROR;
	}

	if(_hcr01->SetPosition(0, 0, 0) < 0) {
		PrintMessage("ERROR : CNRobot_HRB_MTC_B10::Enable() -> Occur a error in _hcr01->SetPosition()\n");
		_hcr01->Close();
		return API_ERROR;
	}

	isOpened = true;

	return 0;
}

int CNRobot_HRB_MTC_B10::Disable(void)
{
	if(isOpened == false) {
		return 0;
	}

	_hcr01->Reset();
	_hcr01->Close();

	isOpened = false;

	return 0;
}

int CNRobot_HRB_MTC_B10::SetParameter(Property parameter)
{
	if(parameter.FindName("Size") == false)				return API_ERROR;
	int size = atoi(parameter.GetValue("Size").c_str());

	if(size < 0 || size > 3) {
		return API_ERROR;
	}

	char name[128];
	CNRobot_HRB_MTC_B10_Profile tempProfile;
	_profile.clear();

	for(int i = 0; i < size; i++) {
		sprintf(name, "MaximumPower%d", i);
		if(parameter.FindName(string(name)) == false)			goto CNR_ROBOT_HRB_MTC_B10_SET_PARAMETER_ERROR;
		tempProfile.maximumPower = atof(parameter.GetValue(name).c_str());

		sprintf(name, "LinePerRevolution%d", i);
		if(parameter.FindName(string(name)) == false)			goto CNR_ROBOT_HRB_MTC_B10_SET_PARAMETER_ERROR;
		tempProfile.encoder = atof(parameter.GetValue(name).c_str());

		sprintf(name, "ReductionRatio%d", i);
		if(parameter.FindName(string(name)) == false)			goto CNR_ROBOT_HRB_MTC_B10_SET_PARAMETER_ERROR;
		tempProfile.reductionRatio = atof(parameter.GetValue(name).c_str());

		sprintf(name, "MaximumVelocity%d", i);
		if(parameter.FindName(string(name)) == false)			goto CNR_ROBOT_HRB_MTC_B10_SET_PARAMETER_ERROR;
		tempProfile.maximumVelocity = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Acceleration%d", i);
		if(parameter.FindName(string(name)) == false)			goto CNR_ROBOT_HRB_MTC_B10_SET_PARAMETER_ERROR;
		tempProfile.acceleration = atof(parameter.GetValue(name).c_str());

		sprintf(name, "MinimumPositionLimit%d", i);
		if(parameter.FindName(string(name)) == false)			goto CNR_ROBOT_HRB_MTC_B10_SET_PARAMETER_ERROR;
		tempProfile.minimumPositionLimit = atof(parameter.GetValue(name).c_str());

		sprintf(name, "MaximumPositionLimit%d", i);
		if(parameter.FindName(string(name)) == false)			goto CNR_ROBOT_HRB_MTC_B10_SET_PARAMETER_ERROR;
		tempProfile.maximumPositionLimit = atof(parameter.GetValue(name).c_str());


		sprintf(name, "Kp%d", i);
		if(parameter.FindName(string(name)) == false)			goto CNR_ROBOT_HRB_MTC_B10_SET_PARAMETER_ERROR;
		tempProfile.kp = (unsigned short)atoi(parameter.GetValue(name).c_str());

		sprintf(name, "Ki%d", i);
		if(parameter.FindName(string(name)) == false)			goto CNR_ROBOT_HRB_MTC_B10_SET_PARAMETER_ERROR;
		tempProfile.ki = (unsigned short)atoi(parameter.GetValue(name).c_str());

		sprintf(name, "Kd%d", i);
		if(parameter.FindName(string(name)) == false)			goto CNR_ROBOT_HRB_MTC_B10_SET_PARAMETER_ERROR;
		tempProfile.kd = (unsigned short)atoi(parameter.GetValue(name).c_str());

		sprintf(name, "ISum%d", i);
		if(parameter.FindName(string(name)) == false)			goto CNR_ROBOT_HRB_MTC_B10_SET_PARAMETER_ERROR;
		tempProfile.iSum = (unsigned short)atoi(parameter.GetValue(name).c_str());
		
		_profile.push_back(tempProfile);
	}

	if(isOpened == true) {
		if(SetupParameters() < 0) {
			return API_ERROR;
		}
	}

	this->parameter = parameter;

	return 0;

CNR_ROBOT_HRB_MTC_B10_SET_PARAMETER_ERROR :
	_profile.clear();
	return API_ERROR;
}

int CNRobot_HRB_MTC_B10::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return 0;
}

int CNRobot_HRB_MTC_B10::StartHoming(void)
{
	return API_NOT_SUPPORTED;
}

int CNRobot_HRB_MTC_B10::Stop(void)
{
	if(_hcr01->Stop() < 0) {
		return API_ERROR;
	}

	return 0;
}

int CNRobot_HRB_MTC_B10::EmergencyStop(void)
{
	if(_hcr01->QuickStop() < 0) {
		return API_ERROR;
	}

	return 0;
}

int CNRobot_HRB_MTC_B10::SetPower(vector<double> power, vector<unsigned long> time)
{
	return API_NOT_SUPPORTED;
}

int CNRobot_HRB_MTC_B10::GetPower(vector<double> &power)
{
	return API_NOT_SUPPORTED;
}

int CNRobot_HRB_MTC_B10::SetVelocity(vector<double> velocity, vector<unsigned long> time)
{
	if(velocity.size() != _profile.size()) {
		PrintMessage("ERROR : CNRobot_HRB_MTC_B10::SetVelocity() -> A size of data is different.\n");
		return API_ERROR;
	}

	for(size_t i = 0; i < velocity.size(); i++) {
		if(_hcr01->SetVelocity((int)(i + 1), (int)(velocity[i] * _profile[i].encoder * _profile[i].reductionRatio / 360.0)) < 0) {
			PrintMessage("ERROR : CNRobot_HRB_MTC_B10::SetVelocity() -> Occur a error in _hcr01->SetVelocity()\n");
			return API_ERROR;
		}
	}

	return 0;
}

int CNRobot_HRB_MTC_B10::GetVelocity(vector<double> &velocity)
{
	velocity.resize(_profile.size());

	int tmp[3];

	_hcr01->GetVelocity(tmp);

	for(size_t i = 0; i < velocity.size(); i++) {
		//velocity[i] = (double)tmp[i] * 360.0 / (_profile[i].encoder * _profile[i].reductionRatio);
		velocity[i] = (double)tmp[i];
	}

	return 0;
}

int CNRobot_HRB_MTC_B10::SetPosition(vector<double> position, vector<unsigned long> time)
{
	if(position.size() != _profile.size()) {
		PrintMessage("ERROR : CNRobot_HRB_MTC_B10::SetPosition() -> A size of data is different.\n");
		return API_ERROR;
	}

	for(size_t i = 0; i < position.size(); i++) {
		if(_hcr01->SetPosition((int)(i + 1), (int)(position[i] * _profile[i].encoder * _profile[i].reductionRatio / 360.0)) < 0) {
			PrintMessage("ERROR : CNRobot_HRB_MTC_B10::SetPosition() -> Occur a error in _hcr01->SetPosition()\n");
			return API_ERROR;
		}
	}

	return 0;
}

int CNRobot_HRB_MTC_B10::GetPosition(vector<double> &position)
{
	position.resize(_profile.size());

	int tmp[3];

	_hcr01->GetPosition(tmp);

	for(size_t i = 0; i < position.size(); i++) {
		position[i] = (double)tmp[i] * 360.0 / (_profile[i].encoder * _profile[i].reductionRatio);
	}

	return 0;
}

int CNRobot_HRB_MTC_B10::SetupParameters(void)
{
	for(size_t i = 0; i < _profile.size(); i++) {
		if(_hcr01->SetPIDGain(i + 1, _profile[i].kp, _profile[i].ki, _profile[i].kd, _profile[i].iSum) < 0) {
			PrintMessage("ERROR : CNRobot_HRB_MTC_B10::SetupParameters() -> Occur a error in _hcr01->SetPIDGain()\n");
			return -1;
		}

		double maximumVelocity = _profile[i].maximumVelocity * (_profile[i].encoder * _profile[i].reductionRatio) / 360.0;
		if(_hcr01->SetMaximumVelocity(i + 1, (unsigned int)maximumVelocity) < 0) {
			PrintMessage("ERROR : CNRobot_HRB_MTC_B10::SetupParameters() -> Occur a error in _hcr01->SetMaximumVelocity()\n");
			return -1;
		}

		double acceleration = _profile[i].acceleration * (_profile[i].encoder * _profile[i].reductionRatio) / 360.0;
		if(_hcr01->SetAcceleration(i + 1, (unsigned int)acceleration) < 0) {
			PrintMessage("ERROR : CNRobot_HRB_MTC_B10::SetupParameters() -> Occur a error in _hcr01->SetAcceleration()\n");
			return -1;
		}
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
	return new CNRobot_HRB_MTC_B10();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new CNRobot_HRB_MTC_B10();
}

#endif
#endif
