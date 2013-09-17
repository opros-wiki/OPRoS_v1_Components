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

#include "KITECH_LinearTrajectoryGenerationComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
KITECH_LinearTrajectoryGenerationComp::KITECH_LinearTrajectoryGenerationComp()
{
	error = 0;
	
	portSetup();
}

//
// constructor declaration (with name)
//
KITECH_LinearTrajectoryGenerationComp::KITECH_LinearTrajectoryGenerationComp(const std::string &name):Component(name)
{
	error = 0;
		
	portSetup();
}

//
// destructor declaration
//

KITECH_LinearTrajectoryGenerationComp::~KITECH_LinearTrajectoryGenerationComp() {
}

void KITECH_LinearTrajectoryGenerationComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new TrajectoryGenerationServiceProvided(this);

	addPort("TrajectoryGenerationService",pa1);

}

// Call back Declaration
ReturnType KITECH_LinearTrajectoryGenerationComp::onInitialize()
{
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);

	if(SetParameter(parameter) == false) {
		return OPROS_CALLER_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType KITECH_LinearTrajectoryGenerationComp::onStart()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_LinearTrajectoryGenerationComp::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_LinearTrajectoryGenerationComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_LinearTrajectoryGenerationComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_LinearTrajectoryGenerationComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_LinearTrajectoryGenerationComp::onDestroy()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_LinearTrajectoryGenerationComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_LinearTrajectoryGenerationComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_LinearTrajectoryGenerationComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_LinearTrajectoryGenerationComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}


bool KITECH_LinearTrajectoryGenerationComp::SetParameter(Property parameter)
{
	if(parameter.FindName("SamplingTime") == false) {
		PrintMessage("ERROR : KITECH_LinearTrajectoryGenerationComp::SetParameter() -> Can't find the SamplingTime in property\n");
		return false;
	}

	samplingTime = atof(parameter.GetValue("SamplingTime").c_str());

	this->parameter = parameter;

	return true;
}

Property KITECH_LinearTrajectoryGenerationComp::GetParameter()
{
	return parameter;
}

int KITECH_LinearTrajectoryGenerationComp::GetError()
{
	return error;
}

bool KITECH_LinearTrajectoryGenerationComp::GenerateTrajectory(vector < valarray<double> > pathData)
{
	acceleration.clear();
	velocity.clear();
	position.clear();

	if (pathData.size() < 2) return false;

	unsigned int n = pathData.size () - 1;

	vector<double> h(n);
	for (unsigned int i=0; i<n; i++) {
		h[i] = pathData[i+1][0] - pathData[i][0];
		if (h[i] < samplingTime) h[i] = samplingTime;
	}

	position.reserve ((int)(pathData[n][0] / samplingTime + 10));
	
	double t = pathData[0][0];
	for (unsigned int i=0; i<n; i++) {
		valarray<double> m = (pathData[i+1] - pathData[i])/h[i];
		
		for (; t<=pathData[i+1][0]; t+=samplingTime) {
			valarray<double> p = m*(t - pathData[i][0]) + pathData[i];
			p[0] = t;
			position.push_back (p);
		}
    }
	position.push_back (pathData[n]);

	return true;
}

vector< valarray<double> > KITECH_LinearTrajectoryGenerationComp::GetAcceleration()
{
	return acceleration;
}

vector< valarray<double> > KITECH_LinearTrajectoryGenerationComp::GetVelocity()
{
	return velocity;
}

vector< valarray<double> > KITECH_LinearTrajectoryGenerationComp::GetPosition()
{
	return position;
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
	return new KITECH_LinearTrajectoryGenerationComp();
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
	return new KITECH_LinearTrajectoryGenerationComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

