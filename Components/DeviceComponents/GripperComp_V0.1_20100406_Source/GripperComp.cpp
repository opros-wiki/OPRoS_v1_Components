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

#include "GripperComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
GripperComp::GripperComp()
{
	hOprosAPI = NULL;
	gripper = NULL;
	error = 0;
	
	portSetup();
}

//
// constructor declaration (with name)
//
GripperComp::GripperComp(const std::string &name):Component(name)
{
	hOprosAPI = NULL;
	gripper = NULL;
	error = 0;
	
	portSetup();
}

//
// destructor declaration
//

GripperComp::~GripperComp() 
{
	onDestroy();
}

void GripperComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new GripperServiceProvided(this);

	addPort("GripperService",pa1);

}

// Call back Declaration
ReturnType GripperComp::onInitialize()
{
	//	XML에 저장된 프라퍼티를 parameter에 저장
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);
	
	//	dll 파일이름을 확인하여 없으면 에러 리턴
	if(parameter.FindName("DllName") == false) {
		PrintMessage("ERROR : GripperComp::onInitialize() -> Can't find the DllName in property\n");
		return OPROS_FIND_PROPERTY_ERROR;
	}

	
#if defined(WIN32)
	//	DLL 로드
	hOprosAPI = LoadLibrary((LPCSTR)parameter.GetValue("DllName").c_str());
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : GripperComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("DllName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}
	
	//	API 로드
	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)GetProcAddress(hOprosAPI, "GetAPI");
	if(getOprosAPI == NULL) {
		PrintMessage("ERROR : GripperComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		FreeLibrary(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#else
	hOprosAPI = dlopen(parameter.GetValue("DllName").c_str(), RTLD_LAZY);
	if(hOprosAPI == NULL) {
		PrintMessage("ERROR : GripperComp::onInitialize() -> Can't find the %s\n", parameter.GetValue("DllName").c_str());
		return OPROS_FIND_DLL_ERROR;
	}

	GET_OPROS_API getOprosAPI;
	getOprosAPI = (GET_OPROS_API)dlsym(hOprosAPI, "GetAPI");
	char *error = dlerror();
	if(error != NULL) {
		PrintMessage("ERROR : GripperComp::onInitialize() -> Can't get a handle of GetAPI Funtion\n");
		dlclose(hOprosAPI);
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}
#endif
	
	gripper = dynamic_cast<Gripper *>(getOprosAPI());
	if(gripper == NULL) {
		PrintMessage("ERROR : GripperComp::onInitialize() -> Can't get a handle of Gripper API\n");
#if defined(WIN32)
		FreeLibrary(hOprosAPI);
#else
		dlclose(hOprosAPI);
#endif
		hOprosAPI = NULL;
		return OPROS_LOAD_DLL_ERROR;
	}

	//	API 초기화
	if(gripper->Initialize(parameter) != API_SUCCESS) {
		PrintMessage("ERROR : GripperComp::onInitialize() -> Can't intilaize a Gripper API\n");
		
		delete gripper;
		gripper = NULL;

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

ReturnType GripperComp::onStart()
{
	if(gripper == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 enable를 호출
	if(gripper->Enable() < 0) {
		PrintMessage("ERROR : GripperComp::onStart() -> Can't enable the Manipulator API\n");
		return OPROS_ENABLE_API_ERROR;
	}

	//	API의 StartHoming 호출
	if(gripper->StartHoming() < 0) {
		PrintMessage("ERROR : GripperComp::onStart() -> Can't run Homing\n");
		return OPROS_ENABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType GripperComp::onStop()
{
	if(gripper == NULL) {
		return OPROS_PRECONDITION_NOT_MET;
	}

	//	API의 disable 호출
	if(gripper->Disable() < 0) {
		PrintMessage("ERROR : GripperComp::onStop() -> Can't disable the Manipulator API\n");
		return OPROS_DISABLE_API_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType GripperComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType GripperComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType GripperComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType GripperComp::onDestroy()
{
	//	API 핸들 삭제
	if(gripper != NULL) {
		gripper->Finalize();
		delete gripper;
		gripper = NULL;
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

ReturnType GripperComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType GripperComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType GripperComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType GripperComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool GripperComp::SetParameter(Property parameter)
{
	if(gripper == NULL) {
		return false;
	}

	if(gripper->SetParameter(parameter) < 0) {
		return false;
	}

	return true;
}
Property GripperComp::GetParameter()
{
	Property parameter;
	error = 0;

	if(gripper == NULL) {
		error = -1;
		return parameter;
	}

	if(gripper->GetParameter(parameter) < 0) {
		error = -1;
	}

	return parameter;
}
int GripperComp::GetError()
{
	return error;
}
bool GripperComp::Stop()
{
	if(gripper == NULL) {
		return false;
	}

	if(gripper->Stop() < 0) {
		return false;
	}

	return true;
}
bool GripperComp::SetPower(vector<double> power,vector<unsigned long> time)
{
	if(gripper == NULL) {
		return false;
	}

	if(gripper->SetPower(power, time) < 0) {
		return false;
	}

	return true;
}
vector<double> GripperComp::GetPower()
{
	vector<double> power;

	error = 0;
	if(gripper == NULL) {
		error = -1;
		return power;
	}

	if(gripper->GetPower(power) < 0) {
		error = -1;
	}

	return power;
}
bool GripperComp::SetVelocity(vector<double> velocity,vector<unsigned long> time)
{
	if(gripper == NULL) {
		return false;
	}

	if(gripper->SetVelocity(velocity, time) < 0) {
		return false;
	}

	return false;
}
vector<double> GripperComp::GetVelocity()
{
	vector<double> velocity;

	error = 0;
	if(gripper == NULL) {
		error = -1;
		return velocity;
	}

	if(gripper->GetVelocity(velocity) < 0) {
		error = -1;
	}

	return velocity;
}
bool GripperComp::SetPosition(vector<double> position,vector<unsigned long> time)
{
	if(gripper == NULL) {
		return false;
	}

	if(gripper->SetPosition(position, time) < 0) {
		return false;
	}

	return true;
}
vector<double> GripperComp::GetPosition()
{
	vector<double> position;

	error = 0;
	if(gripper == NULL) {
		error = -1;
		return position;
	}

	if(gripper->GetPosition(position) < 0) {
		error = -1;
	}

	return position;
}
bool GripperComp::StartGripping()
{
	if(gripper == NULL) {
		return false;
	}

	if(gripper->StartGripping() < 0) {
		return false;
	}

	return true;
}
bool GripperComp::StopGripping()
{
	if(gripper == NULL) {
		return false;
	}

	if(gripper->StopGripping() < 0) {
		return false;
	}

	return true;
}
bool GripperComp::IsGripped()
{
	error = 0;
	if(gripper == NULL) {
		error = -1;
		return false;
	}

	int ret = gripper->IsGripped();
	if(ret < 0) {
		error = -1;
		return false;
	}
	else if(ret == 0) {
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
	return new GripperComp();
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
	return new GripperComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

