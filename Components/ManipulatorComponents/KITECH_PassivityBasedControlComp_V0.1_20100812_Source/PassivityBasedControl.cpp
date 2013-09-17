#include "PassivityBasedControl.h"

PassivityBasedControl::PassivityBasedControl(double gravity[3], double dt, double fsi, double fvi)
: TrackingControl(gravity, dt, fsi, fvi)
{
	t = 0;

	K0.resize(0, 0);
	K1.resize(0, 0);
	K2.resize(0, 0);
	
	sigma.resize(0, 0);
	sigmaPrev.resize(0, 0);
	sigmadot.resize(0, 0);

	sigmaSum.resize(0, 0);

	zetadot.resize(0, 0);
	zetadotPrev.resize(0, 0);
	zeta2dot.resize(0, 0);
}

PassivityBasedControl::~PassivityBasedControl(void)
{
}

bool PassivityBasedControl::SetK0(double k0)
{
	if(k0 < 0.0) {
		return false;
	}

	if(_jointList.size() == 0) {
		return false;
	}

	K0.resize(_jointList.size(), _jointList.size());

	for(size_t i = 0; i < K0.RowNo(); i++) {
		for(size_t j = 0; j < K0.ColNo(); j++) {
			if(i == j) {
				K0(i, j) = k0;
			}
			else {
				K0(i, j) = 0.0;
			}
		}
	}

	return true;
}

double PassivityBasedControl::GetK0(void)
{
	return K1(0, 0);
}

bool PassivityBasedControl::SetK1(double k1)
{
	if(k1 < 0.0) {
		return false;
	}

	if(_jointList.size() == 0) {
		return false;
	}

	K1.resize(_jointList.size(), _jointList.size());

	for(size_t i = 0; i < K1.RowNo(); i++) {
		for(size_t j = 0; j < K1.ColNo(); j++) {
			if(i == j) {
				K1(i, j) = k1;
			}
			else {
				K1(i, j) = 0.0;
			}
		}
	}

	return true;
}

double PassivityBasedControl::GetK1(void)
{
	return K1(0, 0);
}

bool PassivityBasedControl::SetK2(double k2)
{
	if(k2 < 0.0) {
		return false;
	}

	if(_jointList.size() == 0) {
		return false;
	}

	K2.resize(_jointList.size(), _jointList.size());

	for(size_t i = 0; i < K2.RowNo(); i++) {
		for(size_t j = 0; j < K2.ColNo(); j++) {
			if(i == j) {
				K2(i, j) = k2;
			}
			else {
				K2(i, j) = 0.0;
			}
		}
	}

	return true;
}

double PassivityBasedControl::GetK2(void)
{
	return K2(0, 0);
}

vector<double> PassivityBasedControl::RunController(void)
{
	Forward ();

	unsigned int n = _jointList.size ();

	if(sigma.ColNo() == 0) {
		sigma.resize(n, 1);
		sigmaPrev.resize(n, 1);
		sigmadot.resize(n, 1);

		sigmaSum.resize(n, 1);

		zetadot.resize(n, 1);
		zetadotPrev.resize(n, 1);
		zeta2dot.resize(n, 1);

		for(unsigned int i = 0; i < n; i++) {
			sigma(i, 0) = 0.0;
			sigmaPrev(i, 0) = 0.0;
			sigmadot(i, 0) = 0.0;

			sigmaSum(i, 0) = 0.0;

			zetadot(i, 0) = 0.0;
			zetadotPrev(i, 0) = 0.0;
			zeta2dot(i, 0) = 0.0;
		}
	}

	if(K0.ColNo() == 0 || K1.ColNo() == 0 || K2.ColNo() == 0) {
		vector<double> ret;
		return ret;
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

	dMatrix K(n, n);
	K = K0 + K1*t + K2*(t*t);

	dMatrix F(n, n);
	dMatrix I(n, n);
	for(size_t i = 0; i < I.ColNo(); i++) {
		for(size_t j = 0; j < I.RowNo(); j++) {
			if(i == j) {
				I(i, j) = 1.0;
			}
			else {
				I(i, j) = 0.0;
			}
		}
	}
	

	F = I*t + K;
	
	sigma = !F*(_q - _qd);
	sigmadot = (sigma - sigmaPrev) / dt;
	sigmaPrev = sigma;
	
	zetadot = _qdotd - K*(_q - _qd);
	zeta2dot = (zetadot - zetadotPrev) / dt;
	zetadotPrev = zetadot;

	dMatrix PSI(n, 1);
	PSI = H*sigmadot + C*sigma + Kd*sigma;

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
