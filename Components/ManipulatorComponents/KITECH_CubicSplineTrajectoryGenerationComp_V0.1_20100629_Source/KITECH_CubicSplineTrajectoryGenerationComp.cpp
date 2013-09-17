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

#include "KITECH_CubicSplineTrajectoryGenerationComp.h"
#include "OprosPrintMessage.h"
#include "MatrixAlgebra.h"

//
// constructor declaration
//
KITECH_CubicSplineTrajectoryGenerationComp::KITECH_CubicSplineTrajectoryGenerationComp()
{
	error = 0;

	portSetup();
}

//
// constructor declaration (with name)
//
KITECH_CubicSplineTrajectoryGenerationComp::KITECH_CubicSplineTrajectoryGenerationComp(const std::string &name):Component(name)
{
	error = 0;

	portSetup();
}

//
// destructor declaration
//

KITECH_CubicSplineTrajectoryGenerationComp::~KITECH_CubicSplineTrajectoryGenerationComp() {
}

void KITECH_CubicSplineTrajectoryGenerationComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new TrajectoryGenerationServiceProvided(this);

	addPort("TrajectoryGenerationService",pa1);

}

// Call back Declaration
ReturnType KITECH_CubicSplineTrajectoryGenerationComp::onInitialize()
{
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);

	if(SetParameter(parameter) == false) {
		return OPROS_CALLER_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType KITECH_CubicSplineTrajectoryGenerationComp::onStart()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_CubicSplineTrajectoryGenerationComp::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_CubicSplineTrajectoryGenerationComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_CubicSplineTrajectoryGenerationComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_CubicSplineTrajectoryGenerationComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_CubicSplineTrajectoryGenerationComp::onDestroy()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_CubicSplineTrajectoryGenerationComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_CubicSplineTrajectoryGenerationComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_CubicSplineTrajectoryGenerationComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_CubicSplineTrajectoryGenerationComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}


bool KITECH_CubicSplineTrajectoryGenerationComp::SetParameter(Property parameter)
{
	if(parameter.FindName("SamplingTime") == false) {
		PrintMessage("ERROR : KITECH_CubicSplineTrajectoryGenerationComp::SetParameter() -> Can't find the SamplingTime in property\n");
		return false;
	}

	samplingTime = atof(parameter.GetValue("SamplingTime").c_str());

	this->parameter = parameter;

	return true;
}

Property KITECH_CubicSplineTrajectoryGenerationComp::GetParameter()
{
	return parameter;
}

int KITECH_CubicSplineTrajectoryGenerationComp::GetError()
{
	return error;
}

bool KITECH_CubicSplineTrajectoryGenerationComp::GenerateTrajectory(vector < valarray<double> > pathData)
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

	dMatrix A(n+1, n+1);
	A.zero();
	{
		unsigned int i = 0;
		A(0, 0) = 2*h[i];
		A(0, 1) = h[i];
		for (i=1; i<n; ++i) {
			A(i, i-1) = h[i-1];
			A(i, i+0) = 2*(h[i-1] + h[i]);
			A(i, i+1) = h[i];
		}
		A(i, i-1) = h[i-1];
		A(i, i)   = 2.*h[i-1];
	}

	dMatrix b(n+1, pathData[0].size());
	{
		unsigned int i = 0;
		for (unsigned int j=0, m=pathData[0].size(); j<m; ++j) {
			b(i, j) = 6.*((pathData[i+1][j] - pathData[i][j])/h[i]);
		}
		for (i=1; i<n; ++i) {
			for (unsigned int j=0, m=pathData[0].size(); j<m; ++j) {
				b(i, j) = 6.*((pathData[i+1][j] - pathData[i][j])/h[i] - (pathData[i][j] - pathData[i-1][j])/h[i-1]);
			}
		}
		for (unsigned int j=0, m=pathData[0].size(); j<m; ++j) {
			b(i, j) = 6.*(-(pathData[i][j] - pathData[i-1][j])/h[i-1]);
		}
	}

	dMatrix z = !A*b;

	position.reserve ((int)(pathData[n][0] / samplingTime + 10));

	double t = pathData[0][0];
	for (unsigned int i=0; i<n; ++i) {
		for (; t<pathData[i+1][0]; t+=samplingTime) {
			double tm = t - pathData[i][0];
			double tp = pathData[i+1][0] - t;

			double tm3 = tm*tm*tm;
			double tp3 = tp*tp*tp;

			valarray<double> p (pathData[i].size());

			p[0] = t;
			for (int j=1, m=pathData[i].size(); j<m; ++j) {
				p[j] = (z(i+1,j)*tm3 + z(i,j)*tp3)/(6.*h[i]) + (pathData[i+1][j]/h[i] - h[i]*z(i+1,j)/6.)*tm + (pathData[i][j]/h[i] - h[i]*z(i,j)/6.)*tp;
			}
			position.push_back (p);
		}
	}
	position.push_back (pathData[n]);

	return true;
}

vector< valarray<double> > KITECH_CubicSplineTrajectoryGenerationComp::GetAcceleration()
{
	return acceleration;
}

vector< valarray<double> > KITECH_CubicSplineTrajectoryGenerationComp::GetVelocity()
{
	return velocity;
}

vector< valarray<double> > KITECH_CubicSplineTrajectoryGenerationComp::GetPosition()
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
	return new KITECH_CubicSplineTrajectoryGenerationComp();
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
	return new KITECH_CubicSplineTrajectoryGenerationComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

