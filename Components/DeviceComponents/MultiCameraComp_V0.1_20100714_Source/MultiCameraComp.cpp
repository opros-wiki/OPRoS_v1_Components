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

#include "MultiCameraComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
MultiCameraComp::MultiCameraComp()
{
	hOprosAPI = NULL;
	multiCamera = NULL;
	error = 0;
	
	portSetup();
}

//
// constructor declaration (with name)
//
MultiCameraComp::MultiCameraComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	multiCamera = NULL;
	error = 0;

	portSetup();
}

//
// destructor declaration
//

MultiCameraComp::~MultiCameraComp() 
{
	onDestroy();
}

void MultiCameraComp::portSetup() {

	// provided service port setup
	ProvidedServicePort *pa1;
	pa1=new MultiCameraServiceProvided(this);

	addPort("MultiCameraService",pa1);

	// data port setup
	addPort("multiImageData", &multiImageData);

}

// Call back Declaration
ReturnType MultiCameraComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : MultiCameraComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}
	
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("APIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : MultiCameraComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	API 로드
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : MultiCameraComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("DllName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : MultiCameraComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("DllName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : MultiCameraComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	multiCamera = dynamic_cast<MultiCamera *>(getOprosAPI());
	if(multiCamera == NULL) {
		PrintMessage("ERROR : MultiCameraComp::onInitialize() -> Can't get a handle of Multi Camera API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	//	API 초기화
	if(multiCamera->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : MultiCameraComp::onInitialize() -> Can't intilaize a Multi Camera API\n");
		delete multiCamera;
		multiCamera = NULL;

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

ReturnType MultiCameraComp::onStart()
{
	if(multiCamera == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	Property parameter;
	if(multiCamera->GetParameter(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : MultiCameraComp::onStart() -> Can't get a parameter of Multi Camera\n");
		return OPROS_ENABLE_API_ERROR;
	}

	if(parameter.FindName("Count") == false) {
		PrintMessage("ERROR : MultiCameraComp::onStart() -> Can't find a parameter(Count)\n");
		return OPROS_ENABLE_API_ERROR;
	}
	int count = atoi(parameter.GetValue("Count").c_str());
	if(count < 1) {
		PrintMessage("ERROR : MultiCameraComp::onStart() -> Count is smaller 1\n");
		return OPROS_ENABLE_API_ERROR;
	}

	imageBuffer.resize(count);

	char name[128];
	for(int i = 0; i < count; i++) {
		sprintf(name, "Width%d", i);
		if(parameter.FindName(string(name)) == false)			return OPROS_ENABLE_API_ERROR;
		int width = atoi(parameter.GetValue(string(name)).c_str());
		
		sprintf(name, "Height%d", i);
		if(parameter.FindName(string(name)) == false)			return OPROS_ENABLE_API_ERROR;
		int height = atoi(parameter.GetValue(string(name)).c_str());
		
		sprintf(name, "PixelBytes%d", i);
		if(parameter.FindName(string(name)) == false)			return OPROS_ENABLE_API_ERROR;
		int pixelBytes = atoi(parameter.GetValue(string(name)).c_str());

		if(width * height * pixelBytes < 1) {
			PrintMessage("ERROR : MultiCameraComp::onStart() -> A image size is wrong\n");
			return OPROS_ENABLE_API_ERROR;
		}

		imageBuffer[i].resize(width * height * pixelBytes);
	}
	
	//	API의 enable를 호출
	if(multiCamera->Enable() < 0) {
		PrintMessage("ERROR : MultiCameraComp::onStart() -> Can't enable the Multi Camera API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType MultiCameraComp::onStop()
{
	if(multiCamera == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 disable 호출
	if(multiCamera->Disable() < 0) {
		PrintMessage("ERROR : MultiCameraComp::onStop() -> Can't disable the Multi Camera API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType MultiCameraComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType MultiCameraComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType MultiCameraComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType MultiCameraComp::onDestroy()
{
	//	API 핸들 삭제
	if(multiCamera != NULL) {
		multiCamera->Finalize();
		delete multiCamera;
		multiCamera = NULL;
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

ReturnType MultiCameraComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType MultiCameraComp::onExecute()
{
	if(multiCamera == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	for(size_t i = 0; i < imageBuffer.size(); i++) {
		if(multiCamera->GetImage((int)i, &(imageBuffer[i][0])) == API_ERROR) {
			return OPROS_CALL_API_ERROR;
		}
	}

	multiImageData.push(imageBuffer);

	return OPROS_SUCCESS;
}
	
ReturnType MultiCameraComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType MultiCameraComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}


bool MultiCameraComp::SetParameter(Property parameter)
{
	if(multiCamera == NULL) {
		return false;
	}

	if(multiCamera->SetParameter(parameter) < 0) {
		return false;
	}

	return true;
}

Property MultiCameraComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(multiCamera == NULL) {
		error = -1;
		return parameter;
	}

	if(multiCamera->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}

int MultiCameraComp::GetError()
{
	return error;
}

vector< vector<unsigned char> > MultiCameraComp::GetImageData()
{
	return imageBuffer;
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
	return new MultiCameraComp();
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
	return new MultiCameraComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

