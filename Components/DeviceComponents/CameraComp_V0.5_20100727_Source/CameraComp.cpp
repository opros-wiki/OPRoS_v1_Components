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

#include "OprosPrintMessage.h"
#include "CameraComp.h"

//#include "cv.h"
//#include "highgui.h"
//
// constructor declaration
//
CameraComp::CameraComp()
{
	hOprosAPI = NULL;
	camera = NULL;
	error = 0;

	portSetup();
}

//
// constructor declaration (with name)
//
CameraComp::CameraComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	camera = NULL;
	error;
	
	portSetup();
}

//
// destructor declaration
//

CameraComp::~CameraComp()
{
	onDestroy();
}

void CameraComp::portSetup() {

	// provided service port setup
	ProvidedServicePort *pa1;
	pa1=new CameraServiceProvided(this);

	addPort("CameraService",pa1);

	// data port setup
	addPort("imageData", &imageData);
}

// Call back Declaration
ReturnType CameraComp::onInitialize()
{
	//	XML�� ����� ������Ƽ�� parameter�� ����
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll �����̸��� Ȯ���Ͽ� ������ ���� ����
	if(parameter.FindName("APIName") == false) {
		PrintMessage("ERROR : CameraComp::onInitialize() -> Can't find the APIName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	//	DLL �ε�
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("APIName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : CameraComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("APIName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	API �ε�
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : CameraComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("DllName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : CameraComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("DllName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : CameraComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	camera = dynamic_cast<Camera *>(getOprosAPI());
	if(camera == NULL) {
		PrintMessage("ERROR : CameraComp::onInitialize() -> Can't get a handle of Camera API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	//	API �ʱ�ȭ
	if(camera->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : CameraComp::onInitialize() -> Can't intilaize a Camera API\n");
		delete camera;
		camera = NULL;

#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_INITIALIZE_API_ERROR;
	}

	error = 0;

	PrintMessage("SUCCESS : CameraComp::onInitialize()\n");
	return OPROS_SUCCESS;
}

ReturnType CameraComp::onStart()
{
	if(camera == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	int width = atoi(parameter.GetValue("Width").c_str());
	int height = atoi(parameter.GetValue("Height").c_str());
	int pixelBytes = atoi(parameter.GetValue("PixelBytes").c_str());

	if(width * height * pixelBytes <= 0) {
		PrintMessage("ERROR : CameraComp::onStart() -> Can't enable the Camera API(Camera parameter's size is zero\n");
		return OPROS_ENABLE_API_ERROR;
	}

	imageBuffer.resize(width * height * pixelBytes);

	//	API�� enable�� ȣ��
	if(camera->Enable() < 0) {
		PrintMessage("ERROR : CameraComp::onStart() -> Can't enable the Camera API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	PrintMessage("SUCCESS : CameraComp::onStart() -> width = %d, height = %d, pixelBytes = %d\n", width, height, pixelBytes);
	return OPROS_SUCCESS;
}
	
ReturnType CameraComp::onStop()
{
	if(camera == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API�� disable ȣ��
	if(camera->Disable() < 0) {
		PrintMessage("ERROR : CameraComp::onStop() -> Can't disable the Camera API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType CameraComp::onReset()
{
	return OPROS_SUCCESS;
}

ReturnType CameraComp::onError()
{
	return OPROS_SUCCESS;
}

ReturnType CameraComp::onRecover()
{
	return OPROS_SUCCESS;
}

ReturnType CameraComp::onDestroy()
{
	//	API �ڵ� ����
	if(camera != NULL) {
		camera->Finalize();
		delete camera;
		camera = NULL;
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

ReturnType CameraComp::onEvent(Event *evt)
{
	//	CameraComp������ ������ ����.

	return OPROS_SUCCESS;
}

ReturnType CameraComp::onExecute()
{
	if(camera == NULL) {
		PrintMessage("ERROR:CameraComp::onExecute() -> Camera dll is NULL \n");
		return OPROS_PRECONDITION_NOT_MET;
	}

	if(camera->GetImage(&imageBuffer[0]) < 0) {
		PrintMessage("ERROR:CameraComp::onExecute() -> Can't get image from dll \n");
		return OPROS_CALL_API_ERROR;
	}

	imageData.push(imageBuffer);

	return OPROS_SUCCESS;
}
	
ReturnType CameraComp::onUpdated()
{
	//	CameraComp������ ������ ����.

	return OPROS_SUCCESS;
}

ReturnType CameraComp::onPeriodChanged()
{
	//	CameraComp������ ������ ����.

	return OPROS_SUCCESS;
}

bool CameraComp::SetParameter(Property parameter)
{
	if(camera == NULL) {
		return false;
	}

	if(camera->SetParameter(parameter) < 0) {
		return false;
	}

	return true;
}
Property CameraComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(camera == NULL) {
		error = -1;
		PrintMessage("ERROR:CameraComp::GetParameter() -> Can't camera api is NULL\n");
		return parameter;
	}

	if(camera->GetParameter(parameter) < 0) {
		PrintMessage("ERROR:CameraComp::GetParameter() -> Can't get parameter from dll \n");
		error = -1;
	}

	return parameter;
}

int CameraComp::GetError()
{
	return error;
}

vector<unsigned char> CameraComp::GetImage()
{
	error = 0;

	if(camera->GetImage(&imageBuffer[0]) < 0) {
		error = -1;
		vector<unsigned char> tmp(0);
		return tmp;
	}

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
	return new CameraComp();
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
	return new CameraComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

