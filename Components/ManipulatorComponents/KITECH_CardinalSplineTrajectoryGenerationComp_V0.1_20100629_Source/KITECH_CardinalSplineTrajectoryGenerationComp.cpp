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

#include "KITECH_CardinalSplineTrajectoryGenerationComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
KITECH_CardinalSplineTrajectoryGenerationComp::KITECH_CardinalSplineTrajectoryGenerationComp()
{
	error = 0;
	samplingTime = 0.0;
	tension = 0.0;

	portSetup();
}

//
// constructor declaration (with name)
//
KITECH_CardinalSplineTrajectoryGenerationComp::KITECH_CardinalSplineTrajectoryGenerationComp(const std::string &name):Component(name)
{
	error = 0;
	samplingTime = 0.0;
	tension = 0.0;

	portSetup();
}

//
// destructor declaration
//

KITECH_CardinalSplineTrajectoryGenerationComp::~KITECH_CardinalSplineTrajectoryGenerationComp() {
}

void KITECH_CardinalSplineTrajectoryGenerationComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new TrajectoryGenerationServiceProvided(this);

	addPort("TrajectoryGenerationService",pa1);

}

// Call back Declaration
ReturnType KITECH_CardinalSplineTrajectoryGenerationComp::onInitialize()
{
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);

	if(SetParameter(parameter) == false) {
		return OPROS_CALLER_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType KITECH_CardinalSplineTrajectoryGenerationComp::onStart()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_CardinalSplineTrajectoryGenerationComp::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_CardinalSplineTrajectoryGenerationComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_CardinalSplineTrajectoryGenerationComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_CardinalSplineTrajectoryGenerationComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_CardinalSplineTrajectoryGenerationComp::onDestroy()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_CardinalSplineTrajectoryGenerationComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_CardinalSplineTrajectoryGenerationComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_CardinalSplineTrajectoryGenerationComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_CardinalSplineTrajectoryGenerationComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}


bool KITECH_CardinalSplineTrajectoryGenerationComp::SetParameter(Property parameter)
{
	if(parameter.FindName("SamplingTime") == false) {
		PrintMessage("ERROR : KITECH_CardinalSplineTrajectoryGenerationComp::SetParameter() -> Can't find the SamplingTime in property\n");
		return false;
	}
	samplingTime = atof(parameter.GetValue("SamplingTime").c_str());

	if(parameter.FindName("Tension") == false) {
		PrintMessage("ERROR : KITECH_CardinalSplineTrajectoryGenerationComp::SetParameter() -> Can't find the Tension in property\n");
		return false;
	}
	tension = atof(parameter.GetValue("Tension").c_str());

	this->parameter = parameter;

	return true;
}

Property KITECH_CardinalSplineTrajectoryGenerationComp::GetParameter()
{
	return parameter;
}

int KITECH_CardinalSplineTrajectoryGenerationComp::GetError()
{
	return error;
}

bool KITECH_CardinalSplineTrajectoryGenerationComp::GenerateTrajectory(vector < valarray<double> > pathData)
{
	acceleration.clear();
	velocity.clear();
	position.clear();

	if (samplingTime < 0.001) samplingTime = 0.001;
	if (pathData.size() < 2) return false;

	unsigned int n = pathData.size () - 1;

	vector<double> h(n);
	for (unsigned int i=0; i<n; i++) {
		h[i] = pathData[i+1][0] - pathData[i][0];
		if (h[i] < samplingTime) h[i] = samplingTime;
	}

	vector< valarray<double> > m (n+1);
	unsigned int i = 0;

	m[i] = (1. - tension)*(pathData[i+1] - pathData[i])/h[i];
	for (i=1; i<n; i++) {
		m[i] = (1. - tension)*(pathData[i+1] - pathData[i-1])/(h[i] + h[i-1]);
	}
	m[i] = (1. - tension)*(pathData[i] - pathData[i-1])/h[i-1];

	position.reserve ((int)(pathData[n][0] / samplingTime + 10));

	double t = pathData[0][0];
	for (unsigned int i=0; i<n; i++) {
		for (; t<=pathData[i+1][0]; t+=samplingTime) {
			double t1 = (t - pathData[i][0])/h[i];
			double t2 = t1*t1;
			double t3 = t2*t1;

			double h00 = 2*t3-3*t2+1;
			double h10 = t3-2*t2+t1;
			double h01 = -2*t3+3*t2;
			double h11 = t3-t2;
			
			valarray<double> p = h00*pathData[i] + h10*m[i] + h01*pathData[i+1] + h11*m[i+1];
			p[0] = t;
			position.push_back (p);
		}
    }
	position.push_back (pathData[n]);

	return true;
}

vector< valarray<double> > KITECH_CardinalSplineTrajectoryGenerationComp::GetAcceleration()
{
	return acceleration;
}

vector< valarray<double> > KITECH_CardinalSplineTrajectoryGenerationComp::GetVelocity()
{
	return velocity;
}

vector< valarray<double> > KITECH_CardinalSplineTrajectoryGenerationComp::GetPosition()
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
	return new KITECH_CardinalSplineTrajectoryGenerationComp();
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
	return new KITECH_CardinalSplineTrajectoryGenerationComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

