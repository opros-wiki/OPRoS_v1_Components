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

#include "GyroSensorServiceProvided.h"
#include "GyroSensorComp.h"

#include "OprosPrintMessage.h"

//
// constructor declaration
//
GyroSensorComp::GyroSensorComp()
{
	hOprosAPI = NULL;
	gyroSensor = NULL;
	error = 0;

	portSetup();
}

//
// constructor declaration (with name)
//
GyroSensorComp::GyroSensorComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	gyroSensor = NULL;
	error = 0;

	portSetup();
}

//
// destructor declaration
//

GyroSensorComp::~GyroSensorComp() 
{
	onDestroy();
}

void GyroSensorComp::portSetup() {

	// provided service port setup
	ProvidedServicePort *pa1;
	pa1=new GyroSensorServiceProvided(this);

	addPort("GyroSensorService",pa1);

	// data port setup
	addPort("gyroData", &gyroData);

}

// Call back Declaration
ReturnType GyroSensorComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : GyroSensorComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("APIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : GyroSensorComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	API 로드
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : GyroSensorComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("APIName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : GyroSensorComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : GyroSensorComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	gyroSensor = dynamic_cast<GyroSensor *>(getOprosAPI());
	if(gyroSensor == NULL) {
		PrintMessage("ERROR : GyroSensorComp::onInitialize() -> Can't get a handle of GyroSensor API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	//	API 초기화
	if(gyroSensor->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : GyroSensorComp::onInitialize() -> Can't intilaize a GyroSensor API\n");
		
		delete gyroSensor;
		gyroSensor = NULL;

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

ReturnType GyroSensorComp::onStart()
{
	if(gyroSensor == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 enable를 호출
	if(gyroSensor->Enable() < 0) {
		PrintMessage("ERROR : GyroSensorComp::onStart() -> Can't enable the GyroSensor API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType GyroSensorComp::onStop()
{
	if(gyroSensor == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 disable 호출
	if(gyroSensor->Disable() < 0) {
		PrintMessage("ERROR : GripperComp::onStop() -> Can't disable the GyroSensor API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType GyroSensorComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType GyroSensorComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType GyroSensorComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType GyroSensorComp::onDestroy()
{
	//	API 핸들 삭제
	if(gyroSensor != NULL) {
		gyroSensor->Finalize();
		delete gyroSensor;
		gyroSensor = NULL;
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

ReturnType GyroSensorComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType GyroSensorComp::onExecute()
{
	if(gyroSensor == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	vector<ObjectLocation> result;
	if(gyroSensor->GetGyroSensorData(result) < 0) {
		PrintMessage("ERROR : GyroSensorComp::onExecute() -> Can't get the gyro sensor data.\n");
		return OPROS_CALL_API_ERROR;
	}

	gyroData.push(result);

	return OPROS_SUCCESS;
}
	
ReturnType GyroSensorComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType GyroSensorComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool GyroSensorComp::SetParameter(Property parameter)
{
	if(gyroSensor == NULL) {
		return false;
	}

	if(gyroSensor->SetParameter(parameter) < 0) {
		return false;
	}

	return true;
}

Property GyroSensorComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(gyroSensor == NULL) {
		error = -1;
		return parameter;
	}

	if(gyroSensor->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}

int GyroSensorComp::GetError()
{
	return error;
}

vector<ObjectLocation> GyroSensorComp::GetGyroSensorData()
{
	vector<ObjectLocation> result;

	error = 0;
	if(gyroSensor == NULL) {
		error = -1;
		return result;
	}

	if(gyroSensor->GetGyroSensorData(result) < 0) {
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
	return new GyroSensorComp();
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
	return new GyroSensorComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

