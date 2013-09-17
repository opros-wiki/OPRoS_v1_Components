//////////////////////////////////////////////////////
// Kinematics & Dynamics files for Robot applications
// 
// Copyright (c) 2002-2008. All Rights Reserved.
// Division of Applied Robot Technology KITECH
// Web: http://www.orobot.net
// Written by KwangWoong Yang<page365@gmail.com>
//

#include "MathDef.h"
#include "LagrangeDynamics.h"

#pragma warning(disable:4996)


CLagrangeDynamics::CLagrangeDynamics(double gravity[3], double fsi, double fvi)
: CDynamics (gravity, fsi, fvi), _kineticEnergy(0), _potentialEnergy(0)
{ 	
}

CLagrangeDynamics::~CLagrangeDynamics ()
{
}

void CLagrangeDynamics::Forward ()
{
	unsigned int n = _jointList.size ();

	CTransformMatrix T;

	vector<CTransformMatrix> dT(n);
	for (unsigned int i=0; i<n; ++i) {
		dT[i].resize (4,4);	
		dT[i].zero();
	}

	// Jacobian을 만들기 위해 zi벡터와 pi벡터를 계산한다
	for (unsigned int i=0; i<n; ++i) {
		JointInfo *joint = _jointList[i];

		CTransformMatrix A = joint->TransformationMatrix ();
		CTransformMatrix Q = joint->TransformationMatrixQ ();
		CTransformMatrix dQ = joint->TransformationMatrixDiffQ ();

		joint->a = T.GetRotation (joint->axis);		// 회전 축의 회전 성분 (각속도)
		joint->p = T.GetPosition ();				// 전역 좌표계에서의 축의 위치

		joint->dz.resize (n);
		joint->dp.resize (n);
		for (unsigned int j=0; j<n; ++j) {
			joint->dz[j] = dT[j].GetRotation (joint->axis);
			joint->dp[j] = dT[j].GetPosition ();
		}

		// dT[k] = d T / d q[k]
		for (unsigned int k=0; k<n; ++k) {
			if (k > i)       dT[k].zero ();
			else if (k == i) dT[k] = T*dQ;
			else             dT[k] = dT[k]*Q; 
		}

		T *= Q;

		joint->R = T.GetRotation ();				// Get Rotation dMatrix 
		joint->g = joint->p + joint->R * joint->c;

		joint->dg.resize (n);
		joint->dR.resize (n);
		for (unsigned int j=0; j<n; ++j) {
			joint->dR[j] = dT[j].GetRotation ();	// Get Rotation dMatrix 
			joint->dg[j] = joint->dp[j] + joint->dR[j] * joint->c;
		}

		for (unsigned int k=0; k<n; ++k) {
			dT[k] *= A;
		}

		T *= A;
	}
}


dMatrix CLagrangeDynamics::JacobianPos(unsigned int li)
{
	unsigned int n = _jointList.size ();
	dMatrix Jp(3, n);
	Jp.zero();

	for (unsigned int i=0; i<n && i<=li; ++i) {
		JointInfo *joint = _jointList[i];

		if (joint->type == REVOLUTE_JOINT) {
			//Position Jacobian 
			dVector pos = Cross (joint->a, _jointList[li]->g - joint->p);
			Jp(0,i) = pos[0];
			Jp(1,i) = pos[1];
			Jp(2,i) = pos[2];
		}
		else if (joint->type == PRISMATIC_JOINT) {
			//Position Jacobian 
			Jp(0,i) = joint->a[0];
			Jp(1,i) = joint->a[1];
			Jp(2,i) = joint->a[2];
		}
	}
	return Jp;
}

dMatrix CLagrangeDynamics::JacobianOri(unsigned int li)
{
	unsigned int n = _jointList.size ();
	dMatrix Jo(3, n);
	Jo.zero();

	for (unsigned int i=0; i<n && i<=li; ++i) {
		JointInfo *joint = _jointList[i];

		if (joint->type == REVOLUTE_JOINT) {
			//Orientation Jacobian 
			Jo(0,i) = joint->a[0];
			Jo(1,i) = joint->a[1];
			Jo(2,i) = joint->a[2];
		}
		else if (joint->type == PRISMATIC_JOINT) {
			//Orientation Jacobian 
			Jo(0,i) = 0.;
			Jo(1,i) = 0.;
			Jo(2,i) = 0.;
		}
	}
	return Jo;
}

dMatrix CLagrangeDynamics::JacobianPosDiff(unsigned int li, unsigned int k)
{
	unsigned int n = _jointList.size ();
	dMatrix dJp(3, n);
	dJp.zero();

	for (unsigned int i=0; i<n && i<=li; ++i) {
		JointInfo *joint = _jointList[i];

		if (joint->type == REVOLUTE_JOINT) {
			dVector dpos = Cross(joint->dz[k], _jointList[li]->g - joint->p) 
				+ Cross (joint->a, _jointList[li]->dg[k] - joint->dp[k]);  

			//Position Jacobian 
			dJp(0, i) = dpos[0];
			dJp(1, i) = dpos[1];
			dJp(2, i) = dpos[2];
		}
		else if (joint->type == PRISMATIC_JOINT) {
			//Position Jacobian 
			dJp(0, i) = joint->dz[k][0];
			dJp(1, i) = joint->dz[k][1];
			dJp(2, i) = joint->dz[k][2];
		}
	}
	return dJp;
}

dMatrix CLagrangeDynamics::JacobianOriDiff(unsigned int li, unsigned int k)
{
	unsigned int n = _jointList.size ();
	dMatrix dJo(3, n);
	dJo.zero ();

	for (unsigned int i=0; i<n && i<=li; ++i) {
		JointInfo *joint = _jointList[i];

		if (joint->type == REVOLUTE_JOINT) {
			//Orientation Jacobian 
			dJo(0,i) = joint->dz[k][0];
			dJo(1,i) = joint->dz[k][1];
			dJo(2,i) = joint->dz[k][2];
		}
		else if (joint->type == PRISMATIC_JOINT) {
			//Orientation Jacobian 
			dJo(0,i) = 0.;
			dJo(1,i) = 0.;
			dJo(2,i) = 0.;
		}
	}
	return dJo;
}

dMatrix CLagrangeDynamics::InertiaMatrix (vector<dMatrix> &Jp, vector<dMatrix> &Jo)
{
	unsigned int n = _jointList.size ();

	dMatrix M(n, n);
	M.zero();

	for (unsigned int i=0; i<n; ++i) {
		JointInfo *joint = _jointList[i];

		M += joint->mass*~Jp[i]*Jp[i] + ~Jo[i]*joint->R*joint->I*~joint->R*Jo[i];
	}
	return M;
}

dMatrix CLagrangeDynamics::CoriolisMatrix (vector<dMatrix> &Jp, vector<dMatrix> &Jo)
{
	unsigned int n = _jointList.size ();

	vector<dMatrix> dM(n);
	for (unsigned int k=0; k<n; ++k) {
		JointInfo *joint = _jointList[k];

		dMatrix IR = joint->R*joint->I*~joint->R;
		dMatrix dIR = joint->dR[k]*joint->I*~joint->R + joint->R*joint->I*~joint->dR[k];

		dM[k].resize (n, n);
		dM[k].zero();
		for (unsigned int i=0; i<n; ++i) {
			dMatrix dJp = JacobianPosDiff (i, k);
			dMatrix dJo = JacobianOriDiff (i, k);

			dM[k] += joint->mass*(~dJp*Jp[i] + ~Jp[i]*dJp) + ~dJo*IR*Jo[i] + ~Jo[i]*dIR*Jo[i] + ~Jo[i]*IR*dJo;
		}
	}

	dMatrix C(n, n);
	C.zero();

	for (unsigned int i=0; i<n; ++i) {
		for (unsigned int j=0; j<n; ++j) {
			for (unsigned int k=0; k<n; ++k) {
				C(i,j) += (dM[k](i,j) + dM[j](i,k) - dM[i](j,k))*_jointList[k]->dq;
			}
			C(i,j) *= 0.5;
		}
	}

	return C;
}

dMatrix CLagrangeDynamics::GravityMatrix (vector<dMatrix> &Jp, vector<dMatrix> &Jo)
{
	unsigned int n = _jointList.size ();

	dMatrix G(n, 1);
	G.zero();

	for (unsigned int i=0; i<n; ++i) {
		JointInfo *joint = _jointList[i];

		for (unsigned int j=0; j<n; ++j) {
			JointInfo *joint2 = _jointList[j];
			dMatrix Jpc = Jp[j].GetSubMatrix (0,i, 3,1);
			dMatrix gi = joint2->mass*~_gravity*Jpc;
			G(i,0) -= gi(0,0);
		}
	}
	return G;
}

dVector CLagrangeDynamics::FrictionForce ()
{
	dVector friction(_jointList.size ());

	for (unsigned int i=0; i<_jointList.size (); ++i) {
		friction(i,0) = _fsi*Sign(_jointList[i]->dq) + _fvi*_jointList[i]->dq;
	}
	return friction;
}

double CLagrangeDynamics::KineticEnergy (dMatrix &M)
{
	dVector dq(_jointList.size ());

	for (unsigned int i=0; i<_jointList.size (); ++i) {
		dq[i] = _jointList[i]->dq;
	}

	dMatrix a = 0.5*~dq*M*dq;

	return a(0,0);
}

double CLagrangeDynamics::PotentialEnergy ()
{
	dMatrix b(1,1);
	b.zero();

	for (unsigned int i=0; i<_jointList.size (); ++i) {
		b -= _jointList[i]->mass*~_gravity*_jointList[i]->g;
	}
	return b(0,0);
}

dVector CLagrangeDynamics::ForwardDynamics (dVector &torque)
{
	Forward ();

	unsigned int n = _jointList.size ();

	vector<dMatrix> Jp(n);
	vector<dMatrix> Jo(n);
	for (unsigned int i=0; i<n; ++i) {
		Jp[i] = JacobianPos (i);
		Jo[i] = JacobianOri (i);
	}

	dMatrix M = InertiaMatrix (Jp, Jo);
	dMatrix C = CoriolisMatrix (Jp, Jo);
	dMatrix G = GravityMatrix (Jp, Jo);

	dVector F = FrictionForce ();

	_kineticEnergy = KineticEnergy (M);
	_potentialEnergy = PotentialEnergy ();


	dVector dq(n);
	for (unsigned int i=0; i<n; ++i) {
		dq[i] = _jointList[i]->dq;
	}

	double dlsLambda = 0.0001;
	dMatrix I(n, n); I.unit();
	// Moore-Penrose pseudo-inverse with Damped least-square method
	dMatrix invM = ~M * !( M*~M + dlsLambda*dlsLambda*I );

	return invM*(torque-(C*dq + G + F));
}

dVector CLagrangeDynamics::InverseDynamics ()
{
	Forward ();

	unsigned int n = _jointList.size ();

	vector<dMatrix> Jp(n);
	vector<dMatrix> Jo(n);
	for (unsigned int i=0; i<n; ++i) {
		Jp[i] = JacobianPos (i);
		Jo[i] = JacobianOri (i);
	}

	dMatrix M = InertiaMatrix (Jp, Jo);
	dMatrix C = CoriolisMatrix (Jp, Jo);
	dMatrix G = GravityMatrix (Jp, Jo);

	dVector F = FrictionForce ();

	_kineticEnergy = KineticEnergy (M);
	_potentialEnergy = PotentialEnergy ();


	dVector dq(n);
	dVector ddq(n);
	for (unsigned int i=0; i<n; ++i) {
		dq[i] = _jointList[i]->dq;
		ddq[i] = _jointList[i]->ddq;
	}

	return M*ddq + C*dq + G + F;
}

void CLagrangeDynamics::Apply (dVector &accel, double dt)
{
	for (unsigned int i=0; i<_jointList.size (); ++i) {
		_jointList[i]->ddq = accel[i];
		_jointList[i]->dq += dt*_jointList[i]->ddq;
		_jointList[i]->q  += dt*_jointList[i]->dq;
	}
}

void CLagrangeDynamics::Reset ()
{
	for (unsigned int i=0; i<_jointList.size (); ++i) {
		_jointList[i]->ddq = 0.;
		_jointList[i]->dq  = 0.;
		_jointList[i]->q   = 0.;
	}
}
