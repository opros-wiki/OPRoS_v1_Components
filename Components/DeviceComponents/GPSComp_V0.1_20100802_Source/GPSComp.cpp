/*************************************************************

 file: GPSComp.cpp
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

#include "GPSComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
GPSComp::GPSComp()
{
	hOprosAPI = NULL;
	gps = NULL;
	error = 0;
	
	portSetup();
}

//
// constructor declaration (with name)
//
GPSComp::GPSComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	gps = NULL;
	error = 0;
	
	portSetup();
}

//
// destructor declaration
//

GPSComp::~GPSComp() 
{
	onDestroy();
}

void GPSComp::portSetup() {

	// provided service port setup
	ProvidedServicePort *pa1;
	pa1=new GPSServiceProvided(this);

	addPort("GPSService",pa1);

	// data port setup
	addPort("gpsData", &gpsData);
}

// Call back Declaration
ReturnType GPSComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : GPSComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("APIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : GPSComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	API 로드
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : GPSComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("APIName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : GPSComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : GPSComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	gps = dynamic_cast<GPS *>(getOprosAPI());
	if(gps == NULL) {
		PrintMessage("ERROR : GPSComp::onInitialize() -> Can't get a handle of GPS API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	//	API 초기화
	if(gps->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : GPSComp::onInitialize() -> Can't intilaize a GPS API\n");
		
		delete gps;
		gps = NULL;

#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_INITIALIZE_API_ERROR;
	}

	error = 0;

	return OPROS_SUCCESS;
}

ReturnType GPSComp::onStart()
{
	if(gps == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 enable를 호출
	if(gps->Enable() < 0) {
		PrintMessage("ERROR : GPSComp::onStart() -> Can't enable the GPS API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType GPSComp::onStop()
{
	if(gps == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 disable 호출
	if(gps->Disable() < 0) {
		PrintMessage("ERROR : GPSComp::onStop() -> Can't disable the GPS API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType GPSComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType GPSComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType GPSComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType GPSComp::onDestroy()
{
	//	API 핸들 삭제
	if(gps != NULL) {
		gps->Finalize();
		delete gps;
		gps = NULL;
	}

	//	DLL 핸들 삭제
	if(hOprosAPI != NULL) {
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
	}

	return OPROS_SUCCESS;
}

ReturnType GPSComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType GPSComp::onExecute()
{
	if(gps == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	GPSData result;

	lock.Lock();
	if(gps->GetGPSData(result) < 0) {
		PrintMessage("ERROR : GPSComp::onExecute() -> Can't get the GPS data.\n");
		lock.Unlock();
		return OPROS_CALL_API_ERROR;
	}
	lock.Unlock();

	gpsData.push(result);

	return OPROS_SUCCESS;
}
	
ReturnType GPSComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType GPSComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool GPSComp::SetParameter(Property parameter)
{
	if(gps == NULL) {
		return false;
	}

	if(gps->SetParameter(parameter) < 0) {
		return false;
	}

	return true;
}

Property GPSComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(gps == NULL) {
		error = -1;
		return parameter;
	}

	if(gps->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}

int GPSComp::GetError()
{
	return error;
}

GPSData GPSComp::GetGPSData()
{
	GPSData result;

	if(gps == NULL) {
		error = -1;
		return result;
	}

	lock.Lock();
	if(gps->GetGPSData(result) < 0) {
		PrintMessage("ERROR : GPSComp::onExecute() -> Can't get the GPS data.\n");
		error = -1;
	}
	lock.Unlock();

	return result;
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
	return new GPSComp();
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
	return new GPSComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

