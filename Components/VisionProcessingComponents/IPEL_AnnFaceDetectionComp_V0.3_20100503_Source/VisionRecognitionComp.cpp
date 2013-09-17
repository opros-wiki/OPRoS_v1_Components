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

#include "VisionRecognitionServiceProvided.h"
#include "VisionRecognitionComp.h"

//
// constructor declaration
//
VisionRecognitionComp::VisionRecognitionComp()
{

	
	portSetup();
}

//
// constructor declaration (with name)
//
VisionRecognitionComp::VisionRecognitionComp(const std::string &name):Component(name)
{

	
	portSetup();
}

//
// destructor declaration
//

VisionRecognitionComp::~VisionRecognitionComp() {
}

void VisionRecognitionComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new VisionRecognitionServiceProvided(this);

	addPort("VisionRecognitionService",pa1);

}

// Call back Declaration
ReturnType VisionRecognitionComp::onInitialize()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType VisionRecognitionComp::onStart()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType VisionRecognitionComp::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType VisionRecognitionComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType VisionRecognitionComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType VisionRecognitionComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType VisionRecognitionComp::onDestroy()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType VisionRecognitionComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType VisionRecognitionComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType VisionRecognitionComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType VisionRecognitionComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}


bool VisionRecognitionComp::SetParameter(Property parameter)
{
	// user code here
	return true;
}
Property VisionRecognitionComp::GetParameter()
{
	Property parameter;

	return parameter;
}
int VisionRecognitionComp::GetError()
{
	return 0;
}
vector<VisionRecognitionResult> VisionRecognitionComp::Recognize(vector<unsigned char> image,int width,int height,int pixelBytes)
{
	vector<VisionRecognitionResult> ret;

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
	return new VisionRecognitionComp();
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
	return new VisionRecognitionComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

