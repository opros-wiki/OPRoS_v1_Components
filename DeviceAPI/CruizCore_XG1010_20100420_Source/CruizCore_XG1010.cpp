/*************************************************************

 file: CruizCore_XG1010.cpp
 author: Jeon SangUk
 begin: April 20 2010
 copyright: (c) 2009 KNU, OPRoS
 email: hspark@kangwon.ac.kr	
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

#include "CruizCore_XG1010.h"

#include "OprosTimer.h"
#include "OprosPrintMessage.h"
#include "ParsingUserMessage.h"

#define	XG1010_MAX_SIZE	(4096)

using namespace OPRoS;

CruizCore_XG1010::CruizCore_XG1010(void)
{
	hCommPort = INVALID_HANDLE_VALUE;
}

CruizCore_XG1010::~CruizCore_XG1010(void)
{
	if(hCommPort != INVALID_HANDLE_VALUE) {
			finalizeUART();		
	}
}

bool CruizCore_XG1010::initialize(Property parameter)
{
	if(setParameter(parameter) == false) {
		PrintMessage ("ERROR -> setParameter()\n");
		return false;
	}
	if(initializeUART(parameter.getValue("userMessage")) == false) {
		PrintMessage ("ERROR -> initializeUART()\n");
		return false;
	}
	if(XG1010_Reset()<0){
		PrintMessage ("ERROR -> XG1010_Reset()\n");
		return false;
	}
	return true;
}

bool CruizCore_XG1010::enable(void)
{
//	unsigned char sendData[] = "$MIA,I,B,19200,R,110,D,Y,N*8c";
	unsigned char sendData[] = "$MIA,I,B,19200,R,100,D,Y,N*8c";
	
	if(XG1010_SendPack(sendData, sizeof(sendData)) < 0) {
		PrintMessage ("ERROR -> XG1010_SendPack()\n");
			return false;
	}
		
	return true;
}

bool CruizCore_XG1010::disable(void)
{
	return true;
}

bool CruizCore_XG1010::finalize(void)
{
	finalizeUART();
	return true;
}

bool CruizCore_XG1010::setParameter(Property parameter)
{
	size= atoi(parameter.getValue("size").c_str());
	x = atoi(parameter.getValue("x1").c_str());
	y = atoi(parameter.getValue("y1").c_str());
	z = atoi(parameter.getValue("z1").c_str());
	roll = atoi(parameter.getValue("roll1").c_str());
	pitch = atoi(parameter.getValue("pitch1").c_str());
	yaw = atoi(parameter.getValue("yaw1").c_str());

	return true;
}

Property CruizCore_XG1010::getParameter(void)
{
	Property parameter;

	return parameter;
}

DEVICE_STATUS CruizCore_XG1010::getStatus(void)
{
	return status;
}

int CruizCore_XG1010::getValue(int index, valarray<ObjectPosture> *value)
{
	if(value == NULL) {
		return -1;
	}
	else if((int)value->size() == 0) {
		return -1;
	}
	double temp[2];


	if(XG1010_GetValue(temp))
	{
 		(*value)[0].pRate=temp[0];
 		(*value)[0].yaw=temp[1];

		return 1;
	}


	return 0;
}
int CruizCore_XG1010::XG1010_Reset()
{

	unsigned char sendData[] = "$MIB,RESET*87";
	
	if(XG1010_SendPack(sendData, sizeof(sendData)) < 0) {
		PrintMessage ("ERROR -> XG1010_SendPack()\n");
		return -1;
	}

	return 0;

}
int CruizCore_XG1010::XG1010_SendPack(unsigned char *data, int size)
{
	int ret;
	if(size <= 0) {
		return 0;
	}

	for(int i = 0; i < size; i += ret) {
		ret = XG1010_Write((data + i), size - i);
		if(ret < 0) {
			return -1;
		}
	}

	return size;

}
bool CruizCore_XG1010::XG1010_RecvPacket(unsigned char *data)
{

	unsigned char buf[XG1010_MAX_SIZE];
	DWORD ErrorFlags;
	COMSTAT ComStat;
	DWORD queue_mem=0;
	int ReadSize=0;
	

	while(queue_mem<8)
	{
		ClearCommError(hCommPort, &ErrorFlags, &ComStat);
		queue_mem=ComStat.cbInQue;
		if(queue_mem>4000)
		{
			PurgeComm(hCommPort, PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
			queue_mem=0;
		}
	}

	int ret;
	int index = 0;

	//	헤더를 찾음
	while(1) {
		ret = XG1010_Read(&buf[0], 2);
		if(ret < 0) {
			return false;
		}
		if(ret==2){
			if((buf[0] ==0xFF)&&(buf[1] ==0xFF))
			{
				index=2;
				break;
			}
			else
			{
				PurgeComm(hCommPort, PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
			}

		}
		else
		{
			PurgeComm(hCommPort, PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
			return false;
		}
	}

	ClearCommError(hCommPort, &ErrorFlags, &ComStat);	
	ReadSize=(ComStat.cbInQue+2)/8;

	ret = XG1010_Read(&buf[index], (8*ReadSize-index));
	if(ret < 0) {
		return false;
	}
	memcpy(data,&buf[(8*(ReadSize-1))],8);
	return true;
}

bool CruizCore_XG1010::XG1010_ParsingData(unsigned char *data, double *value)
{
	unsigned short checkSum=0;
	
	short int rate;
	short int angle;
	short check_sum;
	if(data[0] != 0xFF || data[1] != 0xFF)
	{
// 		printf("data heading error");
		return false;
	}
	//Assemble data
	rate = (data[2] & 0xFF) | ((data[3] << 8) & 0xFF00);
	angle = (data[4] & 0xFF) | ((data[5] << 8) & 0XFF00);
	//Verify checksum
	check_sum = 0xFFFF + rate + angle;
	if(((unsigned char)(check_sum & 0xFF) != data[6]) ||
		((unsigned char)((check_sum>>8) & 0xFF) != data[7]))
	{
//		printf("Checksum mismatch error");
		return false;
	}
	//Scale and store data
	value[0] = rate / 100.0;
	value[1] = angle / 100.0;
/*	printf("gRate %3.5f \t gAngle %3.5f \n",value[0],value[1]);*/


	return true;
}

bool CruizCore_XG1010::XG1010_GetValue(double *value)
{
	unsigned char data[8];

	if(XG1010_RecvPacket(data) == false) {
		return false;
	}

	if(XG1010_ParsingData(data, value) == false) {
		return false;
	}

	return true;
}

bool CruizCore_XG1010::initializeUART(string uartProperty)
{
	Property uartParameter;
	string tmp;

	if((tmp = ParsingUserMessage(&uartProperty)) == "") {
		return false;
	}
	uartParameter.setValue("timeOut", tmp);

	if((tmp = ParsingUserMessage(&uartProperty)) == "") {
		return false;
	}
	uartParameter.setValue("port", tmp);

	if((tmp = ParsingUserMessage(&uartProperty)) == "") {
		return false;
	}
	uartParameter.setValue("baudRate", tmp);

	if((tmp = ParsingUserMessage(&uartProperty)) == "") {
		return false;
	}
	uartParameter.setValue("dataBits", tmp);

	if((tmp = ParsingUserMessage(&uartProperty)) == "") {
		return false;
	}
	uartParameter.setValue("stopBtis", tmp);

	if((tmp = ParsingUserMessage(&uartProperty)) == "") {
		return false;
	}
	uartParameter.setValue("parity", tmp);

	if((tmp = ParsingUserMessage(&uartProperty)) == "") {
		return false;
	}
	uartParameter.setValue("flowControl", tmp);

	unsigned long timeOut = (unsigned long)atol(uartParameter.getValue("timeOut").c_str());
	string port = uartParameter.getValue("port");
	unsigned long baudRate = (unsigned long)atol(uartParameter.getValue("baudRate").c_str());
	char dataBits = (char)atoi(uartParameter.getValue("dataBits").c_str());
	char stopBits = (char)atoi(uartParameter.getValue("stopBtis").c_str());
	char parity = (char)atoi(uartParameter.getValue("parity").c_str());
	char flowControl = (char)atoi(uartParameter.getValue("flowControl").c_str());
	
// 	printf ("----- RS232 Parameter -----\n");
// 	printf ("- TimeOut     : %d\n", timeOut);
// 	printf ("- Port        : %s\n", port.c_str ());
// 	printf ("- BaudRate    : %d\n", baudRate);
// 	printf ("- DataBits    : %d\n", dataBits);
// 	printf ("- StopBits    : %d\n", stopBits);
// 	printf ("- Parity      : %d\n", parity);
// 	printf ("- FlowControl : %d\n", flowControl);
// 	printf ("___________________________\n");

	hCommPort = CreateFile((char *)port.c_str(),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL ,
		NULL
		);

	if(hCommPort == INVALID_HANDLE_VALUE){
		return false;
	}

	DCB dcb;
	BOOL bRet = GetCommState(hCommPort, &dcb);
	if(bRet == FALSE){
		return false;
	}
	dcb.BaudRate = baudRate;
	dcb.ByteSize = dataBits;
	dcb.Parity = parity;
	dcb.StopBits = stopBits;
	dcb.fParity = 0;

	bRet = SetCommState(hCommPort, &dcb);
	if(bRet == FALSE){
		return false;
	}

	SetupComm(hCommPort,XG1010_MAX_SIZE,XG1010_MAX_SIZE);
	PurgeComm(hCommPort, PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);

	return true;

}
bool CruizCore_XG1010::finalizeUART(void)
{
	if(hCommPort != INVALID_HANDLE_VALUE) {
		CloseHandle(hCommPort);
		hCommPort = INVALID_HANDLE_VALUE;

	}
	return true;
}
int CruizCore_XG1010::XG1010_Read(unsigned char *data,int size)
{
	DWORD dwRead;
	if (ReadFile(hCommPort, data, size, &dwRead, NULL))
	{
		if(size==dwRead)
			return size;
		else
			return -1;
	}
	else
		return -2;
}
int CruizCore_XG1010::XG1010_Write(unsigned char *data,int size)
{
	DWORD dwwritten = 0;
	if (WriteFile(hCommPort, data, size, &dwwritten, NULL))
	{
		if(size==dwwritten)
			return size;
		else
			return -1;
	}
	else
		return -2;
}

extern "C"
{
	__declspec(dllexport) OprosApi *getAPI();
	__declspec(dllexport) void releaseAPI(OprosApi *api);
}

OprosApi *getAPI()
{
	return new CruizCore_XG1010();
}

void releaseAPI(OprosApi *api)
{
	delete api;
}