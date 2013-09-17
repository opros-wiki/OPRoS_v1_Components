/*************************************************************

 file: DasaRobot_TetraUltrasonic.cpp
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
#include "DasaRobot_TetraUltrasonic.h"
#include "OprosPrintMessage.h"

#define ULTRA_SONIC_MAX_SIZE	7

DasaRobot_TetraUltrasonic::DasaRobot_TetraUltrasonic(void)
{

}

DasaRobot_TetraUltrasonic::~DasaRobot_TetraUltrasonic(void)
{

}

int DasaRobot_TetraUltrasonic::Initialize(Property parameter)
{
	if(SetParameter(parameter) == API_ERROR) {
		PrintMessage("DasaRobot_TetraUltrasonic::Initialize() ERROR -> SetParameter()\n");
		return API_ERROR;
	}

	return API_SUCCESS;
}

int DasaRobot_TetraUltrasonic::Finalize(void)
{
	return API_SUCCESS;
}

int DasaRobot_TetraUltrasonic::Enable(void)
{
	return API_SUCCESS;
}

int DasaRobot_TetraUltrasonic::Disable(void)
{
	return API_SUCCESS;
}

int DasaRobot_TetraUltrasonic::SetParameter(Property parameter)
{
	if (parameter.FindName("Size") == false) return API_ERROR;
	if (parameter.FindName("RobotIP") == false) return API_ERROR;
	if (parameter.FindName("RobotPort") == false) return API_ERROR;
	
	sensorCount = atoi (parameter.GetValue("Size").c_str());
	robotIP = parameter.GetValue("RobotIP");
	robotPort = atoi (parameter.GetValue("RobotPort").c_str());

	PrintMessage("-- TetraUltrasonic Parameter\n");
	PrintMessage("-- Size              : %d\n", sensorCount);
	PrintMessage("-- RobotIP           : %s\n", robotIP.c_str ());
	PrintMessage("-- RobotPort         : %d\n", robotPort);
	PrintMessage("\n");

	this->parameter = parameter;

	return API_SUCCESS;
}

int DasaRobot_TetraUltrasonic::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int DasaRobot_TetraUltrasonic::GetUltrasonicSensorData(vector<double> &ultrasonicSensorData)
{
	vector<int> tmp;
	tmp.resize(ULTRA_SONIC_MAX_SIZE);
	ultrasonicSensorData.clear();
	int size;

	if (!ReadUltraSonicSensorArray (&tmp[0], size)) {
		return API_ERROR;
	}

	for(size_t i = 0; i < tmp.size(); i++) {
		ultrasonicSensorData.push_back((double)tmp[i] * 0.01);
	}

	return API_SUCCESS;
}

bool DasaRobot_TetraUltrasonic::ReadUltraSonicSensorArray (int sensorValue [], int &sensorSize)
{
	bool ret = false;
	dsphal_tcp_client_t *tcp_client;

	if ((tcp_client = dsphal_tcp_client_create((char *)robotIP.c_str (), robotPort)) == NULL) {
		printf ("ERROR : can't create client to Tetra\n");
		return false;
	}

	if (0 <= dsphal_tcp_client_connect(tcp_client)) {
		dsphal_datalist_t *datalist_ret = dsphal_request_method_call(tcp_client, (char *)"ReadUltraSonicSensorArray", NULL);
		if (datalist_ret) {
			int usonic_sensor_val[ULTRA_SONIC_MAX_SIZE];
			dsphal_decompose_root_datalist(datalist_ret, (char *)"[{i}{i}{i}{i}{i}{i}{i}]",
				&usonic_sensor_val[0],
				&usonic_sensor_val[1],
				&usonic_sensor_val[2],
				&usonic_sensor_val[3],
				&usonic_sensor_val[4],
				&usonic_sensor_val[5],
				&usonic_sensor_val[6]);

			if (sensorValue) {
				int count = 0;
				for (int i = 0; i < sensorSize && i < ULTRA_SONIC_MAX_SIZE; i++) {
					sensorValue[i] = usonic_sensor_val[i];
					++count;
				}
				sensorSize = count;
			}
			else {
				sensorSize = 0;
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

#if !defined(DEVICE_TEST)
#if defined(WIN32)
extern "C"
{
	__declspec(dllexport) OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new DasaRobot_TetraUltrasonic();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new DasaRobot_TetraUltrasonic();
}

#endif
#endif