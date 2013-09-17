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

#include "TCPIPComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
TCPIPComp::TCPIPComp()
{
	hOprosAPI = NULL;
	tcpip = NULL;
	error = 0;

	portSetup();
}

//
// constructor declaration (with name)
//
TCPIPComp::TCPIPComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	tcpip = NULL;
	error = 0;

	portSetup();
}

//
// destructor declaration
//

TCPIPComp::~TCPIPComp() 
{
	onDestroy();
}

void TCPIPComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new TCPIPServiceProvided(this);

	addPort("TCPIPService",pa1);

}

// Call back Declaration
ReturnType TCPIPComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : TCPIPComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

#if defined(WIN32)
	//	Load a DLL
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("APIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : TCPIPComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	Load a API
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : TCPIPComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	//	Load a shared library
	hOprosAPI = dlopen(parameter.GetValue("DllName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : TCPIPComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("DllName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	//	Load a API
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : TCPIPComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	tcpip = dynamic_cast<TCPIP *>(getOprosAPI());
	if(tcpip == NULL) {
		PrintMessage("ERROR : TCPIPComp::onInitialize() -> Can't get a handle of TCPIP API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	if(tcpip->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : TCPIPComp::onInitialize() -> Can't initialize a TCPIP API\n");
		delete tcpip;
		tcpip = NULL;

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

ReturnType TCPIPComp::onStart()
{
	if(tcpip == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	if(tcpip->Enable() == API_ERROR) {
		PrintMessage("ERROR : TCPIPComp::onStart() -> Can't enable the TCPIP API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType TCPIPComp::onStop()
{
	if(tcpip == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	if(tcpip->Disable() < 0) {
		PrintMessage("ERROR : TCPIPComp::onStop() -> Can't disable the TCPIP API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType TCPIPComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType TCPIPComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType TCPIPComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType TCPIPComp::onDestroy()
{
	//	Delete a handle of API
	if(tcpip != NULL) {
		delete tcpip;
		tcpip = NULL;
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

ReturnType TCPIPComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType TCPIPComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType TCPIPComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType TCPIPComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool TCPIPComp::SetParameter(Property parameter)
{
	if(tcpip == NULL) {
		return false;
	}

	if(tcpip->SetParameter(parameter) == API_ERROR) {
		return false;
	}

	return true;
}

Property TCPIPComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(tcpip == NULL) {
		error = -1;
		return parameter;
	}

	if(tcpip->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}

int TCPIPComp::GetError()
{
	return error;
}

int TCPIPComp::WriteData(vector<unsigned char> data)
{
	if(tcpip == NULL) {
		return -1;
	}

	return tcpip->Write(&data[0], (int)data.size());
}

vector<unsigned char> TCPIPComp::ReadData(int size)
{
	vector<unsigned char> data;
	error = 0;

	if(tcpip == NULL) {
		error = -1;
		return data;
	}

	data.resize(size);
	int ret = tcpip->Read(&data[0], size);
	
	if(ret < 0) {
		error = -1;
		data.clear();
		return data;
	}
	
	vector<unsigned char> buf(ret);
	memcpy(&buf[0], &data[0], ret);

	return buf;
}

bool TCPIPComp::Lock()
{
	if(tcpip == NULL) {
		return false;
	}

	if(tcpip->Lock() == API_ERROR) {
		return false;
	}

	return true;
}

bool TCPIPComp::Unlock()
{
	if(tcpip == NULL) {
		return false;
	}

	if(tcpip->Unlock() == API_ERROR) {
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
	return new TCPIPComp();
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
	return new TCPIPComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

