/*************************************************************

file: KITECH_LineBasedGlobalMapComp.cpp
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
/*
 *  Generated sources by OPRoS Component Generator (OCG V2)
 *  
 */
#include <Component.h>
#include <InputDataPort.h>
#include <OutputDataPort.h>
#include <InputEventPort.h>
#include <OutputEventPort.h>
#include <OPRoSTypes.h>
#include <EventData.h>

#include "GlobalMapServiceProvided.h"
#include "KITECH_LineBasedGlobalMapComp.h"
#include "OprosPrintMessage.h"


//
// constructor declaration
//
KITECH_LineBasedGlobalMapComp::KITECH_LineBasedGlobalMapComp()
{
	error = 0;
	lineBasedGlobalMap = NULL;
	portSetup();
}

//
// constructor declaration (with name)
//
KITECH_LineBasedGlobalMapComp::KITECH_LineBasedGlobalMapComp(const std::string &name):Component(name)
{
	error = 0;
	lineBasedGlobalMap = NULL;
	portSetup();
}

//
// destructor declaration
//

KITECH_LineBasedGlobalMapComp::~KITECH_LineBasedGlobalMapComp()
{

}

void KITECH_LineBasedGlobalMapComp::portSetup()
{
	// provided service port setup
	ProvidedServicePort *pa1 = new GlobalMapServiceProvided(this);
	addPort("GlobalMapService",pa1);
}

// Call back Declaration
ReturnType KITECH_LineBasedGlobalMapComp::onInitialize()
{
	PrintMessage ("KITECH_LineBasedGlobalMapComp::onInitialize()\n");

	parameter.SetProperty(getPropertyMap());
	if (!LoadProperty()) return OPROS_FIND_PROPERTY_ERROR;

	lineBasedGlobalMap = new LineBasedGlobalMap ((char *)mapFileName.c_str(), mapResolution);
	if (lineBasedGlobalMap == NULL) {
		return OPROS_INTERNAL_FAULT;
	}

	lineBasedGlobalMap->ExpandObstacle (1, 1, 255);
	lineBasedGlobalMap->ExpandObstacle (1, 255, 127);
	lineBasedGlobalMap->ExpandObstacle (1, 127, 63);
	lineBasedGlobalMap->ExpandObstacle (INTEGER(mobileSafeRadius/mapResolution), 1, 10);

	error = 0;

	return OPROS_SUCCESS;
}

ReturnType KITECH_LineBasedGlobalMapComp::onStart()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_LineBasedGlobalMapComp::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_LineBasedGlobalMapComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_LineBasedGlobalMapComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_LineBasedGlobalMapComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_LineBasedGlobalMapComp::onDestroy()
{
	if (lineBasedGlobalMap != NULL) {
		delete lineBasedGlobalMap;
		lineBasedGlobalMap = NULL;
	}

	return OPROS_SUCCESS;
}

ReturnType KITECH_LineBasedGlobalMapComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_LineBasedGlobalMapComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_LineBasedGlobalMapComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_LineBasedGlobalMapComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}


bool KITECH_LineBasedGlobalMapComp::SetParameter(Property parameter)
{
	this->parameter = parameter;
	return true;
}

Property KITECH_LineBasedGlobalMapComp::GetParameter()
{
	return parameter;
}

int KITECH_LineBasedGlobalMapComp::GetError()
{
	return error;
}

bool KITECH_LineBasedGlobalMapComp::LoadMapFile(std::string fileName,double cellWidth)
{
	if (lineBasedGlobalMap != NULL) {
		return lineBasedGlobalMap->LoadDxfMap(fileName.c_str(), cellWidth);
	}

	return false;
}

bool KITECH_LineBasedGlobalMapComp::SaveMapFile(std::string fileName)
{
	if (lineBasedGlobalMap != NULL) {
		return true;
	}

	return false;
}

double KITECH_LineBasedGlobalMapComp::GetMapCellWidth()
{
	if (lineBasedGlobalMap != NULL) {
		return lineBasedGlobalMap->_cellWidth;
	}

	return -1.0;
}

int KITECH_LineBasedGlobalMapComp::GetMapWidth()
{
	if (lineBasedGlobalMap != NULL) {
		return lineBasedGlobalMap->_width;
	}
	
	return -1;
}

int KITECH_LineBasedGlobalMapComp::GetMapHeight()
{
	if (lineBasedGlobalMap != NULL) {
		return lineBasedGlobalMap->_height;
	}
	
	return -1;
}

unsigned char KITECH_LineBasedGlobalMapComp::GetPixel(double x,double y)
{
	if (lineBasedGlobalMap != NULL) {
		return lineBasedGlobalMap->GetPixel(x, y);
	}
	
	return 0;
}

unsigned char KITECH_LineBasedGlobalMapComp::GetPixelCell(int x,int y)
{
	if (lineBasedGlobalMap != NULL) {
		return lineBasedGlobalMap->GetPixelCELL(x, y);
	}

	return 0;
}

void KITECH_LineBasedGlobalMapComp::SetPixel(double x,double y,unsigned char data)
{
	if (lineBasedGlobalMap != NULL) {
		lineBasedGlobalMap->SetPixel(x, y, data);
	}
}

void KITECH_LineBasedGlobalMapComp::SetPixelCell(int x,int y,unsigned char data)
{
	if (lineBasedGlobalMap != NULL) {
		lineBasedGlobalMap->SetPixelCELL(x, y, data);
	}
}

bool KITECH_LineBasedGlobalMapComp::IsIn(double x,double y)
{
	if (lineBasedGlobalMap != NULL) {
		return lineBasedGlobalMap->IsIn(x, y);
	}

	return false;
}

bool KITECH_LineBasedGlobalMapComp::IsInCell(int x,int y)
{
	if (lineBasedGlobalMap != NULL) {
		return lineBasedGlobalMap->IsInCELL(x, y);
	}

	return false;
}

bool KITECH_LineBasedGlobalMapComp::IsIntersect(double x1,double y1,double x2,double y2,unsigned char data)
{
	if (lineBasedGlobalMap != NULL) {
		return lineBasedGlobalMap->IsIntersect(x1, y1, x2, y2, data);
	}

	return false;
}

bool KITECH_LineBasedGlobalMapComp::IsIntersectCell(int x1,int y1,int x2,int y2,unsigned char data)
{
	if (lineBasedGlobalMap != NULL) {
		return lineBasedGlobalMap->IsIntersectCELL(x1, y1, x2, y2, data);
	}

	return false;
}

void KITECH_LineBasedGlobalMapComp::DrawLine(double x1,double y1,double x2,double y2,unsigned char data)
{
	if (lineBasedGlobalMap != NULL) {
		lineBasedGlobalMap->DrawLine(x1, y1, x2, y2, data);
	}
}

void KITECH_LineBasedGlobalMapComp::DrawLineCell(int x1,int y1,int x2,int y2,unsigned char data)
{
	if (lineBasedGlobalMap != NULL) {
		lineBasedGlobalMap->DrawLineCELL(x1, y1, x2, y2, data);
	}
}

void KITECH_LineBasedGlobalMapComp::ExpandObstacle(int bulge,unsigned char threshold,unsigned char data)
{
	if (lineBasedGlobalMap != NULL) {
		lineBasedGlobalMap->ExpandObstacle(bulge, threshold, data);
	}
}

void KITECH_LineBasedGlobalMapComp::Reallocate(int offsetX,int offsetY,int width,int height)
{
	if (lineBasedGlobalMap != NULL) {
		lineBasedGlobalMap->Reallocate(offsetX, offsetY, width, height);
	}
}

void KITECH_LineBasedGlobalMapComp::Update(ObjectLocation position,std::vector<double> sensorValue)
{

}

int KITECH_LineBasedGlobalMapComp::M2CUx(double x)
{
	if (lineBasedGlobalMap != NULL) {
		return lineBasedGlobalMap->M2CUx(x);
	}

	return 0;
}

int KITECH_LineBasedGlobalMapComp::M2CUy(double y)
{
	if (lineBasedGlobalMap != NULL) {
		return lineBasedGlobalMap->M2CUy(y);
	}

	return 0;
}

double KITECH_LineBasedGlobalMapComp::CU2Mx(int x)
{
	if (lineBasedGlobalMap != NULL) {
		return lineBasedGlobalMap->CU2Mx(x);
	}

	return 0;
}

double KITECH_LineBasedGlobalMapComp::CU2My(int y)
{
	if (lineBasedGlobalMap != NULL) {
		return lineBasedGlobalMap->CU2My(y);
	}

	return 0;
}

bool KITECH_LineBasedGlobalMapComp::LoadProperty ()
{
	if (parameter.FindName ("MapFileName") == false) {
		PrintMessage ("ERROR -> Can not found MapFileName parameter\n");
		return false;
	}
	mapFileName = parameter.GetValue("MapFileName");
	PrintMessage ("<KITECH_LineBasedGlobalMapComp Parameter> MapFileName : %s\n", mapFileName.c_str());

	if (parameter.FindName ("MapResolution") == false) {
		PrintMessage ("ERROR -> Can not found MapResolution parameter\n");
		return false;
	}
	mapResolution = atof (parameter.GetValue ("MapResolution").c_str ());
	PrintMessage ("<KITECH_LineBasedGlobalMapComp Parameter> MapResolution : %.3lf\n", mapResolution);

	if (parameter.FindName ("MobileSafeRadius") == false) {
		PrintMessage ("ERROR -> Can not found MobileSafeRadius parameter\n");
		return false;
	}
	mobileSafeRadius = atof (parameter.GetValue ("MobileSafeRadius").c_str ());
	PrintMessage ("<KITECH_LineBasedGlobalMapComp Parameter> MobileSafeRadius : %.3lf\n", mobileSafeRadius);

	return true;
}

#ifdef MAKE_COMPONENT_DLL
#ifdef WIN32
extern "C"
{
__declspec(dllexport) Component *getComponent();
__declspec(dllexport) void releaseComponent(Component *pcom);
}

Component *getComponent()
{
	return new KITECH_LineBasedGlobalMapComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#else
extern "C"
{
	Component *getComponent();
	void releaseComponent(IComponent *com);
}
Component *getComponent()
{
	return new KITECH_LineBasedGlobalMapComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

