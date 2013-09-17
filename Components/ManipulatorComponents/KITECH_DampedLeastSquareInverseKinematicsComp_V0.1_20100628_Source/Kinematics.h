//////////////////////////////////////////////////////
// Kinematics files for Robotics applications
// 
// Copyright (c) 2002-2010. All Rights Reserved.
// Division of Applied Robot Technology, KITECH
// Web: http://www.orobot.net
// Written by KwangWoong Yang<page365@gmail.com>
//

#pragma once
#include "TransformMatrix.h"
#include "OprosMath.h"
#include <vector>

using namespace std;

#define	FIXED_JOINT			0	// ������ ����Ʈ: ��ǥ�� �̵��ϱ����� ����Ѵ�.
#define	REVOLUTE_JOINT		1	// ȸ�� � ����Ʈ
#define	PRISMATIC_JOINT		2	// ���� � ����Ʈ

struct JointInfo {
	// ����Ʈ�� �ʱ� ����ġ��
	int type;					// ����
	int axis;					// ȸ��(����) � �߽� �� ���� (0 - x��, 1 - y��, 2 - z��)

	double x, y, z;				// ���� ����Ʈ ��ġ�κ��� ���� ����Ʈ�� ��� ��ġ
	double phi, theta, psi;		// ���� ����Ʈ �ڼ��κ��� ���� ����Ʈ�� ��� �ڼ�
	double radius;				// ��ũ�� ����, OpenGL���� �׸��� ���ؼ� �����

	// ���α׷� ���� �� ���Ǵ� ������
	double q;					// ����Ʈ�� ���� ȸ��(����) ��ġ
	double limit_lo, limit_hi;	// ����Ʈ�� ���� ���� (limit_lo ~ limit_hi)
	double median;				// ����Ʈ�� �߰� �� (Null motion�� �Ҵ��ϱ� ���� ����)
	double weight;				// ����Ʈ�� ����ġ
	dVector a;					// ȸ�� ���� ���ӵ�
	dVector p;					// ���� ��ǥ�迡�� ȸ�� ���� ��ġ

	JointInfo () : q(0.), limit_lo(-M_PI), limit_hi(M_PI), median(0.), weight(0.), a(3), p(3) { }

	CTransformMatrix TransformationMatrixQ ();
	CTransformMatrix TransformationMatrix ();
};


class CKinematics
{
public:
	CKinematics(int taskSize);
	~CKinematics(void);

	virtual dMatrix Forward () = 0;
	virtual dVector Error () = 0;
	virtual dMatrix Jacobian () = 0;

	dVector GetDesired () { return _desired; }	// �������� ��ġ�� ��ȯ�Ѵ�.
	dVector GetCurrent () { return _current; }	// ���� ��ġ�� ��ȯ�Ѵ�.

	// ����Ʈ ��� ���� �ϳ��� ����Ʈ�� ���Ѵ�.
	void AttachJoint (int type, int axis, double x, double y, double z, double phi, double theta, double psi, 
		double radius, double limit_lo = -M_PI, double limit_hi = M_PI, double median = 0., double weight = 1.);

	dVector SolveJTR (double minAlpha, double clampTask);					// Jacobian Transpose ������� Inverse kinematics�� Ǭ��.
	dVector SolveDLS (double dlsLambda, double clampTask, double clampNull);	// Damped least square ������� Inverse kinematics�� Ǭ��.

	dVector GetJointAngle ();					// ���� ����Ʈ ����(q) ������ ��ȯ�Ѵ�.
	bool SetJointAngle(vector<double> jointAngle);
	void Apply (dVector &dq);					// �� ����Ʈ�� ȸ����(dq)�� ���� ����Ʈ ����(q)�� ���Ѵ�.

	vector<JointInfo *> &GetJointList () { return _jointList; }	// ����Ʈ ������ ����ִ� ����� ���´�. (�׸��� ���� ���)

protected:
	vector<JointInfo *> _jointList;

	dVector _desired;
	dVector _current;

	void ClampMag(dVector &w, double maxMag);

	double WeightFunction (double lo, double hi, double q);
	dMatrix WeightMatrix (unsigned int dof);
	dVector NullSpaceVector ();
};
