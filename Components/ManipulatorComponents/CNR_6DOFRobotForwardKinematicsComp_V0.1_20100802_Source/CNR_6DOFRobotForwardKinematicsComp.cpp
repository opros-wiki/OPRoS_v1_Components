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

#include "CNR_6DOFRobotForwardKinematicsComp.h"
#include "OprosPrintMessage.h"

#include "matrix.h"
#include "vector.h"
//
// constructor declaration
//
CNR_6DOFRobotForwardKinematicsComp::CNR_6DOFRobotForwardKinematicsComp()
{
	error = 0;
	
	portSetup();
}

//
// constructor declaration (with name)
//
CNR_6DOFRobotForwardKinematicsComp::CNR_6DOFRobotForwardKinematicsComp(const std::string &name):Component(name)
{
	error = 0;
	
	portSetup();
}

//
// destructor declaration
//

CNR_6DOFRobotForwardKinematicsComp::~CNR_6DOFRobotForwardKinematicsComp() 
{
	onDestroy();
}

void CNR_6DOFRobotForwardKinematicsComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new InverseKinematicsServiceProvided(this);

	addPort("InverseKinematicsService",pa1);
}

// Call back Declaration
ReturnType CNR_6DOFRobotForwardKinematicsComp::onInitialize()
{
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);

	if(SetParameter(parameter) == false) {
		return OPROS_CALLER_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType CNR_6DOFRobotForwardKinematicsComp::onStart()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType CNR_6DOFRobotForwardKinematicsComp::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CNR_6DOFRobotForwardKinematicsComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CNR_6DOFRobotForwardKinematicsComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CNR_6DOFRobotForwardKinematicsComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CNR_6DOFRobotForwardKinematicsComp::onDestroy()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CNR_6DOFRobotForwardKinematicsComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CNR_6DOFRobotForwardKinematicsComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType CNR_6DOFRobotForwardKinematicsComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CNR_6DOFRobotForwardKinematicsComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool CNR_6DOFRobotForwardKinematicsComp::SetParameter(Property parameter)
{
	onDestroy();

	if(parameter.FindName("UpperArmLength") == false) {
		PrintMessage("ERROR : CNR_6DOFRobotForwardKinematicsComp::SetParameter() -> Can't find the UpperArmLength in property\n");
		return false;
	}
	if(parameter.FindName("LowerArmLength") == false) {
		PrintMessage("ERROR : CNR_6DOFRobotForwardKinematicsComp::SetParameter() -> Can't find the LowerArmLength in property\n");
		return false;
	}
	if(parameter.FindName("ToolLength") == false) {
		PrintMessage("ERROR : CNR_6DOFRobotForwardKinematicsComp::SetParameter() -> Can't find the ToolLength in property\n");
		return false;
	}

	PrintMessage("UpperArmLength : %.3f\nLowerArmLength : %.3f\nToolLength : %.3f\n",atof(parameter.GetValue("UpperArmLength").c_str())
																					,atof(parameter.GetValue("LowerArmLength").c_str())
																					,atof(parameter.GetValue("ToolLength").c_str())  );

	this->parameter = parameter;

	return true;
}

Property CNR_6DOFRobotForwardKinematicsComp::GetParameter()
{
	return parameter;
}

int CNR_6DOFRobotForwardKinematicsComp::GetError()
{
	return error;
}

bool CNR_6DOFRobotForwardKinematicsComp::SetJointPosition(vector<double> jointPosition)
{
	int size = jointPosition.size();
	if(size == 6)
	{
		m_joint = jointPosition;
		return true;
	}
	else
		return false;
}

vector<double> CNR_6DOFRobotForwardKinematicsComp::GetJointPosition()
{
	vector<double> jointPosition;

	return jointPosition;
}

bool CNR_6DOFRobotForwardKinematicsComp::SetDesiredPosition(ObjectPosition desiredPosition)
{
	return true;
}

ObjectPosition CNR_6DOFRobotForwardKinematicsComp::GetCurrentPosition()
{
 	ObjectPosition ret;

	//////////////////////////////////////////////////////////////////////////
	//   정기구학 
	//////////////////////////////////////////////////////////////////////////
	struct link
	{
		double theta, a, d, alpha;
	};

	link lnk[6];
	//1
	lnk[0].d = 0;
	lnk[0].a = 0;
	lnk[0].alpha = -M_PI_2;
	//2
	lnk[1].d = 0;
	lnk[1].a = atof(parameter.GetValue("UpperArmLength").c_str());
	lnk[1].alpha = 0;
	//3
	lnk[2].d = 0;
	lnk[2].a = 0;
	lnk[2].alpha = M_PI_2;
	//4
	lnk[3].d = atof(parameter.GetValue("LowerArmLength").c_str());
	lnk[3].a = 0;
	lnk[3].alpha = -M_PI_2;
	//5
	lnk[4].d = 0;
	lnk[4].a = 0;
	lnk[4].alpha = M_PI_2;
	//6
	lnk[5].d = atof(parameter.GetValue("ToolLength").c_str());
	lnk[5].a = 0;
	lnk[5].alpha = 0;


	MSLMatrix NowRot(3,3);
	MSLVector NowPos(3);

	MSLMatrix Rot(3,3);
	MSLVector Pos(3);

	double ct,st,ca,sa;
	int i;


	lnk[0].theta = DEG2RAD(m_joint[0]); // + lnk[0].joint_offset;
	ct = cos(lnk[0].theta);
	st = sin(lnk[0].theta);
	ca = cos(lnk[0].alpha);
	sa = sin(lnk[0].alpha);

	Rot(0,0) =  ct;
	Rot(1,0) =  st;
	Rot(2,0) =  0.0;
	Rot(0,1) = -ca*st;
	Rot(1,1) =  ca*ct;
	Rot(2,1) =  sa;
	Rot(0,2) =  sa*st;
	Rot(1,2) = -sa*ct;
	Rot(2,2) =  ca;
	Pos[0]   =  lnk[0].a * ct;
	Pos[1]   =  lnk[0].a * st;
	Pos[2]   =  lnk[0].d;


	for(i = 1 ; i < 6 ; i++)
	{	

		lnk[i].theta = DEG2RAD(m_joint[i]);//+ lnk[i].joint_offset;
		ct = cos(lnk[i].theta);
		st = sin(lnk[i].theta);
		ca = cos(lnk[i].alpha);
		sa = sin(lnk[i].alpha);

		NowRot(0,0) =  ct;
		NowRot(1,0) =  st;
		NowRot(2,0) =  0.0;
		NowRot(0,1) = -ca*st;
		NowRot(1,1) =  ca*ct;
		NowRot(2,1) =  sa;
		NowRot(0,2) =  sa*st;
		NowRot(1,2) = -sa*ct;
		NowRot(2,2) =  ca;
		NowPos[0]    =  lnk[i].a * ct;
		NowPos[1]    =  lnk[i].a * st;
		NowPos[2]    =  lnk[i].d;

		Pos = Pos + Rot*NowPos;
		Rot = Rot*NowRot;
	}


	ret.x = Pos[0];
	ret.y = Pos[1];
	ret.z = Pos[2];


	//오리엔테이션에서 오일러ZYX(Z회전->Y회전->X회전) 회전의 각도를 뽑아냄
	if (Rot(2,0)==1) {
		ret.roll = RAD2DEG(atan2(-Rot(0,1),-Rot(0,2)));	//alpha(x회전Roll각도)
		ret.pitch = -90.;	//-PI/2;						//betta(y회전Pitch각도)
		ret.yaw = 0.0;						//gamma(Z회전Yaw각도)
	} else if (Rot(2,0)==-1) {
		ret.roll  = RAD2DEG(atan2(Rot(0,1),Rot(0,2)));
		ret.pitch = 90.;	//PI/2;
		ret.yaw = 0.0;
	} else {
		ret.roll = RAD2DEG(atan2(Rot(2,1), Rot(2,2)));
		ret.pitch = RAD2DEG(atan2(-Rot(2,0), sqrt(Rot(0,0)*Rot(0,0) + Rot(1,0)*Rot(1,0))));
		ret.yaw = RAD2DEG(atan2(Rot(1,0), Rot(0,0)));
	}

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
	return new CNR_6DOFRobotForwardKinematicsComp();
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
	return new CNR_6DOFRobotForwardKinematicsComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

