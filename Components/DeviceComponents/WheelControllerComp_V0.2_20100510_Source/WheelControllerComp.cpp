/*************************************************************

 file: WheelControllerComp.cpp
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

#include "OprosPrintMessage.h"
#include "WheelControllerComp.h"


//
// constructor declaration
//
WheelControllerComp::WheelControllerComp()
{
	hOprosAPI = NULL;
	wheelController = NULL;
	error = 0;

	portSetup();
}

//
// constructor declaration (with name)
//
WheelControllerComp::WheelControllerComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	wheelController = NULL;
	error = 0;

	portSetup();
}

//
// destructor declaration
//
WheelControllerComp::~WheelControllerComp()
{
	onDestroy();
}

void WheelControllerComp::portSetup()
{
	// provided service port setup
	ProvidedServicePort *pa1 = new WheelControllerServiceProvided(this);
	addPort("WheelControllerCompService",pa1);
}

// Call back Declaration
ReturnType WheelControllerComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : WheelControllerComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("APIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : WheelControllerComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	API 로드
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : WheelControllerComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("APIName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : WheelControllerComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : WheelControllerComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	wheelController = dynamic_cast<WheelController *>(getOprosAPI());
	if(wheelController == NULL) {
		PrintMessage("ERROR : WheelControllerComp::onInitialize() -> Can't get a handle of WheelController API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	//	API 초기화
	if(wheelController->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : WheelControllerComp::onInitialize() -> Can't intilaize a WheelController API\n");
		
		delete wheelController;
		wheelController = NULL;

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

ReturnType WheelControllerComp::onStart()
{
	//	API 핸들이 NULL이면
	//	에러를 리턴
	if(wheelController == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 Enable를 호출
	if(wheelController->Enable() == API_ERROR) {
		PrintMessage("ERROR : WheelControllerComp::onStart() -> Can't Enable  WheelController API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType WheelControllerComp::onStop()
{
	//	API의 핸들이 NULL이면
	//	에러를 리턴
	if(wheelController == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 Disable 호출
	if(wheelController->Disable() == API_ERROR) {
		PrintMessage("ERROR : WheelControllerComp::onStop() -> Can't Disable WheelController API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType WheelControllerComp::onReset()
{
	return OPROS_SUCCESS;
}

ReturnType WheelControllerComp::onError()
{
	return OPROS_SUCCESS;
}

ReturnType WheelControllerComp::onRecover()
{
	return OPROS_SUCCESS;
}

ReturnType WheelControllerComp::onDestroy()
{
	//	API 핸들 삭제
	if(wheelController != NULL) {
		wheelController->Finalize();
		delete wheelController;
		wheelController = NULL;
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

ReturnType WheelControllerComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType WheelControllerComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType WheelControllerComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType WheelControllerComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool WheelControllerComp::SetParameter(Property parameter)
{
	if(wheelController == NULL) {
		return false;
	}

	if(wheelController->SetParameter(parameter) < 0) {
		return false;
	}

	return true;
}

Property WheelControllerComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(wheelController == NULL) {
		error = -1;
		return parameter;
	}

	if(wheelController->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}

int WheelControllerComp::GetError()
{
	return error;
}

bool WheelControllerComp::SetPosition(ObjectLocation position)
{
	//	API 핸들이 NULL이거나 컴포넌트의 상태가 ACTIVE 또는 INACTIVE 상태가 아니면
	//	에러를 리턴
	if(wheelController == NULL) {
		return false;
	}

	if (wheelController->SetPosition(position) == API_SUCCESS) {
		return true;
	}

	return false;
}

ObjectLocation WheelControllerComp::GetPosition()
{
	ObjectLocation position;
	error = 0;

	if(wheelController == NULL) {
		error = -1;
		return position;
	}

	if (wheelController->GetPosition(position) != API_SUCCESS) {
		error = -1;
	}

	return position;
}

bool WheelControllerComp::DriveWheel(WheelControlVelocity velocity)
{
	//	API 핸들이 NULL이거나 컴포넌트의 상태가 ACTIVE 또는 INACTIVE 상태가 아니면
	//	에러를 리턴
	if(wheelController == NULL) {
		return false;
	}

	if (wheelController->Drive(velocity.forward	, velocity.angular) == API_SUCCESS) {
		return true;
	}

	return false;
}

bool WheelControllerComp::MoveWheel(double distance)
{
	//	API 핸들이 NULL이거나 컴포넌트의 상태가 ACTIVE 또는 INACTIVE 상태가 아니면
	//	에러를 리턴
	if(wheelController == NULL) {
		return false;
	}

	if (wheelController->Move(distance) == API_SUCCESS) {
		return true;
	}

	return false;
}

bool WheelControllerComp::RotateWheel(double degree)
{
	//	API 핸들이 NULL이거나 컴포넌트의 상태가 ACTIVE 또는 INACTIVE 상태가 아니면
	//	에러를 리턴
	if(wheelController == NULL) {
		return false;
	}

	if (wheelController->Rotate(degree) == API_SUCCESS) {
		return true;
	}

	return false;
}

bool WheelControllerComp::StopWheel()
{
	//	API 핸들이 NULL이거나 컴포넌트의 상태가 ACTIVE 또는 INACTIVE 상태가 아니면
	//	에러를 리턴
	if(wheelController == NULL) {
		return false;
	}

	if (wheelController->Stop() == API_SUCCESS) {
		return true;
	}

	return false;
}

bool WheelControllerComp::IsWheelRunning()
{
	// user code here
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
	return new WheelControllerComp();
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
	return new WheelControllerComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

