/*************************************************************

 file: NI_CAN.cpp
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
#include "NI_CAN.h"

#include "OprosPrintMessage.h"
#include "NiCanImpl.h"

using namespace std;

class NICANInfo
{
public:
	NICANInfo(void)
	{
		nOpened = 0;		nInitialized = 0;		timeOut = 0;
		bitRate = 0;		acceptanceCode = 0;		acceptanceMask = 0;		mode = 0;
		can = NULL;
	}
	virtual ~NICANInfo(void)
	{
		if(can != NULL) {
			delete can;
		}
	}

	int nInitialized;
	int nOpened;

	long bitRate;
	long acceptanceCode;
	long acceptanceMask;
	int mode;

	unsigned long timeOut;

	Property parameter;

	NiCanImpl *can;
};

static map<int, NICANInfo> canInfo;

NI_CAN::NI_CAN(void)
{
	_channel = -1;
	_isInitialized = false;
	_isOpened = false;
}

NI_CAN::~NI_CAN(void)
{
	Finalize();

	//	�ʱ�ȭ�� �ڵ��� ������ 0�̸� ä�� ������ ����
	if(canInfo[_channel].nInitialized == 0) {
		delete canInfo[_channel].can;
		canInfo[_channel].can = NULL;
		canInfo.erase(_channel);
	}
}

int NI_CAN::Initialize(Property parameter)
{
	if(SetParameter(parameter) != API_SUCCESS) {
		return API_ERROR;
	}

	//	�ʱ�ȭ�� �ڵ��� ������ ������Ŵ
	if(_isInitialized == false) {
		canInfo[_channel].nInitialized++;
		_isInitialized = true;
	}

	return API_SUCCESS;
}

int NI_CAN::Finalize(void)
{
	//	ä�� ���� ���� Ȯ��
	if(canInfo.find(_channel) == canInfo.end()) {
		return API_ERROR;
	}

	//	Ȱ��ȭ�Ǿ� �ִٸ� ��Ȱ��ȭ ��Ŵ
	Disable();

	//	�ʱ�ȭ�Ǿ� �ִٸ� �ʱ�ȭ ������ ���ҽ�Ű�� �ʱ�ȭ �÷��׸� false�� ����
	if(_isInitialized == true) {
		canInfo[_channel].nInitialized--;
		_isInitialized = false;
	}

	//	��� ������ �ʱ�ȭ
	_channel = -1;
	_isInitialized = false;
	_isOpened = false;

	return API_SUCCESS;
}

int NI_CAN::Enable(void)
{
	if(canInfo.find(_channel) == canInfo.end()) {
		return API_ERROR;
	}

	//	�ʱ�ȭ���� �ʾҴٸ� ���� ��ȯ
	if(_isInitialized == false) {
		return API_ERROR;
	}

	if(_isOpened == true) {
		return API_SUCCESS;
	}

	if(canInfo[_channel].nOpened > 0) {
		canInfo[_channel].nOpened++;
		return API_SUCCESS;
	}

	if(canInfo[_channel].can->Open() < 0) {
		return API_ERROR;
	}

	canInfo[_channel].nOpened++;
	_isOpened = true;

	return API_SUCCESS;
}

int NI_CAN::Disable(void)
{
	if(canInfo.find(_channel) == canInfo.end()) {
		return API_ERROR;
	}

	if(_isOpened == false) {
		return API_ERROR;
	}

	if(canInfo[_channel].nOpened == 1) {
		if(canInfo[_channel].can->Close() < 0) {
			return API_ERROR;
		}
	}
	canInfo[_channel].nOpened--;
	_isOpened = false;

	return API_SUCCESS;
}

int NI_CAN::SetParameter(Property parameter)
{
	//	ä�� ���� ����
	if(parameter.FindName("Channel") == false)			goto ERROR_NI_CAN_SetParameter;
	_channel = atoi(parameter.GetValue("Channel").c_str());
	if(_channel < 0)									goto ERROR_NI_CAN_SetParameter;

	//	�̹� ä�������� �����Ǿ� �ִٸ� ���� ����
	if(canInfo.find(_channel) != canInfo.end()) {
		return API_SUCCESS;
	}

	//	ä�ο� ���� ������ ������ ����
	//	Time Out ����
	if(parameter.FindName("TimeOut") == false)			goto ERROR_NI_CAN_SetParameter;
	canInfo[_channel].timeOut = (unsigned long)atol(parameter.GetValue("TimeOut").c_str());

	if(parameter.FindName("BitRate") == false)			goto ERROR_NI_CAN_SetParameter;	
	canInfo[_channel].bitRate = atol(parameter.GetValue("BitRate").c_str());

	if(parameter.FindName("AcceptanceMask") == false)	goto ERROR_NI_CAN_SetParameter;	
	canInfo[_channel].acceptanceMask = atol(parameter.GetValue("AcceptanceMask").c_str());

	if(parameter.FindName("AcceptanceCode") == false)	goto ERROR_NI_CAN_SetParameter;	
	canInfo[_channel].acceptanceCode = atol(parameter.GetValue("AcceptanceCode").c_str());

	if(parameter.FindName("Mode") == false)				goto ERROR_NI_CAN_SetParameter;	
	canInfo[_channel].mode = atoi(parameter.GetValue("Mode").c_str());

	canInfo[_channel].can = new NiCanImpl(_channel, canInfo[_channel].bitRate,
		canInfo[_channel].acceptanceMask, canInfo[_channel].acceptanceCode, canInfo[_channel].mode, canInfo[_channel].timeOut);

	canInfo[_channel].parameter = parameter;

	return API_SUCCESS;

ERROR_NI_CAN_SetParameter :
	_channel = -1;
	PrintMessage("ERROR : NI_CAN::SetParameter -> Can't find a parameter name\n");
	return API_ERROR;
}

int NI_CAN::GetParameter(Property &parameter)
{
	if(canInfo.find(_channel) == canInfo.end()) {
		return API_ERROR;
	}

	parameter = canInfo[_channel].parameter;

	return API_SUCCESS;
}

int NI_CAN::Lock(void)
{
	if(canInfo.find(_channel) == canInfo.end()) {
		return API_ERROR;
	}

	canInfo[_channel].can->Lock();


	return API_SUCCESS;
}

int NI_CAN::Unlock(void)
{
	if(canInfo.find(_channel) == canInfo.end()) {
		return API_ERROR;
	}

	canInfo[_channel].can->Unlock();

	return API_SUCCESS;
}

int NI_CAN::Write(long id, unsigned char *data, int size)
{
	if(canInfo.find(_channel) == canInfo.end()) {
		return API_ERROR;
	}

	if(_isOpened == false) {
		return API_ERROR;
	}

	int ret;
	if(ret = canInfo[_channel].can->Write(id, data, size) < 0) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int NI_CAN::Read(long &id, unsigned char *data, int size)
{
	if(canInfo.find(_channel) == canInfo.end()) {
		return API_ERROR;
	}

	if(_isOpened == false) {
		return API_ERROR;
	}

	int ret;
	if(ret = canInfo[_channel].can->Read(id, data, size) < 0) {
		return API_ERROR;
	}

	return ret;
}

#if defined(WIN32)
extern "C"
{
__declspec(dllexport) OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new NI_CAN();
}
#endif
