#ifndef	_ManipulATOR_H_
#define	_ManipulATOR_H_

#include "Device.h"
#include "ServoActuator.h"

class ManipulatorProfile : public ServoActuatorProfile
{
public:
	ManipulatorProfile(void)
	{
	}
	virtual ~ManipulatorProfile(void) { };
};

class Manipulator : public Device
{
public:
	Manipulator(void) { };
	virtual ~Manipulator(void) { };

public:
	virtual int StartHoming(void) { return API_NOT_SUPPORTED; }
	virtual int Stop(void) { return API_NOT_SUPPORTED; }
	virtual int EmergencyStop(void) { return API_NOT_SUPPORTED; }
	virtual int SetPower(vector<double> power, vector<unsigned long> time) { return API_NOT_SUPPORTED; }
	virtual int GetPower(vector<double> &power) { return API_NOT_SUPPORTED; }
	virtual int SetVelocity(vector<double> velocity, vector<unsigned long> time) { return API_NOT_SUPPORTED; }
	virtual int GetVelocity(vector<double> &velocity) { return API_NOT_SUPPORTED; }
	virtual int SetPosition(vector<double> position, vector<unsigned long> time) { return API_NOT_SUPPORTED; }
	virtual int GetPosition(vector<double> &position) { return API_NOT_SUPPORTED; }
};


#endif	//	_ManipulATOR_H_
