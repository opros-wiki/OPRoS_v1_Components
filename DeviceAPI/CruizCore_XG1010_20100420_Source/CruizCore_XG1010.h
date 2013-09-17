/*************************************************************

 file: CruizCore_XG1010.h
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

#pragma once

#include "InertialMeasurementUnit.h"
#include "UART.h"
#include "windows.h"

using namespace OPRoS;
using namespace std;

class CruizCore_XG1010 : public InertialMeasurementUnit
{
public:
	CruizCore_XG1010(void);
	virtual ~CruizCore_XG1010(void);

public:
	virtual bool initialize(Property parameter);
	virtual bool enable(void);
	virtual bool disable(void);
	virtual bool finalize(void);
	virtual bool setParameter(Property parameter);
	virtual Property getParameter(void);

	virtual DEVICE_STATUS getStatus(void);

	virtual int getValue(int index, valarray<ObjectPosture> *value);

private:

	bool XG1010_RecvPacket(unsigned char *data);
	bool XG1010_ParsingData(unsigned char *data, double *value);
	bool XG1010_GetValue(double *value);
	int XG1010_Read(unsigned char *data,int size);
	int XG1010_Write(unsigned char *data,int size);

	int size;
	double x;
	double y;
	double z;
	double roll;
	double pitch;
	double yaw;
	
	HANDLE hCommPort;

	int  XG1010_SendPack(unsigned char *data, int size);
	int  XG1010_Reset(void);

	bool initializeUART(string uartProperty);
	bool finalizeUART(void);
};
