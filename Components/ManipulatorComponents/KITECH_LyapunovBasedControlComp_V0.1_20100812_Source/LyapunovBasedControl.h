#pragma once
#include "TrackingControl.h"

class LyapunovBasedControl : public TrackingControl
{
public:
	LyapunovBasedControl(double gravity[3], double dt = 0.01, double fsi = .0, double fvi = .0);
	virtual ~LyapunovBasedControl(void);

private:
	double lambda;
		
	dMatrix zetadot;
	dMatrix zetadotPrev;
	dMatrix zeta2dot;

	dMatrix sigmaSum;
	
public:
	bool SetLambda(double lambda);
	double GetLambda(void);
		
	virtual vector<double> RunController(void);
};
