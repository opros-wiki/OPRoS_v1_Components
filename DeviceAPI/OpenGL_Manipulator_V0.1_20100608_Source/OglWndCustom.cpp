//////////////////////////////////////////////////////
// OpenGL files for Robotics applications
// 
// Copyright (c) 2002-2010. All Rights Reserved.
// Division of Applied Robot Technology, KITECH
// Web: http://www.orobot.net
// Written by KwangWoong Yang<page365@gmail.com>
//

#include "StdAfx.h"
#include "OglWndCustom.h"
#include "MathDef.h"
#include "Transformation.h"
#include "OglObjects.h"
#include <gl/glu.h>

COglWndCustom::COglWndCustom (JointInfo *jointInfo)
: _showAxis(false)
{
	this->jointInfo = jointInfo;
}

// Rendering
void COglWndCustom::OnDraw (CDC* pDC)
{
	SetViewport ();
	oglPlane (5., .5);

	RenderTarget ();
	RenderJoint ();
}

void COglWndCustom::TransformAxis(dMatrix &A)
{
	double m[16];

	m[0] = A(0,0);  m[4] = A(0,1);  m[8] = A(0,2);  m[12] = A(0,3); 
	m[1] = A(1,0);  m[5] = A(1,1);  m[9] = A(1,2);  m[13] = A(1,3); 
	m[2] = A(2,0);  m[6] = A(2,1);  m[10]= A(2,2);  m[14] = A(2,3); 
	m[3] = 0.;      m[7] = 0.;      m[11]= 0.;      m[15] = 1.; 

	glMultMatrixd(m);
}

void COglWndCustom::RenderTarget ()
{
	dVector desired = jointInfo->GetDesired ();

	glPushMatrix();

	glTranslated(desired[0], desired[1], desired[2]);
	glRotated (_RAD2DEG*desired[3], 1, 0, 0);
	glRotated (_RAD2DEG*desired[4], 0, 1, 0);
	glRotated (_RAD2DEG*desired[5], 0, 0, 1);

	glColor3d(1.0, 0., 0.);
	oglBox (0.06, 0.06, 0.06);
	if (_showAxis) oglCoordinate (0.3);

	glPopMatrix();
}

void COglWndCustom::DrawRevLink (double x, double y, double z, double radius)
{
	glPushMatrix();

	double rz = _RAD2DEG*atan2(y, x);
	double ry = 90. - _RAD2DEG*atan2(z, sqrt(x*x + y*y));
	double height = sqrt (x*x + y*y + z*z);

	glRotated( rz, 0, 0, 1);
	glRotated( ry, 0, 1, 0);
	glTranslated (0, 0, height/2.);		

	oglCylinder (height, radius);

	glPopMatrix();
}

void COglWndCustom::DrawFixedJoint(JointBasis *joint)
{
	glColor3d (0.7, 0.7, 0.7);
	DrawRevLink (joint->x, joint->y, joint->z, joint->radius);
}

void COglWndCustom::DrawRevoluteJoint(JointBasis *joint)
{
	glPushMatrix();

	if      (joint->axis == 0) glRotated( 90., 0,1,0 );
	else if (joint->axis == 1) glRotated(-90., 1,0,0 );

	glColor3d(0.5, 0.5, 0.5);
	oglCylinder (joint->radius*2.5, joint->radius*1.3);

	glPopMatrix();

	glPushMatrix();

	TransformAxis (joint->TransformationMatrixQ ());

	glColor3d(0.7, 0.7, 0.7);
	DrawRevLink (joint->x, joint->y, joint->z, joint->radius);

	glPopMatrix();
}

void COglWndCustom::DrawPrismaticJoint(JointBasis *joint)
{
	glPushMatrix();

	if      (joint->axis == 0) glRotated( 90., 0,1,0 );
	else if (joint->axis == 1) glRotated(-90., 1,0,0 );

	glColor3d(0.5, 0.5, 0.5);
	oglBox (joint->radius*2.5, joint->radius*2.5, joint->radius*2.5);
	glTranslated (0, 0, joint->q/2.);		

	glColor3d(0.8, 0.8, 0.8);
	oglBox (joint->radius*1.5, joint->radius*1.5, joint->q);

	glPopMatrix();

	glPushMatrix();

	TransformAxis (joint->TransformationMatrixQ ());

	glColor3d(0.7, 0.7, 0.7);
	DrawRevLink (joint->x, joint->y, joint->z, joint->radius);

	glPopMatrix();
}

void COglWndCustom::RenderJoint()
{
	vector<JointEx *> &jointList = jointInfo->GetJointList ();

	for (vector<JointEx *>::iterator it = jointList.begin (); it != jointList.end (); ++it) {
		JointEx *joint = *it;

		glColor3d(0.7, 0.7, 0.7);
		
		if (joint->type == FIXED_JOINT) {
			DrawFixedJoint (joint);
		}
		else if (joint->type == REVOLUTE_JOINT) {
			DrawRevoluteJoint (joint);
		}
		else if (joint->type == PRISMATIC_JOINT) {
			DrawPrismaticJoint (joint);
		}

		TransformAxis (joint->TransformationMatrix ());
	}
	if (_showAxis) oglCoordinate (0.3);
}


