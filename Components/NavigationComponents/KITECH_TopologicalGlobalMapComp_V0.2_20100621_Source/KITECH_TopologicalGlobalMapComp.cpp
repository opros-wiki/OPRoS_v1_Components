/*************************************************************

file: KITECH_TopologicalGlobalMapComp.cpp
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
#include "KITECH_TopologicalGlobalMapComp.h"
#include "Thinning.h"
#include "OprosPrintMessage.h"
#include "OprosTimer.h"

//
// constructor declaration
//
KITECH_TopologicalGlobalMapComp::KITECH_TopologicalGlobalMapComp()
{
	error = 0;
	gridBasedGlobalMap = NULL;
	portSetup();
}

//
// constructor declaration (with name)
//
KITECH_TopologicalGlobalMapComp::KITECH_TopologicalGlobalMapComp(const std::string &name):Component(name)
{
	error = 0;
	gridBasedGlobalMap = NULL;
	portSetup();
}

//
// destructor declaration
//

KITECH_TopologicalGlobalMapComp::~KITECH_TopologicalGlobalMapComp()
{
}

void KITECH_TopologicalGlobalMapComp::portSetup()
{
	// provided service port setup
	ProvidedServicePort *pa1 = new GlobalMapServiceProvided(this);
	addPort("GlobalMapService",pa1);
}

// Call back Declaration
/*
	KITECH_TopologicalGlobalMapComp의 onInitialize()에서
	bmp 파일의 비트맵 읽어 세선화 알고리즘을 수행하여 처리하기 때문에
	수행속도가 오래 걸림.
	bmp 비트맵의 크기와 형태에 따라 세선화 알고리즘의 수행속도가 틀려짐. 

	<환경 조건>
	1. Tetra 로봇 플렛폼
	2. Intel Core2Duo 2.1GHz
	3. 950 x 850 크기의 map

	<실험>
	1. onInitialize() 수행 속도 측정
		26047ms
		26078ms
		26093ms
		26125ms
		26031ms
		26031ms
		26094ms
		26078ms
		26125ms
		26047ms
*/
ReturnType KITECH_TopologicalGlobalMapComp::onInitialize()
{
	PrintMessage ("KITECH_TopologicalGlobalMapComp::onInitialize()\n");

#define GET_PIXEL(image, x, y)	(*(image + mapWidth * y + x))
#define SET_PIXEL(image, x, y, value)	(*(image + mapWidth * y + x) = value)

	parameter.SetProperty(getPropertyMap());
	if (!LoadProperty()) {
		error = -1;
		return OPROS_FIND_PROPERTY_ERROR;
	}

	gridBasedGlobalMap = new GridBasedGlobalMap (mapFileName.c_str(), mapResolution);
	if (gridBasedGlobalMap == NULL) {
		error = -1;
		return OPROS_INTERNAL_FAULT;
	}

	gridBasedGlobalMap->ExpandObstacle (1, 1, 255);
	gridBasedGlobalMap->ExpandObstacle (1, 255, 127);
	gridBasedGlobalMap->ExpandObstacle (1, 127, 63);
	gridBasedGlobalMap->ExpandObstacle (INTEGER(mobileSafeRadius/mapResolution), 1, 10);

	int mapWidth = gridBasedGlobalMap->_width;
	int mapHeight = gridBasedGlobalMap->_height;
	BYTE *inBuff = new BYTE [mapWidth*mapHeight];
	BYTE *outBuff = new BYTE [mapWidth*mapHeight];

	int x, y;
	for (y = 0; y < mapHeight; y++) {
		for (x = 0; x < mapWidth; x++) {
			BYTE pixel = gridBasedGlobalMap->GetPixelCELL (x, y);
			SET_PIXEL (inBuff, x, y, ((0 < pixel) ? 0 : 4));
		}
	}

	CThinning thinnig;
	if (thinnig.MakeThinning (outBuff, inBuff, mapWidth, mapHeight) < 0) {
		delete [] inBuff;
		delete [] outBuff;
		error = -1;
		return OPROS_INTERNAL_FAULT;
	}

	for (y = 0; y < mapHeight; y++) {
		for (x = 0; x < mapWidth; x++) {
			BYTE pixel = GET_PIXEL (outBuff, x, y);
			BYTE pixel2 = gridBasedGlobalMap->GetPixelCELL (x, y);
			gridBasedGlobalMap->SetPixelCELL (x, y, pixel | pixel2);
		}
	}

	delete [] inBuff;
	delete [] outBuff;

	error = 0;

	return OPROS_SUCCESS;
}

ReturnType KITECH_TopologicalGlobalMapComp::onStart()
{
	// user code here
	PrintMessage ("KITECH_TopologicalGlobalMapComp::onStart()\n");
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_TopologicalGlobalMapComp::onStop()
{
	// user code here
	PrintMessage ("KITECH_TopologicalGlobalMapComp::onStop()\n");
	return OPROS_SUCCESS;
}

ReturnType KITECH_TopologicalGlobalMapComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_TopologicalGlobalMapComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_TopologicalGlobalMapComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_TopologicalGlobalMapComp::onDestroy()
{
	PrintMessage ("KITECH_TopologicalGlobalMapComp::onDestroy()\n");
	if (gridBasedGlobalMap != NULL) {
		delete gridBasedGlobalMap;
		gridBasedGlobalMap = NULL;
	}

	return OPROS_SUCCESS;
}

ReturnType KITECH_TopologicalGlobalMapComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_TopologicalGlobalMapComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_TopologicalGlobalMapComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_TopologicalGlobalMapComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool KITECH_TopologicalGlobalMapComp::SetParameter(Property parameter)
{
	this->parameter = parameter;
	return true;
}

Property KITECH_TopologicalGlobalMapComp::GetParameter()
{
	error = 0;
	return parameter;
}

int KITECH_TopologicalGlobalMapComp::GetError()
{
	return error;
}

bool KITECH_TopologicalGlobalMapComp::LoadMapFile(std::string fileName,double cellWidth)
{
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->LoadGridMap(fileName.c_str(), cellWidth);
	}

	return false;
}

bool KITECH_TopologicalGlobalMapComp::SaveMapFile(std::string fileName)
{
	return true;
}

double KITECH_TopologicalGlobalMapComp::GetMapCellWidth()
{
	if (gridBasedGlobalMap != NULL){
		return gridBasedGlobalMap->_cellWidth;
	}

	return -1.0;
}

int KITECH_TopologicalGlobalMapComp::GetMapWidth()
{
	if (gridBasedGlobalMap != NULL){
		return gridBasedGlobalMap->_width;
	}
	
	return -1;
}

int KITECH_TopologicalGlobalMapComp::GetMapHeight()
{
	if (gridBasedGlobalMap != NULL){
		return gridBasedGlobalMap->_height;
	}

	return -1;
}

unsigned char KITECH_TopologicalGlobalMapComp::GetPixel(double x,double y)
{
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->GetPixel(x, y);
	}

	return 0;
}

unsigned char KITECH_TopologicalGlobalMapComp::GetPixelCell(int x,int y)
{
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->GetPixelCELL(x, y);
	}

	return 0;
}

void KITECH_TopologicalGlobalMapComp::SetPixel(double x,double y,unsigned char data)
{
	if (gridBasedGlobalMap != NULL) {
		gridBasedGlobalMap->SetPixel(x, y, data);
	}
}

void KITECH_TopologicalGlobalMapComp::SetPixelCell(int x,int y,unsigned char data)
{
	if (gridBasedGlobalMap != NULL) {
		gridBasedGlobalMap->SetPixelCELL(x ,y ,data);
	}
}

bool KITECH_TopologicalGlobalMapComp::IsIn(double x,double y)
{
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->IsIn(x, y);
	}

	return false;
}

bool KITECH_TopologicalGlobalMapComp::IsInCell(int x,int y)
{
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->IsInCELL(x ,y);
	}

	return false;
}

bool KITECH_TopologicalGlobalMapComp::IsIntersect(double x1,double y1,double x2,double y2,unsigned char data)
{
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->IsIntersect(x1, y1, x2, y2, data);
	}

	return false;
}

bool KITECH_TopologicalGlobalMapComp::IsIntersectCell(int x1,int y1,int x2,int y2,unsigned char data)
{
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->IsIntersectCELL(x1, y1, x2, y2, data);
	}

	return false;
}

void KITECH_TopologicalGlobalMapComp::DrawLine(double x1,double y1,double x2,double y2,unsigned char data)
{
	if (gridBasedGlobalMap != NULL) {
		gridBasedGlobalMap->DrawLine(x1, y1, x2, y2, data);
	}
}

void KITECH_TopologicalGlobalMapComp::DrawLineCell(int x1,int y1,int x2,int y2,unsigned char data)
{
	if (gridBasedGlobalMap != NULL) {
		gridBasedGlobalMap->DrawLineCELL(x1, y1, x2, y2, data);
	}
}

void KITECH_TopologicalGlobalMapComp::ExpandObstacle(int bulge,unsigned char threshold,unsigned char data)
{
	if (gridBasedGlobalMap != NULL) {
		gridBasedGlobalMap->ExpandObstacle(bulge, threshold, data);
	}
}

void KITECH_TopologicalGlobalMapComp::Reallocate(int offsetX,int offsetY,int width,int height)
{
	if (gridBasedGlobalMap != NULL) {
		gridBasedGlobalMap->Reallocate(offsetX, offsetY, width, height);
	}
}

void KITECH_TopologicalGlobalMapComp::Update(ObjectLocation position,std::vector<double> sensorValue)
{

}

int KITECH_TopologicalGlobalMapComp::M2CUx(double x)
{
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->M2CUx(x);
	}

	return 0;
}

int KITECH_TopologicalGlobalMapComp::M2CUy(double y)
{
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->M2CUy(y);
	}

	return 0;
}

double KITECH_TopologicalGlobalMapComp::CU2Mx(int x)
{
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->CU2Mx(x);
	}

	return 0;
}

double KITECH_TopologicalGlobalMapComp::CU2My(int y)
{
	if (gridBasedGlobalMap != NULL) {
		return gridBasedGlobalMap->CU2My(y);
	}

	return 0;
}

bool KITECH_TopologicalGlobalMapComp::LoadProperty ()
{
	if (parameter.FindName ("MapFileName") == false) {
		PrintMessage ("ERROR -> Can not found MapFileName parameter\n");
		return false;
	}
	mapFileName = parameter.GetValue("MapFileName");
	PrintMessage ("<KITECH_TopologicalGlobalMapComp Parameter> MapFileName : %s\n", mapFileName.c_str());

	if (parameter.FindName ("MapResolution") == false) {
		PrintMessage ("ERROR -> Can not found MapResolution parameter\n");
		return false;
	}
	mapResolution = atof (parameter.GetValue ("MapResolution").c_str ());
	PrintMessage ("<KITECH_TopologicalGlobalMapComp Parameter> MapResolution : %.3lf\n", mapResolution);

	if (parameter.FindName ("MobileSafeRadius") == false) {
		PrintMessage ("ERROR -> Can not found MobileSafeRadius parameter\n");
		return false;
	}
	mobileSafeRadius = atof (parameter.GetValue ("MobileSafeRadius").c_str ());
	PrintMessage ("<KITECH_TopologicalGlobalMapComp Parameter> MobileSafeRadius : %.3lf\n", mobileSafeRadius);

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
	return new KITECH_TopologicalGlobalMapComp();
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
	return new KITECH_TopologicalGlobalMapComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

