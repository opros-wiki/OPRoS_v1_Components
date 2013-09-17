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

#include "KITECH_FifthOrderPolynomialTrajectoryGeneration.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
KITECH_FifthOrderPolynomialTrajectoryGeneration::KITECH_FifthOrderPolynomialTrajectoryGeneration()
{
	error = 0;
	samplingTime = 0.02;
	
	portSetup();
}

//
// constructor declaration (with name)
//
KITECH_FifthOrderPolynomialTrajectoryGeneration::KITECH_FifthOrderPolynomialTrajectoryGeneration(const std::string &name):Component(name)
{
	error = 0;
	samplingTime = 0.02;
	
	portSetup();
}

//
// destructor declaration
//

KITECH_FifthOrderPolynomialTrajectoryGeneration::~KITECH_FifthOrderPolynomialTrajectoryGeneration() 
{
	onDestroy();
}

void KITECH_FifthOrderPolynomialTrajectoryGeneration::portSetup() {

	// provided service port setup
	ProvidedServicePort *pa1;
	pa1=new TrajectoryGenerationServiceProvided(this);

	addPort("TrajectoryGenerationService",pa1);

}

// Call back Declaration
ReturnType KITECH_FifthOrderPolynomialTrajectoryGeneration::onInitialize()
{
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);

	if(SetParameter(parameter) == false) {
		return OPROS_CALLER_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType KITECH_FifthOrderPolynomialTrajectoryGeneration::onStart()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_FifthOrderPolynomialTrajectoryGeneration::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_FifthOrderPolynomialTrajectoryGeneration::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_FifthOrderPolynomialTrajectoryGeneration::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_FifthOrderPolynomialTrajectoryGeneration::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_FifthOrderPolynomialTrajectoryGeneration::onDestroy()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_FifthOrderPolynomialTrajectoryGeneration::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_FifthOrderPolynomialTrajectoryGeneration::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_FifthOrderPolynomialTrajectoryGeneration::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_FifthOrderPolynomialTrajectoryGeneration::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}


bool KITECH_FifthOrderPolynomialTrajectoryGeneration::SetParameter(Property parameter)
{
	if(parameter.FindName("SamplingTime") == false) {
		PrintMessage("ERROR : KITECH_FifthOrderPolynomialTrajectoryGeneration::SetParameter() -> Can't find the SamplingTime in property\n");
		return false;
	}

	samplingTime = atof(parameter.GetValue("SamplingTime").c_str());

	this->parameter = parameter;

	return true;
}

Property KITECH_FifthOrderPolynomialTrajectoryGeneration::GetParameter()
{
	return parameter;
}

int KITECH_FifthOrderPolynomialTrajectoryGeneration::GetError()
{
	return error;
}

bool KITECH_FifthOrderPolynomialTrajectoryGeneration::GenerateTrajectory(vector < valarray<double> > pathData)
{
	vector< valarray<double> > a(6);

	acceleration.clear();
	velocity.clear();
	position.clear();

	if(pathData.size() < 2) {
		return false;
	}

	for(size_t i = 1; i < pathData.size(); i++) {
		if(pathData[i - 1].size() != pathData[i].size()) {
			return false;
		}
	}

	for(size_t i = 0; i < pathData.size() - 1; i++) {
		if(pathData[i + 1][0] - pathData[i][0] <= 0) {
			return false;
		}
	}

	for(size_t i = 0; i < a.size(); i++) {
		a[i].resize(pathData[0].size() - 1);
	}
	
	for(size_t i = 0; i < pathData.size() - 1; i++) {
		int size = (int)((pathData[i + 1][0] - pathData[i][0]) / samplingTime);

		a[0] = pathData[i];
		a[1] = 0.0;
		a[2] = 0.0;
		a[3] = (20.0*pathData[i + 1] - 20.0*pathData[i])/(2.0*pow(pathData[i + 1][0] - pathData[i][0], 3));
		a[4] = (30.0*pathData[i] - 30.0*pathData[i + 1])/(2.0*pow(pathData[i + 1][0] - pathData[i][0], 4));
		a[5] = (12.0*pathData[i + 1] - 12.0*pathData[i])/(2.0*pow(pathData[i + 1][0] - pathData[i][0], 5));

		for(int j = 1; j <= size; j++) {
			double t = samplingTime * (double)j;

			position.push_back((a[0]) + (a[1] * t) + (a[2] * pow(t, 2)) + (a[3] * pow(t, 3)) + (a[4] * pow(t, 4)) + (a[5] * pow(t, 5)));
			velocity.push_back((a[1]) + 2.0*(a[2] * t) + 3.0*(a[3] * pow(t, 2)) + 4.0*(a[4] * pow(t, 3)) + 5.0*(a[5] * pow(t, 4)));
			acceleration.push_back(2.0*(a[2]) + 6.0*(a[3] * t) + 12.0*(a[4] * pow(t, 2)) + 20.0*(a[5] * pow(t, 3)));
		}
	}

	return true;
}

vector< valarray<double> > KITECH_FifthOrderPolynomialTrajectoryGeneration::GetAcceleration()
{
	return acceleration;
}

vector< valarray<double> > KITECH_FifthOrderPolynomialTrajectoryGeneration::GetVelocity()
{
	return velocity;
}

vector< valarray<double> > KITECH_FifthOrderPolynomialTrajectoryGeneration::GetPosition()
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
	return new KITECH_FifthOrderPolynomialTrajectoryGeneration();
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
	return new KITECH_FifthOrderPolynomialTrajectoryGeneration();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

