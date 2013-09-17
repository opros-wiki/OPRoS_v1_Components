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

#include "KITECH_MonotoneCubicTrajectoryGenerationComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
KITECH_MonotoneCubicTrajectoryGenerationComp::KITECH_MonotoneCubicTrajectoryGenerationComp()
{
	error = 0;
	samplingTime = 0.0;
	monotonicity = 0.0;

	portSetup();
}

//
// constructor declaration (with name)
//
KITECH_MonotoneCubicTrajectoryGenerationComp::KITECH_MonotoneCubicTrajectoryGenerationComp(const std::string &name):Component(name)
{
	error = 0;
	samplingTime = 0.0;
	monotonicity = 0.0;

	portSetup();
}

//
// destructor declaration
//

KITECH_MonotoneCubicTrajectoryGenerationComp::~KITECH_MonotoneCubicTrajectoryGenerationComp() {
}

void KITECH_MonotoneCubicTrajectoryGenerationComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new TrajectoryGenerationServiceProvided(this);

	addPort("TrajectoryGenerationService",pa1);

}

// Call back Declaration
ReturnType KITECH_MonotoneCubicTrajectoryGenerationComp::onInitialize()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_MonotoneCubicTrajectoryGenerationComp::onStart()
{
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);

	if(SetParameter(parameter) == false) {
		return OPROS_CALLER_ERROR;
	}

	return OPROS_SUCCESS;
}
	
ReturnType KITECH_MonotoneCubicTrajectoryGenerationComp::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_MonotoneCubicTrajectoryGenerationComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_MonotoneCubicTrajectoryGenerationComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_MonotoneCubicTrajectoryGenerationComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_MonotoneCubicTrajectoryGenerationComp::onDestroy()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_MonotoneCubicTrajectoryGenerationComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_MonotoneCubicTrajectoryGenerationComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_MonotoneCubicTrajectoryGenerationComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_MonotoneCubicTrajectoryGenerationComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool KITECH_MonotoneCubicTrajectoryGenerationComp::SetParameter(Property parameter)
{
	if(parameter.FindName("SamplingTime") == false) {
		PrintMessage("ERROR : KITECH_MonotoneCubicTrajectoryGenerationComp::SetParameter() -> Can't find the SamplingTime in property\n");
		return false;
	}
	samplingTime = atof(parameter.GetValue("SamplingTime").c_str());

	if(parameter.FindName("Monotonicity") == false) {
		PrintMessage("ERROR : KITECH_MonotoneCubicTrajectoryGenerationComp::SetParameter() -> Can't find the Monotonicity in property\n");
		return false;
	}
	monotonicity = atof(parameter.GetValue("Monotonicity").c_str());

	this->parameter = parameter;

	return true;
}

Property KITECH_MonotoneCubicTrajectoryGenerationComp::GetParameter()
{
	return parameter;
}

int KITECH_MonotoneCubicTrajectoryGenerationComp::GetError()
{
	return error;
}

bool KITECH_MonotoneCubicTrajectoryGenerationComp::GenerateTrajectory(vector < valarray<double> > pathData)
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

	vector< valarray<double> > m (n + 1);
	unsigned int i = 0;

	m[i] = (pathData[i+1] - pathData[i])/h[i];
	for (i=1; i<n; i++) {
		m[i] = 0.5*(pathData[i] - pathData[i-1])/h[i-1] + 0.5*(pathData[i+1] - pathData[i])/h[i];
	}
	m[i] = (pathData[i] - pathData[i-1])/h[i-1];				

	for (unsigned int i=0; i<n; i++) {
		valarray<double> Dk = (pathData[i+1] - pathData[i])/h[i];

		for (int j=0; j<(int)pathData[i].size(); j++) {
			if (Dk[j] == 0.) {
				m[i][j] = 0.;
				m[i+1][j] = 0.;
			}
			else {
				double ak = m[i][j]/Dk[j];
				double bk = m[i+1][j]/Dk[j];
				double tk = monotonicity/sqrt(ak*ak + bk*bk);
				if (tk < 1.) {
					m[i][j] = tk*ak*Dk[j];
					m[i+1][j] = tk*bk*Dk[j];
				}
			}
		}
	}

	position.reserve ((int)(pathData[n][0] / samplingTime + 10));

	double t = pathData[0][0];
	for (unsigned int i=0; i<n; i++) {
		for (; t<=pathData[i+1][0]; t+=samplingTime) {
			double tp = (t - pathData[i][0])/h[i];
			double tm = (1. - tp);
			double h00 = (1. + 2.*tp)*tm*tm;
			double h10 = tp*tm*tm;
			double h01 = tp*tp*(3. - 2.*tp);
			double h11 = tp*tp*(tp - 1.);
			
			valarray<double> p = h00*pathData[i] + h10*m[i] + h01*pathData[i+1] + h11*m[i+1];
			p[0] = t;
			position.push_back (p);
		}
    }
	position.push_back (pathData[n]);

	return true;
}

vector< valarray<double> > KITECH_MonotoneCubicTrajectoryGenerationComp::GetAcceleration()
{
	return acceleration;
}

vector< valarray<double> > KITECH_MonotoneCubicTrajectoryGenerationComp::GetVelocity()
{
	return velocity;
}

vector< valarray<double> > KITECH_MonotoneCubicTrajectoryGenerationComp::GetPosition()
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
	return new KITECH_MonotoneCubicTrajectoryGenerationComp();
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
	return new KITECH_MonotoneCubicTrajectoryGenerationComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

