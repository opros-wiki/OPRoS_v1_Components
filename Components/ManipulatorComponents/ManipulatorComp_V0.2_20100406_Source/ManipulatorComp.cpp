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

#include "ManipulatorComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
ManipulatorComp::ManipulatorComp()
{
	hOprosAPI = NULL;
	manipulator = NULL;
	error = 0;
	
	portSetup();
}

//
// constructor declaration (with name)
//
ManipulatorComp::ManipulatorComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	manipulator = NULL;
	error = 0;

	portSetup();
}

//
// destructor declaration
//

ManipulatorComp::~ManipulatorComp() 
{
	onDestroy();
}

void ManipulatorComp::portSetup() {

	// provided service port setup
	ProvidedServicePort *pa1;
	pa1=new ManipulatorServiceProvided(this);

	addPort("ManipulatorService",pa1);

}

// Call back Declaration
ReturnType ManipulatorComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("DllName") == false) {
		PrintMessage("ERROR : ManipulatorComp::onInitialize() -> Can't find the DllName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("DllName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : ManipulatorComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("DllName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	API 로드
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : ManipulatorComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("DllName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : ManipulatorComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("DllName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : ManipulatorComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	manipulator = dynamic_cast<Manipulator *>(getOprosAPI());
	if(manipulator == NULL) {
		PrintMessage("ERROR : ManipulatorComp::onInitialize() -> Can't get a handle of Manipulator API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	//	API 초기화
	if(manipulator->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : ManipulatorComp::onInitialize() -> Can't intilaize a Manipulator API\n");
		
		delete manipulator;
		manipulator = NULL;

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

ReturnType ManipulatorComp::onStart()
{
	// user code here
	if(manipulator == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 enable를 호출
	if(manipulator->Enable() < 0) {
		PrintMessage("ERROR : ManipulatorComp::onStart() -> Can't enable the Manipulator API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	//	API의 StartHoming 호출
	if(manipulator->StartHoming() < 0) {
		PrintMessage("ERROR : ManipulatorComp::onStart() -> Can't run Homing\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType ManipulatorComp::onStop()
{
	// user code here
	if(manipulator == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 disable 호출
	if(manipulator->Disable() < 0) {
		PrintMessage("ERROR : ManipulatorComp::onStop() -> Can't disable the Manipulator API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType ManipulatorComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType ManipulatorComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType ManipulatorComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType ManipulatorComp::onDestroy()
{
	//	API 핸들 삭제
	if(manipulator != NULL) {
		manipulator->Finalize();
		delete manipulator;
		manipulator = NULL;
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

ReturnType ManipulatorComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType ManipulatorComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType ManipulatorComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType ManipulatorComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool ManipulatorComp::SetParameter(Property parameter)
{
	// user code here
	if(manipulator == NULL) {
		return false;
	}

	if(manipulator->SetParameter(parameter) < 0) {
		return false;
	}

	return true;
}
Property ManipulatorComp::GetParameter()
{
	// user code here
	Property parameter;
	error = 0;

	if(manipulator == NULL) {
		error = -1;
		return parameter;
	}

	if(manipulator->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}
int ManipulatorComp::GetError()
{
	// user code here
	return error;
}
bool ManipulatorComp::Stop()
{
	// user code here
	if(manipulator == NULL) {
		return false;
	}

	if(manipulator->Stop() < 0) {
		return false;
	}

	return true;
}

bool ManipulatorComp::SetPower(vector<double> power,vector<unsigned long> time)
{
	if(manipulator == NULL) {
		return false;
	}

	if(manipulator->SetPower(power, time) < 0) {
		return false;
	}

	return true;
}
vector<double> ManipulatorComp::GetPower()
{
	vector<double> power;

	error = 0;
	if(manipulator == NULL) {
		error = -1;
		return power;
	}

	if(manipulator->GetPower(power) < 0) {
		error = -1;
	}

	return power;
}
bool ManipulatorComp::SetVelocity(vector<double> velocity,vector<unsigned long> time)
{
	if(manipulator == NULL) {
		return false;
	}

	if(manipulator->SetVelocity(velocity, time) < 0) {
		return false;
	}

	return false;
}
vector<double> ManipulatorComp::GetVelocity()
{
	vector<double> velocity;

	error = 0;
	if(manipulator == NULL) {
		error = -1;
		return velocity;
	}

	if(manipulator->GetVelocity(velocity) < 0) {
		error = -1;
	}

	return velocity;
}
bool ManipulatorComp::SetPosition(vector<double> position,vector<unsigned long> time)
{
	if(manipulator == NULL) {
		return false;
	}

	if(manipulator->SetPosition(position, time) < 0) {
		return false;
	}

	return true;
}
vector<double> ManipulatorComp::GetPosition()
{
	vector<double> position;

	error = 0;
	if(manipulator == NULL) {
		error = -1;
		return position;
	}

	if(manipulator->GetPosition(position) < 0) {
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
	return new ManipulatorComp();
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
	return new ManipulatorComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

