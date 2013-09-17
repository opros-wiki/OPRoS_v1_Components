#include "StdAfx.h"
#include "JointInfo.h"

JointInfo::JointInfo(void)
: _desired(6), _current(6)
{
}

JointInfo::~JointInfo(void)
{
	for (vector<JointEx *>::iterator it = _jointList.begin (); it != _jointList.end (); ++it) {
		delete *it;
	}
}

void JointInfo::AttachJoint (int type, int axis, double x, double y, double z, double phi, double theta, double psi, double radius)
{
	assert (0 <= axis && axis < 3);

	JointEx *joint = new JointEx;
	
	joint->type = type;
	joint->axis = axis;

	joint->x = x;
	joint->y = y;
	joint->z = z;
	joint->phi   = phi;
	joint->theta = theta;
	joint->psi   = psi;

	joint->radius = radius;

	_jointList.push_back (joint);
}