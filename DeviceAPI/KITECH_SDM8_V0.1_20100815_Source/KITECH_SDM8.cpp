/*************************************************************

 file: KITECH_SDM8.cpp
 author: E.C. Shin
 begin: January 30 2010
 copyright: (c) 2010 KITECH, OPRoS
 email: unchol@kitech.re.kr

***************************************************************

OPRoS source code is provided under a dual license mode:
 LGPL and OPRoS individually.

LGPL: You can redistribute it and/or modify it under the terms
 of the Less GNU General Public License as published by the Free
 Software Foundation, either version 3 of the License.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of 
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 Less GNU General Public License for more details. 

 You should have received a copy of the Less GNU General Public
 License along with this program. If not, see 
 <http://www.gnu.org/licenses/>.

OPRoS individual license: An individual license is a license for
 modifying the source code of OPRoS and distiributing it in a
 closed format for commercial purposes.

 If you are interested in this option, please see 
 <http://www.opros.or.kr>.

This license policy may be changed without prior notice.

***************************************************************/
#include "KITECH_SDM8.h"
#include "OprosPrintMessage.h"

#define ENCODER_RESOLUTION		(360.0 * 1023.0 / 300.0)
#define	OFFSET_PULSE			512

KITECH_SDM8::KITECH_SDM8(void)
{
	hOprosAPI = NULL;
	uart = NULL;
	joints.resize(0);
}

KITECH_SDM8::~KITECH_SDM8(void)
{
	Finalize();
}

int KITECH_SDM8::Initialize(Property parameter)
{
	if(InitializeUART(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : KITECH_SDM8::Initialize() -> Can't initialize a UART API\n");
		return API_ERROR;
	}

	if(SetParameter(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : KITECH_SDM8::Initialize() -> Can't setup a parameter\n");
		return API_ERROR;
	}

	return API_SUCCESS;
}

int KITECH_SDM8::Finalize(void)
{
	if(joints.size() != 0) {
		joints.clear();
	}

	FinalizeUART();

	return API_SUCCESS;
}

int KITECH_SDM8::Enable(void)
{
	for(int i = 0; i < (int)joints.size(); i++) {
		if(joints[i].dynamixel->EnableTorque() == false) {
			return API_ERROR;
		}

		joints[i].dynamixel->SetStatusReturn (1);
		joints[i].dynamixel->SetReturnDelay (5);
		joints[i].dynamixel->SetAlarmLED (OVERLOAD_ERROR | OVERHEATING_ERROR | INPUTVOLTAGE_ERROR);
		joints[i].dynamixel->SetAlarmShutdown (OVERLOAD_ERROR | OVERHEATING_ERROR | INPUTVOLTAGE_ERROR);

		if (joints[i].minimumPositionLimit < joints[i].maximumPositionLimit) {
			//joints[i].dynamixel->SetCwanglelimit ((unsigned short)(joints[i].minimumPositionLimit * joints[i].deg2pulse) + OFFSET_PULSE);
			//joints[i].dynamixel->SetCcwanglelimit ((unsigned short)(joints[i].maximumPositionLimit * joints[i].deg2pulse) + OFFSET_PULSE);

			joints[i].dynamixel->SetCwanglelimit (0);
			joints[i].dynamixel->SetCcwanglelimit (1023);
		}

		joints[i].dynamixel->SetTorquelimit((int)joints[i].maximumPower);	//max torque
	}
	
	return API_SUCCESS;
}

int KITECH_SDM8::Disable(void)
{
	int ret = API_SUCCESS;

	for(int i = 0; i < (int)joints.size(); i++) {
		if(joints[i].dynamixel->DisableTorque() == false) {
			ret = API_ERROR;
		}
	}

	return ret;
}

int KITECH_SDM8::SetParameter(Property parameter)
{
	if(uart == NULL) {
		PrintMessage("ERROR : KITECH_SDM8::SetParameter() -> A handle of UART is NULL.\n");
		return API_ERROR;
	}

	if(parameter.FindName("Size") == false)				return API_ERROR;
	int size = atoi(parameter.GetValue("Size").c_str());

	if(size <= 0) 	return API_ERROR;
	
	joints.clear();
	joints.resize(size);

	char temp[64];
	
	for(int i = 0; i < size; i++) {
		sprintf(temp, "ID%d", i);
		if(parameter.FindName(string(temp)) == false)			goto ERROR_KITECH_SDM8_SET_PARAMETER;
		joints[i].id = atoi(parameter.GetValue(temp).c_str());

		sprintf(temp, "MaximumPower%d", i);
		if(parameter.FindName(string(temp)) == false)			goto ERROR_KITECH_SDM8_SET_PARAMETER;
		joints[i].maximumPower = atof(parameter.GetValue(temp).c_str());

		sprintf(temp, "LinePerRevolution%d", i);
		if(parameter.FindName(string(temp)) == false)			goto ERROR_KITECH_SDM8_SET_PARAMETER;
		joints[i].linePerRevolution = atof(parameter.GetValue(temp).c_str());

		sprintf(temp, "ReductionRatio%d", i);
		if(parameter.FindName(string(temp)) == false)			goto ERROR_KITECH_SDM8_SET_PARAMETER;
		joints[i].reductionRatio = atof(parameter.GetValue(temp).c_str());

		sprintf(temp, "MaximumVelocity%d", i);
		if(parameter.FindName(string(temp)) == false)			goto ERROR_KITECH_SDM8_SET_PARAMETER;
		joints[i].maximumVelocity = atof(parameter.GetValue(temp).c_str());

		sprintf(temp, "Acceleration%d", i);
		if(parameter.FindName(string(temp)) == false)			goto ERROR_KITECH_SDM8_SET_PARAMETER;
		joints[i].acceleration = atof(parameter.GetValue(temp).c_str());

		sprintf(temp, "MinimumPositionLimit%d", i);
		if(parameter.FindName(string(temp)) == false)			goto ERROR_KITECH_SDM8_SET_PARAMETER;
		joints[i].minimumPositionLimit = atof(parameter.GetValue(temp).c_str());

		sprintf(temp, "MaximumPositionLimit%d", i);
		if(parameter.FindName(string(temp)) == false)			goto ERROR_KITECH_SDM8_SET_PARAMETER;
		joints[i].maximumPositionLimit = atof(parameter.GetValue(temp).c_str());		

		joints[i].deg2pulse = ENCODER_RESOLUTION / 360.0 / joints[i].reductionRatio;
		joints[i].deg2rpm = 60.0 / 360.0 / joints[i].reductionRatio;

		joints[i].dynamixel = new RobotisDynamixelUART(joints[i].id, uart);
	}
	
	for(size_t i = 0; i < joints.size(); i++) {
		joints[i].dynamixel->SetMovingspeed(100);
	}

	this->parameter = parameter;

	return API_SUCCESS;

ERROR_KITECH_SDM8_SET_PARAMETER :
	PrintMessage("ERROR : KITECH_SDM8::SetParameter() -> Can't find parameters\n");
	joints.clear();
	joints.resize(size);
	return API_ERROR;
}

int KITECH_SDM8::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int KITECH_SDM8::StartHoming(void)
{
	vector<double> initPosition(joints.size());
	vector<unsigned long> time;

	for(size_t i = 0; i < initPosition.size(); i++) {
		initPosition[i] = 0.0;
	}
	
	return SetPosition(initPosition, time);
}

int KITECH_SDM8::Stop(void)
{
	return API_SUCCESS;
}

int KITECH_SDM8::EmergencyStop(void)
{
	return API_SUCCESS;
}

int KITECH_SDM8::SetPosition(vector<double> position, vector<unsigned long> time)
{
	/*
	if(joints.size() != position.size()) {
		return API_ERROR;
	}

	vector<unsigned short> pulse(joints.size());
	vector<unsigned char> id(joints.size());
	
	for(size_t i = 0; i < position.size(); i++) {
		if(position[i] < joints[i].minimumPositionLimit) {
			position[i] = joints[i].minimumPositionLimit;
		}
		else if(position[i] > joints[i].maximumPositionLimit) {
			position[i] = joints[i].maximumPositionLimit;
		}

		id[i] = (unsigned char)joints[i].id;
		pulse[i] = (unsigned short)(position[i] * joints[i].deg2pulse) + OFFSET_PULSE;
	}

	joints[0].dynamixel->SetGoalpositionSync_Broadcast((int)joints.size() - 1, &pulse[1], &id[1]);
	*/
	
	if(joints.size() != position.size()) {
		return API_ERROR;
	}

	for(size_t i = 0; i < position.size(); i++) {
		if(position[i] < joints[i].minimumPositionLimit) {
			position[i] = joints[i].minimumPositionLimit;
		}
		else if(position[i] > joints[i].maximumPositionLimit) {
			position[i] = joints[i].maximumPositionLimit;
		}

		joints[i].dynamixel->SetGoalposition((unsigned short)(position[i] * joints[i].deg2pulse) + OFFSET_PULSE);
	}
	
	return API_SUCCESS;
}

int KITECH_SDM8::GetPosition(vector<double> &position)
{
	position.resize(joints.size());

	unsigned short pulse;
	for(size_t i = 0; i < position.size(); i++) {
		if (joints[i].dynamixel->GetPresentposition (&pulse) == true) {
			position[i] = (double)(pulse - OFFSET_PULSE) / joints[i].deg2pulse;
		}
		else {
			position.clear();
			return API_ERROR;
		}
	}

	return API_SUCCESS;
}

int KITECH_SDM8::InitializeUART(Property parameter)
{
	Property uartParameter;

	if(parameter.FindName("UARTAPIName") == false)	return API_ERROR;
	if(parameter.FindName("PortName") == false)	return API_ERROR;	uartParameter.SetValue("PortName", parameter.GetValue("PortName"));
	if(parameter.FindName("TimeOut") == false)		return API_ERROR;	uartParameter.SetValue("TimeOut", parameter.GetValue("TimeOut"));
	if(parameter.FindName("BaudRate") == false)	return API_ERROR;	uartParameter.SetValue("BaudRate", parameter.GetValue("BaudRate"));
	if(parameter.FindName("DataBits") == false)	return API_ERROR;	uartParameter.SetValue("DataBits", parameter.GetValue("DataBits"));
	if(parameter.FindName("StopBits") == false)	return API_ERROR;	uartParameter.SetValue("StopBits", parameter.GetValue("StopBits"));
	if(parameter.FindName("Parity") == false)		return API_ERROR;	uartParameter.SetValue("Parity", parameter.GetValue("Parity"));
	if(parameter.FindName("FlowControl") == false)	return API_ERROR;	uartParameter.SetValue("FlowControl", parameter.GetValue("FlowControl"));

	if(uart != NULL) {
		delete uart;
	}
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("UARTAPIName").c_str());
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
	hOprosAPI = dlopen(parameter.GetValue("UARTAPIName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : InitializeUART() -> dlopen (%s)\n",parameter.GetValue("UARTDllName").c_str());
		return API_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage ("ERROR -> %s\n", error);
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return API_ERROR;
	}
#endif

	uart = (UART *)getOprosAPI();
	if(uart == NULL) {
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return API_ERROR;
	}

	//	API 초기화
	if(uart->Initialize(uartParameter) < 0) {
		FinalizeUART();
		return API_ERROR;
	}

	if(uart->Enable() < 0) {
		FinalizeUART();
		return API_ERROR;
	}

	return API_SUCCESS;
}

int KITECH_SDM8::FinalizeUART(void)
{
	if(uart != NULL) {
		uart->Disable();
		uart->Finalize();
		delete uart;
		uart = NULL;
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

#if !defined(DEVICE_TEST)
#if defined(WIN32)
extern "C"
{
	__declspec(dllexport) OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new KITECH_SDM8();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new KITECH_SDM8();
}

#endif
#endif
