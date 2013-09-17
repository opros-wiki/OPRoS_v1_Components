//
// Vector and Matrix files for Robotics applications
// 
// Copyright (c) 2002-2010. All Rights Reserved.
// Division of Applied Robot Technology, KITECH
// Web: http://www.orobot.net
// Written by KwangWoong Yang<page365@gmail.com>
//

#pragma once
#include "MatrixAlgebra.h"

class CTransformMatrix : public dMatrix 
{
public:
	CTransformMatrix ();
	CTransformMatrix (const matrix<double> &m): dMatrix (m) { }
	CTransformMatrix (double x, double y, double z, double phi, double theta, double psi);

	dMatrix GetRotation (); 
	dVector GetRotation (int axis);		// 변환 행렬에서 축에 대한 회전 성분 벡터를 반환한다.
	dVector GetPosition ();				// 변환 행렬의 위치(x, y, z) 벡터를 반환한다.
	dVector GetOrientation ();			// 변환 행렬의 방향(phi, theta, psi) 벡터를 반환한다. (theta: -pi/2 ~ pi/2)
	dVector GetPositionOrientation ();	// 변환 행렬의 위치와 방향 벡터를 반환한다. (theta: -pi/2 ~ pi/2)
};

class CTransformMatrixDiffX : public CTransformMatrix 
{
public:
	CTransformMatrixDiffX (double x, double y, double z, double phi, double theta, double psi)
	{
		dMatrix &dA = *this;

		dA(0,0) =  0;		dA(0,1) =  0;		dA(0,2) =  0;		dA(0,3) =  1; 
		dA(1,0) =  0;		dA(1,1) =  0;		dA(1,2) =  0;		dA(1,3) =  0; 
		dA(2,0) =  0;		dA(2,1) =  0;		dA(2,2) =  0;		dA(2,3) =  0; 
		dA(3,0) =  0;		dA(3,1) =  0;		dA(3,2) =  0;		dA(3,3) =  0; 
	}
};

class CTransformMatrixDiffY : public CTransformMatrix 
{
public:
	CTransformMatrixDiffY (double x, double y, double z, double phi, double theta, double psi)
	{
		dMatrix &dA = *this;

		dA(0,0) =  0;		dA(0,1) =  0;		dA(0,2) =  0;		dA(0,3) =  0; 
		dA(1,0) =  0;		dA(1,1) =  0;		dA(1,2) =  0;		dA(1,3) =  1; 
		dA(2,0) =  0;		dA(2,1) =  0;		dA(2,2) =  0;		dA(2,3) =  0; 
		dA(3,0) =  0;		dA(3,1) =  0;		dA(3,2) =  0;		dA(3,3) =  0; 
	}
};

class CTransformMatrixDiffZ : public CTransformMatrix 
{
public:
	CTransformMatrixDiffZ (double x, double y, double z, double phi, double theta, double psi)
	{
		dMatrix &dA = *this;

		dA(0,0) =  0;		dA(0,1) =  0;		dA(0,2) =  0;		dA(0,3) =  0; 
		dA(1,0) =  0;		dA(1,1) =  0;		dA(1,2) =  0;		dA(1,3) =  0; 
		dA(2,0) =  0;		dA(2,1) =  0;		dA(2,2) =  0;		dA(2,3) =  1; 
		dA(3,0) =  0;		dA(3,1) =  0;		dA(3,2) =  0;		dA(3,3) =  0; 
	}
};

class CTransformMatrixDiffPhi : public CTransformMatrix 
{
public:
	CTransformMatrixDiffPhi (double x, double y, double z, double phi, double theta, double psi)
	{
		dMatrix &dA = *this;

		double sphi = sin(phi),		cphi = cos(phi);
		double stheta = sin(theta),	ctheta = cos(theta);
		double spsi = sin(psi),		cpsi = cos(psi);

		dA(0,0) =  0;								dA(0,1) =  0;								dA(0,2) =  0;				dA(0,3) =  0; 
		dA(1,0) =  cphi*stheta*cpsi - sphi*spsi;	dA(1,1) =  -cphi*stheta*spsi - sphi*cpsi;	dA(1,2) =  -cphi*ctheta;	dA(1,3) =  0; 
		dA(2,0) =  sphi*stheta*cpsi + cphi*spsi;	dA(2,1) =  -sphi*stheta*spsi + cphi*cpsi;	dA(2,2) =  -sphi*ctheta;	dA(2,3) =  0; 
		dA(3,0) =  0;								dA(3,1) =  0;								dA(3,2) =  0;				dA(3,3) =  0; 
	}
};

class CTransformMatrixDiffTheta : public CTransformMatrix 
{
public:
	CTransformMatrixDiffTheta (double x, double y, double z, double phi, double theta, double psi)
	{
		dMatrix &dA = *this;

		double sphi = sin(phi),		cphi = cos(phi);
		double stheta = sin(theta),	ctheta = cos(theta);
		double spsi = sin(psi),		cpsi = cos(psi);

		dA(0,0) = -stheta*cpsi;						dA(0,1) =  stheta*spsi;						dA(0,2) =   ctheta;			dA(0,3) = 0;
		dA(1,0) =  sphi*ctheta*cpsi;				dA(1,1) = -sphi*ctheta*spsi;				dA(1,2) =   sphi*stheta;	dA(1,3) = 0;
		dA(2,0) = -cphi*ctheta*cpsi;				dA(2,1) =  cphi*ctheta*spsi;				dA(2,2) =  -cphi*stheta;	dA(2,3) = 0;
		dA(3,0) =  0;								dA(3,1) =  0;								dA(3,2) =   0;				dA(3,3) = 0; 
	}
};

class CTransformMatrixDiffPsi : public CTransformMatrix 
{
public:
	CTransformMatrixDiffPsi (double x, double y, double z, double phi, double theta, double psi)
	{
		dMatrix &dA = *this;

		double sphi = sin(phi),		cphi = cos(phi);
		double stheta = sin(theta),	ctheta = cos(theta);
		double spsi = sin(psi),		cpsi = cos(psi);

		dA(0,0) = -ctheta*spsi;						dA(0,1) = -ctheta*cpsi;						dA(0,2) = 0;				dA(0,3) = 0;
		dA(1,0) = -sphi*stheta*spsi + cphi*cpsi;	dA(1,1) = -sphi*stheta*cpsi - cphi*spsi;	dA(1,2) = 0;				dA(1,3) = 0;
		dA(2,0) =  cphi*stheta*spsi + sphi*cpsi;	dA(2,1) =  cphi*stheta*cpsi - sphi*spsi;	dA(2,2) = 0;				dA(2,3) = 0;
		dA(3,0) =  0;								dA(3,1) =  0;								dA(3,2) = 0;				dA(3,3) = 0; 
	}
};
