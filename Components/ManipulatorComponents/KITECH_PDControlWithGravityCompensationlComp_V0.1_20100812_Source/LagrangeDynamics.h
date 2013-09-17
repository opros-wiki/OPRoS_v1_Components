//////////////////////////////////////////////////////
// Kinematics & Dynamics files for Robot applications
// 
// Copyright (c) 2002-2008. All Rights Reserved.
// Division of Applied Robot Technology KITECH
// Web: http://www.orobot.net
// Written by KwangWoong Yang<page365@gmail.com>
//

#pragma	once

#include <vector>
#include "Dynamics.h"


class CLagrangeDynamics : public CDynamics
{
public:
	CLagrangeDynamics(double gravity[3], double fsi = .0, double fvi = .0);
	~CLagrangeDynamics();

	dVector ForwardDynamics (dVector &torque);
	dVector InverseDynamics ();
	double GetKineticEnergy() { return _kineticEnergy; }
	double GetPotentialEnergy() { return _potentialEnergy; }

	void Apply (dVector &accel, double dt);
	void Reset ();

protected:
	void Forward ();
	dMatrix JacobianPos(unsigned int li);
	dMatrix JacobianOri(unsigned int li);
	dMatrix JacobianPosDiff(unsigned int li, unsigned int k);
	dMatrix JacobianOriDiff(unsigned int li, unsigned int k);

	dMatrix InertiaMatrix (vector<dMatrix> &Jp, vector<dMatrix> &Jo);
	dMatrix CoriolisMatrix (vector<dMatrix> &Jp, vector<dMatrix> &Jo);
	dMatrix GravityMatrix (vector<dMatrix> &Jp, vector<dMatrix> &Jo);

	dVector FrictionForce ();

	double KineticEnergy (dMatrix &M);
	double PotentialEnergy ();

	double _kineticEnergy;
	double _potentialEnergy;
};

