//////////////////////////////////////////////////////
// Kinematics files for Robotics applications
// 
// Copyright (c) 2002-2010. All Rights Reserved.
// Division of Applied Robot Technology, KITECH
// Web: http://www.orobot.net
// Written by KwangWoong Yang<page365@gmail.com>
//

#pragma once
#include "Transformation.h"
#include <vector>

using namespace std;


#define	FIXED_JOINT		0	// ������ ����Ʈ: ��ǥ�� �̵��ϱ����� ����Ѵ�.
#define	REVOLUTE_JOINT	1	// ȸ�� � ����Ʈ
#define	PRISMATIC_JOINT	2	// ���� � ����Ʈ

struct JointInfo {
	// ����Ʈ�� �ʱ� ����ġ��
	int type;			// ����
	int axis;					// ȸ��(����) � �߽� �� ���� (0 - x��, 1 - y��, 2 - z��)

	double mass;				// joint�� ����
	dVector c;					// joint�� �����߽� ��ġ
	dMatrix I;					// joint�� ���� ���

	double x, y, z;				// ���� ����Ʈ ��ġ�κ��� ���� ����Ʈ�� ��� ��ġ
	double phi, theta, psi;		// ���� ����Ʈ �ڼ��κ��� ���� ����Ʈ�� ��� �ڼ�
	double radius;				// ��ũ�� ����, OpenGL���� �׸��� ���ؼ� �����

	// ���α׷� ���� �� ���Ǵ� ������
	double q;					// ����Ʈ�� ���� ȸ��(����) ��ġ
	double dq, ddq;

	dMatrix R;	// ���� ��ǥ�迡�� joint�� ȸ�� matrix
	dVector a;	// ���� ��ǥ�迡���� z-axis�� ���� ���� ���� 
	dVector p;	// ���� ��ǥ�迡���� joint ��ġ
	dVector g;	// ���� ��ǥ�迡�� joint�� �����߽� ��ġ

	vector<dMatrix> dR;	// R�� q(k)�� ���� ��̺� ��
	vector<dVector> dz;	// z�� q(k)�� ���� ��̺� ��
	vector<dVector> dp;	// p�� q(k)�� ���� ��̺� ��
	vector<dVector> dg;	// c�� q(k)�� ���� ��̺� ��

	JointInfo () : q(0.), dq(0.), ddq(0.), R(3,3), a(3), p(3), g(3) { }

	CTransformMatrix TransformationMatrixQ ();
	CTransformMatrix TransformationMatrixDiffQ ();
	CTransformMatrix TransformationMatrix ();
};


class CDynamics
{
public:
	CDynamics(double gravity[3], double fsi = .0, double fvi = .0);
	~CDynamics();

	void AttachJoint (int type, int axis, double mass, double cx, double cy, double cz, 
					   double Ixx, double Iyy, double Izz, double Ixy, double Iyz, double Izx,
					   double x, double y, double z, double phi, double theta, double psi, double radius);

	int GetJointNo () { return _jointList.size(); }
	vector<JointInfo *> &GetJointList () { return _jointList; }	// ����Ʈ ������ ����ִ� ����� ���´�. (�׸��� ���� ���)

	dVector GetJointAngle ();

public:
	double _fsi;	// Fsi - coulomb friction coefficient
	double _fvi;	// Fvi - viscous friction coefficient
	dVector _gravity;

protected:
	vector<JointInfo *> _jointList;
	dVector _q;
	dVector _qd;

	dVector _qdot;
	dVector _qdotd;

	dVector _q2dot;
	dVector _q2dotd;
};
