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

#include "EncoderComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
EncoderComp::EncoderComp()
{
	hOprosAPI = NULL;
	encoder = NULL;
	error = 0;
	
	portSetup();
}

//
// constructor declaration (with name)
//
EncoderComp::EncoderComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	encoder = NULL;
	error = 0;
	
	portSetup();
}

//
// destructor declaration
//

EncoderComp::~EncoderComp() 
{
	onDestroy();
}

void EncoderComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new EncoderServiceProvided(this);

	addPort("EncoderService",pa1);

	// data port setup

	addPort("encoderData", &encoderData);

}

// Call back Declaration
ReturnType EncoderComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : EncoderComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("APIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : EncoderComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	API 로드
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : EncoderComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("APIName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : EncoderComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : EncoderComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	encoder = dynamic_cast<Encoder *>(getOprosAPI());
	if(encoder == NULL) {
		PrintMessage("ERROR : EncoderComp::onInitialize() -> Can't get a handle of Encoder API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	//	API 초기화
	if(encoder->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : EncoderComp::onInitialize() -> Can't intilaize a Encoder API\n");
		
		delete encoder;
		encoder = NULL;

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

ReturnType EncoderComp::onStart()
{
	if(encoder == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	if(encoder->Enable() < 0) {
		PrintMessage("ERROR : EncoderComp::onStart() -> Can't enable the Encoder API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType EncoderComp::onStop()
{
	if(encoder == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	if(encoder->Disable() < 0) {
		PrintMessage("ERROR : EncoderComp::onStop() -> Can't disable the Encoder API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType EncoderComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType EncoderComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType EncoderComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType EncoderComp::onDestroy()
{
	//	Delete a handle of API
	if(encoder != NULL) {
		delete encoder;
		encoder = NULL;
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

ReturnType EncoderComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType EncoderComp::onExecute()
{
	if(encoder == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	lock.Lock();
	vector<double> result;
	if(encoder->GetEncoderData(result) < 0) {
		lock.Unlock();
		PrintMessage("ERROR : EncoderComp::onExecute() -> Can't get the data of Encoder.\n");
		return OPROS_CALL_API_ERROR;
	}
	lock.Unlock();

	encoderData.push(result);

	return OPROS_SUCCESS;
}
	
ReturnType EncoderComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType EncoderComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool EncoderComp::SetParameter(Property parameter)
{
	if(encoder == NULL) {
		return false;
	}

	if(encoder->SetParameter(parameter) == API_ERROR) {
		return false;
	}

	return true;
}

Property EncoderComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(encoder == NULL) {
		error = -1;
		return parameter;
	}

	if(encoder->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}

int EncoderComp::GetError()
{
	return error;
}

vector<double> EncoderComp::GetEncoderData()
{
	vector<double> result;

	error = 0;
	if(encoder == NULL) {
		error = -1;
		return result;
	}

	lock.Lock();
	if(encoder->GetEncoderData(result) < 0) {
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
	return new EncoderComp();
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
	return new EncoderComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

