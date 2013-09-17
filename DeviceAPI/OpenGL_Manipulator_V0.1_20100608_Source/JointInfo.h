#pragma once

#include "Kinematics.h"
#include <vector>

using namespace std;


class JointEx : public JointBasis {
public:
	// 프로그램 실행 중 사용되는 변수들
	dVector a;		// 회전 축의 각속도
	dVector p;		// 전역 좌표계에서 회전 축의 위치

	JointEx () : a(3), p(3) { }
};

class JointInfo
{
public:
	JointInfo(void);
	virtual ~JointInfo(void);

	dVector GetDesired () { return _desired; }	// 목적지의 위치를 반환한다.
	vector<JointEx *> &GetJointList () { return _jointList; }	// 조인트 정보를 담고있는 목록을 얻어온다. (그리기 위해 사용)

// 조인트 목록 끝에 하나의 조인트를 더한다.
	void AttachJoint (int type, int axis, double x, double y, double z, double phi, double theta, double psi, double radius);

private:
	dVector Error ();
	dMatrix Jacobian ();

	vector<JointEx *> _jointList;
	dVector _desired;
	dVector _current;
};
