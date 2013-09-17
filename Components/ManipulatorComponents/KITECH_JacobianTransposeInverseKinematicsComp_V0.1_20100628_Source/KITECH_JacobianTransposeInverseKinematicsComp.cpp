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

#include "KITECH_JacobianTransposeInverseKinematicsComp.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
KITECH_JacobianTransposeInverseKinematicsComp::KITECH_JacobianTransposeInverseKinematicsComp()
{
	jacobianTranspose = NULL;
	error = 0;
	
	portSetup();
}

//
// constructor declaration (with name)
//
KITECH_JacobianTransposeInverseKinematicsComp::KITECH_JacobianTransposeInverseKinematicsComp(const std::string &name):Component(name)
{
	jacobianTranspose = NULL;
	error = 0;
	
	portSetup();
}

//
// destructor declaration
//

KITECH_JacobianTransposeInverseKinematicsComp::~KITECH_JacobianTransposeInverseKinematicsComp() 
{
	onDestroy();
}

void KITECH_JacobianTransposeInverseKinematicsComp::portSetup() {

	// provided service port setup
	ProvidedServicePort *pa1;
	pa1=new InverseKinematicsServiceProvided(this);

	addPort("InverseKinematicsService",pa1);

}

// Call back Declaration
ReturnType KITECH_JacobianTransposeInverseKinematicsComp::onInitialize()
{
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);

	if(SetParameter(parameter) == false) {
		return OPROS_CALLER_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType KITECH_JacobianTransposeInverseKinematicsComp::onStart()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_JacobianTransposeInverseKinematicsComp::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_JacobianTransposeInverseKinematicsComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_JacobianTransposeInverseKinematicsComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_JacobianTransposeInverseKinematicsComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_JacobianTransposeInverseKinematicsComp::onDestroy()
{
	if(jacobianTranspose != NULL) {
		delete jacobianTranspose;
		jacobianTranspose = NULL;
	}

	return OPROS_SUCCESS;
}

ReturnType KITECH_JacobianTransposeInverseKinematicsComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_JacobianTransposeInverseKinematicsComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_JacobianTransposeInverseKinematicsComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_JacobianTransposeInverseKinematicsComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool KITECH_JacobianTransposeInverseKinematicsComp::SetParameter(Property parameter)
{
	int jointCount;
	int jointType, jointAxis;
	double x, y, z, phi, theta, psi;
	char name[128];

	onDestroy();

	if(parameter.FindName("UseOrientation") == false) {
		PrintMessage("ERROR : KITECH_JacobianTransposeInverseKinematicsComp::SetParameter() -> Can't find the UseOrientation in property\n");
		return false;
	}
	if(atoi(parameter.GetValue("UseOrientation").c_str()) == 0) {
		jacobianTranspose = new JacobianTranspose(POSITION_ONLY);
	}
	else {
		jacobianTranspose = new JacobianTranspose(POSITION_ORIENTATION);
	}

	if(parameter.FindName("JointCount") == false) {
		PrintMessage("ERROR : KITECH_JacobianTransposeInverseKinematicsComp::SetParameter() -> Can't find the JointCount in property\n");
		return false;
	}
	jointCount = atoi(parameter.GetValue("JointCount").c_str());

	PrintMessage("KITECH_JacobianTransposeInverseKinematicsComp Joint Information\n");

	for(int i = 0; i < jointCount; i++) {
		sprintf(name, "JointType%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_JacobianTransposeInverseKinematicsComp_SetParameter;
		else										jointType = atoi(parameter.GetValue(name).c_str());

		sprintf(name, "JointAxis%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_JacobianTransposeInverseKinematicsComp_SetParameter;
		else										jointAxis = atoi(parameter.GetValue(name).c_str());

		sprintf(name, "X%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_JacobianTransposeInverseKinematicsComp_SetParameter;
		else										x = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Y%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_JacobianTransposeInverseKinematicsComp_SetParameter;
		else										y = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Z%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_JacobianTransposeInverseKinematicsComp_SetParameter;
		else										z = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Phi%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_JacobianTransposeInverseKinematicsComp_SetParameter;
		else										phi = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Theta%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_JacobianTransposeInverseKinematicsComp_SetParameter;
		else										theta = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Psi%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_JacobianTransposeInverseKinematicsComp_SetParameter;
		else										psi = atof(parameter.GetValue(name).c_str());

		jacobianTranspose->AttachJoint(jointType, jointAxis, x, y, z, phi, theta, psi, 0.1);

		PrintMessage("Axis%d %d %d %.1f %.1f %.1f %.1f %.1f %.1f\n", i, jointType, jointAxis, x, y, z, phi, theta, psi);
	}

	this->parameter = parameter;

	return true;

ERROR_KITECH_JacobianTransposeInverseKinematicsComp_SetParameter :
	onDestroy();
	return false;
}
Property KITECH_JacobianTransposeInverseKinematicsComp::GetParameter()
{
	return parameter;
}
int KITECH_JacobianTransposeInverseKinematicsComp::GetError()
{
	return error;
}

bool KITECH_JacobianTransposeInverseKinematicsComp::SetJointPosition(vector<double> jointPosition)
{
	if(jacobianTranspose == NULL) {
		return false;
	}

	for(size_t i = 0; i < jointPosition.size(); i++) {
		jointPosition[i] *= _DEG2RAD;
	}

	return jacobianTranspose->SetJointAngle(jointPosition);
}

vector<double> KITECH_JacobianTransposeInverseKinematicsComp::GetJointPosition()
{
	vector<double> jointPosition;

	if(jacobianTranspose == NULL) {
		error = -1;
		return jointPosition;
	}

	dVector ret = jacobianTranspose->GetJointAngle();
	for(size_t i = 0; i < ret.size(); i++) {
		jointPosition.push_back(ret[i]*_RAD2DEG);
	}

	return jointPosition;
}

bool KITECH_JacobianTransposeInverseKinematicsComp::SetDesiredPosition(ObjectPosition desiredPosition)
{
	if(jacobianTranspose == NULL) {
		return false;
	}

	jacobianTranspose->SetDesired(desiredPosition.x, desiredPosition.y, desiredPosition.z,
						desiredPosition.roll * _DEG2RAD,
						desiredPosition.pitch * _DEG2RAD,
						desiredPosition.yaw * _DEG2RAD);


	dVector dq = jacobianTranspose->SolveJTR(0.3, 0.1);
	jacobianTranspose->Apply(dq);
	jacobianTranspose->Forward();

	return true;
}

ObjectPosition KITECH_JacobianTransposeInverseKinematicsComp::GetCurrentPosition()
{
	ObjectPosition currentPosition;

	if(jacobianTranspose == NULL) {
		error = -1;
		return currentPosition;
	}

	jacobianTranspose->Forward();
	dVector ret = jacobianTranspose->GetCurrent();
	currentPosition.x = ret[0];
	currentPosition.y = ret[1];
	currentPosition.z = ret[2];
	currentPosition.roll = (_RAD2DEG * ret[3]);
	currentPosition.pitch = (_RAD2DEG * ret[4]);
	currentPosition.yaw = (_RAD2DEG * ret[5]);

	return currentPosition;
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
	return new KITECH_JacobianTransposeInverseKinematicsComp();
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
	return new KITECH_JacobianTransposeInverseKinematicsComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

