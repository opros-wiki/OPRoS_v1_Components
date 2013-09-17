/*************************************************************

 file: Robotis_DynamixelUART.cpp
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

#include "Robotis_DynamixelUART.h"
#include "OprosPrintMessage.h"

#define	OFFSET_ANGLE	150.0

Robotis_DynamixelUART::Robotis_DynamixelUART(void)
{
	dynamixel = NULL;
	uart = NULL;
	hOprosAPI = NULL;
}

Robotis_DynamixelUART::~Robotis_DynamixelUART(void)
{
	Finalize();
}

int Robotis_DynamixelUART::Initialize(Property parameter)
{
	if(InitializeUART(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : Robotis_DynamixelUART::Initialize() -> Occur a error in InitializeUART().\n");
		return API_ERROR;
	}

	if(SetParameter(parameter) != API_SUCCESS) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Robotis_DynamixelUART::Finalize(void)
{
	Disable();

	if(dynamixel != NULL) {
		delete dynamixel;
	}

	if(uart != NULL) {
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

int Robotis_DynamixelUART::Enable(void)
{
	if(dynamixel == NULL) {
		return API_ERROR;
	}

	if(dynamixel->SetTorqueEnable(1) == false) {
		PrintMessage("ERROR : Robotis_DynamixelUART::Enable() -> Occur a error in SetTorqueEnable().\n");
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Robotis_DynamixelUART::Disable(void)
{
	if(dynamixel == NULL) {
		return API_ERROR;
	}

	if(dynamixel->SetTorqueEnable(0) == false) {
		PrintMessage("ERROR : Robotis_DynamixelUART::Disable() -> Occur a error in SetTorqueEnable().\n");
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Robotis_DynamixelUART::SetParameter(Property parameter)
{
	if(parameter.FindName("MaximumPower") == false)				goto ERROR_Robotis_DynamixelUART_SetParameter;
	_profile.maximumPower = atof(parameter.GetValue("MaximumPower").c_str());

	if(parameter.FindName("LinePerRevolution") == false)		goto ERROR_Robotis_DynamixelUART_SetParameter;
	_profile.linePerRevolution = atof(parameter.GetValue("LinePerRevolution").c_str());
	//	엔코더가 고정되어 있기 때문에 강제로 값을 설정
	_profile.linePerRevolution = 360.0 * 1023.0 / 300.0;

	if(parameter.FindName("ReductionRatio") == false)			goto ERROR_Robotis_DynamixelUART_SetParameter;
	_profile.reductionRatio = atof(parameter.GetValue("ReductionRatio").c_str());

	if(parameter.FindName("MaximumVelocity") == false)			goto ERROR_Robotis_DynamixelUART_SetParameter;
	_profile.maximumVelocity = atof(parameter.GetValue("MaximumVelocity").c_str());

	if(parameter.FindName("Acceleration") == false)				goto ERROR_Robotis_DynamixelUART_SetParameter;
	_profile.acceleration = atof(parameter.GetValue("Acceleration").c_str());

	if(parameter.FindName("MinimumPositionLimit") == false)		goto ERROR_Robotis_DynamixelUART_SetParameter;
	_profile.minimumPositionLimit = atof(parameter.GetValue("MinimumPositionLimit").c_str());

	if(parameter.FindName("MaximumPositionLimit") == false)		goto ERROR_Robotis_DynamixelUART_SetParameter;
	_profile.maximumPositionLimit = atof(parameter.GetValue("MaximumPositionLimit").c_str());

	if(dynamixel == NULL) {
		if(uart == NULL) {
			return API_ERROR;
		}
		dynamixel = new DynamixelUART(uart, 0);
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

ERROR_Robotis_DynamixelUART_SetParameter :
	PrintMessage("ERROR : Faulhaber_MCDC2805::SetParameter() -> Can't find parameters\n");
	return API_ERROR;
}

int Robotis_DynamixelUART::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int Robotis_DynamixelUART::SetPower(double power, unsigned long time)
{
	return API_NOT_SUPPORTED;
}

int Robotis_DynamixelUART::GetPower(double &power)
{
	return API_NOT_SUPPORTED;
}

int Robotis_DynamixelUART::SetVelocity(double velocity, unsigned long time)
{
	return API_NOT_SUPPORTED;
}

int Robotis_DynamixelUART::GetVelocity(double &velocity)
{
	return API_NOT_SUPPORTED;
}

int Robotis_DynamixelUART::SetPosition(double position, unsigned long time)
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
		PrintMessage("ERROR : Robotis_DynamixelUART::SetPosition() -> Occur a error in SetGoalPosition()\n");
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Robotis_DynamixelUART::GetPosition(double &position)
{
	if(dynamixel == NULL) {
		return API_ERROR;
	}

	unsigned short tmp;
	if(dynamixel->GetPresentPosition(tmp) == false) {
		PrintMessage("ERROR : Robotis_DynamixelUART::GetPosition() -> Occur a error in GetPresentPosition()\n");
		position = 0;
		return API_ERROR;
	}

	//	Pulse -> Angle
	position = (double)(tmp) * 360.0 / (_profile.linePerRevolution * _profile.reductionRatio) - OFFSET_ANGLE;

	return API_SUCCESS;
}

int Robotis_DynamixelUART::InitializeUART(Property parameter)
{
	Property uartParameter;
	char *error = NULL;

	if(parameter.FindName("UARTAPIName") == false)	goto ERROR_Robotis_DynamixelUART_InitializeUART;
	if(parameter.FindName("PortName") == false)		goto ERROR_Robotis_DynamixelUART_InitializeUART;
	else	uartParameter.SetValue("PortName", parameter.GetValue("PortName"));
	if(parameter.FindName("TimeOut") == false)		goto ERROR_Robotis_DynamixelUART_InitializeUART;
	else	uartParameter.SetValue("TimeOut", parameter.GetValue("TimeOut"));
	if(parameter.FindName("BaudRate") == false)		goto ERROR_Robotis_DynamixelUART_InitializeUART;
	else	uartParameter.SetValue("BaudRate", parameter.GetValue("BaudRate"));
	if(parameter.FindName("DataBits") == false)		goto ERROR_Robotis_DynamixelUART_InitializeUART;
	else	uartParameter.SetValue("DataBits", parameter.GetValue("DataBits"));
	if(parameter.FindName("StopBits") == false)		goto ERROR_Robotis_DynamixelUART_InitializeUART;
	else	uartParameter.SetValue("StopBits", parameter.GetValue("StopBits"));
	if(parameter.FindName("Parity") == false)		goto ERROR_Robotis_DynamixelUART_InitializeUART;
	else	uartParameter.SetValue("Parity", parameter.GetValue("Parity"));
	if(parameter.FindName("FlowControl") == false)	goto ERROR_Robotis_DynamixelUART_InitializeUART;
	else	uartParameter.SetValue("FlowControl", parameter.GetValue("FlowControl"));

	if(uart != NULL) {
		delete uart;
		uart = NULL;
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

	uart = (UART *)getOprosAPI();
	if(uart == NULL) {
		Finalize();
		return API_ERROR;
	}

	//	API 초기화
	if(uart->Initialize(uartParameter) < 0) {
		Finalize();
		return API_ERROR;
	}

	if(uart->Enable() < 0) {
		Finalize();
		return API_ERROR;
	}

	return API_SUCCESS;

ERROR_Robotis_DynamixelUART_InitializeUART :
	PrintMessage("ERROR : Robotis_DynamixelUART::InitializeUART() -> Can't find a property in parameter.\n");
	return API_ERROR;
}

#if !defined(DEVICE_TEST)
#if defined(WIN32)
extern "C"
{
__declspec(dllexport) OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new Robotis_DynamixelUART();
}
#endif
#endif