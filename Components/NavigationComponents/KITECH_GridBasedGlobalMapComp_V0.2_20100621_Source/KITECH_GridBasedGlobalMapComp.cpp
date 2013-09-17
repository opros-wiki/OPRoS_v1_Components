/*************************************************************

file: KITECH_GridBasedGlobalMapComp.cpp
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
#include "KITECH_GridBasedGlobalMapComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
KITECH_GridBasedGlobalMapComp::KITECH_GridBasedGlobalMapComp()
{
	error = 0;
	gridBasedGlobalMap = NULL;
	portSetup();
}

//
// constructor declaration (with name)
//
KITECH_GridBasedGlobalMapComp::KITECH_GridBasedGlobalMapComp(const std::string &name):Component(name)
{
	error = 0;
	gridBasedGlobalMap = NULL;
	portSetup();
}

//
// destructor declaration
//
KITECH_GridBasedGlobalMapComp::~KITECH_GridBasedGlobalMapComp()
{
}

void KITECH_GridBasedGlobalMapComp::portSetup()
{
	// provided service port setup
	ProvidedServicePort *pa1 = new GlobalMapServiceProvided(this);
	addPort("GlobalMapService",pa1);
}

// Call back Declaration
ReturnType KITECH_GridBasedGlobalMapComp::onInitialize()
{
	PrintMessage ("KITECH_GridBasedGlobalMapComp::onInitialize()\n");

	parameter.SetProperty(getPropertyMap());
	if (!LoadProperty()) return OPROS_FIND_PROPERTY_ERROR;

	gridBasedGlobalMap = new GridBasedGlobalMap ((char *)mapFileName.c_str(), mapResolution);
	if (gridBasedGlobalMap == NULL) {
		return OPROS_INTERNAL_FAULT;
	}

	gridBasedGlobalMap->ExpandObstacle (1, 1, 255);
	gridBasedGlobalMap->ExpandObstacle (1, 255, 127);
	gridBasedGlobalMap->ExpandObstacle (1, 127, 63);
	gridBasedGlobalMap->ExpandObstacle (INTEGER(mobileSafeRadius/mapResolution), 1, 10);

	error = 0;

	return OPROS_SUCCESS;
}

ReturnType KITECH_GridBasedGlobalMapComp::onStart()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_GridBasedGlobalMapComp::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_GridBasedGlobalMapComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_GridBasedGlobalMapComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_GridBasedGlobalMapComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_GridBasedGlobalMapComp::onDestroy()
{
	if (gridBasedGlobalMap != NULL) {
		delete gridBasedGlobalMap;
		gridBasedGlobalMap = NULL;
	}

	return OPROS_SUCCESS;
}

ReturnType KITECH_GridBasedGlobalMapComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_GridBasedGlobalMapComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_GridBasedGlobalMapComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_GridBasedGlobalMapComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool KITECH_GridBasedGlobalMapComp::SetParameter(Property parameter)
{
	this->parameter = parameter;
	return true;
}

Property KITECH_GridBasedGlobalMapComp::GetParameter()
{
	return parameter;
}

int KITECH_GridBasedGlobalMapComp::GetError()
{
	return error;
}

bool KITECH_GridBasedGlobalMapComp::LoadMapFile(std::string fileName, double cellWidth)
{
	error = 0;
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->LoadGridMap (fileName.c_str(), cellWidth);
	}

	error = -1;
	return false;
}

bool KITECH_GridBasedGlobalMapComp::SaveMapFile(std::string fileName)
{
	error = 0;
	if (gridBasedGlobalMap != NULL) {
		return true;
	}

	error = -1;
	return false;
}

double KITECH_GridBasedGlobalMapComp::GetMapCellWidth()
{
	error = 0;
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->_cellWidth;
	}

	error = -1;
	return -1.0;
}

int KITECH_GridBasedGlobalMapComp::GetMapWidth()
{
	error = 0;
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->_width;
	}

	error = -1;
	return -1;
}

int KITECH_GridBasedGlobalMapComp::GetMapHeight()
{
	error = 0;
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->_height;
	}

	error = -1;
	return -1;
}

unsigned char KITECH_GridBasedGlobalMapComp::GetPixel(double x, double y)
{
	error = 0;
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->GetPixel (x, y);
	}

	error = -1;
	return 0;
}

unsigned char KITECH_GridBasedGlobalMapComp::GetPixelCell(int x, int y)
{
	error = 0;
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->GetPixelCELL (x, y);
	}

	error = -1;
	return 0;
}

void KITECH_GridBasedGlobalMapComp::SetPixel(double x, double y, unsigned char data)
{
	error = 0;
	if (gridBasedGlobalMap != NULL) {
		gridBasedGlobalMap->SetPixel (x, y, data);
	}
	else {
		error = -1;
	}
}

void KITECH_GridBasedGlobalMapComp::SetPixelCell(int x, int y, unsigned char data)
{
	error = 0;
	if (gridBasedGlobalMap != NULL) {
		gridBasedGlobalMap->SetPixelCELL (x, y, data);
	}
	else {
		error = -1;
	}
}

bool KITECH_GridBasedGlobalMapComp::IsIn(double x, double y)
{
	error = 0;
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->IsIn (x, y);
	}

	error = -1;
	return false;
}

bool KITECH_GridBasedGlobalMapComp::IsInCell(int x, int y)
{
	error = 0;
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->IsInCELL (x, y);
	}

	error = -1;
	return false;
}

bool KITECH_GridBasedGlobalMapComp::IsIntersect(double x1, double y1, double x2, double y2, unsigned char data)
{
	error = 0;
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->IsIntersect (x1, y1, x2, y2, data);
	}

	error = -1;
	return false;
}

bool KITECH_GridBasedGlobalMapComp::IsIntersectCell(int x1, int y1, int x2, int y2, unsigned char data)
{
	error = 0;
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->IsIntersectCELL (x1, y1, x2, y2, data);
	}

	error = -1;
	return false;
}

void KITECH_GridBasedGlobalMapComp::DrawLine(double x1, double y1, double x2, double y2, unsigned char data)
{
	error = 0;
	if (gridBasedGlobalMap != NULL) {
		gridBasedGlobalMap->DrawLine (x1, y1, x2, y2, data);
	}
	else {
		error = -1;
	}
}

void KITECH_GridBasedGlobalMapComp::DrawLineCell(int x1, int y1, int x2, int y2, unsigned char data)
{
	error = 0;
	if (gridBasedGlobalMap != NULL) {
		gridBasedGlobalMap->DrawLineCELL (x1, y1, x2, y2, data);
	}
	else {
		error = -1;
	}
}

void KITECH_GridBasedGlobalMapComp::ExpandObstacle(int bulge, unsigned char threshold, unsigned char data)
{
	error = 0;
	if (gridBasedGlobalMap != NULL) {
		gridBasedGlobalMap->ExpandObstacle (bulge, threshold, data);
	}
	else {
		error = -1;
	}
}

void KITECH_GridBasedGlobalMapComp::Reallocate(int offsetX, int offsetY, int width, int height)
{
	error = 0;
	if (gridBasedGlobalMap != NULL) {
		gridBasedGlobalMap->Reallocate (offsetX, offsetY, width, height);
	}
	else {
		error = -1;
	}
}

void KITECH_GridBasedGlobalMapComp::Update(ObjectLocation position, std::vector<double> sensorValue)
{
	if (gridBasedGlobalMap != NULL) {

	}
}

int KITECH_GridBasedGlobalMapComp::M2CUx(double x)
{
	error = 0;
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->M2CUx (x);
	}

	error = -1;
	return 0;
}

int KITECH_GridBasedGlobalMapComp::M2CUy(double y)
{
	error = 0;
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->M2CUy (y);
	}

	error = -1;
	return 0;
}

double KITECH_GridBasedGlobalMapComp::CU2Mx(int x)
{
	error = 0;
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->CU2Mx (x);
	}

	error = -1;
	return 0;
}

double KITECH_GridBasedGlobalMapComp::CU2My(int y)
{
	error = 0;
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->CU2My (y);
	}

	error = -1;
	return 0;
}

bool KITECH_GridBasedGlobalMapComp::LoadProperty ()
{
	if (parameter.FindName ("MapFileName") == false) {
		PrintMessage ("ERROR -> Can not found MapFileName parameter\n");
		return false;
	}
	mapFileName = parameter.GetValue("MapFileName");
	PrintMessage ("<GridBasedGlobalMap Parameter> MapFileName : %s\n", mapFileName.c_str());

	if (parameter.FindName ("MapResolution") == false) {
		PrintMessage ("ERROR -> Can not found MapResolution parameter\n");
		return false;
	}
	mapResolution = atof (parameter.GetValue ("MapResolution").c_str ());
	PrintMessage ("<GridBasedGlobalMap Parameter> MapResolution : %.3lf\n", mapResolution);

	if (parameter.FindName ("MobileSafeRadius") == false) {
		PrintMessage ("ERROR -> Can not found MobileSafeRadius parameter\n");
		return false;
	}
	mobileSafeRadius = atof (parameter.GetValue ("MobileSafeRadius").c_str ());
	PrintMessage ("<KITECH_GridBasedGlobalMapComp Parameter> MobileSafeRadius : %.3lf\n", mobileSafeRadius);

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
	return new KITECH_GridBasedGlobalMapComp();
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
	return new KITECH_GridBasedGlobalMapComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

