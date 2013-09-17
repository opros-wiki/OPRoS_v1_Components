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


#define	FIXED_JOINT		0	// 고정된 조인트: 좌표를 이동하기위해 사용한다.
#define	REVOLUTE_JOINT	1	// 회전 운동 조인트
#define	PRISMATIC_JOINT	2	// 직선 운동 조인트

struct JointInfo {
	// 조인트의 초기 설정치들
	int type;			// 종류
	int axis;					// 회전(직선) 운동 중심 축 지정 (0 - x축, 1 - y축, 2 - z축)

	double mass;				// joint의 질량
	dVector c;					// joint의 질량중심 위치
	dMatrix I;					// joint의 관성 행렬

	double x, y, z;				// 이전 조인트 위치로부터 현재 조인트의 상대 위치
	double phi, theta, psi;		// 이전 조인트 자세로부터 현재 조인트의 상대 자세
	double radius;				// 링크의 굵기, OpenGL에서 그리기 위해서 사용함

	// 프로그램 실행 중 사용되는 변수들
	double q;					// 조인트의 현재 회전(직선) 위치
	double dq, ddq;

	dMatrix R;	// 전역 좌표계에서 joint의 회전 matrix
	dVector a;	// 전역 좌표계에서의 z-axis의 방향 단위 벡터 
	dVector p;	// 전역 좌표계에서의 joint 위치
	dVector g;	// 전역 좌표계에서 joint의 질량중심 위치

	vector<dMatrix> dR;	// R의 q(k)에 대한 편미분 값
	vector<dVector> dz;	// z의 q(k)에 대한 편미분 값
	vector<dVector> dp;	// p의 q(k)에 대한 편미분 값
	vector<dVector> dg;	// c의 q(k)에 대한 편미분 값

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
	vector<JointInfo *> &GetJointList () { return _jointList; }	// 조인트 정보를 담고있는 목록을 얻어온다. (그리기 위해 사용)

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
