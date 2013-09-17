#include "InverseDynamicsControl.h"

InverseDynamicsControl::InverseDynamicsControl(double gravity[3], double dt, double fsi, double fvi)
: TrackingControl(gravity, dt, fsi, fvi)
{
	Kp = 0.0;

	iSum.resize(0, 0);
}

InverseDynamicsControl::~InverseDynamicsControl(void)
{
}

bool InverseDynamicsControl::SetKp(double Kp)
{
	if(Kp < 0.0) {
		return false;
	}

	this->Kp = Kp;

	return true;
}

double InverseDynamicsControl::GetKp(void)
{
	return Kp;
}

vector<double> InverseDynamicsControl::RunController(void)
{
	Forward ();

	unsigned int n = _jointList.size ();

	if(iSum.ColNo() == 0) {
		iSum.resize(n, 1);

		for(size_t i = 0; i < n; i++) {
			iSum(i, 0) = 0.0;
		}
	}

	vector<dMatrix> Jp(n);
	vector<dMatrix> Jo(n);
	for (unsigned int i=0; i<n; ++i) {
		Jp[i] = JacobianPos (i);
		Jo[i] = JacobianOri (i);
	}

	dMatrix H = InertiaMatrix (Jp, Jo);
	dMatrix C = CoriolisMatrix (Jp, Jo);
	dMatrix G = GravityMatrix (Jp, Jo);

	//	Calculate a control input
	dVector U(n);
	dMatrix U0(n, 1);

	if(controlMode == MORMAL_CONTROL_MODE) {
		U0 = _q2dotd + Kd*(_qdotd - _qdot) + Kp*(_qd - _q);
	}
	else {
		iSum += (_qd - _q) * dt;
		U0 = _q2dotd + Kd*(_qdotd - _qdot) + Kp*(_qd - _q) + Ki*iSum;
		
	}
	
	U = H*U0 + C*_qdot + G;

	vector<double> torque(n);
	for(size_t i = 0; i < torque.size(); i++) {
		torque[i] = U[i];
	}
		
	return torque;
}
