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

#include "PositionSensorComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
PositionSensorComp::PositionSensorComp()
{
	hOprosAPI = NULL;
	positionSensor = NULL;
	error = 0;

	portSetup();
}

//
// constructor declaration (with name)
//
PositionSensorComp::PositionSensorComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	positionSensor = NULL;
	error = 0;
	
	portSetup();
}

//
// destructor declaration
//

PositionSensorComp::~PositionSensorComp() 
{
	onDestroy();
}

void PositionSensorComp::portSetup() {

	// provided service port setup
	ProvidedServicePort *pa1;
	pa1=new PositionSensorServiceProvided(this);

	addPort("PositionSensorService",pa1);

	// data port setup
	addPort("positionData", &positionData);

}

// Call back Declaration
ReturnType PositionSensorComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : PositionSensorComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("APIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : PositionSensorComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	API 로드
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : PositionSensorComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("APIName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : PositionSensorComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : PositionSensorComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	positionSensor = dynamic_cast<PositionSensor *>(getOprosAPI());
	if(positionSensor == NULL) {
		PrintMessage("ERROR : PositionSensorComp::onInitialize() -> Can't get a handle of PositionSensor API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	//	API 초기화
	if(positionSensor->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : PositionSensorComp::onInitialize() -> Can't intilaize a PositionSensor API\n");
		
		delete positionSensor;
		positionSensor = NULL;

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

ReturnType PositionSensorComp::onStart()
{
	if(positionSensor == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 enable를 호출
	if(positionSensor->Enable() < 0) {
		PrintMessage("ERROR : PositionSensorComp::onStart() -> Can't enable the Position Sensor API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType PositionSensorComp::onStop()
{
	if(positionSensor == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 disable 호출
	if(positionSensor->Disable() < 0) {
		PrintMessage("ERROR : PositionSensorComp::onStop() -> Can't disable the Position Sensor API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType PositionSensorComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType PositionSensorComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType PositionSensorComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType PositionSensorComp::onDestroy()
{
	//	API 핸들 삭제
	if(positionSensor != NULL) {
		positionSensor->Finalize();
		delete positionSensor;
		positionSensor = NULL;
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

ReturnType PositionSensorComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType PositionSensorComp::onExecute()
{
	if(positionSensor == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	vector<ObjectPosition> result;
	if(positionSensor->GetPositionSensorData(result) < 0) {
		PrintMessage("ERROR : PositionSensorComp::onExecute() -> Can't get the position sensor data.\n");
		return OPROS_CALL_API_ERROR;
	}

	positionData.push(result);

	return OPROS_SUCCESS;
}
	
ReturnType PositionSensorComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType PositionSensorComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool PositionSensorComp::SetParameter(Property parameter)
{
	if(positionSensor == NULL) {
		return false;
	}

	if(positionSensor->SetParameter(parameter) < 0) {
		return false;
	}

	return true;
}
Property PositionSensorComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(positionSensor == NULL) {
		error = -1;
		return parameter;
	}

	if(positionSensor->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}
int PositionSensorComp::GetError()
{
	return error;
}
vector<ObjectPosition> PositionSensorComp::GetPositionSensorData()
{
	vector<ObjectPosition> result;

	error = 0;
	if(positionSensor == NULL) {
		error = -1;
		return result;
	}

	if(positionSensor->GetPositionSensorData(result) < 0) {
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
	return new PositionSensorComp();
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
	return new PositionSensorComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

