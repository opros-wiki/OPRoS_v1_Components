#include "DynamicsControl.h"

#ifndef M_PI
#define M_PI		3.14159265358979323846	// pi 
#endif

DynamicsControl::DynamicsControl(double gravity[3], double dt, double fsi, double fvi)
:CLagrangeDynamics(gravity, fsi, fvi)
{
	this->dt = dt;
	maximumAcceleration = M_PI*100;
	maximumVelocity = M_PI*10;
	minimumPosition = -M_PI;
	maximumPosition = M_PI;
}

DynamicsControl::~DynamicsControl(void)
{
	
}

bool DynamicsControl::SetMaximumAcceleration(double maximumAcceleration)
{
	if(maximumAcceleration <= 0) {
		return false;
	}

	this->maximumAcceleration = maximumAcceleration;

	return true;
}

double DynamicsControl::GetMaximumAcceleration(void)
{
	return maximumAcceleration;
}

bool DynamicsControl::SetMaximumVelocity(double maximumVelocity)
{
	if(maximumVelocity <= 0) {
		return false;
	}

	this->maximumVelocity = maximumVelocity;

	return true;
}

double DynamicsControl::GetMaximumVelocity(void)
{
	return maximumVelocity;
}

bool DynamicsControl::SetMinimumPosition(double minimumPosition)
{
	if(minimumPosition >= 0) {
		return false;
	}

	this->minimumPosition = minimumPosition;

	return true;
}

double DynamicsControl::GetMinimumPosition(void)
{
	return minimumPosition;
}

bool DynamicsControl::SetMaximumPosition(double maximumPosition)
{
	if(maximumPosition <= 0) {
		return false;
	}

	this->maximumPosition = maximumPosition;

	return true;
}

double DynamicsControl::GetMaximumPosition(void)
{
	return maximumPosition;
}

bool DynamicsControl::SetJointAcceleration(vector<double> jointAcceleration)
{
	if(jointAcceleration.size() != _jointList.size()) {
		return false;
	}

	for(size_t i = 0; i < _jointList.size(); i++) {
		_q2dot[i] = jointAcceleration[i];
	}

	return true;
}

vector<double> DynamicsControl::GetJointAcceleration(void)
{
	vector<double> jointAcceleration(_jointList.size());

	for(size_t i = 0; i < _jointList.size(); i++) {
		jointAcceleration[i] = _q2dot[i];
	}

	return jointAcceleration;
}

bool DynamicsControl::SetJointVelocity(vector<double> jointVelocity)
{
	if(jointVelocity.size() != _jointList.size()) {
		return false;
	}

	for(size_t i = 0; i < _jointList.size(); i++) {
		_qdot[i] = jointVelocity[i];
	}

	return true;
}

vector<double> DynamicsControl::GetJointVelocity(void)
{
	vector<double> jointVelocity(_jointList.size());

	for(size_t i = 0; i < _jointList.size(); i++) {
		jointVelocity[i] = _qdot[i];
	}

	return jointVelocity;
}

bool DynamicsControl::SetJointPosition(vector<double> jointPosition)
{
	if(jointPosition.size() != _jointList.size()) {
		return false;
	}

	for(size_t i = 0; i < _jointList.size(); i++) {
		_q[i] = jointPosition[i];
	}

	return true;
}

vector<double> DynamicsControl::GetJointPosition(void)
{
	vector<double> jointPosition(_jointList.size());

	for(size_t i = 0; i < _jointList.size(); i++) {
		jointPosition[i] = _q[i];
	}

	return jointPosition;
}

bool DynamicsControl::SetDesiredJointAcceleration(vector<double> jointDesiredAcceleration)
{
	if(jointDesiredAcceleration.size() != _jointList.size()) {
		return false;
	}

	for(size_t i = 0; i < _jointList.size(); i++) {
		_q2dotd[i] = jointDesiredAcceleration[i];
	}

	return true;
}

vector<double> DynamicsControl::GetDesiredJointAcceleration(void)
{
	vector<double> jointDesiredAcceleration(_jointList.size());

	for(size_t i = 0; i < _jointList.size(); i++) {
		jointDesiredAcceleration[i] = _q2dotd[i];
	}

	return jointDesiredAcceleration;
}

bool DynamicsControl::SetDesiredJointVelocity(vector<double> jointDesiredVelocity)
{
	if(jointDesiredVelocity.size() != _jointList.size()) {
		return false;
	}

	for(size_t i = 0; i < _jointList.size(); i++) {
		_qdotd[i] = jointDesiredVelocity[i];
	}

	return true;
}

vector<double> DynamicsControl::GetDesiredJointVelocity(void)
{
	vector<double> jointDesiredVelocity(_jointList.size());

	for(size_t i = 0; i < _jointList.size(); i++) {
		jointDesiredVelocity[i] = _qdotd[i];
	}

	return jointDesiredVelocity;
}

bool DynamicsControl::SetDesiredJointPosition(vector<double> jointDesiredPosition)
{
	if(jointDesiredPosition.size() != _jointList.size()) {
		return false;
	}

	for(size_t i = 0; i < _jointList.size(); i++) {
		_qd[i] = jointDesiredPosition[i];
	}

	return true;
}

vector<double> DynamicsControl::GetDesiredJointPosition(void)
{
	vector<double> jointDesiredPosition(_jointList.size());

	for(size_t i = 0; i < _jointList.size(); i++) {
		jointDesiredPosition[i] = _qd[i];
	}

	return jointDesiredPosition;
}

void DynamicsControl::CalculateVelocityPosition(void)
{
	for (size_t i = 0; i < _jointList.size (); i++) {
		//	가속도 제한 체크
		if(_q2dot(i, 0) > maximumAcceleration) {
			_q2dot(i, 0) = maximumAcceleration;
		}
		else if(_q2dot(i, 0) < -maximumAcceleration) {
			_q2dot(i, 0) = -maximumAcceleration;
		}
		_jointList[i]->ddq = _q2dot[i];


		//	속도 제한 체크
		_qdot[i] += dt*_jointList[i]->ddq;

		if(_qdot(i, 0) > maximumVelocity) {
			_qdot(i, 0) = maximumVelocity;
		}
		else if(_qdot(i, 0) < -maximumVelocity) {
			_qdot(i, 0) = -maximumVelocity;
		}
		
		_jointList[i]->dq = _qdot[i];

		//	위치 제한 체크
		_q[i] += dt*_jointList[i]->dq;

		if(_q(i, 0) > maximumPosition) {
			_q(i, 0) = maximumPosition;
		}
		else if(_q(i, 0) < minimumPosition) {
			_q(i, 0) = minimumPosition;
		}
		
		_jointList[i]->q = _q[i];
	}
}