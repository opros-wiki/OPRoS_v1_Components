#include "YujinRobot_iRobiQSonar.h"
#include "OprosPrintMessage.h"

YujinRobot_iRobiQSonar::YujinRobot_iRobiQSonar(void)
{
	sonar = NULL;
}

YujinRobot_iRobiQSonar::~YujinRobot_iRobiQSonar(void)
{
	Finalize();
}

int YujinRobot_iRobiQSonar::Initialize(Property parameter)
{
	if(SetParameter(parameter) == API_ERROR) {
		return API_ERROR;
	}

	if(sonar != NULL) {
		delete sonar;
	}
	sonar = new iRobiQSonar();

	if(sonar->iRobiQ_Initialize() == false) {
		Finalize();
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQSonar::Finalize(void)
{
	Disable();

	if(sonar != NULL) {
		sonar->iRobiQ_Finalize();
		delete sonar;
		sonar = NULL;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQSonar::Enable(void)
{
	if(sonar == NULL) {
		return API_ERROR;
	}

	if(sonar->iRobiQ_Connect(ip, port, serviceId) == false) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQSonar::Disable(void)
{
	if(sonar == NULL) {
		return API_ERROR;
	}

	if(sonar->iRobiQ_Disconnect() == false) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQSonar::SetParameter(Property parameter)
{
	if(parameter.FindName("Size") == false)				return API_ERROR;
	int size = atoi(parameter.GetValue("Size").c_str());

	if(size < 0) {
		return API_ERROR;
	}

	char name[128];
	for(int i = 0; i < size; i++) {
		sprintf(name, "X%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQSonar_SetParameter;
		
		sprintf(name, "Y%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQSonar_SetParameter;
		
		sprintf(name, "Z%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQSonar_SetParameter;
		
		sprintf(name, "Roll%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQSonar_SetParameter;
		
		sprintf(name, "Pitch%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQSonar_SetParameter;
		
		sprintf(name, "Yaw%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQSonar_SetParameter;
	}

	this->parameter = parameter;

	return API_SUCCESS;

ERROR_YujinRobot_iRobiQSonar_SetParameter :
	PrintMessage("ERROR : YujinRobot_iRobiQSonar::SetParameter() -> Can't find a property in parameter.\n");
	return API_ERROR;
}

int YujinRobot_iRobiQSonar::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int YujinRobot_iRobiQSonar::GetUltrasonicSensorData(vector<double> &ultrasonicSensorData)
{
	if(sonar == NULL) {
		ultrasonicSensorData.resize(0);
		return API_ERROR;
	}

	if(sonar->iRobiQ_GetSonarSensorData(ultrasonicSensorData) == false) {
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
	return new YujinRobot_iRobiQSonar();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new YujinRobot_iRobiQSonar();
}

#endif
#endif