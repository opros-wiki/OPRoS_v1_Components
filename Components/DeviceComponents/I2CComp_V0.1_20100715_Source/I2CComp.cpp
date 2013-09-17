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

#include "I2CComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
I2CComp::I2CComp()
{
	hOprosAPI = NULL;
	i2c = NULL;
	error = 0;

	portSetup();
}

//
// constructor declaration (with name)
//
I2CComp::I2CComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	i2c = NULL;
	error = 0;

	portSetup();
}

//
// destructor declaration
//

I2CComp::~I2CComp() 
{
	onDestroy();
}

void I2CComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new I2CServiceProvided(this);

	addPort("I2CService",pa1);

}

// Call back Declaration
ReturnType I2CComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : I2CComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

#if defined(WIN32)
	//	Load a DLL
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("APIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : I2CComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	Load a API
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : I2CComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	//	Load a shared library
	hOprosAPI = dlopen(parameter.GetValue("DllName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : I2CComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("DllName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	//	Load a API
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : I2CComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	i2c = dynamic_cast<I2C *>(getOprosAPI());
	if(i2c == NULL) {
		PrintMessage("ERROR : I2CComp::onInitialize() -> Can't get a handle of I2C API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	if(i2c->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : I2CComp::onInitialize() -> Can't initialize a I2C API\n");
		delete i2c;
		i2c = NULL;

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

ReturnType I2CComp::onStart()
{
	if(i2c == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	if(i2c->Enable() == API_ERROR) {
		PrintMessage("ERROR : I2CComp::onStart() -> Can't enable the I2C API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType I2CComp::onStop()
{
	if(i2c == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	if(i2c->Disable() < 0) {
		PrintMessage("ERROR : I2CComp::onStop() -> Can't disable the I2C API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType I2CComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType I2CComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType I2CComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType I2CComp::onDestroy()
{
	//	Delete a handle of API
	if(i2c != NULL) {
		delete i2c;
		i2c = NULL;
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

ReturnType I2CComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType I2CComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType I2CComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType I2CComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool I2CComp::SetParameter(Property parameter)
{
	if(i2c == NULL) {
		return false;
	}

	if(i2c->SetParameter(parameter) == API_ERROR) {
		return false;
	}

	return true;
}

Property I2CComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(i2c == NULL) {
		error = -1;
		return parameter;
	}

	if(i2c->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}

int I2CComp::GetError()
{
	return error;
}

int I2CComp::WriteData(unsigned long address, vector<unsigned char> data)
{
	if(i2c == NULL) {
		return -1;
	}

	return i2c->Write(address, &data[0], (int)data.size());
}

vector<unsigned char> I2CComp::ReadData(unsigned long address, int size)
{
	vector<unsigned char> data;
	error = 0;

	if(i2c == NULL) {
		error = -1;
		return data;
	}

	data.resize(size);
	int ret = i2c->Read(address, &data[0], size);
	
	if(ret < 0) {
		error = -1;
		data.clear();
		return data;
	}
	
	vector<unsigned char> buf(ret);
	memcpy(&buf[0], &data[0], ret);

	return buf;
}

bool I2CComp::Lock()
{
	if(i2c == NULL) {
		return false;
	}

	if(i2c->Lock() == API_ERROR) {
		return false;
	}

	return true;
}

bool I2CComp::Unlock()
{
	if(i2c == NULL) {
		return false;
	}

	if(i2c->Unlock() == API_ERROR) {
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
	return new I2CComp();
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
	return new I2CComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

