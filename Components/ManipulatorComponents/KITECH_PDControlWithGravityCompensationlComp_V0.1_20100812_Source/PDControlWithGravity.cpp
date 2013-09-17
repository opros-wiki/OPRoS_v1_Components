#include "PDControlWithGravity.h"

PDControlWithGravity::PDControlWithGravity(double gravity[3], double dt, double fsi, double fvi)
:PDControl(gravity, dt, fsi, fvi)
{
}

PDControlWithGravity::~PDControlWithGravity(void)
{
}

vector<double> PDControlWithGravity::RunController(void)
{
	Forward ();

	unsigned int n = _jointList.size ();

	vector<dMatrix> Jp(n);
	vector<dMatrix> Jo(n);
	for (unsigned int i=0; i<n; ++i) {
		Jp[i] = JacobianPos (i);
		Jo[i] = JacobianOri (i);
	}

	dMatrix G = GravityMatrix (Jp, Jo);

	//	Calculate a control input
	dVector U(n);
	
	U = Kp * (_qd - _q) - Kd * _qdot + G;

	vector<double> torque(n);
	for(size_t i = 0; i < torque.size(); i++) {
		torque[i] = U[i];
	}
		
	return torque;
}