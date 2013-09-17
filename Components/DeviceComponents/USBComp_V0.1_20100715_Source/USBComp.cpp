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

#include "USBComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
USBComp::USBComp()
{
	hOprosAPI = NULL;
	usb = NULL;
	error = 0;

	portSetup();
}

//
// constructor declaration (with name)
//
USBComp::USBComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	usb = NULL;
	error = 0;
	
	portSetup();
}

//
// destructor declaration
//

USBComp::~USBComp() 
{
	onDestroy();
}

void USBComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new USBServiceProvided(this);

	addPort("USBService",pa1);

}

// Call back Declaration
ReturnType USBComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : USBComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

#if defined(WIN32)
	//	Load a DLL
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("APIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : USBComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	Load a API
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : USBComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	//	Load a shared library
	hOprosAPI = dlopen(parameter.GetValue("DllName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : USBComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("DllName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	//	Load a API
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : USBComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	usb = dynamic_cast<USB *>(getOprosAPI());
	if(usb == NULL) {
		PrintMessage("ERROR : USBComp::onInitialize() -> Can't get a handle of USB API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	if(usb->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : USBComp::onInitialize() -> Can't initialize a USB API\n");
		delete usb;
		usb = NULL;

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

ReturnType USBComp::onStart()
{
	if(usb == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	if(usb->Enable() == API_ERROR) {
		PrintMessage("ERROR : USBComp::onStart() -> Can't enable the USB API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType USBComp::onStop()
{
	if(usb == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	if(usb->Disable() < 0) {
		PrintMessage("ERROR : USBComp::onStop() -> Can't disable the USB API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType USBComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType USBComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType USBComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType USBComp::onDestroy()
{
	//	Delete a handle of API
	if(usb != NULL) {
		delete usb;
		usb = NULL;
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

ReturnType USBComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType USBComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType USBComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType USBComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool USBComp::SetParameter(Property parameter)
{
	if(usb == NULL) {
		return false;
	}

	if(usb->SetParameter(parameter) == API_ERROR) {
		return false;
	}

	return true;
}

Property USBComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(usb == NULL) {
		error = -1;
		return parameter;
	}

	if(usb->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}

int USBComp::GetError()
{
	return error;
}

int USBComp::WriteData(vector<unsigned char> data)
{
	if(usb == NULL) {
		return -1;
	}

	return usb->Write(&data[0], (int)data.size());
}

vector<unsigned char> USBComp::ReadData(int size)
{
	vector<unsigned char> data;
	error = 0;

	if(usb == NULL) {
		error = -1;
		return data;
	}

	data.resize(size);
	int ret = usb->Read(&data[0], size);
	
	if(ret < 0) {
		error = -1;
		data.clear();
		return data;
	}
	
	vector<unsigned char> buf(ret);
	memcpy(&buf[0], &data[0], ret);

	return buf;
}

bool USBComp::Lock()
{
	if(usb == NULL) {
		return false;
	}

	if(usb->Lock() == API_ERROR) {
		return false;
	}

	return true;
}

bool USBComp::Unlock()
{
	if(usb == NULL) {
		return false;
	}

	if(usb->Unlock() == API_ERROR) {
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
	return new USBComp();
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
	return new USBComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

