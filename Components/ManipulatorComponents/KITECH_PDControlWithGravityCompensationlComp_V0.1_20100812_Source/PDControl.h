#pragma once
#include "DynamicsControl.h"

class PDControl : public DynamicsControl
{
public:
	PDControl(double gravity[3], double dt = 0.01, double fsi = .0, double fvi = .0);
	virtual ~PDControl(void);

protected:
	double Kp;
	double Kd;

public:
	bool SetKp(double Kp);
	double GetKp(void);
	bool SetKd(double Kd);
	double GetKd(void);
	
	virtual vector<double> RunController(void);
};
