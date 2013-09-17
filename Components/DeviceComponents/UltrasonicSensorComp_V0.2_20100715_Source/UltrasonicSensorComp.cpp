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

#include "UltrasonicSensorComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
UltrasonicSensorComp::UltrasonicSensorComp()
{
	hOprosAPI = NULL;
	ultrasonicSensor = NULL;
	error = 0;
	
	portSetup();
}

//
// constructor declaration (with name)
//
UltrasonicSensorComp::UltrasonicSensorComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	ultrasonicSensor = NULL;
	error = 0;
	
	portSetup();
}

//
// destructor declaration
//

UltrasonicSensorComp::~UltrasonicSensorComp() 
{
	onDestroy();
}

void UltrasonicSensorComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new UltrasonicSensorServiceProvided(this);

	addPort("UltrasonicSensorService",pa1);

	// data port setup

	addPort("ultrasonicData", &ultrasonicData);

}

// Call back Declaration
ReturnType UltrasonicSensorComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : UltrasonicSensorComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("APIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : UltrasonicSensorComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	API 로드
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : UltrasonicSensorComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("APIName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : UltrasonicSensorComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : UltrasonicSensorComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	ultrasonicSensor = dynamic_cast<UltrasonicSensor *>(getOprosAPI());
	if(ultrasonicSensor == NULL) {
		PrintMessage("ERROR : UltrasonicSensorComp::onInitialize() -> Can't get a handle of Ultrasonic Sensor API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	//	API 초기화
	if(ultrasonicSensor->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : UltrasonicSensorComp::onInitialize() -> Can't intilaize a Ultrasonic Sensor API\n");
		
		delete ultrasonicSensor;
		ultrasonicSensor = NULL;

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

ReturnType UltrasonicSensorComp::onStart()
{
	if(ultrasonicSensor == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 enable를 호출
	if(ultrasonicSensor->Enable() < 0) {
		PrintMessage("ERROR : UltrasonicSensorComp::onStart() -> Can't enable the Ultrasonic Sensor API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType UltrasonicSensorComp::onStop()
{
	if(ultrasonicSensor == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 disable 호출
	if(ultrasonicSensor->Disable() < 0) {
		PrintMessage("ERROR : UltrasonicSensorComp::onStop() -> Can't disable the Ultrasonic Sensor API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType UltrasonicSensorComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType UltrasonicSensorComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType UltrasonicSensorComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType UltrasonicSensorComp::onDestroy()
{
	//	API 핸들 삭제
	if(ultrasonicSensor != NULL) {
		ultrasonicSensor->Finalize();
		delete ultrasonicSensor;
		ultrasonicSensor = NULL;
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

ReturnType UltrasonicSensorComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType UltrasonicSensorComp::onExecute()
{
	if(ultrasonicSensor == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	vector<double> result;
	if(ultrasonicSensor->GetUltrasonicSensorData(result) < 0) {
		PrintMessage("ERROR : UltrasonicSensorComp::onExecute() -> Can't get the data of Ultrasonic Sensor.\n");
		return OPROS_CALL_API_ERROR;
	}

	ultrasonicData.push(result);

	return OPROS_SUCCESS;
}
	
ReturnType UltrasonicSensorComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType UltrasonicSensorComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool UltrasonicSensorComp::SetParameter(Property parameter)
{
	if(ultrasonicSensor == NULL) {
		return false;
	}

	if(ultrasonicSensor->SetParameter(parameter) < 0) {
		return false;
	}

	return true;
}

Property UltrasonicSensorComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(ultrasonicSensor == NULL) {
		error = -1;
		return parameter;
	}

	if(ultrasonicSensor->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}

int UltrasonicSensorComp::GetError()
{
	return error;
}

vector<double> UltrasonicSensorComp::GetUltrasonicSensorData()
{
	vector<double> result;

	error = 0;
	if(ultrasonicSensor == NULL) {
		error = -1;
		return result;
	}

	if(ultrasonicSensor->GetUltrasonicSensorData(result) < 0) {
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
	return new UltrasonicSensorComp();
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
	return new UltrasonicSensorComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

