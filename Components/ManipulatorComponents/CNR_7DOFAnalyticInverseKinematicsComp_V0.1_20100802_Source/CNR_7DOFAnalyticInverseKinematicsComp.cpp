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

#include "CNR_7DOFAnalyticInverseKinematicsComp.h"
#include "OprosPrintMessage.h"
#include "matrix.h"
#include "vector.h"
//
// constructor declaration
//
CNR_7DOFAnalyticInverseKinematicsComp::CNR_7DOFAnalyticInverseKinematicsComp()
{
	error = 0;
	
	portSetup();
}

//
// constructor declaration (with name)
//
CNR_7DOFAnalyticInverseKinematicsComp::CNR_7DOFAnalyticInverseKinematicsComp(const std::string &name):Component(name)
{
	error = 0;
	
	portSetup();
}

//
// destructor declaration
//

CNR_7DOFAnalyticInverseKinematicsComp::~CNR_7DOFAnalyticInverseKinematicsComp() 
{
	onDestroy();
}

void CNR_7DOFAnalyticInverseKinematicsComp::portSetup() {

	// provided service port setup
	
	ProvidedServicePort *pa1;
	pa1=new InverseKinematicsServiceProvided(this);

	addPort("InverseKinematicsService",pa1);

}

// Call back Declaration
ReturnType CNR_7DOFAnalyticInverseKinematicsComp::onInitialize()
{
	Property parameter;
	std::map<std::string, std::string> temp = getPropertyMap();
	parameter.SetProperty(temp);

	if(SetParameter(parameter) == false) {
		return OPROS_CALLER_ERROR;
	}

	return OPROS_SUCCESS;
}

ReturnType CNR_7DOFAnalyticInverseKinematicsComp::onStart()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType CNR_7DOFAnalyticInverseKinematicsComp::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CNR_7DOFAnalyticInverseKinematicsComp::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CNR_7DOFAnalyticInverseKinematicsComp::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CNR_7DOFAnalyticInverseKinematicsComp::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CNR_7DOFAnalyticInverseKinematicsComp::onDestroy()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CNR_7DOFAnalyticInverseKinematicsComp::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CNR_7DOFAnalyticInverseKinematicsComp::onExecute()
{
	// user code here
	return OPROS_SUCCESS;
}
	
ReturnType CNR_7DOFAnalyticInverseKinematicsComp::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType CNR_7DOFAnalyticInverseKinematicsComp::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool CNR_7DOFAnalyticInverseKinematicsComp::SetParameter(Property parameter)
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
	if(parameter.FindName("RedundantValue") == false) {
		PrintMessage("ERROR : CNR_6DOFRobotForwardKinematicsComp::SetParameter() -> Can't find the RedundantValue in property\n");
		return false;
	}

	PrintMessage("UpperArmLength : %.3f\nLowerArmLength : %.3f\nToolLength : %.3f\nRedundantValue : %.3f\n"
		,atof(parameter.GetValue("UpperArmLength").c_str())
		,atof(parameter.GetValue("LowerArmLength").c_str())
		,atof(parameter.GetValue("ToolLength").c_str())  
		,atof(parameter.GetValue("RedundantValue").c_str()));

	this->parameter = parameter;


	return true;
}

Property CNR_7DOFAnalyticInverseKinematicsComp::GetParameter()
{
	return parameter;
}

int CNR_7DOFAnalyticInverseKinematicsComp::GetError()
{
	return error;
}

bool CNR_7DOFAnalyticInverseKinematicsComp::SetJointPosition(vector<double> jointPosition)
{
	m_joint = jointPosition;
	return true;
}

vector<double> CNR_7DOFAnalyticInverseKinematicsComp::GetJointPosition()
{
	vector<double> jointPosition(7);


		// user code here
		MSLVector EE(m_Position.x, m_Position.y, m_Position.z); //앤드이펙터 포지션

		double cr, cp , cy;
		double sr, sp , sy;

		cr = cos(DEG2RAD(m_Position.roll));		sr = sin(DEG2RAD(m_Position.roll));	//roll값 적용
		cp = cos(DEG2RAD(m_Position.pitch));		sp = sin(DEG2RAD(m_Position.pitch));	//pitch값적용
		if(m_Position.yaw == 0){//yaw값이 0이면 해가 안구해져서 이렇게 처리
			cy = cos(1e-011);		sy = sin(1e-011);	//yaw값 적용
		}	else	{
			cy = cos(DEG2RAD(m_Position.yaw));		sy = sin(DEG2RAD(m_Position.yaw));	//yaw값 적용
		}


		double uplen = atof(parameter.GetValue("UpperArmLength").c_str());		//상완길이 파라미터로부터 설정해야함	
		double lowlen = atof(parameter.GetValue("LowerArmLength").c_str());		//하완길이 파라미터로부터 설정해야함
		double handlen = atof(parameter.GetValue("ToolLength").c_str());		//손목길이 파라미터로부터 설정해야함	

		double ax_o,ay_o,az_o,ox_o,oy_o,oz_o,nx_o,ny_o,nz_o;//원래의 프레임 방향인자

		nx_o = cy*cp;		ox_o = cy*sp*sr-sy*cr;	ax_o = cy*sp*cr+sy*sr;	
		ny_o = sy*cp;		oy_o = sy*sp*sr+cy*cr;	ay_o = sy*sp*cr-cy*sr;	
		nz_o = -sp;			oz_o = cp*sr;			az_o = cp*cr;	

		double px_o, py_o,pz_o;	//	원래의 손목위치;

		px_o = EE[0] - handlen * ax_o; //손의 길이만큼 목표위치를 빼서 손목의 위치를 계산
		py_o = EE[1] - handlen * ay_o;
		pz_o = EE[2] - handlen * az_o;


		MSLVector W(3);

		W[0] =  py_o;	//손목의 위치를 알고리즘에게 맞게 변환해서 입력
		W[1] = -pz_o;
		W[2] = -px_o;

		if(W[0] == 0 && W[1] == 0)
			W[0] += 1e-011;//x,y가 둘다 0이면 해가 안구해져서 이렇게 처리



		double  nx,ny,nz,ox,oy,oz,ax,ay,az;

		//회전축 n,o,a를 알고리즘 방향기준에 맞게 변환
		nx = ny_o;
		ox = oy_o;
		ax = ay_o;

		ny = -nz_o;
		oy = -oz_o;
		ay = -az_o;

		nz = -nx_o; 
		oz = -ox_o; 
		az = -ax_o;

		double wlen = W.length();	//손목까지의 거리

		MSLVector P(0.0, 0.0, 100.0);  //첫번째 관절벡터
		double len1 = uplen;				//상완길이
		double len2 = lowlen;				//하완길이
		MSLVector SCP, C;
		SCP = (P*W)/(W*W)*W;		//scp는 shoulder 점에서 p벡터의 w벡터에 대한 수선벡터의 베이스까지향하는 벡터이다. (scp+ (p벡터의 w벡터에 대한 수선벡터) = p벡터) 
		C = P - SCP;

		double v,omega,dtemp;
		double rx, ry, rz, so,co;
		omega = DEG2RAD(atof(parameter.GetValue("RedundantValue").c_str()));		//여자유도 변수 적용
		v = 1-cos(omega);
		dtemp = sqrt(W[0]*W[0] + W[1]*W[1] +W[2]*W[2]);
		rx = W[0]/dtemp; 
		ry = W[1]/dtemp; 
		rz = W[2]/dtemp;

		so = sin(omega);
		co = cos(omega);

		MSLMatrix R(3,3);
		R[0][0] = rx * rx * v + co;
		R[0][1] = rx * ry * v - rz * so; 
		R[0][2] = rx *rz*v + ry * so;

		R[1][0] = rx * ry * v + rz * so;   
		R[1][1] = ry * ry * v + co;
		R[1][2] = ry * rz * v - rx * so;

		R[2][0] = rx * rz * v - ry * so;
		R[2][1] = ry * rz * v + rx * so;
		R[2][2] = rz * rz * v + co;

		C = R * C;		//c벡터를 손목 회전벡터로 오메가각도만큼 회전
		C = C.norm() ;	//c를 노말라이징

		double he;
		he = 0.5 * (wlen + uplen + lowlen);
		he = sqrt(he*(he - wlen)*(he - lowlen)*(he - uplen));
		double clen = 2.0 * he / wlen;
		C = clen * C;		//W벡터 중간정도에서 엘보까지 가는 벡터 완성
		MSLVector SE;	//어깨에서 엘보까지 벡터
		SE = (W/wlen)*sqrt(uplen*uplen - clen*clen) + C;
		MSLVector EW; //엘보에서 손목까지 벡터
		EW = W - SE;

		double th1, th2, th3, th4, th5, th6, th7;
		double c1,s1,c2,s2,c3,s3,c4,s4,c5,s5,c6,s6;
		th2 = acos(SE[1]/uplen);
		c2 = cos(th2);
		s2 = sin(th2);

		double ss,cc;
		ss = -SE[2]/(uplen*sin(th2));
		cc = -SE[0]/(uplen*sin(th2));

		th1 = atan2(ss,cc);
		c1 = cos(th1);
		s1 = sin(th1);

		th4 = acos( (SE*EW)/((SE.length())*(EW.length())) );

		c4 = cos(th4);
		s4 = sin(th4);

		double AA,BB,CC;
		AA = -EW[0]/lowlen - c1*s2*c4;
		BB = -EW[2]/lowlen - s1*s2*c4;
		ss = (c1*BB - s1*AA)/s4;
		cc = (-EW[1]/lowlen + c2*c4)/(-s2*s4);
		th3 = atan2(ss,cc);
		c3 = cos(th3);
		s3 = sin(th3);

		MSLVector RHZ(ax, ay, az);
		th6 = acos( (EW*RHZ)/lowlen);
		c6 = cos(th6);
		s6 = sin(th6);

		AA = -ax -(-(c1*c2*c3+s1*s3)*s4+c1*s2*c4)*c6;
		BB = -ay -(-s2*c3*s4-c2*c4)*c6;
		CC =  (-c1*c2*s3+s1*c3)*(s2*c3*c4-c2*s4) - (-s2*s3)*((c1*c2*c3+s1*s3)*c4+c1*s2*s4);

		cc = ( (-s2*s3) *(AA) - (-c1*c2*s3+s1*c3) *(BB) )/((CC)*s6 );
		ss = -( (s2*c3*c4-c2*s4) *(AA)-  ((c1*c2*c3+s1*s3)*c4+c1*s2*s4) *(BB)) /((CC)*s6);


		th5 = atan2(ss,cc);
		c5 = cos(th5);
		s5 = sin(th5);

		AA = -((c1*c2*c3+s1*s3)*c4+c1*s2*s4)*s5+(-c1*c2*s3+s1*c3)*c5;
		BB = -((s1*c2*c3-c1*s3)*c4+s1*s2*s4)*s5+(-s1*c2*s3-c1*c3)*c5;

		ss = (oz*AA - ox*BB)/(oz*nx - ox*nz );
		cc = (nx*BB - nz*AA)/(oz*nx - ox*nz );

		th7 = atan2(ss,cc);

		jointPosition[0] = ASV_DEG(RAD2DEG(fmod(th1+M_PI_2, 2.*M_PI)));
 		jointPosition[1] = ASV_DEG(RAD2DEG(fmod(th2, 2.*M_PI)));
		jointPosition[2] = ASV_DEG(RAD2DEG(fmod(th3, 2.*M_PI)));
		jointPosition[3] = ASV_DEG(RAD2DEG(fmod(th4, 2.*M_PI)));
		jointPosition[4] = ASV_DEG(RAD2DEG(fmod(th5, 2.*M_PI)));
		jointPosition[5] = ASV_DEG(RAD2DEG(fmod(th6, 2.*M_PI)));
		jointPosition[6] = ASV_DEG(RAD2DEG(fmod(th7, 2.*M_PI)));
	
	return jointPosition;
}
double CNR_7DOFAnalyticInverseKinematicsComp::ASV_DEG(double val)
{
	if(val > 0)
	{	if( fabs(val) > fabs(val-360.) )
	val = val - 360.;		}
	else
	{	if( fabs(val) > fabs(val+360.) )
	val = val - 360.;	}
	
	return val;
}


bool CNR_7DOFAnalyticInverseKinematicsComp::SetDesiredPosition(ObjectPosition desiredPosition)
{
	m_Position = desiredPosition;
	return true;
}

ObjectPosition CNR_7DOFAnalyticInverseKinematicsComp::GetCurrentPosition()
{
	ObjectPosition objectPosition;

	if(m_joint.size() != 7)
	{
		return objectPosition;
	}

	struct link
	{
		double theta, a, d, alpha;
	};

	link lnk[7];
	//1
	lnk[0].d = 0;
	lnk[0].a = 0;
	lnk[0].alpha = -M_PI_2;
	//2
	lnk[1].d = 0;
	lnk[1].a = 0;
	lnk[1].alpha = -M_PI_2;
	//3
	lnk[2].d = atof(parameter.GetValue("UpperArmLength").c_str());	//상완길이
	lnk[2].a = 0;
	lnk[2].alpha = -M_PI_2;
	//4
	lnk[3].d = 0;
	lnk[3].a = 0;
	lnk[3].alpha = M_PI_2;
	//5
	lnk[4].d = atof(parameter.GetValue("LowerArmLength").c_str());	//하완길이
	lnk[4].a = 0;
	lnk[4].alpha = -M_PI_2;
	//6
	lnk[5].d = 0;
	lnk[5].a = 0;
	lnk[5].alpha = M_PI_2;
	//7
	lnk[6].d = atof(parameter.GetValue("ToolLength").c_str());		//그리퍼(손)길이
	lnk[6].a = 0;
	lnk[6].alpha = 0;


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


	for(i = 1 ; i < 7 ; i++)
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


	objectPosition.x = Pos[0];
	objectPosition.y = Pos[1];
	objectPosition.z = Pos[2];


	//오리엔테이션에서 오일러ZYX(Z회전->Y회전->X회전) 회전의 각도를 뽑아냄
	if (Rot(2,0)==1) {
		objectPosition.roll = RAD2DEG(atan2(-Rot(0,1),-Rot(0,2)));	//alpha(x회전Roll각도)
		objectPosition.pitch = -90.;	//-PI/2;						//betta(y회전Pitch각도)
		objectPosition.yaw = 0.0;						//gamma(Z회전Yaw각도)
	} else if (Rot(2,0)==-1) {
		objectPosition.roll  = RAD2DEG(atan2(Rot(0,1),Rot(0,2)));
		objectPosition.pitch = 90.;	//PI/2;
		objectPosition.yaw = 0.0;
	} else {
		objectPosition.roll = RAD2DEG(atan2(Rot(2,1), Rot(2,2)));
		objectPosition.pitch = RAD2DEG(atan2(-Rot(2,0), sqrt(Rot(0,0)*Rot(0,0) + Rot(1,0)*Rot(1,0))));
		objectPosition.yaw = RAD2DEG(atan2(Rot(1,0), Rot(0,0)));
	}

	return objectPosition;
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
	return new CNR_7DOFAnalyticInverseKinematicsComp();
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
	return new CNR_7DOFAnalyticInverseKinematicsComp();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
#endif

