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

#include "InfraredSensorComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
InfraredSensorComp::InfraredSensorComp()
{
	hOprosAPI = NULL;
	infraredSensor = NULL;
	error = 0;
	
	portSetup();
}

//
// constructor declaration (with name)
//
InfraredSensorComp::InfraredSensorComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	infraredSensor = NULL;
	error = 0;
	
	portSetup();
}

//
// destructor declaration
//

InfraredSensorComp::~InfraredSensorComp() 
{
	onDestroy();
}

void InfraredSensorComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new InfraredSensorServiceProvided(this);

	addPort("InfraredSensorService",pa1);

	// data port setup

	addPort("infraredData", &infraredData);

}

// Call back Declaration
ReturnType InfraredSensorComp::onInitialize()
{
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : InfraredSensorComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("APIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : InfraredSensorComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : InfraredSensorComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("APIName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : InfraredSensorComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : InfraredSensorComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	infraredSensor = dynamic_cast<InfraredSensor *>(getOprosAPI());
	if(infraredSensor == NULL) {
		PrintMessage("ERROR : InfraredSensorComp::onInitialize() -> Can't get a handle of Infrared Sensor API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	if(infraredSensor->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : InfraredSensorComp::onInitialize() -> Can't intilaize a Infrared Sensor API\n");
		
		delete infraredSensor;
		infraredSensor = NULL;

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

ReturnType InfraredSensorComp::onStart()
{
	if(infraredSensor == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	if(infraredSensor->Enable() < 0) {
		PrintMessage("ERROR : InfraredSensorComp::onStart() -> Can't enable the Infrared Sensor API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType InfraredSensorComp::onStop()
{
	if(infraredSensor == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	if(infraredSensor->Disable() < 0) {
		PrintMessage("ERROR : InfraredSensorComp::onStop() -> Can't disable the Infrared Sensor API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType InfraredSensorComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType InfraredSensorComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType InfraredSensorComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType InfraredSensorComp::onDestroy()
{
	//	Delete a handle of API
	if(infraredSensor != NULL) {
		delete infraredSensor;
		infraredSensor = NULL;
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

ReturnType InfraredSensorComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType InfraredSensorComp::onExecute()
{
	if(infraredSensor == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	lock.Lock();
	vector<double> result;
	if(infraredSensor->GetInfraredSensorData(result) < 0) {
		lock.Unlock();
		PrintMessage("ERROR : InfraredSensorComp::onExecute() -> Can't get the data of Infrared Sensor.\n");
		return OPROS_CALL_API_ERROR;
	}
	lock.Unlock();

	infraredData.push(result);

	return OPROS_SUCCESS;
}
	
ReturnType InfraredSensorComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType InfraredSensorComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool InfraredSensorComp::SetParameter(Property parameter)
{
	if(infraredSensor == NULL) {
		return false;
	}

	if(infraredSensor->SetParameter(parameter) == API_ERROR) {
		return false;
	}

	return true;
}

Property InfraredSensorComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(infraredSensor == NULL) {
		error = -1;
		return parameter;
	}

	if(infraredSensor->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}

int InfraredSensorComp::GetError()
{
	return error;
}

vector<double> InfraredSensorComp::GetInfraredData()
{
	vector<double> result;

	error = 0;
	if(infraredSensor == NULL) {
		error = -1;
		return result;
	}

	lock.Lock();
	if(infraredSensor->GetInfraredSensorData(result) < 0) {
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
	return new InfraredSensorComp();
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
	return new InfraredSensorComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

