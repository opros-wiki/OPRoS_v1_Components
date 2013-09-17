//////////////////////////////////////////////////////
// Kinematics files for Robotics applications
// 
// Copyright (c) 2002-2010. All Rights Reserved.
// Division of Applied Robot Technology, KITECH
// Web: http://www.orobot.net
// Written by KwangWoong Yang<page365@gmail.com>
//

#pragma	once

#include "Kinematics.h"

#define POSITION_ONLY			1
#define ORIENTATION_ONLY		2
#define POSITION_ORIENTATION	(POSITION_ONLY|ORIENTATION_ONLY)

class DampedLeastSquare : public CKinematics
{
public:
	DampedLeastSquare (int inverseAxis = POSITION_ORIENTATION); 
	~DampedLeastSquare (); 
	
	void SetDesired (double x, double y, double z, double phi, double theta, double psi);	// 목적지의 위치를 설정한다.

	virtual dMatrix Forward ();
	virtual dVector Error ();
	virtual dMatrix Jacobian ();

private:
	int _inverseAxis;
};
