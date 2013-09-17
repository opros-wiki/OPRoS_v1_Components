//////////////////////////////////////////////////////
// Kinematics files for Robotics applications
// 
// Copyright (c) 2002-2010. All Rights Reserved.
// Division of Applied Robot Technology, KITECH
// Web: http://www.orobot.net
// Written by KwangWoong Yang<page365@gmail.com>
//

#include "DampedLeastSquare.h"
#include "TransformMatrix.h"
#include "OprosMath.h"
#include "Quaternion.h"


double GetDeltaOri (const dVector &d, const dVector &s)
{
	double d3 = DeltaRad (d[3], s[3]);
	double d4 = DeltaRad (d[4], s[4]);
	double d5 = DeltaRad (d[5], s[5]);

	return sqrt(d3*d3 + d4*d4 + d5*d5);
}

dVector GetNearestPosOri (const CTransformMatrix &A, const dVector &d)
{
	// theta(pitch)의 선택에 따라 현재 angle이 두 개의 solution이 나올 수 있는데,
	// 그 중 목적 angle에 가까운 값을 찾는다.
	//  - theta in the range (-pi/2, pi/2)
	//  - theta in the range (pi/2, 3pi/2)

	dVector c0 = A.GetPositionOrientation ();
	dVector c1 = A.GetPositionOrientation2 ();
	dVector &c = (GetDeltaOri(d, c0) < GetDeltaOri(d, c1)) ? c0 : c1;

	for (int i=3; i<6; ++i) {
		if ( M_PI/2. < d[i] && c[i] < -M_PI/2.) c[i] += 2*M_PI;
		if (-M_PI/2. > d[i] && c[i] >  M_PI/2.) c[i] -= 2*M_PI;
	}
	return c;
}


DampedLeastSquare::DampedLeastSquare (int inverseAxis)
: CKinematics(6), _inverseAxis(inverseAxis)
{ 
}

DampedLeastSquare::~DampedLeastSquare ()
{
}

dMatrix DampedLeastSquare::Forward ()
{
	CTransformMatrix T;

	for (unsigned int i=0; i<_jointList.size (); ++i) {
		JointInfo *joint = _jointList[i];

		dMatrix A = joint->TransformationMatrix ();

		joint->a = T.GetRotation (joint->axis);		// 회전 축의 회전 성분 (각속도)
		joint->p = T.GetPosition ();				// 전역 좌표계에서의 축의 위치

		T *= A;
	}
	//_current = T.GetPosition ();
	_current = GetNearestPosOri (T, _desired);

	return T;
}

dMatrix DampedLeastSquare::Jacobian()
{
	//Position Jacobian 
	dMatrix J(6, _jointList.size());
	J.zero ();

	dVector currentPos (3);
	currentPos[0] = _current[0];
	currentPos[1] = _current[1]; 
	currentPos[2] = _current[2]; 

	for (unsigned int i=0; i<_jointList.size (); ++i) {
		JointInfo *joint = _jointList[i];

		if (joint->type == REVOLUTE_JOINT) {
			if (_inverseAxis & POSITION_ONLY) {
				//Position Jacobian 
				dVector pos = Cross (joint->a, currentPos - joint->p);
				J(0,i) = pos[0];
				J(1,i) = pos[1];
				J(2,i) = pos[2];
			}
			if (_inverseAxis & ORIENTATION_ONLY) {
				//Orientation Jacobian 
				J(3,i) = joint->a[0];
				J(4,i) = joint->a[1];
				J(5,i) = joint->a[2];
			}
		}
		else if (joint->type == PRISMATIC_JOINT) {
			if (_inverseAxis & POSITION_ONLY) {
				//Position Jacobian 
				J(0,i) = joint->a[0];
				J(1,i) = joint->a[1];
				J(2,i) = joint->a[2];
			}
			if (_inverseAxis & ORIENTATION_ONLY) {
				//Orientation Jacobian 
				J(3,i) = 0.;
				J(4,i) = 0.;
				J(5,i) = 0.; 
			}
		}
	}
	return J;
}

dVector DampedLeastSquare::Error ()
{
	dVector error(6);
	error.zero ();
	
	if (_inverseAxis & POSITION_ONLY) {
		error[0] = _desired[0] - _current[0];
		error[1] = _desired[1] - _current[1];
		error[2] = _desired[2] - _current[2];
	}

	if (_inverseAxis & ORIENTATION_ONLY) {
		Quaternion qc (_current[3], _current[4], _current[5]);
		Quaternion qd (_desired[3], _desired[4], _desired[5]);

		Quaternion qe = qd*qc.conjugate ();
		error[3] = qe.v()[0];
		error[4] = qe.v()[1];
		error[5] = qe.v()[2];
	}

	return error;
}

void DampedLeastSquare::SetDesired (double x, double y, double z, double phi, double theta, double psi)
{
	_desired[0] = x;		
	_desired[1] = y;		
	_desired[2] = z; 
	_desired[3] = DeltaRad (phi, 0);
	_desired[4] = DeltaRad (theta, 0);
	_desired[5] = DeltaRad (psi, 0);
}
