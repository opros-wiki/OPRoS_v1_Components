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

#include "KITECH_PDControlWithGravity.h"
#include "OprosPrintMessage.h"

//
// constructor declaration
//
KITECH_PDControlWithGravity::KITECH_PDControlWithGravity()
{
	error = 0;
	_dynamics = NULL;
	
	portSetup();
}

//
// constructor declaration (with name)
//
KITECH_PDControlWithGravity::KITECH_PDControlWithGravity(const std::string &name):Component(name)
{
	error = 0;
	_dynamics = NULL;
	
	portSetup();
}

//
// destructor declaration
//

KITECH_PDControlWithGravity::~KITECH_PDControlWithGravity() 
{
	onDestroy();
}

void KITECH_PDControlWithGravity::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new TrackingControlServiceProvided(this);

	addPort("TrackingControlService",pa1);

}

// Call back Declaration
ReturnType KITECH_PDControlWithGravity::onInitialize()
{
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);

	if(SetParameter(parameter) == false) {
		return OPROS_CALLER_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType KITECH_PDControlWithGravity::onStart()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_PDControlWithGravity::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_PDControlWithGravity::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_PDControlWithGravity::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_PDControlWithGravity::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_PDControlWithGravity::onDestroy()
{
	if(_dynamics != NULL) {
		delete _dynamics;
		_dynamics = NULL;
	}

	return OPROS_SUCCESS;
}

ReturnType KITECH_PDControlWithGravity::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_PDControlWithGravity::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType KITECH_PDControlWithGravity::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KITECH_PDControlWithGravity::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool KITECH_PDControlWithGravity::SetParameter(Property parameter)
{
	double period;
	int jointCount;
	int jointType, jointAxis;
	double x, y, z, phi, theta, psi;
	double mass, cx, cy, cz;
	double ixx, iyy, izz, ixy, iyz, izx;

	char name[128];
	double gravity[3] = {0., 0., -9.81 };

	onDestroy();

	if(parameter.FindName("Period") == false) {
		PrintMessage("ERROR : KITECH_PDControlWithGravity::SetParameter() -> Can't find the Period in property\n");
		return false;
	}
	period = atof(parameter.GetValue("Period").c_str());
	_dynamics = new PDControlWithGravity(gravity, period);

	//	Set gains
	if(parameter.FindName("Kp") == false) {
		PrintMessage("ERROR : KITECH_PassivityBasedControlComp::SetParameter() -> Can't find the JointCount in property\n");
		goto ERROR_KITECH_PDControlWithGravity_SetParameter;
	}
	_dynamics->SetKp(atof(parameter.GetValue("Kp").c_str()));

	if(parameter.FindName("Kd") == false) {
		PrintMessage("ERROR : KITECH_PassivityBasedControlComp::SetParameter() -> Can't find the JointCount in property\n");
		goto ERROR_KITECH_PDControlWithGravity_SetParameter;
	}
	_dynamics->SetKd(atof(parameter.GetValue("Kd").c_str()));


	//	Setup a joint information
	if(parameter.FindName("JointCount") == false) {
		PrintMessage("ERROR : KITECH_PDControlWithGravity::SetParameter() -> Can't find the JointCount in property\n");
		goto ERROR_KITECH_PDControlWithGravity_SetParameter;
	}
	jointCount = atoi(parameter.GetValue("JointCount").c_str());

	PrintMessage("KITECH_PDControlWithGravity Joint Information\n");

	for(int i = 0; i < jointCount; i++) {
		sprintf(name, "JointType%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_PDControlWithGravity_SetParameter;
		else										jointType = atoi(parameter.GetValue(name).c_str());

		sprintf(name, "JointAxis%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_PDControlWithGravity_SetParameter;
		else										jointAxis = atoi(parameter.GetValue(name).c_str());

		sprintf(name, "X%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_PDControlWithGravity_SetParameter;
		else										x = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Y%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_PDControlWithGravity_SetParameter;
		else										y = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Z%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_PDControlWithGravity_SetParameter;
		else										z = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Phi%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_PDControlWithGravity_SetParameter;
		else										phi = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Theta%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_PDControlWithGravity_SetParameter;
		else										theta = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Psi%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_PDControlWithGravity_SetParameter;
		else										psi = atof(parameter.GetValue(name).c_str());

		sprintf(name, "Mass%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_PDControlWithGravity_SetParameter;
		else										mass = atof(parameter.GetValue(name).c_str());

		
		sprintf(name, "CX%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_PDControlWithGravity_SetParameter;
		else										cx = atof(parameter.GetValue(name).c_str());

		
		sprintf(name, "CY%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_PDControlWithGravity_SetParameter;
		else										cy = atof(parameter.GetValue(name).c_str());

		sprintf(name, "CZ%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_PDControlWithGravity_SetParameter;
		else										cz = atof(parameter.GetValue(name).c_str());

		sprintf(name, "IXX%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_PDControlWithGravity_SetParameter;
		else										ixx = atof(parameter.GetValue(name).c_str());

		sprintf(name, "IYY%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_PDControlWithGravity_SetParameter;
		else										iyy = atof(parameter.GetValue(name).c_str());

		sprintf(name, "IZZ%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_PDControlWithGravity_SetParameter;
		else										izz = atof(parameter.GetValue(name).c_str());

		sprintf(name, "IXY%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_PDControlWithGravity_SetParameter;
		else										ixy = atof(parameter.GetValue(name).c_str());

		sprintf(name, "IYZ%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_PDControlWithGravity_SetParameter;
		else										iyz = atof(parameter.GetValue(name).c_str());

		sprintf(name, "IZX%d", i);
		if(parameter.FindName(name) == false)		goto ERROR_KITECH_PDControlWithGravity_SetParameter;
		else										izx = atof(parameter.GetValue(name).c_str());

		_dynamics->AttachJoint(jointType, jointAxis, mass, cx, cy, cz, ixx, iyy, izz, ixy, iyz, izx, x, y, z, phi, theta, psi, 0.3);

		PrintMessage("Axis%d %d %d %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f\n",
					i, jointType, jointAxis, x, y, z, phi, theta, psi, mass, cx, cy, cz, ixx, iyy, izz, ixy, iyz, izx);
	}

	this->parameter = parameter;

	return true;

ERROR_KITECH_PDControlWithGravity_SetParameter :
	PrintMessage("ERROR : KITECH_PDControlWithGravity::SetParameter() -> Can't find parameters in property\n");
	onDestroy();
	return false;
}

Property KITECH_PDControlWithGravity::GetParameter()
{
	return parameter;
}

int KITECH_PDControlWithGravity::GetError()
{
	return error;
}

bool KITECH_PDControlWithGravity::SetJointAcceleration(vector<double> jointAcceleration)
{
	if(_dynamics == NULL) {
		return false;
	}

	return _dynamics->SetJointAcceleration(jointAcceleration);
}

vector<double> KITECH_PDControlWithGravity::GetJointAcceleration()
{
	vector<double> jointAcceleration;
	error = 0;

	if(_dynamics == NULL) {
		error = -1;
	}
	else {
		jointAcceleration = _dynamics->GetJointAcceleration();
	}

	return jointAcceleration;
}

bool KITECH_PDControlWithGravity::SetJointVelocity(vector<double> jointVelocity)
{
	if(_dynamics == NULL) {
		return false;
	}
	
	return _dynamics->SetJointVelocity(jointVelocity);
}

vector<double> KITECH_PDControlWithGravity::GetJointVelocity()
{
	vector<double> jointVelocity;
	error = 0;

	if(_dynamics == NULL) {
		error = -1;
	}
	else {
		jointVelocity = _dynamics->GetJointVelocity();
	}

	return jointVelocity;
}

bool KITECH_PDControlWithGravity::SetJointPosition(vector<double> jointPosition)
{
	if(_dynamics == NULL) {
		return false;
	}

	return _dynamics->SetJointPosition(jointPosition);
}

vector<double> KITECH_PDControlWithGravity::GetJointPosition()
{
	vector<double> jointPosition;
	error = 0;

	if(_dynamics == NULL) {
		error = -1;
	}
	else {
		jointPosition = _dynamics->GetJointPosition();
	}

	return jointPosition;
}

bool KITECH_PDControlWithGravity::SetDesiredJointAcceleration(vector<double> desiredJointAcceleration)
{
	if(_dynamics == NULL) {
		return false;
	}

	return _dynamics->SetDesiredJointAcceleration(desiredJointAcceleration);
}

vector<double> KITECH_PDControlWithGravity::GetDesiredJointAcceleration()
{
	vector<double> desiredJointAcceleration;
	error = 0;

	if(_dynamics == NULL) {
		error = -1;
	}
	else {
		desiredJointAcceleration = _dynamics->GetDesiredJointAcceleration();
	}

	return desiredJointAcceleration;
}

bool KITECH_PDControlWithGravity::SetDesiredJointVelocity(vector<double> desiredJointVelocity)
{
	if(_dynamics == NULL) {
		return false;
	}
	
	return _dynamics->SetDesiredJointVelocity(desiredJointVelocity);
}
vector<double> KITECH_PDControlWithGravity::GetDesiredJointVelocity()
{
	vector<double> desiredJointVelocity;
	error = 0;

	if(_dynamics == NULL) {
		error = -1;
	}
	else {
		desiredJointVelocity = _dynamics->GetDesiredJointVelocity();
	}

	return desiredJointVelocity;
}

bool KITECH_PDControlWithGravity::SetDesiredJointPosition(vector<double> desiredJointPosition)
{
	if(_dynamics == NULL) {
		return false;
	}

	return _dynamics->SetDesiredJointPosition(desiredJointPosition);
}
vector<double> KITECH_PDControlWithGravity::GetDesiredJointPosition()
{
	vector<double> desiredJointPosition;
	error = 0;

	if(_dynamics == NULL) {
		error = -1;
	}
	else {
		desiredJointPosition = _dynamics->GetDesiredJointPosition();
	}

	return desiredJointPosition;
}

vector<double> KITECH_PDControlWithGravity::SloveTrackingControl()
{
	vector<double> torque;
	error = 0;

	if(_dynamics == NULL) {
		error = -1;
	}
	else {
		torque = _dynamics->RunController();
	}

	return torque;
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
	return new KITECH_PDControlWithGravity();
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
	return new KITECH_PDControlWithGravity();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

