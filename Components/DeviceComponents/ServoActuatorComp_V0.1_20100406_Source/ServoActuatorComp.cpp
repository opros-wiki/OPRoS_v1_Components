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

using namespace opros;

#include "ServoActuatorServiceProvided.h"
#include "ServoActuatorComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
ServoActuatorComp::ServoActuatorComp()
{
	hOprosAPI = NULL;
	servoActuator = NULL;
	error = 0;
	
	portSetup();
}

//
// constructor declaration (with name)
//
ServoActuatorComp::ServoActuatorComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	servoActuator = NULL;
	error = 0;
	
	portSetup();
}

//
// destructor declaration
//

ServoActuatorComp::~ServoActuatorComp() 
{
	onDestroy();
}

void ServoActuatorComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new ServoActuatorServiceProvided(this);

	addPort("ServoActuatorService",pa1);

}

// Call back Declaration
ReturnType ServoActuatorComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("DllName") == false) {
		PrintMessage("ERROR : ServoActuatorComp::onInitialize() -> Can't find the DllName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("DllName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : ServoActuatorComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("DllName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	API 로드
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : ServoActuatorComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("DllName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : ServoActuatorComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("DllName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : ServoActuatorComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	servoActuator = dynamic_cast<ServoActuator *>(getOprosAPI());
	if(servoActuator == NULL) {
		PrintMessage("ERROR : ServoActuatorComp::onInitialize() -> Can't get a handle of ServoActuator API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	//	API 초기화
	if(servoActuator->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : ServoActuatorComp::onInitialize() -> Can't intilaize a ServoActuator API\n");
		
		delete servoActuator;
		servoActuator = NULL;

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

ReturnType ServoActuatorComp::onStart()
{
	if(servoActuator == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	if(servoActuator->Enable() < 0) {
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType ServoActuatorComp::onStop()
{
	// user code here
	if(servoActuator == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	if(servoActuator->Disable() < 0) {
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType ServoActuatorComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType ServoActuatorComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType ServoActuatorComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType ServoActuatorComp::onDestroy()
{
	//	API 핸들 삭제
	if(servoActuator != NULL) {
		servoActuator->Finalize();
		delete servoActuator;
		servoActuator = NULL;
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

ReturnType ServoActuatorComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType ServoActuatorComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType ServoActuatorComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType ServoActuatorComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool ServoActuatorComp::SetParameter(Property parameter)
{
	// user code here
	if(servoActuator == NULL) {
		return false;
	}

	if(servoActuator->SetParameter(parameter) < 0) {
		return false;
	}

	return true;
}
Property ServoActuatorComp::GetParameter()
{
	// user code here
	Property parameter;
	error = 0;

	if(servoActuator == NULL) {
		error = -1;
		return parameter;
	}

	if(servoActuator->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}
int ServoActuatorComp::GetError()
{
	// user code here
	return 0;
}
bool ServoActuatorComp::SetPower(double power,unsigned long time)
{
	// user code here
	if(servoActuator == NULL) {
		return false;
	}

	if(servoActuator->SetPower(power, time) < 0) {
		return false;
	}

	return true;
}
double ServoActuatorComp::GetPower()
{
	double power = 0.0;

	error = 0;
	if(servoActuator == NULL) {
		error = -1;
		return power;
	}

	if(servoActuator->GetPower(power) < 0) {
		error = -1;
	}

	return power;
}
bool ServoActuatorComp::SetVelocity(double velocity,unsigned long time)
{
	// user code here
	if(servoActuator == NULL) {
		return false;
	}

	if(servoActuator->SetVelocity(velocity, time) < 0) {
		return false;
	}

	return true;
}
double ServoActuatorComp::GetVelocity()
{
	double velocity = 0.0;

	error = 0;
	if(servoActuator == NULL) {
		error = -1;
		return velocity;
	}

	if(servoActuator->GetVelocity(velocity) < 0) {
		error = -1;
	}

	return velocity;
}
bool ServoActuatorComp::SetPosition(double position,unsigned long time)
{
	// user code here
	if(servoActuator == NULL) {
		return false;
	}

	if(servoActuator->SetPosition(position, time) < 0) {
		return false;
	}

	return true;
}
double ServoActuatorComp::GetPosition()
{
	double position = 0.0;

	error = 0;
	if(servoActuator == NULL) {
		error = -1;
		return position;
	}

	if(servoActuator->GetPosition(position) < 0) {
		error = -1;
	}

	return position;
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
	return new ServoActuatorComp();
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
	return new ServoActuatorComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

