
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

#include "CNR_6DOFAnalyticInverseKinematicsComp.h"
#include "OprosPrintMessage.h"
#include "matrix.h"
#include "vector.h"
//
// constructor declaration
//
CNR_6DOFAnalyticInverseKinematicsComp::CNR_6DOFAnalyticInverseKinematicsComp() 
{
	error = 0;

	portSetup();
}

//
// constructor declaration (with name)
//
CNR_6DOFAnalyticInverseKinematicsComp::CNR_6DOFAnalyticInverseKinematicsComp(const std::string &name):Component(name)
{
	error = 0;

	portSetup();
}

//
// destructor declaration
//

CNR_6DOFAnalyticInverseKinematicsComp::~CNR_6DOFAnalyticInverseKinematicsComp() 
{
	onDestroy();
}

void CNR_6DOFAnalyticInverseKinematicsComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new InverseKinematicsServiceProvided(this);

	addPort("InverseKinematicsService",pa1);

}

// Call back Declaration
ReturnType CNR_6DOFAnalyticInverseKinematicsComp::onInitialize()
{
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);

	if(SetParameter(parameter) == false) {
		return OPROS_CALLER_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType CNR_6DOFAnalyticInverseKinematicsComp::onStart()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType CNR_6DOFAnalyticInverseKinematicsComp::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CNR_6DOFAnalyticInverseKinematicsComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CNR_6DOFAnalyticInverseKinematicsComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CNR_6DOFAnalyticInverseKinematicsComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CNR_6DOFAnalyticInverseKinematicsComp::onDestroy()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CNR_6DOFAnalyticInverseKinematicsComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CNR_6DOFAnalyticInverseKinematicsComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType CNR_6DOFAnalyticInverseKinematicsComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CNR_6DOFAnalyticInverseKinematicsComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool CNR_6DOFAnalyticInverseKinematicsComp::SetParameter(Property parameter)
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

Property CNR_6DOFAnalyticInverseKinematicsComp::GetParameter()
{
	return parameter;
}

int CNR_6DOFAnalyticInverseKinematicsComp::GetError()
{
	return error;
}

bool CNR_6DOFAnalyticInverseKinematicsComp::SetJointPosition(vector<double> jointPosition)
{
	//���α׷� ����ȭ ������ ���� ó������ �迭ũ�Ⱑ 0�� �迭�� ����
	if(jointPosition.size() != 6) {
		error = -1;
		return false;
	}
	m_Joint = jointPosition;
	return true;
}

vector<double> CNR_6DOFAnalyticInverseKinematicsComp::GetJointPosition()
{
	vector<double> jointPosition(6);

		double m_fInverPointX, m_fInverPointY, m_fInverPointZ;	//��ǥ��
		double cr, cp , cy;
		double sr, sp , sy;
		int cha;
		double t1=0,t2=0,t3=0,t4=0,t5=0,t6=0 ;    //��Ÿ���� 
		double a1,a2,a3,d4,d6;				//�κ��μ��� 
		double ax,ay,az,ox,oy,oz,nx,ny,nz,px,py,pz;	//RTH������

		double tempt=0, temptA=0,temptB=0, A=0,Alpha=0;               //�ӽ����庯��

		m_fInverPointX = m_Position.x;
		m_fInverPointY = m_Position.y;
		m_fInverPointZ = m_Position.z;

		cr = cos(DEG2RAD(m_Position.roll));		sr = sin(DEG2RAD(m_Position.roll));	//roll�� ����
		cp = cos(DEG2RAD(m_Position.pitch));		sp = sin(DEG2RAD(m_Position.pitch));	//pitch������
		cy = cos(DEG2RAD(m_Position.yaw));		sy = sin(DEG2RAD(m_Position.yaw));	//yaw�� ����


		a1= 0.;		//�̰��� ������� �ǹ̴� ����� 6��κ� DH ����
		a2= atof(parameter.GetValue("UpperArmLength").c_str());	//��ϱ���
		a3=0.;		//�̰��� ������� �ǹ̴� ����� 6��κ� DH ����
		d4= atof(parameter.GetValue("LowerArmLength").c_str());	//�Ͽϱ���
		d6= atof(parameter.GetValue("ToolLength").c_str());				//�׸���(��)����
		//���������̼�
		nx = cy*cp;		ox = cy*sp*sr-sy*cr;	ax = cy*sp*cr+sy*sr;	
		ny = sy*cp;		oy = sy*sp*sr+cy*cr;	ay = sy*sp*cr-cy*sr;	
		nz = -sp;		oz = cp*sr;				az = cp*cr;				



		px=m_fInverPointX - d6*ax;	//�׸����� ���̸�ŭ ��ġ���� ���ش�
		py=m_fInverPointY -	d6*ay;	
		pz=m_fInverPointZ -	d6*az;	


		//t1������

		if(px!=0)
			tempt=atan2(py,px);		//0���� �����°� ����
		else if(px==0)
		{
			if(py>0)
				tempt=M_PI/2.0;					
			else if(py<0)
				tempt=-M_PI/2.0;
			else 
				tempt=0.0;
		}

		t1=tempt;    
		//t2������
		tempt=0;

		A=(cos(t1)*px+sin(t1)*py-a1);

		Alpha=atan2((pz/sqrt(pz*pz+A*A)),(A/sqrt(pz*pz+A*A)));

		tempt=acos((A*A+pz*pz-d4*d4-a3*a3+a2*a2)/(2*a2*sqrt(pz*pz+A*A)));

		temptA=tempt+Alpha;
		temptB=tempt*-1.0+Alpha;

		//	if(fabs(temptA-M_PI/2.0)>fabs(temptB-M_PI/2.0))		//�ΰ��߿� 90���� ������ ���ϰ� ������ ū���� ���Ѵ�
		//	{	t2=temptB; cha=0;}			// �̰��� ���õǸ� V ������� ������ ���´�.
		//	else
		//{	t2=temptA; cha=1;}			//������ ^ ������ �����̰� ����  
		if( fabs(ASV_DEG(RAD2DEG(fmod(temptA*-1., 2.*M_PI)))-m_Joint[1]) > fabs(ASV_DEG(RAD2DEG(fmod(temptB*-1., 2.*M_PI)))-m_Joint[1]) )  //���� ������ ����� ������ ���� ����
		{
			t2=temptB; cha=0;
		}
		else
		{
			t2=temptA; cha=1;
		}

		//t3������
		tempt=0,temptA=0,temptB=0,Alpha=0;

		tempt=acos((A*A+pz*pz-a2*a2-a3*a3-d4*d4)/(2*a2*sqrt(d4*d4+a3*a3)));
		Alpha=atan2((d4/sqrt(d4*d4+a3*a3)),(a3/sqrt(d4*d4+a3*a3)));

		temptA=tempt+Alpha;
		temptB=tempt*-1.0+Alpha;

		if(cha==0)		//t2���� temptB�̸� t3������ temptA�� ��� �ϰ� �ݴ�� �ݴ�� ����Ѵ�.
			t3=temptA;
		else
			t3=temptB;

		//t4������
		tempt=0,temptA=0,temptB=0,Alpha=0;
		tempt=atan((sin(t1)*ax-cos(t1)*ay)/(cos(t2+t3)*(cos(t1)*ax+sin(t1)*ay)+sin(t2+t3)*az));

		if(az<=0)				// �ǵ����̸� ���� �Ʒ��� ���� ����� (���ݻ��·δ� ������������ �����θ� ���´�)
			t4=tempt;			
		else
			t4=tempt+M_PI;

		//t5������
		tempt=0;

		temptA=-cos(t4)*(cos(t2+t3)*(cos(t1)*ax+sin(t1)*ay)+sin(t2+t3)*az)-sin(t4)*(sin(t1)*ax-cos(t1)*ay);
		temptB=sin(t2+t3)*(cos(t1)*ax+sin(t1)*ay)-cos(t2+t3)*az;

		t5=atan2(temptA,temptB);


		//t6��� 
		temptA=0,temptB=0;

		temptA=-sin(t4)*(cos(t2+t3)*(cos(t1)*nx+sin(t1)*ny)+sin(t2+t3)*nz)+cos(t4)*(sin(t1)*nx-cos(t1)*ny);
		temptB=-sin(t4)*(cos(t2+t3)*(cos(t1)*ox+sin(t1)*oy)+sin(t2+t3)*oz)+cos(t4)*(sin(t1)*ox-cos(t1)*oy);

		t6=atan2(temptA,temptB);

		fmod(t5, 2.*M_PI);//�ո��� 180�� �̻� �̳� -180���Ϸ� ������ �ʰ��Ѵ�. 


		//���� 6��κ� �ⱸ�а� ������� Ʋ����  ���� ��  1) 2��°���� ���� �ݴ� 2) 3��° �����ɼ� 180��(-)�̰� ������ �ݴ� 3) 6��° ���� 180�� �ɼ�(+)
		double tt1, tt2, tt3, tt4, tt5, tt6;

		tt1 = t1;
		tt2 = t2*-1;
		tt3 = -1*(t3-M_PI);
		tt4 = t4;
		tt5 = t5;
		tt6 = t6+M_PI;

		jointPosition[0] = ASV_DEG(RAD2DEG(fmod(tt1, 2.*M_PI)));
		jointPosition[1] = ASV_DEG(RAD2DEG(fmod(tt2, 2.*M_PI)));
		jointPosition[2] = ASV_DEG(RAD2DEG(fmod(tt3, 2.*M_PI)));
		jointPosition[3] = ASV_DEG(RAD2DEG(fmod(tt4, 2.*M_PI)));
		jointPosition[4] = ASV_DEG(RAD2DEG(fmod(tt5, 2.*M_PI)));
		jointPosition[5] = ASV_DEG(RAD2DEG(fmod(tt6, 2.*M_PI)));
// 		PrintMessage("%.3f %.3f %.3f %.3f %.3f %.3f\n",jointPosition[0],jointPosition[1],jointPosition[2]
// 										,jointPosition[3],jointPosition[4],jointPosition[5]	);

 	return jointPosition;
}
double CNR_6DOFAnalyticInverseKinematicsComp::ASV_DEG(double val)
{
	if(val > 0)
	{	if( fabs(val) > fabs(val-360.) )
	val = val - 360.;		}
	else
	{	if( fabs(val) > fabs(val+360.) )
	val = val - 360.;	}

	return val;
}

bool CNR_6DOFAnalyticInverseKinematicsComp::SetDesiredPosition(ObjectPosition desiredPosition)
{
	m_Position = desiredPosition;
	return true;
}

ObjectPosition CNR_6DOFAnalyticInverseKinematicsComp::GetCurrentPosition()
{
	ObjectPosition ret;
	if(m_Joint.size() != 6)
	{
		return ret;
	}

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

	lnk[0].theta = DEG2RAD(m_Joint[0]); // + lnk[0].joint_offset;
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

		lnk[i].theta = DEG2RAD(m_Joint[i]);//+ lnk[i].joint_offset;
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


	//���������̼ǿ��� ���Ϸ�ZYX(Zȸ��->Yȸ��->Xȸ��) ȸ���� ������ �̾Ƴ�
	if (Rot(2,0)==1) {
		ret.roll = RAD2DEG(atan2(-Rot(0,1),-Rot(0,2)));	//alpha(xȸ��Roll����)
		ret.pitch = -90.;	//-PI/2;						//betta(yȸ��Pitch����)
		ret.yaw = 0.0;						//gamma(Zȸ��Yaw����)
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
	return new CNR_6DOFAnalyticInverseKinematicsComp();
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
	return new CNR_6DOFAnalyticInverseKinematicsComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

