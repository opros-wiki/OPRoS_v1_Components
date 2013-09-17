/*************************************************************

 file: RND_ModularArm.cpp
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

#include <stdlib.h>

#include "RND_ModularArm.h"
#include "OprosPrintMessage.h"
#include "OprosTimer.h"

RND_ModularArm::RND_ModularArm(void)
{
	can = NULL;
}

RND_ModularArm::~RND_ModularArm(void)
{
	Finalize();
}

int RND_ModularArm::Initialize(Property parameter)
{
	if(InitializeCAN(parameter) < 0) {
		PrintMessage("ERROR : RND_ModularArm::Initialize() -> Occur a error in InitializeCAN().\n");
		return API_ERROR;
	}

	if(SetParameter(parameter) == API_ERROR) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int RND_ModularArm::Finalize(void)
{
	Disable();

	_manipulator.clear();

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

int RND_ModularArm::Enable(void)
{
	for(size_t i = 0; i < _manipulator.size(); i++) {
		if(_manipulator[i].ucmc->UCMC_EnableMotorPower() < 0) {
			PrintMessage("ERROR : RND_ModularArm::Enable() -> Can't enable a UCMC Servo Controller.\n");
			return API_ERROR;
		}
	}

	isHome = false;

	return API_SUCCESS;
}

int RND_ModularArm::Disable(void)
{
	for(size_t i = 0; i < _manipulator.size(); i++) {
		if(_manipulator[i].ucmc->UCMC_DisableMotorPower() < 0) {
			PrintMessage("ERROR : RND_ModularArm::Enable() -> Can't disable a UCMC Servo Controller.\n");
			return API_ERROR;
		}
	}

	return API_SUCCESS;
}

int RND_ModularArm::SetParameter(Property parameter)
{
	char name[128];
	long id;
	int size;
	
	_manipulator.clear();
	if(can == NULL) {
		PrintMessage("ERROR : RND_ModularArm::SetParameter() -> A handle of CAN is NULL.\n");
		return API_ERROR;
	}

	if(parameter.FindName("Size") == false)						goto ERROR_RND_ModularArm_SetParameter;
	size = atoi(parameter.GetValue("Size").c_str());

	_manipulator.resize(size);
	

	for(int i = 0; i < size; i++) {
		sprintf(name, "ID%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_RND_ModularArm_SetParameter;
		id = atol(parameter.GetValue(name).c_str());

		sprintf(name, "MaximumPower%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_RND_ModularArm_SetParameter;
		_manipulator[i].maximumPower = atof(parameter.GetValue(name).c_str());

		sprintf(name, "LinePerRevolution%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_RND_ModularArm_SetParameter;
		_manipulator[i].linePerRevolution = atof(parameter.GetValue(name).c_str());

		sprintf(name, "ReductionRatio%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_RND_ModularArm_SetParameter;
		_manipulator[i].reductionRatio = atof(parameter.GetValue(name).c_str());

		sprintf(name, "MaximumVelocity%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_RND_ModularArm_SetParameter;
		_manipulator[i].maximumVelocity = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Acceleration%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_RND_ModularArm_SetParameter;
		_manipulator[i].acceleration = atof(parameter.GetValue(name).c_str());

		sprintf(name, "MinimumPositionLimit%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_RND_ModularArm_SetParameter;
		_manipulator[i].minimumPositionLimit = atof(parameter.GetValue(name).c_str());

		sprintf(name, "MaximumPositionLimit%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_RND_ModularArm_SetParameter;
		_manipulator[i].maximumPositionLimit = atof(parameter.GetValue(name).c_str());

		sprintf(name, "ZeroSearchVelocity%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_RND_ModularArm_SetParameter;
		_manipulator[i].zeroSearchVelocity = (short)atoi(parameter.GetValue(name).c_str());

		sprintf(name, "SwitchSearchVelocity%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_RND_ModularArm_SetParameter;
		_manipulator[i].switchSearchVelocity = (short)atoi(parameter.GetValue(name).c_str());

		sprintf(name, "HomeOffset%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_RND_ModularArm_SetParameter;
		_manipulator[i].homeOffset = atof(parameter.GetValue(name).c_str());
	
		_manipulator[i].ucmc = new UCMC(id, can);
		_manipulator[i].ucmc->UCMC_ResetVariables();
	}

	for(size_t i = 0; i < _manipulator.size(); i++) {
		if(_manipulator[i].maximumPower < 0.0) {
			PrintMessage("ERROR : RND_ModularArm::SetParameter() -> A value of maximum power is wrong.\n");
			_manipulator.clear();	return API_ERROR;
		}

		if(_manipulator[i].linePerRevolution <= 0.0) {
			PrintMessage("ERROR : RND_ModularArm::SetParameter() -> A value of line per revolution is wrong.\n");
			_manipulator.clear();	return API_ERROR;
		}

		if(_manipulator[i].maximumVelocity <= 0.0) {
			PrintMessage("ERROR : RND_ModularArm::SetParameter() -> A value of maximum velocity is wrong.\n");
			_manipulator.clear();	return API_ERROR;
		}

		if(_manipulator[i].acceleration <= 0.0) {
			PrintMessage("ERROR : RND_ModularArm::SetParameter() -> A value of acceleration is wrong.\n");
			_manipulator.clear();	return API_ERROR;
		}

		if(_manipulator[i].maximumPower != 0.0) {
			if(_manipulator[i].ucmc->UCMC_SetContinuousCurrent(20) < 0) {
				PrintMessage("ERROR : RND_ModularArm::SetParameter() -> Can't setup a continuous power.\n");
				_manipulator.clear();	return API_ERROR;
			}

			if(_manipulator[i].ucmc->UCMC_SetOutputCurrent((unsigned long)(_manipulator[i].maximumPower * 1500.0)) < 0) {
				PrintMessage("ERROR : RND_ModularArm::SetParameter() -> Can't setup a maximum power.\n");
				_manipulator.clear();	return API_ERROR;
			}

			if(_manipulator[i].ucmc->UCMC_SetContinuousCurrent((unsigned long)(_manipulator[i].maximumPower * 1000.0)) < 0) {
				PrintMessage("ERROR : RND_ModularArm::SetParameter() -> Can't setup a continuous power.\n");
				_manipulator.clear();	return API_ERROR;
			}
		}
		
		if(_manipulator[i].ucmc->UCMC_SetEncoderCount((short)_manipulator[i].linePerRevolution) < 0) {
			PrintMessage("ERROR : RND_ModularArm::SetParameter() -> Can't setup a line per revolution.\n");
			_manipulator.clear();	return API_ERROR;
		}

		if(_manipulator[i].ucmc->UCMC_SetProfileVelocity(100) < 0) {
			PrintMessage("ERROR : RND_ModularArm::SetParameter() -> Can't setup a profile velocity(First).\n");
			_manipulator.clear();	return API_ERROR;
		}

		if(_manipulator[i].ucmc->UCMC_SetMaxVelocity((short)(_manipulator[i].maximumVelocity * 60.0 * abs(_manipulator[i].reductionRatio / 360.0) * 1.1)) < 0) {
			PrintMessage("ERROR : RND_ModularArm::SetParameter() -> Can't setup a maximum velocity.\n");
			_manipulator.clear();	return API_ERROR;
		}

		if(_manipulator[i].ucmc->UCMC_SetProfileVelocity((short)(_manipulator[i].maximumVelocity * 60.0 * abs(_manipulator[i].reductionRatio / 360.0))) < 0) {
			PrintMessage("ERROR : RND_ModularArm::SetParameter() -> Can't setup a profile velocity(second).\n");
			_manipulator.clear();	return API_ERROR;
		}

		if(_manipulator[i].ucmc->UCMC_SetHomingMethod(1) < 0) {
			PrintMessage("ERROR : RND_ModularArm::SetParameter() -> Can't setup a homing method.\n");
			_manipulator.clear();	return API_ERROR;
		}

		if(_manipulator[i].ucmc->UCMC_SetZeroSearchVelocity(_manipulator[i].zeroSearchVelocity) < 0) {
			PrintMessage("ERROR : RND_ModularArm::SetParameter() -> Can't setup a zero search velocity.\n");
			_manipulator.clear();	return API_ERROR;
		}

		if(_manipulator[i].ucmc->UCMC_SetSwitchSearchVelocity(_manipulator[i].switchSearchVelocity) < 0) {
			PrintMessage("ERROR : RND_ModularArm::SetParameter() -> Can't setup a switch search velocity.\n");
			_manipulator.clear();	return API_ERROR;
		}
	}

	this->parameter = parameter;

	return API_SUCCESS;

ERROR_RND_ModularArm_SetParameter :
	_manipulator.clear();
	
	PrintMessage("ERROR : RND_ModularArm::SetParameter() -> Can't find %s in parameter\n", name);

	return API_ERROR;
}

int RND_ModularArm::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int RND_ModularArm::StartHoming(void)
{
	vector<double> offsetPosition(_manipulator.size());
	for(size_t i = 0; i < _manipulator.size(); i++) {
		_manipulator[i].ucmc->UCMC_StartHoming();
		
		for(int time = 0; ; time++) {
			unsigned short status;
			if(_manipulator[i].ucmc->UCMC_GetStatus(&status) < 0) {
				Finalize();
				return API_ERROR;
			}

			if(status == 0x0190) {
				if(_manipulator[i].ucmc->UCMC_SetActualPosition(0) < 0) {
					Finalize();
					return API_ERROR;
				}

				break;
			}
			OprosSleep(100);

			if(time == 1000) {
				Finalize();
				return API_ERROR;
			}
		}
	}

	for(size_t i = 0; i < _manipulator.size(); i++) {
		offsetPosition[i] = _manipulator[i].homeOffset;
	}

	vector<unsigned long> time;
	if(SetPosition(offsetPosition, time) == API_ERROR) {
		Finalize();
		return API_ERROR;
	}
	OprosSleep(500);

	for(size_t i = 0; i < _manipulator.size(); i++) {
		for(int time = 0; ; time++) {
			unsigned short status;
			if(_manipulator[i].ucmc->UCMC_GetStatus(&status) < 0) {
				Finalize();
				return API_ERROR;
			}

			if(status == 0x0190) {
				if(_manipulator[i].ucmc->UCMC_SetActualPosition(0) < 0) {
					Finalize();
					return API_ERROR;
				}

				break;
			}
			OprosSleep(100);

			if(time == 1000) {
				Finalize();
				return API_ERROR;
			}
		}
	}

	isHome = true;

	return API_SUCCESS;
}

int RND_ModularArm::Stop(void)
{
	for(size_t i = 0; i < _manipulator.size(); i++) {
		if(_manipulator[i].ucmc->UCMC_SetProfileVelocity(0) < 0) {
			PrintMessage("ERROR : RND_ModularArm::Stop() -> Occur a error in UCMC_SetProfileVelocity().\n");
			return API_ERROR;
		}
	}

	return API_SUCCESS;
}

int RND_ModularArm::EmergencyStop(void)
{
	for(size_t i = 0; i < _manipulator.size(); i++) {
		if(_manipulator[i].ucmc->UCMC_QuickStop() < 0) {
			PrintMessage("ERROR : RND_ModularArm::EmergencyStop() -> Occur a error in UCMC_QuickStop().\n");
			return API_ERROR;
		}
	}

	return API_SUCCESS;
}

int RND_ModularArm::SetPower(vector<double> power, vector<unsigned long> time)
{
	if(power.size() != _manipulator.size()) {
		return API_ERROR;
	}

	for(size_t i = 0; i < power.size(); i++) {
		if(power[i] > _manipulator[i].maximumPower) {
			power[i] = _manipulator[i].maximumPower;
		}
		else if(power[i] < -_manipulator[i].maximumPower)	{
			power[i] = -_manipulator[i].maximumPower;
		}

		if(_manipulator[i].ucmc->UCMC_SetTargetCurrent((long)(power[i] * 1000.0)) < 0) {
			PrintMessage ("ERROR : RND_ModularArm::SetPower() -> Occur a error int UCMC_SetTargetCurrent().\n");
			return API_ERROR;
		}
	}

	return API_SUCCESS;
}

int RND_ModularArm::GetPower(vector<double> &power)
{
	long current;

	power.clear();

	for(size_t i = 0; i < _manipulator.size(); i++) {
		if(_manipulator[i].ucmc->UCMC_GetActualCurrent(&current) < 0) {
			power.clear();
			PrintMessage ("ERROR : RND_ModularArm::GetPower() -> Occur a error int UCMC_GetActualCurrent().\n");
			return API_ERROR;
		}

		power.push_back((double)current * 0.001);
	}

	return API_SUCCESS;
}

int RND_ModularArm::SetVelocity(vector<double> velocity, vector<unsigned long> time)
{
	if(velocity.size() != _manipulator.size()) {
		return API_ERROR;
	}

	for(size_t i = 0; i < _manipulator.size(); i++) {
		if(velocity[i] > _manipulator[i].maximumVelocity) {
			velocity[i] = _manipulator[i].maximumVelocity;
		}
		else if(velocity[i] < -_manipulator[i].maximumVelocity) {
			velocity[i] = -_manipulator[i].maximumVelocity;
		}

		//	Degree/s -> RPM
		short tmp = (short)(velocity[i] * 60.0 * _manipulator[i].reductionRatio / 360.0);

		if(_manipulator[i].ucmc->UCMC_SetTargetVelocity(tmp) < 0) {
			PrintMessage ("ERROR : RND_ModularArm::SetVelocity() -> Occur a error int UCMC_SetTargetVelocity().\n");
			return API_ERROR;
		}
	}

	return API_SUCCESS;
}

int RND_ModularArm::GetVelocity(vector<double> &velocity)
{
	velocity.clear();

	for(size_t i = 0; i < _manipulator.size(); i++) {
		short tmp;
		if(_manipulator[i].ucmc->UCMC_GetActualVelocity(&tmp) < 0) {
			velocity.clear();
			PrintMessage ("ERROR : RND_ModularArm::GetVelocity() -> Occur a error int UCMC_GetActualVelocity().\n");
			return API_ERROR;
		}

		//	RPM -> Degree/s
		velocity.push_back((double)(tmp) * 360.0 / 60.0 / _manipulator[i].reductionRatio);
	}

	return API_SUCCESS;
}

int RND_ModularArm::SetPosition(vector<double> position, vector<unsigned long> time)
{
	if(position.size() != _manipulator.size()) {
		return API_ERROR;
	}

	for(size_t i = 0; i < position.size(); i++) {
		if(isHome == true) {
			if(position[i] > _manipulator[i].maximumPositionLimit) {
				position[i] = _manipulator[i].maximumPositionLimit;
			}
			else if(position[i] < _manipulator[i].minimumPositionLimit) {
				position[i] = _manipulator[i].minimumPositionLimit;
			}
		}

		//	Angle -> Pulse
		if(_manipulator[i].ucmc->UCMC_SetProfileTargetPosition((long)(position[i] * (_manipulator[i].linePerRevolution * _manipulator[i].reductionRatio) / 360.0)) < 0) {
			PrintMessage ("ERROR : RND_ModularArm::SetPosition() -> Occur a error int UCMC_SetProfileTargetPosition().\n");
			return API_ERROR;
		}
	}

	return API_SUCCESS;
}

int RND_ModularArm::GetPosition(vector<double> &position)
{
	position.clear();

	for(size_t i = 0; i < _manipulator.size(); i++) {
		long tmp;
		if(_manipulator[i].ucmc->UCMC_GetActualPosition(&tmp) < 0) {
			position.clear();
			PrintMessage ("ERROR : RND_ModularArm::GetPosition() -> Occur a error int UCMC_GetActualPosition().\n");
			return API_ERROR;
		}
		//	Pulse -> Angle
		position.push_back((double)(tmp) * 360.0 / (_manipulator[i].linePerRevolution * _manipulator[i].reductionRatio));
	}

	return API_SUCCESS;
}


int RND_ModularArm::InitializeCAN(Property parameter)
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
	return new RND_ModularArm();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new RND_ModularArm();
}

#endif
#endif
