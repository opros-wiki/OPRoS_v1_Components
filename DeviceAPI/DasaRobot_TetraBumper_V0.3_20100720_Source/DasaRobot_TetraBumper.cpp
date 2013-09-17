/*************************************************************

 file: DasaRobot_TetraBumper.cpp
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
#include "DasaRobot_TetraBumper.h"
#include "OprosPrintMessage.h"

#define BUMPER_MAX_SIZE			8


DasaRobot_TetraBumper::DasaRobot_TetraBumper(void)
{

}

DasaRobot_TetraBumper::~DasaRobot_TetraBumper(void)
{

}

int DasaRobot_TetraBumper::Initialize(Property parameter)
{
	if (SetParameter(parameter) == API_ERROR) {
		PrintMessage("DasaRobot_TetraBumper::Initialize() ERROR -> SetParameter()\n");
		return API_ERROR;
	}

	return API_SUCCESS;
}

int DasaRobot_TetraBumper::Finalize(void)
{
	return API_SUCCESS;
}

int DasaRobot_TetraBumper::Enable(void)
{
	return API_SUCCESS;
}

int DasaRobot_TetraBumper::Disable(void)
{
	return API_SUCCESS;
}

int DasaRobot_TetraBumper::SetParameter(Property parameter)
{
	if (parameter.FindName("Size") == false) return API_ERROR;
	if (parameter.FindName("RobotIP") == false) return API_ERROR;
	if (parameter.FindName("RobotPort") == false) return API_ERROR;
	
	bumperCount = atoi (parameter.GetValue("Size").c_str());
	robotIP = parameter.GetValue("RobotIP");
	robotPort = atoi (parameter.GetValue("RobotPort").c_str());

	PrintMessage("-- DasaRobot_TetraBumper Parameter\n");
	PrintMessage("-- Size              : %d\n", bumperCount);
	PrintMessage("-- RobotIP           : %s\n", robotIP.c_str ());
	PrintMessage("-- RobotPort         : %d\n", robotPort);
	PrintMessage("\n");

	this->parameter = parameter;

	return API_SUCCESS;
}

int DasaRobot_TetraBumper::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int DasaRobot_TetraBumper::GetBumperSensorData(vector<bool> &bumperSensorData)
{
	int size;
	bumperSensorData.resize(BUMPER_MAX_SIZE);
	
	if (!ReadBumperArray ((bool *)&bumperSensorData[0], size)) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

bool DasaRobot_TetraBumper::ReadBumperArray (bool *bumperValue, int &bumperSize)
{
	bool ret = false;
	dsphal_tcp_client_t *tcp_client;

	if ((tcp_client = dsphal_tcp_client_create((char *)robotIP.c_str (), robotPort)) == NULL) {
		printf ("ERROR : can't create client to Tetra\n");
		return false;
	}

	if (0 <= dsphal_tcp_client_connect(tcp_client)) {
		dsphal_datalist_t *datalist_ret = dsphal_request_method_call(tcp_client, (char *)"ReadBumperArray", NULL);
		if (datalist_ret) {
			int bumper_val[BUMPER_MAX_SIZE];
			dsphal_decompose_root_datalist(datalist_ret, (char *)"[{i}{i}{i}{i}{i}{i}{i}{i}]",
				&bumper_val[0],
				&bumper_val[1],
				&bumper_val[2],
				&bumper_val[3],
				&bumper_val[4],
				&bumper_val[5],
				&bumper_val[6],
				&bumper_val[7]);

			if (bumperValue) {
				int count = 0;
				for (int i = 0; i < bumperSize && i < BUMPER_MAX_SIZE; i++) {
					bumperValue[i] = (bumper_val[i] ? true : false);
					++count;
				}
				bumperSize = count;
			}
			else {
				bumperSize = 0;
			}

			dsphal_datalist_destroy(datalist_ret);
			ret = true;
		}
		else {
			printf ("ERROR : datalist_ret is NULL\n");
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

void DasaRobot_TetraBumper::SetBumperDirMode ()
{
	dsphal_tcp_client_t *tcp_client;

	if ((tcp_client = dsphal_tcp_client_create((char *)robotIP.c_str (), robotPort)) == NULL) {
		printf ("ERROR : can't create client to Tetra\n");
		return;
	}

	if (0 <= dsphal_tcp_client_connect(tcp_client)) {
		dsphal_request_method_call(tcp_client, (char *)"SetBumperDirMode", NULL);
	}
	else {
		printf ("ERROR : can't connect to Tetra\n");
	}

	dsphal_tcp_client_destroy(tcp_client);
}

void DasaRobot_TetraBumper::SetBumperOffMode ()
{
	dsphal_tcp_client_t *tcp_client;

	if ((tcp_client = dsphal_tcp_client_create((char *)robotIP.c_str (), robotPort)) == NULL) {
		printf ("ERROR : can't create client to Tetra\n");
		return;
	}

	if (0 <= dsphal_tcp_client_connect(tcp_client)) {
		dsphal_request_method_call(tcp_client, (char *)"SetBumperOffMode", NULL);
	}
	else {
		printf ("ERROR : can't connect to Tetra\n");
	}

	dsphal_tcp_client_destroy(tcp_client);
}

#if !defined(DEVICE_TEST)
#if defined(WIN32)
extern "C"
{
	__declspec(dllexport) OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new DasaRobot_TetraBumper();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new DasaRobot_TetraBumper();
}
#endif
#endif