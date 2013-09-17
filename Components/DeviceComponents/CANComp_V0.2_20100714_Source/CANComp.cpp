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

#include "CANComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
CANComp::CANComp()
{
	hOprosAPI = NULL;
	can = NULL;
	error = 0;

	portSetup();
}

//
// constructor declaration (with name)
//
CANComp::CANComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	can = NULL;
	error = 0;
	
	portSetup();
}

//
// destructor declaration
//

CANComp::~CANComp() 
{
	onDestroy();
}

void CANComp::portSetup() {

	// provided service port setup
	ProvidedServicePort *pa1;
	pa1=new CANServiceProvided(this);

	addPort("CANService",pa1);

}

// Call back Declaration
ReturnType CANComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : CANComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	//	Load a DLL
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("APIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : CANComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	Load a API
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : CANComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	//	Load a shared library
	hOprosAPI = dlopen(parameter.GetValue("DllName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : CANComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("DllName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	//	Load a API
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : CANComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	can = dynamic_cast<CAN *>(getOprosAPI());
	if(can == NULL) {
		PrintMessage("ERROR : CANComp::onInitialize() -> Can't get a handle of CAN API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	if(can->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : CANComp::onInitialize() -> Can't initialize a CAN API\n");
		delete can;
		can = NULL;

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

ReturnType CANComp::onStart()
{
	if(can == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	if(can->Enable() == API_ERROR) {
		PrintMessage("ERROR : CANComp::onStart() -> Can't enable the CAN API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType CANComp::onStop()
{
	if(can == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 disable 호출
	if(can->Disable() < 0) {
		PrintMessage("ERROR : CANComp::onStop() -> Can't disable the CAN API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType CANComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CANComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CANComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CANComp::onDestroy()
{
	//	Delete a handle of API
	if(can != NULL) {
		delete can;
		can = NULL;
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

ReturnType CANComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CANComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType CANComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CANComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool CANComp::SetParameter(Property parameter)
{
	if(can == NULL) {
		return false;
	}

	if(can->SetParameter(parameter) == API_ERROR) {
		return false;
	}

	return true;
}

Property CANComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(can == NULL) {
		error = -1;
		return parameter;
	}

	if(can->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}

int CANComp::GetError()
{
	return error;
}

bool CANComp::WriteCANObject(CANObject canObject)
{
	if(can == NULL) {
		return false;
	}

	if(can->Write(canObject.id, &canObject.data[0], canObject.data.size()) < 0) {
		return false;
	}

	return true;
}

CANObject CANComp::ReadCANObject()
{
	CANObject canObject;

	if(can == NULL) {
		error = -1;
		return canObject;
	}

	if(can->Read(canObject.id, &canObject.data[0], 8) < 0) {
		error = -1;
	}

	return canObject;
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
	return new CANComp();
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
	return new CANComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

