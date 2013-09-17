#include "LyapunovBasedControl.h"

LyapunovBasedControl::LyapunovBasedControl(double gravity[3], double dt, double fsi, double fvi)
: TrackingControl(gravity, dt, fsi, fvi)
{
	lambda = 0.0;

	zetadot.resize(0, 0);
	zetadotPrev.resize(0, 0);
	zeta2dot.resize(0, 0);

	sigmaSum.resize(0, 0);
}

LyapunovBasedControl::~LyapunovBasedControl(void)
{
}

bool LyapunovBasedControl::SetLambda(double lambda)
{
	if(lambda < 0.0) {
		return false;
	}

	this->lambda = lambda;

	return true;
}

double LyapunovBasedControl::GetLambda(void)
{
	return lambda;
}

vector<double> LyapunovBasedControl::RunController(void)
{
	Forward ();

	unsigned int n = _jointList.size ();

	if(zetadot.ColNo() == 0) {
		zetadot.resize(_jointList.size(), 1);
		zetadotPrev.resize(_jointList.size(), 1);
		zeta2dot.resize(_jointList.size(), 1);
		sigmaSum.resize(_jointList.size(), 1);

		for(int i = 0; i < (int)_jointList.size(); i++) {
			zetadot(i, 0) = 0.0;
			zetadotPrev(i, 0) = 0.0;
			zeta2dot(i, 0) = 0.0;
			sigmaSum(i, 0) = 0.0;
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

	dMatrix sigma(n, 1);
	sigma = (_qdot - _qdotd) + lambda*(_q - _qd);
	
	zetadot = _qdotd - lambda*(_q - _qd);
	zeta2dot = (zetadot - zetadotPrev) / dt;
	zetadotPrev = zetadot;

	dVector U(n);
	if(controlMode == MORMAL_CONTROL_MODE) {
		U = H*zeta2dot + C*zetadot + G - Kd*sigma;
	}
	else {
		sigmaSum += sigma * dt;
		U = H*zeta2dot + C*zetadot + G - Kd*sigma - Ki*sigmaSum;
	}
	
	vector<double> torque(n);
	for(size_t i = 0; i < torque.size(); i++) {
		torque[i] = U[i];
	}
		
	return torque;
}
