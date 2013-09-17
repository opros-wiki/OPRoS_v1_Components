/*************************************************************

 file: DasaRobot_TetraIR.cpp
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
#include "DasaRobot_TetraIR.h"
#include "OprosPrintMessage.h"

#define PSD_MAX_SIZE			16


DasaRobot_TetraIR::DasaRobot_TetraIR(void)
{

}

DasaRobot_TetraIR::~DasaRobot_TetraIR(void)
{

}

int DasaRobot_TetraIR::Initialize(Property parameter)
{
	if(SetParameter(parameter) == API_ERROR) {
		PrintMessage("DasaRobot_TetraIR::Initialize() ERROR -> SetParameter()\n");
		return API_ERROR;
	}

	return API_SUCCESS;
}

int DasaRobot_TetraIR::Finalize(void)
{
	return API_SUCCESS;
}

int DasaRobot_TetraIR::Enable(void)
{
	return API_SUCCESS;
}

int DasaRobot_TetraIR::Disable(void)
{
	return API_SUCCESS;
}

int DasaRobot_TetraIR::SetParameter(Property parameter)
{
	if (parameter.FindName("Size") == false) return API_ERROR;
	if (parameter.FindName("RobotIP") == false) return API_ERROR;
	if (parameter.FindName("RobotPort") == false) return API_ERROR;
	
	sensorCount = atoi (parameter.GetValue("Size").c_str());
	robotIP = parameter.GetValue("RobotIP");
	robotPort = atoi (parameter.GetValue("RobotPort").c_str());

	PrintMessage("-- DasaRobot_TetraIR Parameter\n");
	PrintMessage("-- Size              : %d\n", sensorCount);
	PrintMessage("-- RobotIP           : %s\n", robotIP.c_str ());
	PrintMessage("-- RobotPort         : %d\n", robotPort);
	PrintMessage("\n");

	this->parameter = parameter;

	return API_SUCCESS;
}

int DasaRobot_TetraIR::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int DasaRobot_TetraIR::GetInfraredSensorData(vector<double> &infraredSensorData)
{
	vector<int> tmp;
	tmp.resize(PSD_MAX_SIZE);
	infraredSensorData.clear();
	int size;

	if (!ReadPsdSensorArray (&tmp[0], size)) {
		return API_ERROR;
	}

	for(size_t i = 0; i < tmp.size(); i++) {
		infraredSensorData.push_back((double)tmp[i] * 0.01);
	}

	return API_SUCCESS;
}

bool DasaRobot_TetraIR::ReadPsdSensorArray (int sensorValue [], int &sensorSize)
{
	bool ret = false;
	dsphal_tcp_client_t *tcp_client;

	if ((tcp_client = dsphal_tcp_client_create((char *)robotIP.c_str (), robotPort)) == NULL) {
		printf ("ERROR : can't create client to Tetra\n");
		return false;
	}

	if (0 <= dsphal_tcp_client_connect(tcp_client)) {
		dsphal_datalist_t *datalist_ret = dsphal_request_method_call(tcp_client, (char *)"ReadPsdSensorArray", NULL);
		if (datalist_ret) {
			int psd_sensor_val[PSD_MAX_SIZE];
			dsphal_decompose_root_datalist(datalist_ret, (char *)"[{i}{i}{i}{i}{i}{i}{i}{i}{i}{i}{i}{i}{i}{i}{i}{i}]",
				&psd_sensor_val[0],
				&psd_sensor_val[1],
				&psd_sensor_val[2],
				&psd_sensor_val[3],
				&psd_sensor_val[4],
				&psd_sensor_val[5],
				&psd_sensor_val[6],
				&psd_sensor_val[7],
				&psd_sensor_val[8],
				&psd_sensor_val[9],
				&psd_sensor_val[10],
				&psd_sensor_val[11],
				&psd_sensor_val[12],
				&psd_sensor_val[13],
				&psd_sensor_val[14],
				&psd_sensor_val[15]);

			if (sensorValue) {
				int count = 0;
				for (int i = 0; i < sensorSize && i < PSD_MAX_SIZE; i++) {
					sensorValue[i] = psd_sensor_val[i];
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
	return new DasaRobot_TetraIR();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new DasaRobot_TetraIR();
}
#endif
#endif