//////////////////////////////////////////////////////
// Kinematics files for Robotics applications
// 
// Copyright (c) 2002-2010. All Rights Reserved.
// Division of Applied Robot Technology, KITECH
// Web: http://www.orobot.net
// Written by KwangWoong Yang<page365@gmail.com>
//

#include "Kinematics.h"

CTransformMatrix JointInfo::TransformationMatrixQ ()
{
	double x_=0, y_=0, z_=0;
	double phi_=0, theta_=0, psi_=0;

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

CTransformMatrix JointInfo::TransformationMatrix ()
{
	return TransformationMatrixQ() * CTransformMatrix (x, y, z, phi, theta, psi);
}


CKinematics::CKinematics(int taskSize) :
	_desired(taskSize), _current(taskSize)
{
	_desired.zero ();
	_current.zero ();
}

CKinematics::~CKinematics(void)
{
	for (vector<JointInfo *>::iterator it = _jointList.begin (); it != _jointList.end (); ++it) {
		delete *it;
	}
}

void CKinematics::AttachJoint (int type, int axis, double x, double y, double z, double phi, double theta, double psi, 
							   double radius, double limit_lo, double limit_hi, double median, double weight)
{
	assert (0 <= axis && axis < 3);

	JointInfo *joint = new JointInfo;
	
	joint->type = type;
	joint->axis = axis;

	joint->x = x;
	joint->y = y;
	joint->z = z;
	joint->phi   = phi;
	joint->theta = theta;
	joint->psi   = psi;

	joint->radius = radius;

	joint->limit_lo = limit_lo;
	joint->limit_hi = limit_hi;
	joint->median = median;
	joint->weight = weight;

	_jointList.push_back (joint);
}

double CKinematics::WeightFunction (double lo, double hi, double q)
{
 	if (lo < hi) {
		if (q < lo) q = lo;
		if (q > hi) q = hi;

		// w = 2(q - lo)/(hi - lo) -1		// ȸ������ ���� [lo, hi]�� [-1, 1]�� ������ ��ȯ�� q�� ��ġ�� ���
		// w = w^32	// U�� ����� ����� �ٲ۴�.
		double w = 2*(q - lo)/(hi - lo) - 1;
		w *= w; w *= w; w *= w; w *= w; w *= w; 
		return w;
	}
	else {
		return 1.;
	}
}

dMatrix CKinematics::WeightMatrix (unsigned int dof)
{
	dMatrix W(dof, dof);
	W.unit();

/*
	if (_weightCur.size() != dof) {
		_weightCur.resize (dof);
		
		for (unsigned int i=0; i<dof; ++i) {
			JointNullMotion *joint = _jointList[i];
			_weightCur[i] = joint->w;
		}
	}

	_weightPrv = _weightCur;

	for (unsigned int i=0; i<_jointList.size () && i<dof; ++i) {
		JointNullMotion *joint = _jointList[i];

		// Joint�� ȸ����(q)�� ��谪(lo:limits low, hi:limits high) ��ó�� �� �� weight�� �����Ѵ�
		_weightCur[i] = joint->w*(1. - WeightFunction(joint->lo, joint->hi, _kin->GetJointAngle(i)));
		// 1 step ���� weight(_weightPrv)���� ���� ���� weight(_weightCur)���� ���Ͽ�
		// weight�� ������ ���� ��� ��ó�� ���� ����̹Ƿ� weight ���� �״�� �ΰ�
		// weight�� ������ ���� ��迡�� ���������� ����̹Ƿ� weight ���� �ְ����� �Ѵ�.
		W(i,i) = (_weightPrv[i] < _weightCur[i]) ? joint->w : _weightCur[i];
	}
*/
	for (unsigned int i=0; i<_jointList.size () && i<dof; ++i) {
		JointInfo *joint = _jointList[i];
		W(i,i) = joint->weight;
	}
	return W;
}

dVector CKinematics::NullSpaceVector ()
{
	dVector h(_jointList.size ());

	for (unsigned int i=0; i<_jointList.size (); ++i) {
		JointInfo *joint = _jointList[i];

		// Joint�� ȸ����(q)�� ������(basis: ����ڰ� ������ �κ��� �⺻ �ڼ�) ��ó�� �����ϵ��� �Ѵ�
		h[i] = joint->median - joint->q;
	}

	return h;
}

void CKinematics::ClampMag(dVector &w, double maxMag)
{
	double mag = Norm2 (w);
	
	if (maxMag < mag){
		w *= maxMag/mag;
	}
}

dVector CKinematics::SolveJTR (double minAlpha, double clampTask)
{
	Forward ();
	dMatrix J = Jacobian ();
	dVector de = Error ();

	ClampMag (de, clampTask);

	// Compute alpha constant as quotient of 2 inner products as suggested by
	// Buss & Kim, to minimze de after caller updates theta
	dVector JJtde = (J * ~J) * de;
	double alpha = Dot(de, JJtde)/Dot (JJtde, JJtde);

	if (alpha < minAlpha) {
		alpha = minAlpha;
	}

	return alpha * ~J * de;
}

dVector CKinematics::SolveDLS (double dlsLambda, double clampTask, double clampNull)
{
	Forward ();
	dMatrix J = Jacobian ();
	dVector de = Error ();

	ClampMag (de, clampTask);

	dMatrix invJ;

	// Moore-Penrose pseudo-inverse:
	// case m < n: invA = ~A * !(A * ~A)
	if (J.rowno() <= J.colno()) {
		dMatrix I(J.rowno(), J.rowno()); 
		I.unit();
		// Damped least-square method
		invJ = ~J * !( J*~J + dlsLambda*dlsLambda*I );
	}
	// case m > n: invA = !(~A * A) * ~A
	else {
		dMatrix I(J.colno(), J.colno()); 
		I.unit();
		// Damped least-square method
		invJ = !( ~J*J + dlsLambda*dlsLambda*I ) * ~J;
	}

	dVector dq = invJ * de;

	if (0. < clampNull) {
		dVector null = NullSpaceVector ();

		ClampMag (null, clampNull);

		dMatrix I(J.colno(), J.colno());
		I.unit();

		dq += (I - invJ*J)*null;
	}

	return dq;
}

bool CKinematics::SetJointAngle(vector<double> jointAngle)
{
	if(jointAngle.size() != _jointList.size()) {
		return false;
	}

	for(size_t i = 0; i < _jointList.size(); i++) {
		JointInfo *joint = _jointList[i];
		joint->q = jointAngle[i];
	}

	Forward();

	return true;
}

dVector CKinematics::GetJointAngle ()
{
	dVector ang(_jointList.size());

	for (unsigned int i=0; i<_jointList.size(); ++i) {
		JointInfo *joint = _jointList[i];
		ang[i] = joint->q;
	}
	return ang;
}

void CKinematics::Apply (dVector &dq)
{
	for (unsigned int i=0; i<_jointList.size () && i<dq.size(); ++i) {
		JointInfo *joint = _jointList[i];
		joint->q += dq[i];
		if (joint->limit_lo < joint->limit_hi) {
			joint->q = Limit (joint->q, joint->limit_lo, joint->limit_hi);
		}
	}
}

