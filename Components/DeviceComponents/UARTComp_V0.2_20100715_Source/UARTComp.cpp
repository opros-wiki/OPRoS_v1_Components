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

#include "UARTComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
UARTComp::UARTComp()
{
	hOprosAPI = NULL;
	uart = NULL;
	error = 0;

	portSetup();
}

//
// constructor declaration (with name)
//
UARTComp::UARTComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	uart = NULL;
	error = 0;

	portSetup();
}

//
// destructor declaration
//

UARTComp::~UARTComp() 
{
	onDestroy();
}

void UARTComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new UARTServiceProvided(this);

	addPort("UARTService",pa1);

}

// Call back Declaration
ReturnType UARTComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : UARTComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	//	Load a DLL
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("APIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : UARTComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	Load a API
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : UARTComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	//	Load a shared library
	hOprosAPI = dlopen(parameter.GetValue("DllName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : UARTComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("DllName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	//	Load a API
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : UARTComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	uart = dynamic_cast<UART *>(getOprosAPI());
	if(uart == NULL) {
		PrintMessage("ERROR : UARTComp::onInitialize() -> Can't get a handle of UART API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	if(uart->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : UARTComp::onInitialize() -> Can't initialize a UART API\n");
		delete uart;
		uart = NULL;

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

ReturnType UARTComp::onStart()
{
	if(uart == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	if(uart->Enable() == API_ERROR) {
		PrintMessage("ERROR : UARTComp::onStart() -> Can't enable the UART API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType UARTComp::onStop()
{
	if(uart == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 disable 호출
	if(uart->Disable() < 0) {
		PrintMessage("ERROR : UARTComp::onStop() -> Can't disable the UART API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType UARTComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType UARTComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType UARTComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType UARTComp::onDestroy()
{
	//	Delete a handle of API
	if(uart != NULL) {
		delete uart;
		uart = NULL;
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

ReturnType UARTComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType UARTComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType UARTComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType UARTComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool UARTComp::SetParameter(Property parameter)
{
	if(uart == NULL) {
		return false;
	}

	if(uart->SetParameter(parameter) == API_ERROR) {
		return false;
	}

	return true;
}

Property UARTComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(uart == NULL) {
		error = -1;
		return parameter;
	}

	if(uart->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}
int UARTComp::GetError()
{
	return error;
}

int UARTComp::WriteData(vector<unsigned char> data)
{
	if(uart == NULL) {
		return -1;
	}

	return uart->Write(&data[0], (int)data.size());
}

vector<unsigned char> UARTComp::ReadData(int size)
{
	vector<unsigned char> data;
	error = 0;

	if(uart == NULL) {
		error = -1;
		return data;
	}

	data.resize(size);
	int ret = uart->Read(&data[0], size);
	
	if(ret < 0) {
		error = -1;
		data.clear();
		return data;
	}
	
	vector<unsigned char> buf(ret);
	memcpy(&buf[0], &data[0], ret);

	return buf;
}

bool UARTComp::Lock()
{
	if(uart == NULL) {
		return false;
	}

	if(uart->Lock() == API_ERROR) {
		return false;
	}

	return true;
}

bool UARTComp::Unlock()
{
	if(uart == NULL) {
		return false;
	}

	if(uart->Unlock() == API_ERROR) {
		return false;
	}

	return true;
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
	return new UARTComp();
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
	return new UARTComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

