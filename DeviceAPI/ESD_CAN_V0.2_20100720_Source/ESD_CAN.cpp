/*************************************************************

 file: ESD_CAN.cpp
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

#include "ESD_CAN.h"
#include "OprosLock.h"
#include "ESD_CAN_Impl.h"

class ESDCANInfo
{
public:
	ESDCANInfo(int channel, long bitRate, long acceptanceMask, long acceptanceCode, bool isExtended, long timeOut)
	{
		handle = new ESD_CAN_Impl(channel, bitRate, acceptanceMask, acceptanceCode, isExtended, timeOut);
		nHandle = 0;
		nOpened = 0;
	}
	virtual ~ESDCANInfo(void)
	{
		delete handle;
	}

	int nHandle;
	int nOpened;

	OprosLock lock;

	int Open(void)	{	return handle->Open();	}
	int Close(void)	{	return handle->Close();	}
	int Write(long id, unsigned char *data, int size)	{	return handle->Write(id, data, size);	}
	int Read(long *id, unsigned char *data, int size)	{	return handle->Read(id, data, size);	}

private:
	ESD_CAN_Impl *handle;
};

static map<int, ESDCANInfo *> canInfo;

ESD_CAN::ESD_CAN(void)
{
	channel = -1;

	isInitialized = false;
	isOpened = false;
}

ESD_CAN::~ESD_CAN(void)
{
	Finalize();
}

int ESD_CAN::Initialize(Property parameter)
{
	if(isInitialized == true) {
		return API_SUCCESS;
	}

	if(parameter.FindName("Channel") == false)			return API_ERROR;
	channel = atoi(parameter.GetValue("Channel").c_str());

	if(channel < 0) {
		return API_ERROR;
	}

	if(canInfo.find(channel) != canInfo.end()) {
		canInfo[channel]->nHandle++;
		isInitialized = true;
		return API_SUCCESS;
	}

	if(parameter.FindName("TimeOut") == false)			return API_ERROR;
	long timeOut = atol(parameter.GetValue("TimeOut").c_str());
	if(parameter.FindName("BitRate") == false)			return API_ERROR;
	long bitRate = atol(parameter.GetValue("BitRate").c_str());
	if(parameter.FindName("AcceptanceMask") == false)			return API_ERROR;
	long acceptanceMask = atol(parameter.GetValue("AcceptanceMask").c_str());
	if(parameter.FindName("AcceptanceCode") == false)			return API_ERROR;
	long acceptanceCode = atol(parameter.GetValue("AcceptanceCode").c_str());
	if(parameter.FindName("Mode") == false)			return API_ERROR;
	bool isExtended = true;
	if(atoi(parameter.GetValue("Mode").c_str()) == 0) {
		isExtended = false;
	}

	ESDCANInfo *tmp = new ESDCANInfo(channel, bitRate, acceptanceMask, acceptanceCode, isExtended, timeOut);
	canInfo[channel] = tmp;
	canInfo[channel]->nHandle++;

	isInitialized = true;

	return API_SUCCESS;
}

int ESD_CAN::Finalize(void)
{
	if(isInitialized == false) {
		return API_SUCCESS;
	}

	if(channel < 0) {
		return API_SUCCESS;
	}

	Disable();

	if(--canInfo[channel]->nHandle == 0) {
		delete canInfo[channel];
		canInfo.erase(channel);
	}

	channel = -1;
	isInitialized = false;

	return API_SUCCESS;
}

int ESD_CAN::Enable(void)
{
	if(channel < 0) {
		return API_ERROR;
	}

	if(canInfo.find(channel) == canInfo.end()) {
		return API_ERROR;
	}

	if(canInfo[channel]->nOpened > 0) {
		canInfo[channel]->nOpened++;
		isOpened = true;
		return API_SUCCESS;
	}

	if(canInfo[channel]->Open() < 0) {
		return API_ERROR;
	}
	
	canInfo[channel]->nOpened++;
	isOpened = true;

	return API_SUCCESS;
}

int ESD_CAN::Disable(void)
{
	if(isOpened == false) {
		return API_SUCCESS;
	}

	if(canInfo.find(channel) != canInfo.end()) {
		return API_ERROR;
	}

	if(--canInfo[channel]->nOpened == 0) {
		
	}

	isOpened = false;

	return API_SUCCESS;
}

int ESD_CAN::SetParameter(Property parameter)
{
	return API_NOT_SUPPORTED;
}

int ESD_CAN::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int ESD_CAN::Lock(void)
{
	if(canInfo.find(channel) == canInfo.end()) {
		return API_ERROR;
	}

	canInfo[channel]->lock.Lock();

	return API_SUCCESS;
}

int ESD_CAN::Unlock(void)
{
	if(canInfo.find(channel) == canInfo.end()) {
		return API_ERROR;
	}

	canInfo[channel]->lock.Unlock();

	return API_SUCCESS;
}

int ESD_CAN::Write(long id, unsigned char *data, int size)
{
	if(canInfo.find(channel) == canInfo.end()) {
		return API_ERROR;
	}

	if(canInfo[channel]->Write(id, data, size) < 0) {
		return API_ERROR;
	}

	return size;
}

int ESD_CAN::Read(long &id, unsigned char *data, int size)
{
	if(canInfo.find(channel) == canInfo.end()) {
		return API_ERROR;
	}

	int ret = canInfo[channel]->Read(&id, data, size);
	if(ret < 0) {
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
	return new ESD_CAN();
}
#endif