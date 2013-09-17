/*************************************************************

 file: Kvaser_CAN.cpp
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

#include "Kvaser_CAN.h"
#include "OprosLock.h"
#include "canlib.h"

#include "OprosPrintMessage.h"

#if defined(WIN32)
#pragma comment (lib,"./windows/canlib32.lib") 
#endif

class KvaserCANInfo
{
public:
	KvaserCANInfo(void)
	{
		nOpened = 0;
		handle = -1;
	};
	virtual ~KvaserCANInfo(void) { };

public:
	int handle;
	int nOpened;

	unsigned long timeOut;
	unsigned long bitRate;
	long acceptanceMask;
	long acceptanceCode;
	unsigned int mode;

	OprosLock lock;
};

static vector<KvaserCANInfo> canInfo;
static int nInitialized = 0;

Kvaser_CAN::Kvaser_CAN(void)
{
	int nChannel;

	if(nInitialized++ == 0) {
		canInitializeLibrary();
		canStatus status = canGetNumberOfChannels(&nChannel);
		if(status == canOK) {
			PrintMessage("INFO : Kvaser_CAN::Kvaser_CAN() -> The number of channels is %d\n", nChannel);
			canInfo.resize(nChannel);
		}
	}

	channel = -1;
	isOpened = false;
}

Kvaser_CAN::~Kvaser_CAN(void)
{
	Finalize();

	if(--nInitialized == 0) {
#if defined(WIN32)
		canUnloadLibrary();
#endif
	}
}

int Kvaser_CAN::Initialize(Property parameter)
{
	if(SetParameter(parameter) == API_ERROR) {
		PrintMessage("ERROR : Kvaser_CAN::Initialize() -> Occur a error in InitializeCAN().\n");
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Kvaser_CAN::Finalize(void)
{
	return Disable();
}

int Kvaser_CAN::Enable(void)
{
	if(channel < 0 || channel >= (int)canInfo.size()) {
		PrintMessage("ERROR : Kvaser_CAN::Enable() -> The channel number is not available, Channel : %d.\n", channel);
		return API_ERROR;
	}

	if(isOpened == true) {
		return API_SUCCESS;
	}

	if(canInfo[channel].nOpened > 0) {
		canInfo[channel].nOpened++;
		isOpened = true;
		return API_SUCCESS;
	}

	if(OpenKvaserCAN() < 0) {
		PrintMessage("ERROR : Kvaser_CAN::Enable() -> Occur a error in OpenKvaserCAN()..\n");
		return API_ERROR;
	}

	isOpened = true;
	canInfo[channel].nOpened++;

	return API_SUCCESS;
}

int Kvaser_CAN::Disable(void)
{
	if(channel < 0 || channel >= (int)canInfo.size()) {
		PrintMessage("ERROR : Kvaser_CAN::Disable() -> The channel number is not available, Channel : %d.\n", channel);
		return API_ERROR;
	}

	if(isOpened == false) {
		return API_SUCCESS;
	}

	if(--canInfo[channel].nOpened == 0) {
		if(CloseKvaserCAN() < 0) {
			return API_ERROR;
		}
	}

	return API_SUCCESS;
}

int Kvaser_CAN::SetParameter(Property parameter)
{
	if(parameter.FindName("Channel") == false)				return API_ERROR;
	channel = atoi(parameter.GetValue("Channel").c_str());

	if(channel < 0 || channel >= (int)canInfo.size()) {
		PrintMessage("ERROR : Kvaser_CAN::SetParameter() -> The channel number is not available, Channel : %d.\n", channel);
		return API_ERROR;
	}

	if(parameter.FindName("TimeOut") == false)				return API_ERROR;
	canInfo[channel].timeOut = atol(parameter.GetValue("TimeOut").c_str());
	
	if(parameter.FindName("BitRate") == false)				return API_ERROR;
	canInfo[channel].bitRate = atol(parameter.GetValue("BitRate").c_str());
	
	if(parameter.FindName("AcceptanceMask") == false)		return API_ERROR;
	canInfo[channel].acceptanceMask = atol(parameter.GetValue("AcceptanceMask").c_str());
	
	if(parameter.FindName("AcceptanceCode") == false)		return API_ERROR;
	canInfo[channel].acceptanceCode = atol(parameter.GetValue("AcceptanceCode").c_str());
	
	if(parameter.FindName("Mode") == false)					return API_ERROR;
	canInfo[channel].mode = atoi(parameter.GetValue("Mode").c_str());
	
	if(canInfo[channel].mode == 0)	canInfo[channel].mode = canMSG_STD;
	else							canInfo[channel].mode = canMSG_EXT;

	this->parameter = parameter;

	return API_SUCCESS;
}

int Kvaser_CAN::GetParameter(Property &parameter)
{
	parameter = this->parameter;
	return API_SUCCESS;
}

int Kvaser_CAN::Lock(void)
{
	if(channel < 0 || channel >= (int)canInfo.size()) {
		PrintMessage("ERROR : Kvaser_CAN::Lock() -> The channel number is not available, Channel : %d.\n", channel);
		return API_ERROR;
	}

	canInfo[channel].lock.Lock();

	return API_SUCCESS;
}

int Kvaser_CAN::Unlock(void)
{
	if(channel < 0 || channel >= (int)canInfo.size()) {
		PrintMessage("ERROR : Kvaser_CAN::Unlock() -> The channel number is not available, Channel : %d.\n", channel);
		return API_ERROR;
	}

	canInfo[channel].lock.Unlock();

	return API_SUCCESS;
}

int Kvaser_CAN::Write(long id, unsigned char *data, int size)
{
	return WriteKvaserCAN(id, data, size);
}

int Kvaser_CAN::Read(long &id, unsigned char *data, int size)
{
	return ReadKvaserCAN(id, data);
}

int Kvaser_CAN::OpenKvaserCAN(void)
{
	if(channel < 0 || channel >= (int)canInfo.size()) {
		PrintMessage("ERROR : Kvaser_CAN::OpenKvaserCAN() -> The channel number is not available, Channel : %d.\n", channel);
		return -1;
	}

	canInfo[channel].handle = canOpenChannel(channel, canOPEN_EXCLUSIVE);
	if(canInfo[channel].handle < 0) {
		PrintMessage("ERROR : Kvaser_CAN::OpenKvaserCAN() -> Occur a error in canOpenChannel().\n");
		goto OPEN_KVASER_CAN_ERROR;
	}

	unsigned long bitRate;
#if defined(WIN32)
	switch(canInfo[channel].bitRate) {
		case 1000000 :	bitRate = canBITRATE_1M;	break;
		case 500000 :	bitRate = canBITRATE_500K;	break;
		case 250000 :	bitRate = canBITRATE_250K;	break;
		case 125000 :	bitRate = canBITRATE_125K;	break;
		case 100000 :	bitRate = canBITRATE_100K;	break;
		case 50000 :	bitRate = canBITRATE_50K;	break;
		case 10000 :	bitRate = canBITRATE_10K;	break;
		default :		goto OPEN_KVASER_CAN_ERROR;
	}
#else
	switch(canInfo[channel].bitRate) {
		case 1000000 :	bitRate = BAUD_1M;		break;
		case 500000 :	bitRate = BAUD_500K;	break;
		case 250000 :	bitRate = BAUD_250K;	break;
		case 125000 :	bitRate = BAUD_125K;	break;
		case 100000 :	bitRate = BAUD_100K;	break;
		case 50000 :	bitRate = BAUD_50K;		break;
		default :		goto OPEN_KVASER_CAN_ERROR;
	}
#endif

	if(canSetBusParams(canInfo[channel].handle, bitRate, 4, 4, 1, 3, 0) != canOK) {
		PrintMessage("ERROR : Kvaser_CAN::OpenKvaserCAN() -> Occur a error in canSetBusParams().\n");
		goto OPEN_KVASER_CAN_ERROR;
	}

	if(canSetBusOutputControl(canInfo[channel].handle, canDRIVER_NORMAL) != canOK) {
		PrintMessage("ERROR : Kvaser_CAN::OpenKvaserCAN() -> Occur a error in canSetBusOutputControl().\n");
		goto OPEN_KVASER_CAN_ERROR;
	}

	if(canBusOn(canInfo[channel].handle) != canOK) {
		PrintMessage("ERROR : Kvaser_CAN::OpenKvaserCAN() -> Occur a error in canBusOn().\n");
		goto OPEN_KVASER_CAN_ERROR;
	}

	return API_SUCCESS;

OPEN_KVASER_CAN_ERROR :
	canBusOff(canInfo[channel].handle);
	canClose(canInfo[channel].handle);
	return -1;
}

int Kvaser_CAN::CloseKvaserCAN(void)
{
	if(channel < 0 || channel >= (int)canInfo.size()) {
		PrintMessage("ERROR : Kvaser_CAN::CloseKvaserCAN() -> The channel number is not available, Channel : %d.\n", channel);
		return API_ERROR;
	}

	if(canBusOff(canInfo[channel].handle) != canOK) {
		return -1;
	}

	if(canClose(canInfo[channel].handle) != canOK) {
		return -1;
	}

	return 0;
}

int Kvaser_CAN::WriteKvaserCAN(long id, unsigned char *data, int size)
{
	if(channel < 0 || channel >= (int)canInfo.size()) {
		PrintMessage("ERROR : Kvaser_CAN::WriteKvaserCAN() -> The channel number is not available, Channel : %d.\n", channel);
		return API_ERROR;
	}

	if(canWriteWait(canInfo[channel].handle, id, (void *)data, size, canInfo[channel].mode, canInfo[channel].timeOut) != canOK) {
		canResetBus(canInfo[channel].handle);
#if defined(WIN32)
		canFlushTransmitQueue(canInfo[channel].handle);
#endif
		return -1;
	}

	return size;
}

int Kvaser_CAN::ReadKvaserCAN(long &id, unsigned char *data)
{
	if(channel < 0 || channel >= (int)canInfo.size()) {
		PrintMessage("ERROR : Kvaser_CAN::ReadKvaserCAN() -> The channel number is not available, Channel : %d.\n", channel);
		return API_ERROR;
	}

	unsigned int size;
	unsigned int flag;
	unsigned long time;
	canStatus ret;

	ret = canReadWait(canInfo[channel].handle, &id, (void *)data, &size, &flag, &time, canInfo[channel].timeOut);

	if(ret != canOK) {
		return -1;
	}

	return size;
}

#if defined(WIN32)
extern "C"
{
__declspec(dllexport) OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new Kvaser_CAN();
}
#endif