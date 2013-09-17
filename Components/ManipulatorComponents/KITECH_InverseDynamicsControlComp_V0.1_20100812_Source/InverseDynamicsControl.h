#pragma once
#include "TrackingControl.h"

class InverseDynamicsControl : public TrackingControl
{
public:
	InverseDynamicsControl(double gravity[3], double dt = 0.01, double fsi = .0, double fvi = .0);
	virtual ~InverseDynamicsControl(void);

private:
	double Kp;

	dMatrix iSum;

public:
	bool SetKp(double Kp);
	double GetKp(void);
			
	virtual vector<double> RunController(void);
};
