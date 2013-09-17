/*************************************************************

 file: YujinRobot_iRobiQTouch.cpp
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

#include "YujinRobot_iRobiQTouch.h"
#include "OprosPrintMessage.h"

YujinRobot_iRobiQTouch::YujinRobot_iRobiQTouch(void)
{
	touch = NULL;
}

YujinRobot_iRobiQTouch::~YujinRobot_iRobiQTouch(void)
{
	Finalize();
}

int YujinRobot_iRobiQTouch::Initialize(Property parameter)
{
	if(SetParameter(parameter) == API_ERROR) {
		return API_ERROR;
	}

	if(touch != NULL) {
		delete touch;
	}
	touch = new iRobiQTouch();

	if(touch->iRobiQ_Initialize() == false) {
		Finalize();
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQTouch::Finalize(void)
{
	Disable();

	if(touch != NULL) {
		touch->iRobiQ_Finalize();
		delete touch;
		touch = NULL;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQTouch::Enable(void)
{
	if(touch == NULL) {
		return API_ERROR;
	}

	if(touch->iRobiQ_Connect(ip, port, serviceId) == false) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQTouch::Disable(void)
{
	if(touch == NULL) {
		return API_ERROR;
	}

	if(touch->iRobiQ_Disconnect() == false) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int YujinRobot_iRobiQTouch::SetParameter(Property parameter)
{
	if(parameter.FindName("Size") == false)				return API_ERROR;
	int size = atoi(parameter.GetValue("Size").c_str());

	if(size < 0) {
		return API_ERROR;
	}

	char name[128];
	for(int i = 0; i < size; i++) {
		sprintf(name, "X%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQTouch_SetParameter;
		
		sprintf(name, "Y%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQTouch_SetParameter;
		
		sprintf(name, "Z%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQTouch_SetParameter;
		
		sprintf(name, "Roll%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQTouch_SetParameter;
		
		sprintf(name, "Pitch%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQTouch_SetParameter;
		
		sprintf(name, "Yaw%d", i);
		if(parameter.FindName(string(name)) == false)			goto ERROR_YujinRobot_iRobiQTouch_SetParameter;
	}

	this->parameter = parameter;

	return API_SUCCESS;

ERROR_YujinRobot_iRobiQTouch_SetParameter :
	PrintMessage("ERROR : YujinRobot_iRobiQTouch::SetParameter() -> Can't find a property in parameter.\n");
	return API_ERROR;
}

int YujinRobot_iRobiQTouch::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int YujinRobot_iRobiQTouch::GetTouchSensorData(vector<bool> &touchSensorData)
{
	if(touch == NULL) {
		touchSensorData.resize(0);
		return API_ERROR;
	}

	if(touch->iRobiQ_GetTouchSensorData(touchSensorData) == false) {
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
	return new YujinRobot_iRobiQTouch();
}
#else
extern "C"
{
	OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new YujinRobot_iRobiQTouch();
}

#endif
#endif
