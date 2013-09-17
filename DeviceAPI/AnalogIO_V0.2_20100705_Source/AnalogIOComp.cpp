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

#include "AnalogIOComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
AnalogIOComp::AnalogIOComp()
		:analogOutputData(OPROS_LAST,1)
{
	hOprosAPI = NULL;
	analogIO = NULL;
	error = 0;

	portSetup();
}

//
// constructor declaration (with name)
//
AnalogIOComp::AnalogIOComp(const std::string &name):Component(name)
		,analogOutputData(OPROS_LAST,1)
{
	hOprosAPI = NULL;
	analogIO = NULL;
	error = 0;
	
	portSetup();
}

//
// destructor declaration
//

AnalogIOComp::~AnalogIOComp() 
{
	onDestroy();
}

void AnalogIOComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new AnalogIOServiceProvided(this);
	addPort("AnalogIOService",pa1);

	// data port setup
	addPort("analogInputData", &analogInputData);
	addPort("analogOutputData", &analogOutputData);

}

// Call back Declaration
ReturnType AnalogIOComp::onInitialize()
{
	//	XML�� ����� ������Ƽ�� parameter�� ����
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll �����̸��� Ȯ���Ͽ� ������ ���� ����
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : AnalogIOComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	//	DLL �ε�
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("APIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : AnalogIOComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	API �ε�
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : AnalogIOComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("DllName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : AnalogIOComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("DllName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : AnalogIOComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	analogIO = dynamic_cast<AnalogIO *>(getOprosAPI());
	if(analogIO == NULL) {
		PrintMessage("ERROR : AnalogIOComp::onInitialize() -> Can't get a handle of Manipulator API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	//	API �ʱ�ȭ
	if(analogIO->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : AnalogIOComp::onInitialize() -> Can't initialize a Manipulator API\n");
		delete analogIO;
		analogIO = NULL;

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

ReturnType AnalogIOComp::onStart()
{
	if(analogIO == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API�� enable�� ȣ��
	if(analogIO->Enable() == API_ERROR) {
		PrintMessage("ERROR : AnalogIOComp::onStart() -> Can't enable the Analog IO API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType AnalogIOComp::onStop()
{
	if(analogIO == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API�� disable ȣ��
	if(analogIO->Disable() < 0) {
		PrintMessage("ERROR : AnalogIOComp::onStop() -> Can't disable the Analog IO API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType AnalogIOComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType AnalogIOComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType AnalogIOComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType AnalogIOComp::onDestroy()
{
	//	API �ڵ� ����
	if(analogIO != NULL) {
		delete analogIO;
		analogIO = NULL;
	}

	//	DLL �ڵ� ����
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

ReturnType AnalogIOComp::onEvent(Event *evt)
{
	return OPROS_SUCCESS;
}

ReturnType AnalogIOComp::onExecute()
{
	vector<double> ret;

	if(analogIO == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	Analog Input
	if(analogIO->GetAnalogInputData(ret) == API_ERROR) {
		return OPROS_CALL_API_ERROR;
	}
	analogInputData.push(ret);

	//	Analog Output
	boost::any *pdata = analogOutputData.pop();
	if (pdata != NULL) {
		vector<double> *temp = boost::unsafe_any_cast< vector<double> >(pdata);
		
		if(temp->size() > 0) {
			if(analogIO->SetAnalogOutputData(*temp) < 0) {
				delete pdata;
				return OPROS_CALL_API_ERROR;
			}
		}
		delete pdata;
	}

	return OPROS_SUCCESS;
}
	
ReturnType AnalogIOComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType AnalogIOComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}


bool AnalogIOComp::SetParameter(Property parameter)
{
	if(analogIO == NULL) {
		return false;
	}

	if(analogIO->SetParameter(parameter) < 0) {
		return false;
	}

	return true;
}

Property AnalogIOComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(analogIO == NULL) {
		error = -1;
		return parameter;
	}

	if(analogIO->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}

int AnalogIOComp::GetError()
{
	return error;
}

bool AnalogIOComp::SetAnalogOutputData(vector<double> analogOutputData)
{
	if(analogIO == NULL) {
		return false;
	}

	if(analogIO->SetAnalogOutputData(analogOutputData) == API_ERROR) {
		return false;
	}

	return true;
}

vector<double> AnalogIOComp::GetAnalogInputData()
{
	vector<double> ret;
	error = 0;

	if(analogIO == NULL) {
		error = -1;
		return ret;
	}

	if(analogIO->GetAnalogInputData(ret) == API_ERROR) {
		error = -1;
	}

	return ret;
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
	return new AnalogIOComp();
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
	return new AnalogIOComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

