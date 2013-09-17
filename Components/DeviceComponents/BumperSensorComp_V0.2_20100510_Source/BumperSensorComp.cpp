/*************************************************************

 file: BumperSensorComp.cpp
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

#include "BumperSensorComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
BumperSensorComp::BumperSensorComp()
{
	hOprosAPI = NULL;
	bumperSensor = NULL;
	error = 0;

	portSetup();
}

//
// constructor declaration (with name)
//
BumperSensorComp::BumperSensorComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	bumperSensor = NULL;
	error = 0;

	portSetup();
}

//
// destructor declaration
//

BumperSensorComp::~BumperSensorComp() 
{
	onDestroy();
}

void BumperSensorComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new BumperSensorServiceProvided(this);

	addPort("BumperSensorService",pa1);

	// data port setup

	addPort("bumperData", &bumperData);

}

// Call back Declaration
ReturnType BumperSensorComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : BumperSensorComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("APIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : BumperSensorComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	API 로드
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : BumperSensorComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("APIName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : BumperSensorComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : BumperSensorComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	bumperSensor = dynamic_cast<BumperSensor *>(getOprosAPI());
	if(bumperSensor == NULL) {
		PrintMessage("ERROR : BumperSensorComp::onInitialize() -> Can't get a handle of BumperSensor API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	//	API 초기화
	if(bumperSensor->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : BumperSensorComp::onInitialize() -> Can't intilaize a BumperSensor API\n");
		
		delete bumperSensor;
		bumperSensor = NULL;

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

ReturnType BumperSensorComp::onStart()
{
	if(bumperSensor == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 enable를 호출
	if(bumperSensor->Enable() < 0) {
		PrintMessage("ERROR : BumperSensorComp::onStart() -> Can't enable the Bumper Sensor API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType BumperSensorComp::onStop()
{
	if(bumperSensor == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 disable 호출
	if(bumperSensor->Disable() < 0) {
		PrintMessage("ERROR : BumperSensorComp::onStop() -> Can't disable the Bumper Sensor API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType BumperSensorComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType BumperSensorComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType BumperSensorComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType BumperSensorComp::onDestroy()
{
	//	API 핸들 삭제
	if(bumperSensor != NULL) {
		bumperSensor->Finalize();
		delete bumperSensor;
		bumperSensor = NULL;
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

ReturnType BumperSensorComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType BumperSensorComp::onExecute()
{
	if(bumperSensor == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	vector<bool> result;
	if(bumperSensor->GetBumperSensorData(result) < 0) {
		PrintMessage("ERROR : BumperSensorComp::onExecute() -> Can't get the bumper sensor data.\n");
		return OPROS_CALL_API_ERROR;
	}

	bumperData.push(result);

	return OPROS_SUCCESS;
}
	
ReturnType BumperSensorComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType BumperSensorComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool BumperSensorComp::SetParameter(Property parameter)
{
	if(bumperSensor == NULL) {
		return false;
	}

	if(bumperSensor->SetParameter(parameter) < 0) {
		return false;
	}

	return true;
}

Property BumperSensorComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(bumperSensor == NULL) {
		error = -1;
		return parameter;
	}

	if(bumperSensor->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}

int BumperSensorComp::GetError()
{
	return error;
}

vector<bool> BumperSensorComp::GetBumperSensorData()
{
	vector<bool> result;

	error = 0;
	if(bumperSensor == NULL) {
		error = -1;
		return result;
	}

	if(bumperSensor->GetBumperSensorData(result) < 0) {
		error = -1;
	}

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
	return new BumperSensorComp();
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
	return new BumperSensorComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif


