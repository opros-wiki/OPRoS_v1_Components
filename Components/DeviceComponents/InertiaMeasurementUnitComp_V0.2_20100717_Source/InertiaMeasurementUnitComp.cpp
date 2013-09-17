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

#include "InertiaMeasurementUnitComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
InertiaMeasurementUnitComp::InertiaMeasurementUnitComp()
{
	hOprosAPI = NULL;
	imu = NULL;
	error = 0;
	
	portSetup();
}

//
// constructor declaration (with name)
//
InertiaMeasurementUnitComp::InertiaMeasurementUnitComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	imu = NULL;
	error = 0;
	
	portSetup();
}

//
// destructor declaration
//

InertiaMeasurementUnitComp::~InertiaMeasurementUnitComp() 
{
	onDestroy();
}

void InertiaMeasurementUnitComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new InertiaMeasurementUnitServiceProvided(this);

	addPort("InertiaMeasurementUnitService",pa1);

	// data port setup

	addPort("imuData", &imuData);

}

// Call back Declaration
ReturnType InertiaMeasurementUnitComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : InertiaMeasurementUnitComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("APIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : InertiaMeasurementUnitComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	API 로드
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : InertiaMeasurementUnitComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("APIName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : InertiaMeasurementUnitComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : InertiaMeasurementUnitComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	imu = dynamic_cast<InertiaMeasurementUnit *>(getOprosAPI());
	if(imu == NULL) {
		PrintMessage("ERROR : InertiaMeasurementUnitComp::onInitialize() -> Can't get a handle of Inertia Measurement Unit API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	//	API 초기화
	if(imu->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : InertiaMeasurementUnitComp::onInitialize() -> Can't intilaize a Inertia Measurement Unit API\n");
		delete imu;
		imu = NULL;

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

ReturnType InertiaMeasurementUnitComp::onStart()
{
	if(imu == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	if(imu->Enable() < 0) {
		PrintMessage("ERROR : InertiaMeasurementUnitComp::onStart() -> Can't enable the Inertia Measurement Unit API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType InertiaMeasurementUnitComp::onStop()
{
	if(imu == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	if(imu->Disable() < 0) {
		PrintMessage("ERROR : InertiaMeasurementUnitComp::onStop() -> Can't disable the Inertia Measurement Unit API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType InertiaMeasurementUnitComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType InertiaMeasurementUnitComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType InertiaMeasurementUnitComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType InertiaMeasurementUnitComp::onDestroy()
{
	//	Delete a handle of API
	if(imu != NULL) {
		delete imu;
		imu = NULL;
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

ReturnType InertiaMeasurementUnitComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType InertiaMeasurementUnitComp::onExecute()
{
	if(imu == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	lock.Lock();
	vector<ObjectPosture> result;
	if(imu->GetInertiaMeasurementUnitData(result) < 0) {
		lock.Unlock();
		PrintMessage("ERROR : InertiaMeasurementUnitComp::onExecute() -> Can't get the data of Inertia Measurement Unit.\n");
		return OPROS_CALL_API_ERROR;
	}
	lock.Unlock();

	imuData.push(result);

	return OPROS_SUCCESS;
}
	
ReturnType InertiaMeasurementUnitComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType InertiaMeasurementUnitComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool InertiaMeasurementUnitComp::SetParameter(Property parameter)
{
	if(imu == NULL) {
		return false;
	}

	if(imu->SetParameter(parameter) == API_ERROR) {
		return false;
	}

	return true;
}

Property InertiaMeasurementUnitComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(imu == NULL) {
		error = -1;
		return parameter;
	}

	if(imu->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}

int InertiaMeasurementUnitComp::GetError()
{
	return error;
}

vector<ObjectPosture> InertiaMeasurementUnitComp::GetInertiaMeasurementUnitData()
{
	vector<ObjectPosture> result;

	error = 0;
	if(imu == NULL) {
		error = -1;
		return result;
	}

	lock.Lock();
	if(imu->GetInertiaMeasurementUnitData(result) < 0) {
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
	return new InertiaMeasurementUnitComp();
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
	return new InertiaMeasurementUnitComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

