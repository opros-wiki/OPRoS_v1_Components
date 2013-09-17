#include "YujinRobot_iRobiQIR.h"
#include "OprosPrintMessage.h"

YujinRobot_iRobiQIR::YujinRobot_iRobiQIR(void)
{
	ir = NULL;
}

YujinRobot_iRobiQIR::~YujinRobot_iRobiQIR(void)
{
	Finalize();
}

int YujinRobot_iRobiQIR::Initialize(Property parameter)
{
	if(SetParameter(parameter) == API_ERROR) {
		return API_ERROR;
	}

	if(ir != NULL) {
		delete ir;
	}
	ir = new iRobiQIR();

	if(ir->iRobiQ_Initialize() == false) {
		Finalize();
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQIR::Finalize(void)
{
	Disable();

	if(ir != NULL) {
		ir->iRobiQ_Finalize();
		delete ir;
		ir = NULL;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQIR::Enable(void)
{
	if(ir == NULL) {
		return API_ERROR;
	}

	if(ir->iRobiQ_Connect(ip, port, serviceId) == false) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQIR::Disable(void)
{
	if(ir == NULL) {
		return API_ERROR;
	}

	if(ir->iRobiQ_Disconnect() == false) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQIR::SetParameter(Property parameter)
{
	if(parameter.FindName("Size") == false)				return API_ERROR;
	int size = atoi(parameter.GetValue("Size").c_str());

	if(size < 0) {
		return API_ERROR;
	}

	char name[128];
	for(int i = 0; i < size; i++) {
		sprintf(name, "X%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQIR_SetParameter;
		
		sprintf(name, "Y%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQIR_SetParameter;
		
		sprintf(name, "Z%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQIR_SetParameter;
		
		sprintf(name, "Roll%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQIR_SetParameter;
		
		sprintf(name, "Pitch%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQIR_SetParameter;
		
		sprintf(name, "Yaw%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQIR_SetParameter;
	}

	this->parameter = parameter;

	return API_SUCCESS;

ERROR_YujinRobot_iRobiQIR_SetParameter :
	PrintMessage("ERROR : YujinRobot_iRobiQIR::SetParameter() -> Can't find a property in parameter.\n");
	return API_ERROR;
}

int YujinRobot_iRobiQIR::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int YujinRobot_iRobiQIR::GetInfraredSensorData(vector<double> &infraredSensorData)
{
	if(ir == NULL) {
		infraredSensorData.resize(0);
		return API_ERROR;
	}

	if(ir->iRobiQ_GetIRSensorData(infraredSensorData) == false) {
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
	return new YujinRobot_iRobiQIR();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new YujinRobot_iRobiQIR();
}

#endif
#endif