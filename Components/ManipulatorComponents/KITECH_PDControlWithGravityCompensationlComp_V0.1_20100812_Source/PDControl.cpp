#include "PDControl.h"

PDControl::PDControl(double gravity[3], double dt, double fsi, double fvi)
:DynamicsControl(gravity, dt, fsi, fvi)
{
	Kp = 0.0;
	Kd = 0.0;
}

PDControl::~PDControl(void)
{
}

bool PDControl::SetKp(double Kp)
{
	if(Kp < 0.0) {
		return false;
	}

	this->Kp = Kp;

	return true;
}

double PDControl::GetKp(void)
{
	return Kp;
}

bool PDControl::SetKd(double Kd)
{
	if(Kd < 0.0) {
		return false;
	}
	
	this->Kd = Kd;

	return true;
}

double PDControl::GetKd(void)
{
	return Kd;
}

vector<double> PDControl::RunController(void)
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
	vector<double> torque(n);
	U = Kp * (_qd - _q) - Kd * _qdot;
	
	for(size_t i = 0; i < torque.size(); i++) {
		torque[i] = U[i];
	}
		
	return torque;
}