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

#include "TouchSensorComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
TouchSensorComp::TouchSensorComp()
{
	hOprosAPI = NULL;
	touchSensor = NULL;
	error = 0;

	portSetup();
}

//
// constructor declaration (with name)
//
TouchSensorComp::TouchSensorComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	touchSensor = NULL;
	error = 0;

	portSetup();
}

//
// destructor declaration
//

TouchSensorComp::~TouchSensorComp() 
{
	onDestroy();
}

void TouchSensorComp::portSetup() {

	// provided service port setup
	ProvidedServicePort *pa1;
	pa1=new TouchSensorServiceProvided(this);

	addPort("TouchSensorService",pa1);

	// data port setup
	addPort("touchData", &touchData);

}

// Call back Declaration
ReturnType TouchSensorComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : TouchSensorComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("DllName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : TouchSensorComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("DllName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	API 로드
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : TouchSensorComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("DllName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : TouchSensorComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : TouchSensorComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	touchSensor = dynamic_cast<TouchSensor *>(getOprosAPI());
	if(touchSensor == NULL) {
		PrintMessage("ERROR : TouchSensorComp::onInitialize() -> Can't get a handle of TouchSensor API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	//	API 초기화
	if(touchSensor->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : TouchSensorComp::onInitialize() -> Can't intilaize a TouchSensor API\n");
		
		delete touchSensor;
		touchSensor = NULL;

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

ReturnType TouchSensorComp::onStart()
{
	if(touchSensor == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 enable를 호출
	if(touchSensor->Enable() < 0) {
		PrintMessage("ERROR : TouchSensorComp::onStart() -> Can't enable the Touch Sensor API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType TouchSensorComp::onStop()
{
	if(touchSensor == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 disable 호출
	if(touchSensor->Disable() < 0) {
		PrintMessage("ERROR : GripperComp::onStop() -> Can't disable the Touch Sensor API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType TouchSensorComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType TouchSensorComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType TouchSensorComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType TouchSensorComp::onDestroy()
{
	//	API 핸들 삭제
	if(touchSensor != NULL) {
		touchSensor->Finalize();
		delete touchSensor;
		touchSensor = NULL;
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

ReturnType TouchSensorComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType TouchSensorComp::onExecute()
{
	if(touchSensor == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	vector<bool> result;
	if(touchSensor->GetTouchSensorData(result) < 0) {
		PrintMessage("ERROR : TouchSensorComp::onExecute() -> Can't get the touch sensor data.\n");
		return OPROS_CALL_API_ERROR;
	}

	touchData.push(result);

	return OPROS_SUCCESS;
}
	
ReturnType TouchSensorComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType TouchSensorComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}


bool TouchSensorComp::SetParameter(Property parameter)
{
	if(touchSensor == NULL) {
		return false;
	}

	if(touchSensor->SetParameter(parameter) < 0) {
		return false;
	}

	return true;
}
Property TouchSensorComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(touchSensor == NULL) {
		error = -1;
		return parameter;
	}

	if(touchSensor->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}
int TouchSensorComp::GetError()
{
	return error;
}
vector<bool> TouchSensorComp::GetTouchSensorData()
{
	vector<bool> result;

	error = 0;
	if(touchSensor == NULL) {
		error = -1;
		return result;
	}

	if(touchSensor->GetTouchSensorData(result) < 0) {
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
	return new TouchSensorComp();
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
	return new TouchSensorComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

