//////////////////////////////////////////////////////
// Kinematics files for Robotics applications
// 
// Copyright (c) 2002-2010. All Rights Reserved.
// Division of Applied Robot Technology, KITECH
// Web: http://www.orobot.net
// Written by KwangWoong Yang<page365@gmail.com>
//

#include "StdAfx.h"
#include "Kinematics.h"

CTransformMatrix JointBasis::TransformationMatrixQ ()
{
	double x_ = 0;
	double y_ = 0;
	double z_ = 0;
	double phi_   = 0;
	double theta_ = 0;
	double psi_   = 0;

	if (type == PRISMATIC_JOINT){
		if (axis == 0)      x_ = q;
		else if (axis == 1) y_ = q;
		else if (axis == 2) z_ = q;
	}
	else if (type == REVOLUTE_JOINT) {
		if (axis == 0)      phi_   = q;
		else if (axis == 1) theta_ = q;
		else if (axis == 2) psi_   = q;
	}

	return CTransformMatrix (x_, y_, z_, phi_, theta_, psi_);
}

CTransformMatrix JointBasis::TransformationMatrix ()
{
	return TransformationMatrixQ() * CTransformMatrix (x, y, z, phi, theta, psi);
}
