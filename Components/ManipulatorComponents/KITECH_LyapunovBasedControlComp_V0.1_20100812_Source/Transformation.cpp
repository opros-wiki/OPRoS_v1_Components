//////////////////////////////////////////////////////
// Vector and Matrix files for Robotics applications
// 
// Copyright (c) 2002-2010. All Rights Reserved.
// Division of Applied Robot Technology, KITECH
// Web: http://www.orobot.net
// Written by KwangWoong Yang<page365@gmail.com>
//

#include "Transformation.h"

CTransformMatrix::CTransformMatrix () 
: dMatrix (4, 4)
{
	unit ();
}

CTransformMatrix::CTransformMatrix (double x, double y, double z, double phi, double theta, double psi)
: dMatrix (4, 4)
{
	dMatrix &A = *this;

	double sphi = sin(phi),		cphi = cos(phi);
	double stheta = sin(theta),	ctheta = cos(theta);
	double spsi = sin(psi),		cpsi = cos(psi);

	// transformation matrix: Trans(x,y,z) x Rx(phi) x Ry(theta) x Rz(psi)
	// 좌표 변환 순서:
	// 1. x, y, z 만큼 위치를 이동한다.
	// 2. x축으로 phi 만큼 회전한다.
	// 3. y축으로 theta 만큼 회전한다.
	// 4. z축으로 psi 만큼 회전한다.
	A(0,0) =  ctheta*cpsi;					A(0,1) = -ctheta*spsi;					A(0,2) =  stheta;		A(0,3) = x;
	A(1,0) =  sphi*stheta*cpsi + cphi*spsi;	A(1,1) = -sphi*stheta*spsi + cphi*cpsi;	A(1,2) = -sphi*ctheta;	A(1,3) = y;
	A(2,0) = -cphi*stheta*cpsi + sphi*spsi;	A(2,1) =  cphi*stheta*spsi + sphi*cpsi;	A(2,2) =  cphi*ctheta;	A(2,3) = z;
	A(3,0) =  0;							A(3,1) =  0;							A(3,2) =  0;			A(3,3) = 1; 
}

dMatrix CTransformMatrix::GetRotation ()
{
	dMatrix &A = *this;
	dMatrix R(3,3);

	R(0,0) = A(0,0);	R(0,1) = A(0,1);	R(0,2) = A(0,2);
	R(1,0) = A(1,0);	R(1,1) = A(1,1);	R(1,2) = A(1,2);
	R(2,0) = A(2,0);	R(2,1) = A(2,1);	R(2,2) = A(2,2);

	return R;
}

dVector CTransformMatrix::GetRotation (int axis)
{
	assert (0<=axis && axis<3);

	dMatrix &A = *this;
	dVector v(3);

	v[0] = A(0,axis);
	v[1] = A(1,axis);
	v[2] = A(2,axis);

	return v;
}

dVector CTransformMatrix::GetPosition ()
{
	dMatrix &A = *this;
	dVector v(3);

	v[0] = A(0,3);
	v[1] = A(1,3);
	v[2] = A(2,3);

	return v;
}

dVector CTransformMatrix::GetOrientation ()
{
	dMatrix &A = *this;
	dVector v(3);

	// theta in the range (-pi/2, pi/2)
	v[0] = atan2(-A(1,2), A(2,2)); 
	v[1] = atan2( A(0,2), sqrt(A(1,2)*A(1,2) + A(2,2)*A(2,2)) ); 
	v[2] = atan2(-A(0,1), A(0,0)); 

	return v;
}

dVector CTransformMatrix::GetPositionOrientation () 
{
	dMatrix &A = *this;
	dVector v(6);

	v[0] = A(0,3);
	v[1] = A(1,3);
	v[2] = A(2,3);
	// theta in the range (-pi/2, pi/2)
	v[3] = atan2(-A(1,2), A(2,2)); 
	v[4] = atan2( A(0,2), sqrt(A(1,2)*A(1,2) + A(2,2)*A(2,2)) ); 
	v[5] = atan2(-A(0,1), A(0,0)); 

	return v;
}

