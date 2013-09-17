/*************************************************************

 file: Solubot_UCMC.cpp
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
#include "Solubot_UCMC.h"

#include "OprosPrintMessage.h"


Solubot_UCMC::Solubot_UCMC(void)
{
	ucmc = NULL;
	can = NULL;
	hOprosAPI = NULL;
}

Solubot_UCMC::~Solubot_UCMC(void)
{
	Finalize();
}

int Solubot_UCMC::Initialize(Property parameter)
{
	if(InitializeCAN(parameter) < 0) {
		PrintMessage("ERROR : Solubot_UCMC::Initialize() -> Occur a error in InitializeCAN().\n");
		return API_ERROR;
	}

	if(SetParameter(parameter) < 0) {
		Finalize();
		return API_ERROR;
	}

	if(ucmc->UCMC_ResetVariables() < 0) {
		PrintMessage("ERROR : Solubot_UCMC::Initialize() -> Occur a error in UCMC_ResetVariables().\n");
		Finalize();
		return API_ERROR;
	}

	PrintMessage("SUCCESS : Solubot_UCMC::Initialize().\n");

	return API_SUCCESS;
}

int Solubot_UCMC::Finalize(void)
{
	if(ucmc != NULL) {
		ucmc->UCMC_ResetVariables();

		delete ucmc;
		ucmc = NULL;
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

int Solubot_UCMC::Enable(void)
{
	if(ucmc->UCMC_EnableMotorPower() < 0) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Solubot_UCMC::Disable(void)
{
	if(ucmc->UCMC_DisableMotorPower() < 0) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Solubot_UCMC::SetParameter(Property parameter)
{
	long id;
	short maxVelocity;
	long accel;

	if(ucmc == NULL) {
		if(parameter.FindName("ID") == false)						goto Solubot_UCMC_SET_PARAMETER_ERROR;
		id = atol(parameter.GetValue("ID").c_str());
		
		ucmc = new UCMC(id, can);
	}

	if(parameter.FindName("MaximumPower") == false)				goto Solubot_UCMC_SET_PARAMETER_ERROR;
	_profile.maximumPower = atof(parameter.GetValue("MaximumPower").c_str());

	if(parameter.FindName("LinePerRevolution") == false)		goto Solubot_UCMC_SET_PARAMETER_ERROR;
	_profile.linePerRevolution = atof(parameter.GetValue("LinePerRevolution").c_str());

	if(parameter.FindName("ReductionRatio") == false)			goto Solubot_UCMC_SET_PARAMETER_ERROR;
	_profile.reductionRatio = atof(parameter.GetValue("ReductionRatio").c_str());

	if(parameter.FindName("MaximumVelocity") == false)			goto Solubot_UCMC_SET_PARAMETER_ERROR;
	_profile.maximumVelocity = atof(parameter.GetValue("MaximumVelocity").c_str());

	if(parameter.FindName("Acceleration") == false)				goto Solubot_UCMC_SET_PARAMETER_ERROR;
	_profile.acceleration = atof(parameter.GetValue("Acceleration").c_str());

	if(parameter.FindName("MinimumPositionLimit") == false)		goto Solubot_UCMC_SET_PARAMETER_ERROR;
	_profile.minimumPositionLimit = atof(parameter.GetValue("MinimumPositionLimit").c_str());

	if(parameter.FindName("MaximumPositionLimit") == false)		goto Solubot_UCMC_SET_PARAMETER_ERROR;
	_profile.maximumPositionLimit = atof(parameter.GetValue("MaximumPositionLimit").c_str());


	maxVelocity = abs((short)(_profile.maximumVelocity * 60.0 * _profile.reductionRatio / 360.0));
	if (ucmc->UCMC_SetProfileVelocity(maxVelocity) < 0) {	// max velocity보다 낮게 설정해 준다.
		PrintMessage("ERROR : Solubot_UCMC::UCMC_SetProfileVelocity(%d)\n", maxVelocity);
		return API_ERROR;
	}
	if (ucmc->UCMC_SetMaxVelocity ((short)(maxVelocity*1.1)) < 0) {
		PrintMessage("ERROR : Solubot_UCMC::UCMC_SetMaxVelocity(%d)\n", (short)(maxVelocity*1.1));
		return API_ERROR;
	}
	if (ucmc->UCMC_SetProfileVelocity(maxVelocity) < 0) {
		PrintMessage("ERROR : Solubot_UCMC::UCMC_SetProfileVelocity(%d)\n", maxVelocity);
		return API_ERROR;
	}
	PrintMessage("Solubot_UCMC::UCMC_SetProfileVelocity(%d)\n", maxVelocity);
	PrintMessage("Solubot_UCMC::UCMC_SetMaxVelocity(%d)\n", (short)(maxVelocity*1.1));

	accel = (short)(_profile.acceleration * 60.0 * _profile.reductionRatio / 360.0);
	if (ucmc->UCMC_SetAcceleration (labs(accel)) < 0) {
		PrintMessage("ERROR : Solubot_UCMC::UCMC_SetAcceleration(%d)\n", labs(accel));
		return API_ERROR;
	}
	if (ucmc->UCMC_SetDeceleration (labs(accel)) < 0) {
		PrintMessage("ERROR : Solubot_UCMC::UCMC_SetDeceleration(%d)\n", labs(accel));
		return API_ERROR;
	}
	if (ucmc->UCMC_SetQuickStopDeceleration (labs(accel)) < 0) {
		PrintMessage("ERROR : Solubot_UCMC::UCMC_SetQuickStopDeceleration(%d)\n", labs(accel));
		return API_ERROR;
	}
	PrintMessage("Solubot_UCMC::UCMC_SetAcceleration(%d)\n", labs(accel));
	PrintMessage("Solubot_UCMC::UCMC_SetDeceleration(%d)\n", labs(accel));
	PrintMessage("Solubot_UCMC::UCMC_SetQuickStopDeceleration(%d)\n", labs(accel));

	this->parameter = parameter;

	PrintMessage("SUCCESS : Solubot_UCMC::SetParameter().\n");

	return API_SUCCESS;

Solubot_UCMC_SET_PARAMETER_ERROR :
	PrintMessage("ERROR : Solubot_UCMC::SetParameter() -> Can't find parameters\n");
	return API_ERROR;
}

int Solubot_UCMC::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int Solubot_UCMC::SetPower(double power, unsigned long time)
{
	if(power > _profile.maximumPower || power < -_profile.maximumPower) {
		return API_ERROR;
	}

	if(ucmc->UCMC_SetTargetCurrent((long)(power * 1000.0)) < 0) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Solubot_UCMC::GetPower(double &power)
{
	long tmp;

	if(ucmc->UCMC_GetActualCurrent(&tmp) < 0) {
		power = 0.0;
		return API_ERROR;
	}

	power = (double)(tmp) / 1000.0;

	return API_SUCCESS;
}

int Solubot_UCMC::SetVelocity(double velocity, unsigned long time)
{
	if(velocity > _profile.maximumVelocity || velocity < -_profile.maximumVelocity) {
		PrintMessage ("ERROR : Solubot_UCMC::SetVelocity(%.3lf) maxVelocity:%.3lf -> \n", velocity, _profile.maximumVelocity);
		return API_ERROR;
	}

	//	Degree/s -> RPM
	short tmp = (short)(velocity * 60.0 * _profile.reductionRatio / 360.0);

	if(ucmc->UCMC_SetTargetVelocity(tmp) < 0) {
		PrintMessage ("ERROR : Solubot_UCMC::SetVelocity() -> UCMC_SetTargetVelocity (%d)\n", tmp);
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Solubot_UCMC::GetVelocity(double &velocity)
{
	short tmp;

	if(ucmc->UCMC_GetActualVelocity(&tmp) < 0) {
		velocity = 0;
		return API_ERROR;
	}

	//	RPM -> Degree/s
	velocity = (double)(tmp) * 360.0 / 60.0 / _profile.reductionRatio;

	return API_SUCCESS;
}

int Solubot_UCMC::SetPosition(double position, unsigned long time)
{
	if(position > _profile.maximumPositionLimit || position < _profile.minimumPositionLimit) {
		return API_ERROR;
	}

	//	Angle -> Pulse
	long tmp = (long)(position * (_profile.linePerRevolution * _profile.reductionRatio) / 360.0);

	if(ucmc->UCMC_SetTargetPosition(tmp) < 0) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Solubot_UCMC::GetPosition(double &position)
{
	long tmp;
	if(ucmc->UCMC_GetActualPosition(&tmp) < 0) {
		PrintMessage("ERROR : Solubot_UCMC::GetPosition()\n");
		position = 0;
		return API_ERROR;
	}

	//	Pulse -> Angle
	position = (double)(tmp) * 360.0 / (_profile.linePerRevolution * _profile.reductionRatio);

	return API_SUCCESS;
}

int Solubot_UCMC::InitializeCAN(Property parameter)
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
	return new Solubot_UCMC();
}
#endif
#endif
