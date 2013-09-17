#include "YujinRobot_iRobiQBumper.h"
#include "OprosPrintMessage.h"

YujinRobot_iRobiQBumper::YujinRobot_iRobiQBumper(void)
{
	bumper = NULL;
}

YujinRobot_iRobiQBumper::~YujinRobot_iRobiQBumper(void)
{
	Finalize();
}

int YujinRobot_iRobiQBumper::Initialize(Property parameter)
{
	if(SetParameter(parameter) == API_ERROR) {
		return API_ERROR;
	}

	if(bumper != NULL) {
		delete bumper;
	}
	bumper = new iRobiQBumper();

	if(bumper->iRobiQ_Initialize() == false) {
		Finalize();
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQBumper::Finalize(void)
{
	Disable();

	if(bumper != NULL) {
		bumper->iRobiQ_Finalize();
		delete bumper;
		bumper = NULL;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQBumper::Enable(void)
{
	if(bumper == NULL) {
		return API_ERROR;
	}

	if(bumper->iRobiQ_Connect(ip, port, serviceId) == false) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQBumper::Disable(void)
{
	if(bumper == NULL) {
		return API_ERROR;
	}

	if(bumper->iRobiQ_Disconnect() == false) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQBumper::SetParameter(Property parameter)
{
	if(parameter.FindName("Size") == false)				return API_ERROR;
	int size = atoi(parameter.GetValue("Size").c_str());

	if(size < 0) {
		return API_ERROR;
	}

	char name[128];
	for(int i = 0; i < size; i++) {
		sprintf(name, "X%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQBumper_SetParameter;
		
		sprintf(name, "Y%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQBumper_SetParameter;
		
		sprintf(name, "Z%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQBumper_SetParameter;
		
		sprintf(name, "Roll%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQBumper_SetParameter;
		
		sprintf(name, "Pitch%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQBumper_SetParameter;
		
		sprintf(name, "Yaw%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQBumper_SetParameter;
	}

	this->parameter = parameter;

	return API_SUCCESS;

ERROR_YujinRobot_iRobiQBumper_SetParameter :
	PrintMessage("ERROR : YujinRobot_iRobiQBumper::SetParameter() -> Can't find a property in parameter.\n");
	return API_ERROR;
}

int YujinRobot_iRobiQBumper::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int YujinRobot_iRobiQBumper::GetBumperSensorData(vector<bool> &bumperSensorData)
{
	if(bumper == NULL) {
		bumperSensorData.resize(0);
		return API_ERROR;
	}

	bumperSensorData.resize(1);
	bumperSensorData[0] = bumper->iRobiQBumper_GetBumperState();

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
	return new YujinRobot_iRobiQBumper();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new YujinRobot_iRobiQBumper();
}

#endif
#endif
