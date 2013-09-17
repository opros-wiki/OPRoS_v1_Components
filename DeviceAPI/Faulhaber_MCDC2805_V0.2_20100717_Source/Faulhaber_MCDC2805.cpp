/*************************************************************

 file: Faulhaber_MCDC2805.cpp
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

#include "Faulhaber_MCDC2805.h"

#include "OprosTimer.h"
#include "OprosPrintMessage.h"

#define	MCDC2805_MAX_DATA_LEN		(64)
#define	ASCII_LF					(10)
#define	ASCII_CR					(13)
#define	MCDC2805_DELAY				(100)

Faulhaber_MCDC2805::Faulhaber_MCDC2805(void)
{
	_uart = NULL;
	hOprosAPI = NULL;
}

Faulhaber_MCDC2805::~Faulhaber_MCDC2805(void)
{
	Finalize();
}

int Faulhaber_MCDC2805::Initialize(Property parameter)
{
	if(InitializeUART(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : Faulhaber_MCDC2805::Initialize() -> Occur a error in InitializeUART().\n");
		return API_ERROR;
	}

	if(SetParameter(parameter) < 0) {
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Faulhaber_MCDC2805::Finalize(void)
{
	Disable();

	if(_uart != NULL) {
		delete _uart;
		_uart = NULL;
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

int Faulhaber_MCDC2805::Enable(void)
{
	if(MCDC2805_EnDrive() < 0) {
		PrintMessage("ERROR : Faulhaber_MCDC2805::Enable() -> Occur a error in MCDC2805_EnDrive().\n");
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Faulhaber_MCDC2805::Disable(void)
{
	if(MCDC2805_DiDrive() < 0) {
		PrintMessage("ERROR : Faulhaber_MCDC2805::Disable() -> Occur a error in MCDC2805_DiDrive().\n");
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Faulhaber_MCDC2805::SetParameter(Property parameter)
{
	if(parameter.FindName("MaximumPower") == false)				goto ERROR_Faulhaber_MCDC2805_SetParameter;
	_profile.maximumPower = atof(parameter.GetValue("MaximumPower").c_str());

	if(parameter.FindName("LinePerRevolution") == false)		goto ERROR_Faulhaber_MCDC2805_SetParameter;
	_profile.linePerRevolution = atof(parameter.GetValue("LinePerRevolution").c_str());

	if(parameter.FindName("ReductionRatio") == false)			goto ERROR_Faulhaber_MCDC2805_SetParameter;
	_profile.reductionRatio = atof(parameter.GetValue("ReductionRatio").c_str());

	if(parameter.FindName("MaximumVelocity") == false)			goto ERROR_Faulhaber_MCDC2805_SetParameter;
	_profile.maximumVelocity = atof(parameter.GetValue("MaximumVelocity").c_str());

	if(parameter.FindName("Acceleration") == false)				goto ERROR_Faulhaber_MCDC2805_SetParameter;
	_profile.acceleration = atof(parameter.GetValue("Acceleration").c_str());

	if(parameter.FindName("MinimumPositionLimit") == false)		goto ERROR_Faulhaber_MCDC2805_SetParameter;
	_profile.minimumPositionLimit = atof(parameter.GetValue("MinimumPositionLimit").c_str());

	if(parameter.FindName("MaximumPositionLimit") == false)		goto ERROR_Faulhaber_MCDC2805_SetParameter;
	_profile.maximumPositionLimit = atof(parameter.GetValue("MaximumPositionLimit").c_str());

	if(MCDC2805_SetPickCur((unsigned short)(_profile.maximumPower * 2.0)) < 0) {
		PrintMessage("ERROR : Faulhaber_MCDC2805::SetParameter() -> Occur a error in MCDC2805_SetPickCur().\n");
		return API_ERROR;
	}

	if(MCDC2805_SetContCur((unsigned short)(_profile.maximumPower)) < 0) {
		PrintMessage("ERROR : Faulhaber_MCDC2805::SetParameter() -> Occur a error in MCDC2805_SetContCur().\n");
		return API_ERROR;
	}

	if(MCDC2805_SetEncRes((unsigned short)(_profile.linePerRevolution)) < 0) {
		PrintMessage("ERROR : Faulhaber_MCDC2805::SetParameter() -> Occur a error in MCDC2805_SetEncRes().\n");
		return API_ERROR;
	}

	if(MCDC2805_SetMaxSpeed((unsigned short)(_profile.maximumVelocity * 60 * _profile.reductionRatio / 360.0)) < 0) {
		PrintMessage("ERROR : Faulhaber_MCDC2805::SetParameter() -> Occur a error in MCDC2805_SetMaxSpeed().\n");
		return API_ERROR;
	}

	if(MCDC2805_SetAccel((unsigned short)(_profile.acceleration * 60.0 * _profile.reductionRatio / 360.0)) < 0) {
		PrintMessage("ERROR : Faulhaber_MCDC2805::SetParameter() -> Occur a error in MCDC2805_SetAccel().\n");
		return API_ERROR;
	}

	if(MCDC2805_SetNegativeLimit((long)(_profile.minimumPositionLimit * (_profile.linePerRevolution * _profile.reductionRatio) / 360.0)) < 0) {
		PrintMessage("ERROR : Faulhaber_MCDC2805::SetParameter() -> Occur a error in MCDC2805_SetNegativeLimit().\n");
		return API_ERROR;
	}

	if(MCDC2805_SetPositiveLimit((long)(_profile.maximumPositionLimit * (_profile.linePerRevolution * _profile.reductionRatio) / 360.0)) < 0) {
		PrintMessage("ERROR : Faulhaber_MCDC2805::SetParameter() -> Occur a error in MCDC2805_SetPositiveLimit().\n");
		return API_ERROR;
	}

	this->parameter = parameter;

	return API_SUCCESS;

ERROR_Faulhaber_MCDC2805_SetParameter :
	PrintMessage("ERROR : Faulhaber_MCDC2805::SetParameter() -> Can't find parameters\n");
	return API_ERROR;
}

int Faulhaber_MCDC2805::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int Faulhaber_MCDC2805::SetPower(double power, unsigned long time)
{
	return API_NOT_SUPPORTED;
}

int Faulhaber_MCDC2805::GetPower(double &power)
{
	short current;

	if(MCDC2805_GetCur(&current) < 0) {
		return API_ERROR;
	}

	power = (double)(current) * 0.001;

	return API_SUCCESS;
}

int Faulhaber_MCDC2805::SetVelocity(double velocity, unsigned long time)
{
	if(velocity > _profile.maximumVelocity || velocity < -_profile.maximumVelocity) {
		PrintMessage ("ERROR : Faulhaber_MCDC2805::SetVelocity() -> The velocity is bigger than maximum velocity\n");
		return API_ERROR;
	}

	//	Degree/s -> RPM
	short tmp = (short)(velocity * 60.0 * _profile.reductionRatio / 360.0);

	if(MCDC2805_SetVel(tmp) < 0) {
		PrintMessage("ERROR : Faulhaber_MCDC2805::SetVelocity() -> Occur a error in MCDC2805_SetVel()\n");
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Faulhaber_MCDC2805::GetVelocity(double &velocity)
{
	short tmp;

	if(MCDC2805_GetVel(&tmp) < 0) {
		PrintMessage("ERROR : Faulhaber_MCDC2805::GetVelocity() -> Occur a error in MCDC2805_GetVel()\n");
		velocity = 0;
		return API_ERROR;
	}

	//	RPM -> Degree/s
	velocity = (double)(tmp) * 360.0 / 60.0 / _profile.reductionRatio;

	return API_SUCCESS;
}

int Faulhaber_MCDC2805::SetPosition(double position, unsigned long time)
{
	if(position > _profile.maximumPositionLimit || position < _profile.minimumPositionLimit) {
		return API_ERROR;
	}

	//	Angle -> Pulse
	long tmp = (long)(position * (_profile.linePerRevolution * _profile.reductionRatio) / 360.0);

	if(MCDC2805_SetPos(tmp) < 0) {
		PrintMessage("ERROR : Faulhaber_MCDC2805::SetPosition() -> Occur a error in MCDC2805_SetPos()\n");
		return API_ERROR;
	}

	return API_SUCCESS;
}

int Faulhaber_MCDC2805::GetPosition(double &position)
{
	long tmp;
	if(MCDC2805_GetPos(&tmp) < 0) {
		PrintMessage("ERROR : Faulhaber_MCDC2805::GetPosition() -> Occur a error in MCDC2805_GetPos()\n");
		position = 0;
		return API_ERROR;
	}

	//	Pulse -> Angle
	position = (double)(tmp) * 360.0 / (_profile.linePerRevolution * _profile.reductionRatio);

	return API_SUCCESS;
}

int Faulhaber_MCDC2805::InitializeUART(Property parameter)
{
	Property uartParameter;
	char *error = NULL;

	if(parameter.FindName("UARTAPIName") == false)	goto ERROR_Faulhaber_MCDC2805_InitializeUART;
	if(parameter.FindName("PortName") == false)		goto ERROR_Faulhaber_MCDC2805_InitializeUART;
	else	uartParameter.SetValue("PortName", parameter.GetValue("PortName"));
	if(parameter.FindName("TimeOut") == false)		goto ERROR_Faulhaber_MCDC2805_InitializeUART;
	else	uartParameter.SetValue("TimeOut", parameter.GetValue("TimeOut"));
	if(parameter.FindName("BaudRate") == false)		goto ERROR_Faulhaber_MCDC2805_InitializeUART;
	else	uartParameter.SetValue("BaudRate", parameter.GetValue("BaudRate"));
	if(parameter.FindName("DataBits") == false)		goto ERROR_Faulhaber_MCDC2805_InitializeUART;
	else	uartParameter.SetValue("DataBits", parameter.GetValue("DataBits"));
	if(parameter.FindName("StopBits") == false)		goto ERROR_Faulhaber_MCDC2805_InitializeUART;
	else	uartParameter.SetValue("StopBits", parameter.GetValue("StopBits"));
	if(parameter.FindName("Parity") == false)		goto ERROR_Faulhaber_MCDC2805_InitializeUART;
	else	uartParameter.SetValue("Parity", parameter.GetValue("Parity"));
	if(parameter.FindName("FlowControl") == false)	goto ERROR_Faulhaber_MCDC2805_InitializeUART;
	else	uartParameter.SetValue("FlowControl", parameter.GetValue("FlowControl"));

	if(_uart != NULL) {
		delete _uart;
		_uart = NULL;
	}
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("UARTAPIName").c_str());
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
	hOprosAPI = dlopen(parameter.GetValue("UARTAPIName").c_str(), RTLD_LAZY);
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

	_uart = (UART *)getOprosAPI();
	if(_uart == NULL) {
		Finalize();
		return API_ERROR;
	}

	//	API 초기화
	if(_uart->Initialize(uartParameter) < 0) {
		Finalize();
		return API_ERROR;
	}

	if(_uart->Enable() < 0) {
		Finalize();
		return API_ERROR;
	}

	return API_SUCCESS;

ERROR_Faulhaber_MCDC2805_InitializeUART :
	PrintMessage("ERROR : Faulhaber_MCDC2805::InitializeUART() -> Can't find a property in parameter.\n");
	return API_ERROR;
}

int Faulhaber_MCDC2805::MCDC2805_SendPack(unsigned char data[], int len)
{
	OprosTimer timeTick;
	int ret;

	if(_uart == NULL) {
		return -1;
	}

	timeTick.StartTimeTick();

	for(int i = 0; i < len; i += ret) {
		ret = _uart->Write(&data[i], len - i);

		if(ret < 0) {
			return -1;
		}
		else if(ret == 0) {
			if(timeTick.GetTimeTick() > MCDC2805_DELAY) {
				return -1;
			}
			OprosSleep(1);
		}
	}

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_RecvPack(unsigned char data[])
{
	OprosTimer timeTick;
	int ret;

	if(_uart == NULL) {
		return -1;
	}

	timeTick.StartTimeTick();

	for(int i = 0; i < MCDC2805_MAX_DATA_LEN; i += ret) {
		ret = _uart->Read(&data[i], 1);
		if(ret < 0) {
			return -1;
		}
		if(ret > 0) {
			if(i > 1) {
				if((data[i - 1] == ASCII_CR) && (data[i] == ASCII_LF)) {
					return i;
				}
			}
		}

		if(timeTick.GetTimeTick() > MCDC2805_DELAY) {
			return -1;
		}
		OprosSleep(0);
	}
	
	return -1;
}

int Faulhaber_MCDC2805::MCDC2805_SetBaudRate(int baudRate)
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'B', 'A', 'U', 'D'};
	int len = 4;

	if(!((baudRate == 1200) || (baudRate == 2400) || (baudRate == 4800) || (baudRate == 9600) || (baudRate == 19200))) {
		return -1;
	}
	
	len += sprintf((char *)&data[len], "%d", baudRate);
	if(len <= 4) {
		return -1;
	}

	data[len++] = ASCII_CR;

	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_SetNodeAddr(unsigned char nodeAddr)
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'N', 'O', 'D', 'E', 'A', 'D', 'R'};
	int len = 7;

	len += sprintf((char *)&data[len], "%d", nodeAddr);
	if(len <= 7) {
		return -1;
	}

	data[len++] = ASCII_CR;

	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_GetNodeAddr(unsigned char nodeAddr[1])
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'G', 'N', 'O', 'D', 'E', 'A', 'D', 'R', ASCII_CR};
	int len = 9;
	
	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	if(MCDC2805_RecvPack(data) < 0) {
		return -1;
	}

	nodeAddr[0] = (unsigned char)atoi((char *)data);

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_ResetNode(void)
{
	unsigned char data[] = {'R', 'N', ASCII_CR};

	if(MCDC2805_SendPack(data, sizeof(data)) < 0) {
		return -1;
	}

	return 0;
}


int Faulhaber_MCDC2805::MCDC2805_SaveToEeprom(void)
{
	unsigned char data[] = {'E', 'E', 'P', 'S', 'A', 'V', ASCII_CR};

	if(MCDC2805_SendPack(data, sizeof(data)) < 0) {
		return -1;
	}

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_EnDrive(void)
{
	unsigned char data[] = {'E', 'N', ASCII_CR};

	if(MCDC2805_SendPack(data, sizeof(data)) < 0) {
		return -1;
	}

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_DiDrive(void)
{
	unsigned char data[] = {'D', 'I', ASCII_CR};

	if(MCDC2805_SendPack(data, sizeof(data)) < 0) {
		return -1;
	}

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_GetStatus(unsigned char status[1])
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'G', 'S', 'T', ASCII_CR};
	int len = 4;

	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	if(MCDC2805_RecvPack(data) < 7) {
		return -1;
	}

	status[0] = 0x00;
	for(int i = 0; i < 7; i++) {
		if(data[i] == '1') {
			status[0] |= (1 << i);
		}
	}

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_GetFault(unsigned char fault[1])
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'G', 'F', 'S', ASCII_CR};
	int len = 4;

	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	if(MCDC2805_RecvPack(data) < 4) {
		return -1;
	}

	fault[0] = 0x00;
	for(int i = 0; i < 4; i++) {
		if(data[i] == '1') {
			fault[0] |= (1 << i);
		}
	}

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_GetActualStatus(unsigned char actualStatus[1])
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'G', 'A', 'S', 'T', ASCII_CR};
	int len = 5;

	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	if(MCDC2805_RecvPack(data) < 4) {
		return -1;
	}

	actualStatus[0] = 0x00;
	for(int i = 0; i < 4; i++) {
		if(data[i] == '1') {
			actualStatus[0] |= (1 << i);
		}
	}

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_SetPickCur(unsigned short pickCur)
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'L', 'P', 'C'};
	int len = 3;

	if(pickCur > 12000) {
		return -1;
	}

	len += sprintf((char *)&data[len], "%d", pickCur);
	if(len <= 3) {
		return -1;
	}

	data[len++] = ASCII_CR;

	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_GetPickCur(unsigned short pickCur[1])
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'G', 'P', 'C', ASCII_CR};
	int len = 4;
	
	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	if(MCDC2805_RecvPack(data) < 0) {
		return -1;
	}

	pickCur[0] = (unsigned short)atoi((char *)data);

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_SetContCur(unsigned short contCur)
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'L', 'C', 'C'};
	int len = 3;

	if(contCur > 12000) {
		return -1;
	}

	len += sprintf((char *)&data[len], "%d", contCur);
	if(len <= 3) {
		return -1;
	}

	data[len++] = ASCII_CR;

	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_GetContCur(unsigned short contCur[1])
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'G', 'C', 'C', ASCII_CR};
	int len = 4;
	
	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	if(MCDC2805_RecvPack(data) < 0) {
		return -1;
	}

	contCur[0] = (unsigned short)atoi((char *)data);

	return 0;
}


int Faulhaber_MCDC2805::MCDC2805_GetCur(short cur[])
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'G', 'R', 'C', ASCII_CR};
	int len = 4;
	
	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	if(MCDC2805_RecvPack(data) < 0) {
		return -1;
	}

	cur[0] = (short)atoi((char *)data);

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_SetEncRes(unsigned short encRes)
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'E', 'N', 'C', 'R', 'E', 'S'};
	int len = 6;

	len += sprintf((char *)&data[len], "%d", encRes);
	if(len <= 6) {
		return -1;
	}

	data[len++] = ASCII_CR;

	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	return 0;
}
int Faulhaber_MCDC2805::MCDC2805_GetEncRes(unsigned short encRes[1])
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'G', 'E', 'N', 'C', 'R', 'E', 'S', ASCII_CR};
	int len = 8;

	
	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	if(MCDC2805_RecvPack(data) < 0) {
		return -1;
	}

	encRes[0] = (unsigned short)atoi((char *)data);

	return 0;
}
int Faulhaber_MCDC2805::MCDC2805_SetPGain(unsigned char pGain)
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'P', 'O', 'R'};
	int len = 3;

	len += sprintf((char *)&data[len], "%d", pGain);
	if(len <= 3) {
		return -1;
	}

	data[len++] = ASCII_CR;

	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_GetPGain(unsigned char pGain[1])
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'G', 'P', 'O', 'R', ASCII_CR};
	int len = 5;

	
	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	if(MCDC2805_RecvPack(data) < 0) {
		return -1;
	}

	pGain[0] = (unsigned char)atoi((char *)data);

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_SetIGain(unsigned char iGain)
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'I'};
	int len = 1;

	len += sprintf((char *)&data[len], "%d", iGain);
	if(len <= 1) {
		return -1;
	}

	data[len++] = ASCII_CR;

	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_GetIGain(unsigned char iGain[1])
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'G', 'I', ASCII_CR};
	int len = 3;

	
	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	if(MCDC2805_RecvPack(data) < 0) {
		return -1;
	}

	iGain[0] = (unsigned char)atoi((char *)data);

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_SetAccel(unsigned short accel)
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'A', 'C'};
	int len = 2;

	if(accel > 30000) {
		return -1;
	}

	len += sprintf((char *)&data[len], "%d", accel);
	if(len <= 2) {
		return -1;
	}

	data[len++] = ASCII_CR;

	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_GetAccel(unsigned short accel[1])
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'G', 'A', 'C', ASCII_CR};
	int len = 4;

	
	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	if(MCDC2805_RecvPack(data) < 0) {
		return -1;
	}

	accel[0] = (unsigned short)atoi((char *)data);

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_SetMaxSpeed(unsigned short speed)
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'S', 'P'};
	int len = 2;

	if(speed > 30000) {
		return -1;
	}

	len += sprintf((char *)&data[len], "%d", speed);
	if(len <= 2) {
		return -1;
	}

	data[len++] = ASCII_CR;

	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_GetMaxSpeed(unsigned short speed[1])
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'G', 'S', 'P', ASCII_CR};
	int len = 4;

	
	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	if(MCDC2805_RecvPack(data) < 0) {
		return -1;
	}

	speed[0] = (unsigned short)atoi((char *)data);

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_SetVel(short vel)
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'V'};
	int len = 1;

	if((vel > 30000) || (vel < -30000)) {
		return -1;
	}

	len += sprintf((char *)&data[len], "%d", vel);
	if(len < 2) {
		return -1;
	}

	data[len++] = ASCII_CR;

	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_GetVel(short vel[1])
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'G', 'N', ASCII_CR};
	int len = 3;

	
	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	if(MCDC2805_RecvPack(data) < 0) {
		return -1;
	}

	vel[0] = (short)atoi((char *)data);

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_SetPositiveLimit(long positiveLimit)
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'L', 'L'};
	int len = 2;

	if(positiveLimit <= 0) {
		return -1;
	}

	len += sprintf((char *)&data[len], "%ld", positiveLimit);
	if(len <= 2) {
		return -1;
	}

	data[len++] = ASCII_CR;

	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_GetPositiveLimit(long positiveLimit[1])
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'G', 'P', 'L', ASCII_CR};
	int len = 4;

	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	if(MCDC2805_RecvPack(data) < 0) {
		return -1;
	}

	positiveLimit[0] = atol((char *)data);

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_SetNegativeLimit(long negativeLimit)
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'L', 'L'};
	int len = 2;

	if(negativeLimit >= 0) {
		return -1;
	}

	len += sprintf((char *)&data[len], "%ld", negativeLimit);
	if(len <= 2) {
		return -1;
	}

	data[len++] = ASCII_CR;

	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_GetNegativeLimit(long negativeLimit[1])
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'G', 'N', 'L', ASCII_CR};
	int len = 4;

	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	if(MCDC2805_RecvPack(data) < 0) {
		return -1;
	}

	negativeLimit[0] = atol((char *)data);

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_SetPos(long pos)
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'L', 'A'};
	int len = 2;

	len += sprintf((char *)&data[len], "%ld", pos);
	if(len <= 2) {
		return -1;
	}

	data[len++] = ASCII_CR;

	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	data[0] = 'M';
	data[1] = ASCII_CR;
	len = 2;

	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	return 0;
}

int Faulhaber_MCDC2805::MCDC2805_GetPos(long pos[1])
{
	unsigned char data[MCDC2805_MAX_DATA_LEN] = {'P', 'O', 'S', ASCII_CR};
	int len = 4;

	if(MCDC2805_SendPack(data, len) < 0) {
		return -1;
	}

	if(MCDC2805_RecvPack(data) < 0) {
		return -1;
	}

	pos[0] = atol((char *)data);

	return 0;
}

#if !defined(DEVICE_TEST)
#if defined(WIN32)
extern "C"
{
__declspec(dllexport) OprosApi *GetAPI();
}

OprosApi *GetAPI()
{
	return new Faulhaber_MCDC2805();
}
#endif
#endif
