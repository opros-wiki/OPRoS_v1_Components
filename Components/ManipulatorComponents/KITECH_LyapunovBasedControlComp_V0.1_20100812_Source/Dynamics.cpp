//////////////////////////////////////////////////////
// Kinematics files for Robotics applications
// 
// Copyright (c) 2002-2010. All Rights Reserved.
// Division of Applied Robot Technology, KITECH
// Web: http://www.orobot.net
// Written by KwangWoong Yang<page365@gmail.com>
//

#include "Dynamics.h"

CTransformMatrix JointInfo::TransformationMatrixQ ()
{
	if (type == PRISMATIC_JOINT){
		if (axis == 0)      return CTransformMatrix (q, 0, 0, 0, 0, 0);
		else if (axis == 1) return CTransformMatrix (0, q, 0, 0, 0, 0);
		else if (axis == 2) return CTransformMatrix (0, 0, q, 0, 0, 0);
	}
	else if (type == REVOLUTE_JOINT) {
		if (axis == 0)      return CTransformMatrix (0, 0, 0, q, 0, 0);
		else if (axis == 1) return CTransformMatrix (0, 0, 0, 0, q, 0);
		else if (axis == 2) return CTransformMatrix (0, 0, 0, 0, 0, q);
	}
	return CTransformMatrix (0, 0, 0, 0, 0, 0);
}

CTransformMatrix JointInfo::TransformationMatrixDiffQ ()
{
	if (type == PRISMATIC_JOINT){
		if (axis == 0)      return CTransformMatrixDiffX (q, 0, 0, 0, 0, 0);
		else if (axis == 1) return CTransformMatrixDiffY (0, q, 0, 0, 0, 0);
		else if (axis == 2) return CTransformMatrixDiffZ (0, 0, q, 0, 0, 0);
	}
	else if (type == REVOLUTE_JOINT) {
		if (axis == 0)      return CTransformMatrixDiffPhi   (0, 0, 0, q, 0, 0);
		else if (axis == 1) return CTransformMatrixDiffTheta (0, 0, 0, 0, q, 0);
		else if (axis == 2) return CTransformMatrixDiffPsi   (0, 0, 0, 0, 0, q);
	}
	return CTransformMatrixDiffX (0, 0, 0, 0, 0, 0);
}

CTransformMatrix JointInfo::TransformationMatrix ()
{
	return CTransformMatrix (x, y, z, phi, theta, psi);
}

CDynamics::CDynamics(double gravity[3], double fsi, double fvi)
: _fsi(fsi), _fvi(fvi)
{
	_gravity[0] = gravity[0];
	_gravity[1] = gravity[1];
	_gravity[2] = gravity[2];
}

CDynamics::~CDynamics()
{
	for (vector<JointInfo *>::iterator it = _jointList.begin (); it != _jointList.end (); ++it) {
		delete *it;
	}
}

void CDynamics::AttachJoint (int type, int axis, double mass, double cx, double cy, double cz, 
							   double Ixx, double Iyy, double Izz, double Ixy, double Iyz, double Izx,
							   double x, double y, double z, double phi, double theta, double psi, double radius)
{
	JointInfo *joint = new JointInfo;
	
	joint->type = type;
	joint->axis = axis; 
	joint->mass = mass; 
	joint->c[0] = cx; 
	joint->c[1] = cy; 
	joint->c[2] = cz; 

	joint->I.resize (3, 3);
	joint->I(0,0) = Ixx;
	joint->I(1,1) = Iyy;
	joint->I(2,2) = Izz;
	joint->I(0,1) = Ixy;
	joint->I(1,0) = Ixy;
	joint->I(1,2) = Iyz;
	joint->I(2,1) = Iyz;
	joint->I(0,2) = Izx;
	joint->I(2,0) = Izx;

	joint->x = x; 
	joint->y = y; 
	joint->z = z; 
	joint->phi = phi; 
	joint->theta = theta; 
	joint->psi = psi; 
	joint->radius = radius;

	_jointList.push_back (joint);

	size_t size = _jointList.size();
	_qd.resize(size);
	_q.resize(size);

	_qdotd.resize(size);
	_qdot.resize(size);

	_q2dotd.resize(size);
	_q2dot.resize(size);

	for(size_t i = 0; i < _jointList.size(); i++) {
		_qd[i] = 0.0;
		_q[i] = 0.0;
		_qdotd[i] = 0.0;
		_qdot[i] = 0.0;
		_q2dotd[i] = 0.0;
		_q2dot[i] = 0.0;
	}
}

dVector CDynamics::GetJointAngle ()
{
	dVector ang(_jointList.size());

	for (unsigned int i=0; i<_jointList.size(); ++i) {
		JointInfo *joint = _jointList[i];
		ang[i] = joint->q;
	}
	return ang;
}

