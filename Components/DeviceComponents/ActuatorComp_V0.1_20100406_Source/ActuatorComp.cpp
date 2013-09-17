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

#include "ActuatorComp.h"
#include "OprosPrintMessage.h"

using namespace opros;

//
// constructor declaration
//
ActuatorComp::ActuatorComp()
{
	hOprosAPI = NULL;
	actuator = NULL;
	error = 0;

	portSetup();
}

//
// constructor declaration (with name)
//
ActuatorComp::ActuatorComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	actuator = NULL;
	error = 0;

	portSetup();
}

//
// destructor declaration
//

ActuatorComp::~ActuatorComp() 
{
	onDestroy();
}

void ActuatorComp::portSetup() 
{
	// provided service port setup
	ProvidedServicePort *pa1;
	pa1=new ActuatorServiceProvided(this);

	addPort("ActuatorService",pa1);

}

// Call back Declaration
ReturnType ActuatorComp::onInitialize()
{
	// user code here
	
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("DllName") == false) {
		PrintMessage("ERROR : ActuatorComp::onInitialize() -> Can't find the DllName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("DllName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : ActuatorComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("DllName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	API 로드
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : ActuatorComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("DllName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : ActuatorComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("DllName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : ActuatorComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	actuator = dynamic_cast<Actuator *>(getOprosAPI());
	if(actuator == NULL) {
		PrintMessage("ERROR : ActuatorComp::onInitialize() -> Can't get a handle of Actuator API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	//	API 초기화
	if(actuator->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : ActuatorComp::onInitialize() -> Can't intilaize a Actuator API\n");
		
		delete actuator;
		actuator = NULL;

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

ReturnType ActuatorComp::onStart()
{
	// user code here
	if(actuator == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	if(actuator->Enable() < 0) {
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType ActuatorComp::onStop()
{
	if(actuator == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	if(actuator->Disable() < 0) {
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType ActuatorComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType ActuatorComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType ActuatorComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType ActuatorComp::onDestroy()
{
	//	API 핸들 삭제
	if(actuator != NULL) {
		actuator->Finalize();
		delete actuator;
		actuator = NULL;
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

ReturnType ActuatorComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType ActuatorComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType ActuatorComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType ActuatorComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}


bool ActuatorComp::SetParameter(Property parameter)
{
	// user code here
	if(actuator == NULL) {
		return false;
	}

	if(actuator->SetParameter(parameter) < 0) {
		return false;
	}

	return true;
}
Property ActuatorComp::GetParameter()
{
	// user code here
	Property parameter;

	if(actuator == NULL) {
		error = -1;
		return parameter;
	}

	if(actuator->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}
int ActuatorComp::GetError()
{
	// user code here
	return error;
}
bool ActuatorComp::SetPower(double power,unsigned long time)
{
	// user code here
	if(actuator == NULL) {
		return false;
	}

	if(actuator->SetPower(power, time) < 0) {
		return false;
	}

	return true;
}
double ActuatorComp::GetPower()
{
	// user code here
	if(actuator == NULL) {
		error = -1;
		return 0.0;
	}

	double power;
	if(actuator->GetPower(power) < 0) {
		error = -1;
		return 0.0;
	}

	return power;
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
	return new ActuatorComp();
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
	return new ActuatorComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

