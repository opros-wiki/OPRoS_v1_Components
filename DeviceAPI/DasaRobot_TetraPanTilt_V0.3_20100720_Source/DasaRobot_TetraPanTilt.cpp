/*************************************************************

 file: DasaRobot_TetraPanTilt.cpp
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
#include "dsphal.h"
#include "OprosPrintMessage.h"
#include "DasaRobot_TetraPanTilt.h"

#define CENTER_ANGLE			(150.)
#define MAX_ANGLE				(300.)
#define MAX_STEP				(1023.)

#define PAN_ID					1
#define TILT_ID					2


DasaRobot_TetraPanTilt::DasaRobot_TetraPanTilt (void)
{

}
DasaRobot_TetraPanTilt::~DasaRobot_TetraPanTilt (void)
{

}

int DasaRobot_TetraPanTilt::Initialize(Property parameter)
{
	if(SetParameter(parameter) == API_ERROR) {
		PrintMessage("DasaRobot_TetraPanTilt::Initialize() ERROR -> SetParameter()\n");
		return API_ERROR;
	}

	return API_SUCCESS;
}

int DasaRobot_TetraPanTilt::Finalize(void)
{
	return API_SUCCESS;
}

int DasaRobot_TetraPanTilt::Enable(void)
{
	return API_SUCCESS;
}

int DasaRobot_TetraPanTilt::Disable(void)
{
	if (PowerDown (PAN_ID) == false) return API_ERROR;
	if (PowerDown (TILT_ID) == false) return API_ERROR;

	return API_SUCCESS;
}

int DasaRobot_TetraPanTilt::SetParameter(Property parameter)
{
	if (parameter.FindName("RobotIP") == false) return API_ERROR;
	if (parameter.FindName("RobotPort") == false) return API_ERROR;
	
	robotIP = parameter.GetValue("RobotIP");
	robotPort = atoi (parameter.GetValue("RobotPort").c_str());

	PrintMessage("-- DasaRobot_TetraPanTilt Parameter\n");
	PrintMessage("-- RobotIP           : %s\n", robotIP.c_str ());
	PrintMessage("-- RobotPort         : %d\n", robotPort);
	PrintMessage("\n");

	this->parameter = parameter;

	return API_SUCCESS;
}

int DasaRobot_TetraPanTilt::GetParameter(Property &parameter)
{
	parameter = this->parameter;
	return API_SUCCESS;
}

int DasaRobot_TetraPanTilt::StartHoming(void)
{
	vector<double> position(2);
	vector<unsigned long> time;

	position[0] = position[1] = 0.0;

	return SetPosition (position, time);
}

int DasaRobot_TetraPanTilt::Stop(void)
{
	return API_NOT_SUPPORTED;
}

int DasaRobot_TetraPanTilt::EmergencyStop(void)
{
	return API_NOT_SUPPORTED;
}

int DasaRobot_TetraPanTilt::SetPower(vector<double> power, vector<unsigned long> time)
{
	return API_NOT_SUPPORTED;
}

int DasaRobot_TetraPanTilt::GetPower(vector<double> &power)
{
	return API_NOT_SUPPORTED;
}

int DasaRobot_TetraPanTilt::SetVelocity(vector<double> velocity, vector<unsigned long> time)
{
	return API_NOT_SUPPORTED;
}

int DasaRobot_TetraPanTilt::GetVelocity(vector<double> &velocity)
{
	return API_NOT_SUPPORTED;
}

int DasaRobot_TetraPanTilt::SetPosition(vector<double> position, vector<unsigned long> time)
{
	if(position.size() != 2) {
		return API_ERROR;
	}

	if (position[0] < -90.0 || 90.0 < position[0]) return API_ERROR;
	position[0] = (CENTER_ANGLE + position[0]) / (MAX_ANGLE / MAX_STEP);
	
	if (position[1] < -45 || 90 < position[1]) return API_ERROR;
	position[1] = ((CENTER_ANGLE + position[1]) / (MAX_ANGLE / MAX_STEP)) - 4.;
	
	for(size_t i = 0; i < position.size(); i++) {
		if(position[i] < 0.0 || position[i] > 1023.0) {
			return API_ERROR;
		}

		if (SetServoPosition ((int)i, (int)position[i]) == false) {
			return API_ERROR;
		}
	}

	return API_SUCCESS;
}

int DasaRobot_TetraPanTilt::GetPosition(vector<double> &position)
{
	int step;

	position.resize(2);

	if (GetServoPosition (0, &step) == false) {
		return API_ERROR;
	}
	position[0] = ((double)step * (MAX_ANGLE / MAX_STEP)) - CENTER_ANGLE;
	
	if (GetServoPosition (1, &step) == false) {
		return API_ERROR;
	}
	position[1] = ((double)step * (MAX_ANGLE / MAX_STEP)) - CENTER_ANGLE;

	return API_SUCCESS;
}

bool DasaRobot_TetraPanTilt::PowerDown (int servoID) 
{
	bool ret = false;
	dsphal_tcp_client_t *tcp_client;

	if ((tcp_client = dsphal_tcp_client_create ((char *)robotIP.c_str (), robotPort)) == NULL) {
		printf ("ERROR : can't create client to Tetra\n");
		return false;
	}

	if (0 <= dsphal_tcp_client_connect (tcp_client)) {
		dsphal_datalist_t *datalist_arg = dsphal_build_root_datalist((char *)"[{i}]", servoID);
		if (datalist_arg) {
			dsphal_datalist_t *datalist_ret = dsphal_request_method_call(tcp_client, (char *)"PowerDownServo", datalist_arg);
			if (datalist_ret) {
				dsphal_decompose_root_datalist(datalist_ret, (char *)"[{i}]", &ret);
				dsphal_datalist_destroy(datalist_ret);
				ret = true;
			}
			else {
				ret = false;
			}
			dsphal_datalist_destroy(datalist_arg);
		}
		else {
			printf ("ERROR : datalist_arg is NULL\n");
			ret = false;
		}
	}
	else {
		printf ("ERROR : can't connect to Tetra\n");
		ret = false;
	}

	dsphal_tcp_client_destroy(tcp_client);

	return ret;
}

bool DasaRobot_TetraPanTilt::SetServoPosition (int servoID, int position)
{
	bool ret = false;
	dsphal_tcp_client_t *tcp_client;

	if ((tcp_client = dsphal_tcp_client_create ((char *)robotIP.c_str (), robotPort)) == NULL) {
		printf ("ERROR : can't create client to Tetra\n");
		return false;
	}

	if (0 <= dsphal_tcp_client_connect (tcp_client)) {
		dsphal_datalist_t *datalist_arg = dsphal_build_root_datalist((char *)"[{i}{i}]", servoID, position);
		if (datalist_arg) {
			dsphal_datalist_t *datalist_ret = dsphal_request_method_call(tcp_client, (char *)"SetServoPosition", datalist_arg);
			if (datalist_ret) {
				dsphal_decompose_root_datalist(datalist_ret, (char *)"[{i}]", &ret);
				dsphal_datalist_destroy(datalist_ret);
				ret = true;
			}
			else {
				ret = false;
			}
			dsphal_datalist_destroy(datalist_arg);
		}
		else {
			printf ("ERROR : datalist_arg is NULL\n");
			ret = false;
		}
	}
	else {
		printf ("ERROR : can't connect to Tetra\n");
		ret = false;
	}

	dsphal_tcp_client_destroy(tcp_client);

	return ret;
}

bool DasaRobot_TetraPanTilt::GetServoPosition (int servoID, int *position)
{
	bool ret = false;
	dsphal_tcp_client_t *tcp_client;

	if ((tcp_client = dsphal_tcp_client_create ((char *)robotIP.c_str (), robotPort)) == NULL) {
		printf ("ERROR : can't create client to Tetra\n");
		return false;
	}

	if (0 <= dsphal_tcp_client_connect (tcp_client)) {
		dsphal_datalist_t *datalist_arg = dsphal_build_root_datalist((char *)"[{i}]", servoID);
		if (datalist_arg) {
			dsphal_datalist_t *datalist_ret = dsphal_request_method_call(tcp_client, (char *)"GetServoPosition", datalist_arg);
			if (datalist_ret) {
				dsphal_decompose_root_datalist(datalist_ret, (char *)"[{i}]", position);
				dsphal_datalist_destroy(datalist_ret);
				ret = true;
			}
			else {
				ret = false;
			}
			dsphal_datalist_destroy(datalist_arg);
		}
		else {
			printf ("ERROR : datalist_arg is NULL\n");
			ret = false;
		}
	}
	else {
		printf ("ERROR : can't connect to Tetra\n");
		ret = false;
	}

	dsphal_tcp_client_destroy(tcp_client);

	return ret;
}

bool DasaRobot_TetraPanTilt::SetServoSpeed (int servoID, int speed)
{
	bool ret = false;
	dsphal_tcp_client_t *tcp_client;

	if ((tcp_client = dsphal_tcp_client_create ((char *)robotIP.c_str (), robotPort)) == NULL) {
		printf ("ERROR : can't create client to Tetra\n");
		return false;
	}

	if (0 <= dsphal_tcp_client_connect (tcp_client)) {
		dsphal_datalist_t *datalist_arg = dsphal_build_root_datalist((char *)"[{i}{i}]", servoID, speed);
		if (datalist_arg) {
			dsphal_datalist_t *datalist_ret = dsphal_request_method_call(tcp_client, (char *)"SetServoSpeed", datalist_arg);
			if (datalist_ret) {
				dsphal_decompose_root_datalist(datalist_ret, (char *)"[{i}]", &ret);
				dsphal_datalist_destroy(datalist_ret);
				ret = true;
			}
			else {
				ret = false;
			}
			dsphal_datalist_destroy(datalist_arg);
		}
		else {
			printf ("ERROR : datalist_arg is NULL\n");
			ret = false;
		}
	}
	else {
		printf ("ERROR : can't connect to Tetra\n");
		ret = false;
	}

	dsphal_tcp_client_destroy(tcp_client);

	return ret;
}

#if !defined(DEVICE_TEST)
#if defined(WIN32)
extern "C"
{
	__declspec(dllexport) OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new DasaRobot_TetraPanTilt();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new DasaRobot_TetraPanTilt();
}

#endif
#endif