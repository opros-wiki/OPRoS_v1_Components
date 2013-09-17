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

#include "KITECH_DampedLeastSquareInverseKinematicsComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
KITECH_DampedLeastSquareInverseKinematicsComp::KITECH_DampedLeastSquareInverseKinematicsComp()
{
	dampedLeastSquare = NULL;
	error = 0;
	
	portSetup();
}

//
// constructor declaration (with name)
//
KITECH_DampedLeastSquareInverseKinematicsComp::KITECH_DampedLeastSquareInverseKinematicsComp(const std::string &name):Component(name)
{
	dampedLeastSquare = NULL;
	error = 0;
	
	portSetup();
}

//
// destructor declaration
//

KITECH_DampedLeastSquareInverseKinematicsComp::~KITECH_DampedLeastSquareInverseKinematicsComp() 
{
	onDestroy();
}

void KITECH_DampedLeastSquareInverseKinematicsComp::portSetup() {

	// provided service port setup
	ProvidedServicePort *pa1;
	pa1=new InverseKinematicsServiceProvided(this);

	addPort("InverseKinematicsService",pa1);

}

// Call back Declaration
ReturnType KITECH_DampedLeastSquareInverseKinematicsComp::onInitialize()
{
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);

	if(SetParameter(parameter) == false) {
		return OPROS_CALLER_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType KITECH_DampedLeastSquareInverseKinematicsComp::onStart()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_DampedLeastSquareInverseKinematicsComp::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_DampedLeastSquareInverseKinematicsComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_DampedLeastSquareInverseKinematicsComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_DampedLeastSquareInverseKinematicsComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_DampedLeastSquareInverseKinematicsComp::onDestroy()
{
	if(dampedLeastSquare != NULL) {
		delete dampedLeastSquare;
		dampedLeastSquare = NULL;
	}

	return OPROS_SUCCESS;
}

ReturnType KITECH_DampedLeastSquareInverseKinematicsComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_DampedLeastSquareInverseKinematicsComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_DampedLeastSquareInverseKinematicsComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_DampedLeastSquareInverseKinematicsComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}


bool KITECH_DampedLeastSquareInverseKinematicsComp::SetParameter(Property parameter)
{
	int jointCount;
	int jointType, jointAxis;
	double x, y, z, phi, theta, psi;
	char name[128];

	onDestroy();

	if(parameter.FindName("UseOrientation") == false) {
		PrintMessage("ERROR : KITECH_DampedLeastSquareInverseKinematicsComp::SetParameter() -> Can't find the UseOrientation in property\n");
		return false;
	}
	if(atoi(parameter.GetValue("UseOrientation").c_str()) == 0) {
		dampedLeastSquare = new DampedLeastSquare(POSITION_ONLY);
	}
	else {
		dampedLeastSquare = new DampedLeastSquare(POSITION_ORIENTATION);
	}

	if(parameter.FindName("JointCount") == false) {
		PrintMessage("ERROR : KITECH_DampedLeastSquareInverseKinematicsComp::SetParameter() -> Can't find the JointCount in property\n");
		return false;
	}
	jointCount = atoi(parameter.GetValue("JointCount").c_str());

	PrintMessage("KITECH_DampedLeastSquareInverseKinematicsComp Joint Information\n");

	for(int i = 0; i < jointCount; i++) {
		sprintf(name, "JointType%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_DampedLeastSquareInverseKinematicsComp_SetParameter;
		else										jointType = atoi(parameter.GetValue(name).c_str());

		sprintf(name, "JointAxis%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_DampedLeastSquareInverseKinematicsComp_SetParameter;
		else										jointAxis = atoi(parameter.GetValue(name).c_str());

		sprintf(name, "X%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_DampedLeastSquareInverseKinematicsComp_SetParameter;
		else										x = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Y%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_DampedLeastSquareInverseKinematicsComp_SetParameter;
		else										y = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Z%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_DampedLeastSquareInverseKinematicsComp_SetParameter;
		else										z = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Phi%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_DampedLeastSquareInverseKinematicsComp_SetParameter;
		else										phi = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Theta%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_DampedLeastSquareInverseKinematicsComp_SetParameter;
		else										theta = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Psi%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_DampedLeastSquareInverseKinematicsComp_SetParameter;
		else										psi = atof(parameter.GetValue(name).c_str());

		dampedLeastSquare->AttachJoint(jointType, jointAxis, x, y, z, phi, theta, psi, 0.1);

		PrintMessage("Axis%d %d %d %.1f %.1f %.1f %.1f %.1f %.1f\n", i, jointType, jointAxis, x, y, z, phi, theta, psi);
	}

	this->parameter = parameter;

	return true;

ERROR_KITECH_DampedLeastSquareInverseKinematicsComp_SetParameter :
	onDestroy();
	return false;
}
Property KITECH_DampedLeastSquareInverseKinematicsComp::GetParameter()
{
	return parameter;
}
int KITECH_DampedLeastSquareInverseKinematicsComp::GetError()
{
	return error;
}

bool KITECH_DampedLeastSquareInverseKinematicsComp::SetJointPosition(vector<double> jointPosition)
{
	if(dampedLeastSquare == NULL) {
		return false;
	}

	for(size_t i = 0; i < jointPosition.size(); i++) {
		jointPosition[i] *= _DEG2RAD;
	}

	return dampedLeastSquare->SetJointAngle(jointPosition);
}

vector<double> KITECH_DampedLeastSquareInverseKinematicsComp::GetJointPosition()
{
	vector<double> jointPosition;

	if(dampedLeastSquare == NULL) {
		error = -1;
		return jointPosition;
	}

	dVector ret = dampedLeastSquare->GetJointAngle();
	for(size_t i = 0; i < ret.size(); i++) {
		jointPosition.push_back(ret[i]*_RAD2DEG);
	}

	return jointPosition;
}

bool KITECH_DampedLeastSquareInverseKinematicsComp::SetDesiredPosition(ObjectPosition desiredPosition)
{
	if(dampedLeastSquare == NULL) {
		return false;
	}

	dampedLeastSquare->SetDesired(desiredPosition.x, desiredPosition.y, desiredPosition.z,
						desiredPosition.roll * _DEG2RAD,
						desiredPosition.pitch * _DEG2RAD,
						desiredPosition.yaw * _DEG2RAD);


	dVector dq = dampedLeastSquare->SolveDLS(0.3, 0.1, 0.0);
	dampedLeastSquare->Apply(dq);
	dampedLeastSquare->Forward();

	return true;
}

ObjectPosition KITECH_DampedLeastSquareInverseKinematicsComp::GetCurrentPosition()
{
	ObjectPosition currentPosition;

	if(dampedLeastSquare == NULL) {
		error = -1;
		return currentPosition;
	}

	dampedLeastSquare->Forward();
	dVector ret = dampedLeastSquare->GetCurrent();
	currentPosition.x = ret[0];
	currentPosition.y = ret[1];
	currentPosition.z = ret[2];
	currentPosition.roll = (_RAD2DEG * ret[3]);
	currentPosition.pitch = (_RAD2DEG * ret[4]);
	currentPosition.yaw = (_RAD2DEG * ret[5]);

	return currentPosition;
}
/*

vector<double> KITECH_DampedLeastSquareInverseKinematicsComp::SloveInverseKinematics(vector<double> jointPosition,ObjectPosition desiredPosition)
{
	vector<double> ret(0);
	error = 0;

	if(dampedLeastSquare == NULL) {
		error = -1;
		return ret;
	}

	dampedLeastSquare->SetDesired(desiredPosition.x, desiredPosition.y, desiredPosition.z,
						desiredPosition.roll * _DEG2RAD,
						desiredPosition.pitch * _DEG2RAD,
						desiredPosition.yaw * _DEG2RAD);


	dVector dq = dampedLeastSquare->SolveDLS(0.1);
	dampedLeastSquare->Apply(dq);
	dVector q = dampedLeastSquare->GetJointAngle();

	for(size_t i = 0; i < q.size(); i++) {
		ret.push_back(q[i] * _RAD2DEG);
	}

	return ret;
}
*/


#ifdef MAKE_COMPONENT_DLL
#ifdef WIN32

extern "C"
{
__declspec(dllexport) Component *getComponent();
__declspec(dllexport) void releaseComponent(Component *pcom);
}

Component *getComponent()
{
	return new KITECH_DampedLeastSquareInverseKinematicsComp();
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
	return new KITECH_DampedLeastSquareInverseKinematicsComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

