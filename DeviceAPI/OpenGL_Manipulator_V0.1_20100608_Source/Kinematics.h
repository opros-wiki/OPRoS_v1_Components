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


#define	FIXED_JOINT		0	// 고정된 조인트: 좌표를 이동하기위해 사용한다.
#define	REVOLUTE_JOINT	1	// 회전 운동 조인트
#define	PRISMATIC_JOINT	2	// 직선 운동 조인트


struct JointBasis {
	// 조인트의 초기 설정치들
	int type;			// 종류
	int axis;					// 회전(직선) 운동 중심 축 지정 (0 - x축, 1 - y축, 2 - z축)

	double x, y, z;				// 이전 조인트 위치로부터 현재 조인트의 상대 위치
	double phi, theta, psi;		// 이전 조인트 자세로부터 현재 조인트의 상대 자세
	double radius;				// 링크의 굵기, OpenGL에서 그리기 위해서 사용함

	// 프로그램 실행 중 사용되는 변수들
	double q;					// 조인트의 현재 회전(직선) 위치

	JointBasis () : q(0.) { }

	CTransformMatrix TransformationMatrixQ ();
	CTransformMatrix TransformationMatrix ();
};

