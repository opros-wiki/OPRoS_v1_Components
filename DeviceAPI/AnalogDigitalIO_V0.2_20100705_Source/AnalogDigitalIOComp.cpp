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

#include "AnalogDigitalIOComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
AnalogDigitalIOComp::AnalogDigitalIOComp()
		:analogOutputData(OPROS_LAST,1),digitalOutputData(OPROS_LAST,1)
{
	hOprosAPI = NULL;
	analogDigitalIO = NULL;
	error = 0;
	
	portSetup();
}

//
// constructor declaration (with name)
//
AnalogDigitalIOComp::AnalogDigitalIOComp(const std::string &name):Component(name)
		,analogOutputData(OPROS_LAST,1),digitalOutputData(OPROS_LAST,1)
{
	hOprosAPI = NULL;
	analogDigitalIO = NULL;
	error = 0;
	
	portSetup();
}

//
// destructor declaration
//

AnalogDigitalIOComp::~AnalogDigitalIOComp() 
{
	onDestroy();
}

void AnalogDigitalIOComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new AnalogDigitalIOServiceProvided(this);
	addPort("AnalogDigitalIOService",pa1);

	// data port setup
	addPort("analogInputData", &analogInputData);
	addPort("analogOutputData", &analogOutputData);
	addPort("digitalInputData", &digitalInputData);
	addPort("digitalOutputData", &digitalOutputData);

}

// Call back Declaration
ReturnType AnalogDigitalIOComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : AnalogDigitalIOComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("APIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : AnalogDigitalIOComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	API 로드
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : AnalogDigitalIOComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("DllName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : AnalogDigitalIOComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : AnalogDigitalIOComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	analogDigitalIO = dynamic_cast<AnalogDigitalIO *>(getOprosAPI());
	if(analogDigitalIO == NULL) {
		PrintMessage("ERROR : AnalogDigitalIOComp::onInitialize() -> Can't get a handle of Analog/Digital IO API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	//	API 초기화
	if(analogDigitalIO->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : AnalogDigitalIOComp::onInitialize() -> Can't initialize a Analog/Digital IO API\n");
		delete analogDigitalIO;
		analogDigitalIO = NULL;

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

ReturnType AnalogDigitalIOComp::onStart()
{
	if(analogDigitalIO == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 enable를 호출
	if(analogDigitalIO->Enable() == API_ERROR) {
		PrintMessage("ERROR : AnalogDigitalIOComp::onStart() -> Can't enable the Analog/Digital IO API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType AnalogDigitalIOComp::onStop()
{
	if(analogDigitalIO == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 disable 호출
	if(analogDigitalIO->Disable() < 0) {
		PrintMessage("ERROR : AnalogDigitalIOComp::onStop() -> Can't disable the Analog/Digital IO API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType AnalogDigitalIOComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType AnalogDigitalIOComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType AnalogDigitalIOComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType AnalogDigitalIOComp::onDestroy()
{
	//	API 핸들 삭제
	if(analogDigitalIO != NULL) {
		delete analogDigitalIO;
		analogDigitalIO = NULL;
	}

	//	DLL 핸들 삭제
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

ReturnType AnalogDigitalIOComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType AnalogDigitalIOComp::onExecute()
{
	vector<double> analogData;

	if(analogDigitalIO == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	Analog Input
	if(analogDigitalIO->GetAnalogInputData(analogData) == API_ERROR) {
		return OPROS_CALL_API_ERROR;
	}
	analogInputData.push(analogData);

	//	Analog Output
	boost::any *pdata = analogOutputData.pop();
	if (pdata != NULL) {
		vector<double> *temp = boost::unsafe_any_cast< vector<double> >(pdata);
		
		if(temp->size() > 0) {
			if(analogDigitalIO->SetAnalogOutputData(*temp) < 0) {
				delete pdata;
				return OPROS_CALL_API_ERROR;
			}
		}
		delete pdata;
	}

	vector<bool> digitalData;

	//	Digital Input
	if(analogDigitalIO->GetDigitalInputData(digitalData) == API_ERROR) {
		return OPROS_CALL_API_ERROR;
	}
	digitalInputData.push(digitalData);

	//	Digital Output
	pdata = digitalOutputData.pop();
	if (pdata != NULL) {
		vector<bool> *temp = boost::unsafe_any_cast< vector<bool> >(pdata);
		
		if(temp->size() > 0) {
			if(analogDigitalIO->SetDigitalOutputData(*temp) < 0) {
				delete pdata;
				return OPROS_CALL_API_ERROR;
			}
		}
		delete pdata;
	}

	return OPROS_SUCCESS;
}
	
ReturnType AnalogDigitalIOComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType AnalogDigitalIOComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}


bool AnalogDigitalIOComp::SetParameter(Property parameter)
{
	if(analogDigitalIO == NULL) {
		return false;
	}

	if(analogDigitalIO->SetParameter(parameter) < 0) {
		return false;
	}

	return true;
}

Property AnalogDigitalIOComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(analogDigitalIO == NULL) {
		error = -1;
		return parameter;
	}

	if(analogDigitalIO->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}

int AnalogDigitalIOComp::GetError()
{
	return error;
}

bool AnalogDigitalIOComp::SetAnalogOutputData(vector<double> analogOutputData)
{
	if(analogDigitalIO == NULL) {
		return false;
	}

	if(analogDigitalIO->SetAnalogOutputData(analogOutputData) == API_ERROR) {
		return false;
	}

	return true;
}

vector<double> AnalogDigitalIOComp::GetAnalogInputData()
{
	vector<double> ret;
	error = 0;

	if(analogDigitalIO == NULL) {
		error = -1;
		return ret;
	}

	if(analogDigitalIO->GetAnalogInputData(ret) == API_ERROR) {
		error = -1;
	}

	return ret;
}

bool AnalogDigitalIOComp::SetDigitalOutputData(vector<bool> digitalOutputData)
{
	if(analogDigitalIO == NULL) {
		return false;
	}

	if(analogDigitalIO->SetDigitalOutputData(digitalOutputData) == API_ERROR) {
		return false;
	}

	return true;
}

vector<bool> AnalogDigitalIOComp::GetDigitalInputData()
{
	vector<bool> ret;
	error = 0;

	if(analogDigitalIO == NULL) {
		error = -1;
		return ret;
	}

	if(analogDigitalIO->GetDigitalInputData(ret) == API_ERROR) {
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
	return new AnalogDigitalIOComp();
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
	return new AnalogDigitalIOComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

