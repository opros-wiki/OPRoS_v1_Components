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

#include "LaserScannerComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
LaserScannerComp::LaserScannerComp()
{
	hOprosAPI = NULL;
	laserScanner = NULL;
	error = 0;
	
	portSetup();
}

//
// constructor declaration (with name)
//
LaserScannerComp::LaserScannerComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	laserScanner = NULL;
	error = 0;
	
	portSetup();
}

//
// destructor declaration
//

LaserScannerComp::~LaserScannerComp() 
{
	onDestroy();
}

void LaserScannerComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new LaserScannerServiceProvided(this);

	addPort("LaserScannerService",pa1);

	// data port setup

	addPort("laserScannerData", &laserScannerData);

}

// Call back Declaration
ReturnType LaserScannerComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : LaserScannerComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("APIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : LaserScannerComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	API 로드
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : LaserScannerComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("APIName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : LaserScannerComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : LaserScannerComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	laserScanner = dynamic_cast<LaserScanner *>(getOprosAPI());
	if(laserScanner == NULL) {
		PrintMessage("ERROR : LaserScannerComp::onInitialize() -> Can't get a handle of Laser Scanner API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	//	API 초기화
	if(laserScanner->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : LaserScannerComp::onInitialize() -> Can't intilaize a Laser Scanner API\n");
		
		delete laserScanner;
		laserScanner = NULL;

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

ReturnType LaserScannerComp::onStart()
{
	if(laserScanner == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 enable를 호출
	if(laserScanner->Enable() < 0) {
		PrintMessage("ERROR : LaserScannerComp::onStart() -> Can't enable the Laser Scanner API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType LaserScannerComp::onStop()
{
	if(laserScanner == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 disable 호출
	if(laserScanner->Disable() < 0) {
		PrintMessage("ERROR : LaserScannerComp::onStop() -> Can't disable the Laser Scanner API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType LaserScannerComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType LaserScannerComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType LaserScannerComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType LaserScannerComp::onDestroy()
{
	//	API 핸들 삭제
	if(laserScanner != NULL) {
		laserScanner->Finalize();
		delete laserScanner;
		laserScanner = NULL;
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

ReturnType LaserScannerComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType LaserScannerComp::onExecute()
{
	if(laserScanner == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	vector<double> data;
	if(laserScanner->GetLaserScannerData(data) < 0) {
		PrintMessage("ERROR : LaserScannerComp::onExecute() -> Can't get the Laser Scanner Data.\n");
		return OPROS_CALL_API_ERROR;
	}

	laserScannerData.push(data);

	return OPROS_SUCCESS;
}
	
ReturnType LaserScannerComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType LaserScannerComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}


bool LaserScannerComp::SetParameter(Property parameter)
{
	if(laserScanner == NULL) {
		return false;
	}

	if(laserScanner->SetParameter(parameter) < 0) {
		return false;
	}

	return true;
}
Property LaserScannerComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(laserScanner == NULL) {
		error = -1;
		return parameter;
	}

	if(laserScanner->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}
int LaserScannerComp::GetError()
{
	return error;
}
vector<double> LaserScannerComp::GetLaserScannerData()
{
	vector<double> data;

	error = 0;
	if(laserScanner == NULL) {
		error = -1;
		return data;
	}

	if(laserScanner->GetLaserScannerData(data) < 0) {
		error = -1;
	}

	return data;
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
	return new LaserScannerComp();
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
	return new LaserScannerComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

