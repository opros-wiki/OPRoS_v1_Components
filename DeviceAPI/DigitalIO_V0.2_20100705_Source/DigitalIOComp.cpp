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

#include "DigitalIOComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
DigitalIOComp::DigitalIOComp()
		:digitalOutputData(OPROS_LAST,1)
{
	hOprosAPI = NULL;
	digitalIO = NULL;
	error = 0;
	
	portSetup();
}

//
// constructor declaration (with name)
//
DigitalIOComp::DigitalIOComp(const std::string &name):Component(name)
		,digitalOutputData(OPROS_LAST,1)
{
	hOprosAPI = NULL;
	digitalIO = NULL;
	error = 0;
	
	portSetup();
}

//
// destructor declaration
//

DigitalIOComp::~DigitalIOComp() 
{
	onDestroy();
}

void DigitalIOComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new DigitalIOServiceProvided(this);
	addPort("DigitalIOService",pa1);

	// data port setup
	addPort("digitalInputData", &digitalInputData);
	addPort("digitalOutputData", &digitalOutputData);

}

// Call back Declaration
ReturnType DigitalIOComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : DigitalIOComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("APIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : DigitalIOComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	API 로드
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : DigitalIOComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("DllName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : DigitalIOComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("DllName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : DigitalIOComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	digitalIO = dynamic_cast<DigitalIO *>(getOprosAPI());
	if(digitalIO == NULL) {
		PrintMessage("ERROR : DigitalIOComp::onInitialize() -> Can't get a handle of Digital IO API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	//	API 초기화
	if(digitalIO->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : DigitalIOComp::onInitialize() -> Can't initialize a Digital IO API\n");
		delete digitalIO;
		digitalIO = NULL;

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

ReturnType DigitalIOComp::onStart()
{
	if(digitalIO == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 enable를 호출
	if(digitalIO->Enable() == API_ERROR) {
		PrintMessage("ERROR : DigitalIOComp::onStart() -> Can't enable the Digital IO API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType DigitalIOComp::onStop()
{
	if(digitalIO == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 disable 호출
	if(digitalIO->Disable() < 0) {
		PrintMessage("ERROR : DigitalIOComp::onStop() -> Can't disable the Digital IO API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType DigitalIOComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType DigitalIOComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType DigitalIOComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType DigitalIOComp::onDestroy()
{
	//	API 핸들 삭제
	if(digitalIO != NULL) {
		delete digitalIO;
		digitalIO = NULL;
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

ReturnType DigitalIOComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType DigitalIOComp::onExecute()
{
	vector<bool> ret;

	if(digitalIO == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	Digital Input
	if(digitalIO->GetDigitalInputData(ret) == API_ERROR) {
		return OPROS_CALL_API_ERROR;
	}
	digitalInputData.push(ret);

	//	Digital Output
	boost::any *pdata = digitalOutputData.pop();
	if (pdata != NULL) {
		vector<bool> *temp = boost::unsafe_any_cast< vector<bool> >(pdata);
		
		if(temp->size() > 0) {
			if(digitalIO->SetDigitalOutputData(*temp) < 0) {
				delete pdata;
				return OPROS_CALL_API_ERROR;
			}
		}
		delete pdata;
	}

	return OPROS_SUCCESS;
}
	
ReturnType DigitalIOComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType DigitalIOComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}


bool DigitalIOComp::SetParameter(Property parameter)
{
	if(digitalIO == NULL) {
		return false;
	}

	if(digitalIO->SetParameter(parameter) < 0) {
		return false;
	}

	return true;
}

Property DigitalIOComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(digitalIO == NULL) {
		error = -1;
		return parameter;
	}

	if(digitalIO->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}

int DigitalIOComp::GetError()
{
	return error;
}

bool DigitalIOComp::SetDigitalOutputData(vector<bool> digitalOutputData)
{
	if(digitalIO == NULL) {
		return false;
	}

	if(digitalIO->SetDigitalOutputData(digitalOutputData) == API_ERROR) {
		return false;
	}

	return true;
}

vector<bool> DigitalIOComp::GetDigitalInputData()
{
	vector<bool> ret;
	error = 0;

	if(digitalIO == NULL) {
		error = -1;
		return ret;
	}

	if(digitalIO->GetDigitalInputData(ret) == API_ERROR) {
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
	return new DigitalIOComp();
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
	return new DigitalIOComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

