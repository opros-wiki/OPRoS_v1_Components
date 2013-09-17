#pragma once

#include "DynamicsControl.h"

#define	MORMAL_CONTROL_MODE		0
#define	INETGRAL_CONTROL_MODE	1
#define	ADAPTIVE_CONTROL_MODE	2

class TrackingControl : public DynamicsControl
{
public:
	TrackingControl(double gravity[3], double dt = 0.01,  double fsi = .0, double fvi = .0);
	virtual ~TrackingControl(void);

protected:
	int controlMode;
	double Ki;
	double Kd;

public:
	bool SetControlMode(int controlMode);
	int GetcontrolMode(void);

	bool SetKi(double Ki);
	double GetKi(void);

	bool SetKd(double Kd);
	double GetKd(void);
};
