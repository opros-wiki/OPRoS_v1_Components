#pragma once
#include "TrackingControl.h"

class PassivityBasedControl : public TrackingControl
{
public:
	PassivityBasedControl(double gravity[3], double dt = 0.01, double fsi = .0, double fvi = .0);
	virtual ~PassivityBasedControl(void);

private:
	double t;

	dMatrix K0;
	dMatrix K1;
	dMatrix K2;
	
	dMatrix sigma;
	dMatrix sigmaPrev;
	dMatrix sigmadot;

	dMatrix sigmaSum;

	dMatrix zetadot;
	dMatrix zetadotPrev;
	dMatrix zeta2dot;

public:
	bool SetK0(double k0);
	double GetK0(void);
	bool SetK1(double k1);
	double GetK1(void);
	bool SetK2(double k2);
	double GetK2(void);

	virtual vector<double> RunController(void);
};
