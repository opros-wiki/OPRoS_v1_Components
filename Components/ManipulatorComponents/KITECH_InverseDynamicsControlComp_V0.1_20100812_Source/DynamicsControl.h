#pragma once

#include "LagrangeDynamics.h"

class DynamicsControl : public CLagrangeDynamics
{
public:
	DynamicsControl(double gravity[3], double dt = 0.01, double fsi = .0, double fvi = .0);
	virtual ~DynamicsControl(void);

protected:
	double dt;

	double maximumAcceleration;
	double maximumVelocity;
	double minimumPosition;
	double maximumPosition;

	void CalculateVelocityPosition(void);

public:
	bool SetMaximumAcceleration(double maximumAcceleration);
	double GetMaximumAcceleration(void);
	bool SetMaximumVelocity(double maximumVelocity);
	double GetMaximumVelocity(void);
	bool SetMinimumPosition(double minimumPosition);
	double GetMinimumPosition(void);
	bool SetMaximumPosition(double maximumPosition);
	double GetMaximumPosition(void);

	bool SetJointAcceleration(vector<double> jointAcceleration);
	vector<double> GetJointAcceleration(void);

	bool SetJointVelocity(vector<double> jointVelocity);
	vector<double> GetJointVelocity(void);

	bool SetJointPosition(vector<double> jointPosition);
	vector<double> GetJointPosition(void);

	bool SetDesiredJointAcceleration(vector<double> desiredJointAcceleration);
	vector<double> GetDesiredJointAcceleration(void);

	bool SetDesiredJointVelocity(vector<double> desiredJointVelocity);
	vector<double> GetDesiredJointVelocity(void);

	bool SetDesiredJointPosition(vector<double> desiredJointPosition);
	vector<double> GetDesiredJointPosition(void);
};
