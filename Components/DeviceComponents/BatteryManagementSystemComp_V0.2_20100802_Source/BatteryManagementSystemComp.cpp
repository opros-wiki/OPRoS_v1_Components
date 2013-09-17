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

#include "BatteryManagementSystemComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
BatteryManagementSystemComp::BatteryManagementSystemComp()
{
	hOprosAPI = NULL;
	bms = NULL;
	error = 0;
	
	portSetup();
}

//
// constructor declaration (with name)
//
BatteryManagementSystemComp::BatteryManagementSystemComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	bms = NULL;
	error = 0;
	
	portSetup();
}

//
// destructor declaration
//

BatteryManagementSystemComp::~BatteryManagementSystemComp() 
{
	onDestroy();
}

void BatteryManagementSystemComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new BatteryManagementSystemServiceProvided(this);

	addPort("BatteryManagementSystemService",pa1);

	// data port setup

	addPort("voltageData", &voltageData);

}

// Call back Declaration
ReturnType BatteryManagementSystemComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : BatteryManagementSystemComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("APIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : BatteryManagementSystemComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	API 로드
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : BatteryManagementSystemComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("APIName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : BatteryManagementSystemComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : BatteryManagementSystemComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	bms = dynamic_cast<BatteryManagementSystem *>(getOprosAPI());
	if(bms == NULL) {
		PrintMessage("ERROR : BatteryManagementSystemComp::onInitialize() -> Can't get a handle of Battery Managerment System API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	//	API 초기화
	if(bms->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : BatteryManagementSystemComp::onInitialize() -> Can't intilaize a Battery Managerment System API\n");
		delete bms;
		bms = NULL;

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

ReturnType BatteryManagementSystemComp::onStart()
{
	if(bms == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 enable를 호출
	if(bms->Enable() < 0) {
		PrintMessage("ERROR : BatteryManagementSystemComp::onStart() -> Can't enable the Battery Managerment System API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType BatteryManagementSystemComp::onStop()
{
	if(bms == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 disable 호출
	if(bms->Disable() < 0) {
		PrintMessage("ERROR : BatteryManagementSystemComp::onStop() -> Can't disable the Battery Managerment System API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType BatteryManagementSystemComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType BatteryManagementSystemComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType BatteryManagementSystemComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType BatteryManagementSystemComp::onDestroy()
{
	//	Delete a handle of API
	if(bms != NULL) {
		delete bms;
		bms = NULL;
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

ReturnType BatteryManagementSystemComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType BatteryManagementSystemComp::onExecute()
{
	if(bms == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	lock.Lock();
	double result;
	if(bms->GetBatteryVoltage(result) < 0) {
		lock.Unlock();
		PrintMessage("ERROR : BatteryManagementSystemComp::onExecute() -> Can't get the data of Battery Managerment System.\n");
		return OPROS_CALL_API_ERROR;
	}
	lock.Unlock();

	voltageData.push(result);

	return OPROS_SUCCESS;
}
	
ReturnType BatteryManagementSystemComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType BatteryManagementSystemComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool BatteryManagementSystemComp::SetParameter(Property parameter)
{
	if(bms == NULL) {
		return false;
	}

	if(bms->SetParameter(parameter) == API_ERROR) {
		return false;
	}

	return true;
}

Property BatteryManagementSystemComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(bms == NULL) {
		error = -1;
		return parameter;
	}

	if(bms->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}

int BatteryManagementSystemComp::GetError()
{
	return error;
}

double BatteryManagementSystemComp::GetBatteryVoltage()
{
	double result = 0.0;

	error = 0;
	if(bms == NULL) {
		error = -1;
		return result;
	}

	lock.Lock();
	if(bms->GetBatteryVoltage(result) < 0) {
		error = -1;
	}
	lock.Unlock();

	return result;
}

vector< double > BatteryManagementSystemComp::GetCellVoltage()
{
	vector<double> result;

	error = 0;
	if(bms == NULL) {
		error = -1;
		return result;
	}

	lock.Lock();
	if(bms->GetCellVoltage(result) < 0) {
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
	return new BatteryManagementSystemComp();
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
	return new BatteryManagementSystemComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

