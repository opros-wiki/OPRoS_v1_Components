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

#include "AccelerationSensorComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
AccelerationSensorComp::AccelerationSensorComp()
{
	hOprosAPI = NULL;
	accelerationSensor = NULL;
	error = 0;
	
	portSetup();
}

//
// constructor declaration (with name)
//
AccelerationSensorComp::AccelerationSensorComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	accelerationSensor = NULL;
	error = 0;
	
	portSetup();
}

//
// destructor declaration
//

AccelerationSensorComp::~AccelerationSensorComp() 
{
	onDestroy();
}

void AccelerationSensorComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new AccelerationSensorServiceProvided(this);

	addPort("AccelerationSensorService",pa1);

	// data port setup

	addPort("accelerationData", &accelerationData);

}

// Call back Declaration
ReturnType AccelerationSensorComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : AccelerationSensorComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("APIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : AccelerationSensorComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	API 로드
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : AccelerationSensorComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("APIName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : AccelerationSensorComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : AccelerationSensorComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	accelerationSensor = dynamic_cast<AccelerationSensor *>(getOprosAPI());
	if(accelerationSensor == NULL) {
		PrintMessage("ERROR : AccelerationSensorComp::onInitialize() -> Can't get a handle of Acceleration Sensor API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	//	API 초기화
	if(accelerationSensor->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : AccelerationSensorComp::onInitialize() -> Can't intilaize a Acceleration Sensor API\n");
		
		delete accelerationSensor;
		accelerationSensor = NULL;

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

ReturnType AccelerationSensorComp::onStart()
{
	if(accelerationSensor == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 enable를 호출
	if(accelerationSensor->Enable() < 0) {
		PrintMessage("ERROR : AccelerationSensorComp::onStart() -> Can't enable the Acceleration Sensor API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType AccelerationSensorComp::onStop()
{
	if(accelerationSensor == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 disable 호출
	if(accelerationSensor->Disable() < 0) {
		PrintMessage("ERROR : AccelerationSensorComp::onStop() -> Can't disable the Acceleration Sensor API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType AccelerationSensorComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType AccelerationSensorComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType AccelerationSensorComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType AccelerationSensorComp::onDestroy()
{
	//	Delete a handle of API
	if(accelerationSensor != NULL) {
		delete accelerationSensor;
		accelerationSensor = NULL;
	}

	//	Delete a handle of shared library or DLL
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

ReturnType AccelerationSensorComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType AccelerationSensorComp::onExecute()
{
	if(accelerationSensor == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	lock.Lock();
	vector<double> result;
	if(accelerationSensor->GetAccelerationSensorData(result) < 0) {
		lock.Unlock();
		PrintMessage("ERROR : AccelerationSensorComp::onExecute() -> Can't get the data of Acceleration Sensor.\n");
		return OPROS_CALL_API_ERROR;
	}
	lock.Unlock();

	accelerationData.push(result);

	return OPROS_SUCCESS;
}
	
ReturnType AccelerationSensorComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType AccelerationSensorComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool AccelerationSensorComp::SetParameter(Property parameter)
{
	if(accelerationSensor == NULL) {
		return false;
	}

	if(accelerationSensor->SetParameter(parameter) == API_ERROR) {
		return false;
	}

	return true;
}

Property AccelerationSensorComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(accelerationSensor == NULL) {
		error = -1;
		return parameter;
	}

	if(accelerationSensor->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}

int AccelerationSensorComp::GetError()
{
	return error;
}

vector<double> AccelerationSensorComp::GetAccelerationData()
{
	vector<double> result;

	error = 0;
	if(accelerationSensor == NULL) {
		error = -1;
		return result;
	}

	lock.Lock();
	if(accelerationSensor->GetAccelerationSensorData(result) < 0) {
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
	return new AccelerationSensorComp();
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
	return new AccelerationSensorComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

