//////////////////////////////////////////////////////
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

	dVector GetRotation (int axis) const;		// ��ȯ ��Ŀ��� �࿡ ���� ȸ�� ���� ���͸� ��ȯ�Ѵ�.
	dVector GetPosition () const;				// ��ȯ ����� ��ġ(x, y, z) ���͸� ��ȯ�Ѵ�.
	dVector GetOrientation () const;			// ��ȯ ����� ����(phi, theta, psi) ���͸� ��ȯ�Ѵ�. (theta: -pi/2 ~ pi/2)
	dVector GetOrientation2 () const;			// ��ȯ ����� ����(phi, theta, psi) ���͸� ��ȯ�Ѵ�. (theta:  pi/2 ~ 3*pi/2)
	dVector GetPositionOrientation () const;	// ��ȯ ����� ��ġ�� ���� ���͸� ��ȯ�Ѵ�. (theta: -pi/2 ~ pi/2)
	dVector GetPositionOrientation2 () const;	// ��ȯ ����� ��ġ�� ���� ���͸� ��ȯ�Ѵ�. (theta:  pi/2 ~ 3*pi/2)
};
