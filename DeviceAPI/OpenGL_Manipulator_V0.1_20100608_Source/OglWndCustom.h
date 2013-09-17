//////////////////////////////////////////////////////
// OpenGL files for Robotics applications
// 
// Copyright (c) 2002-2010. All Rights Reserved.
// Division of Applied Robot Technology, KITECH
// Web: http://www.orobot.net
// Written by KwangWoong Yang<page365@gmail.com>
//

#pragma once
#include "OglWnd.h"
#include "JointInfo.h"

class COglWndCustom : public COglWnd
{
public:
	COglWndCustom (JointInfo *jointInfo);

	virtual void OnDraw(CDC* pDC);

	bool _showAxis;

private:
	JointInfo *jointInfo;

	void TransformAxis(dMatrix &A);
	void DrawRevLink (double x, double y, double z, double radius);

	void DrawFixedJoint (JointBasis *joint);
	void DrawRevoluteJoint (JointBasis *joint);
	void DrawPrismaticJoint (JointBasis *joint);

	void RenderTarget ();
	void RenderJoint();
};
