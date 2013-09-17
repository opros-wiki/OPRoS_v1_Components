#pragma once

#include "Manipulator.h"
#include "HRC01.h"

class CNRobot_HRB_MTC_B10_Profile : public ManipulatorProfile
{
public:
	CNRobot_HRB_MTC_B10_Profile(void) 
	{
		encoder = 0.0;
		reductionRatio = 0.0;

		kp = 0;
		ki = 0;
		kd = 0;
		iSum = 0;
	}
	virtual ~CNRobot_HRB_MTC_B10_Profile(void) { }

public:
	double encoder;
	double reductionRatio;

	unsigned short kp;
	unsigned short ki;
	unsigned short kd;
	unsigned short iSum;
};

class CNRobot_HRB_MTC_B10 : public Manipulator
{
public:
	CNRobot_HRB_MTC_B10(void);
	virtual ~CNRobot_HRB_MTC_B10(void);

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);

	int StartHoming(void);
	int Stop(void);
	int EmergencyStop(void);
	int SetPower(vector<double> power, vector<unsigned long> time);
	int GetPower(vector<double> &power);
	int SetVelocity(vector<double> velocity, vector<unsigned long> time);
	int GetVelocity(vector<double> &velocity);
	int SetPosition(vector<double> position, vector<unsigned long> time);
	int GetPosition(vector<double> &position);

protected:
	Property parameter;
	vector<CNRobot_HRB_MTC_B10_Profile> _profile;
	
	HRC01 *_hcr01;
	bool isOpened;

	int SetupParameters(void);
};

/*	Profile Example
	<property name="APIName" type="string">CNRobot_HRB-MTC-B10.dll</property>
    <property name="Size" type="int">3</property>
    <property name="MaximumPower0" type="double">1.0</property>
    <property name="LinePerRevolution0" type="double">104.0</property>
    <property name="ReductionRatio0" type="double">51.0</property>
    <property name="MaximumVelocity0" type="double">360.0</property>
    <property name="Acceleration0" type="double">360.0</property>
    <property name="MinimumPositionLimit0" type="double">-1000000.0</property>
    <property name="MaximumPositionLimit0" type="double">1000000.0</property>
    
    <property name="Kp0" type="unsigned short">100</property>
    <property name="Ki0" type="unsigned short">0</property>
    <property name="Kd0" type="unsigned short">400</property>
    <property name="ISum0" type="unsigned short">1000</property>
    
    
    <property name="MaximumPower1" type="double">1.0</property>
    <property name="LinePerRevolution1" type="double">104.0</property>
    <property name="ReductionRatio1" type="double">51.0</property>
    <property name="MaximumVelocity1" type="double">360.0</property>
    <property name="Acceleration1" type="double">360.0</property>
    <property name="MinimumPositionLimit1" type="double">-1000000.0</property>
    <property name="MaximumPositionLimit1" type="double">1000000.0</property>
    
    <property name="Kp1" type="unsigned short">100</property>
    <property name="Ki1" type="unsigned short">0</property>
    <property name="Kd1" type="unsigned short">400</property>
    <property name="ISum1" type="unsigned short">1000</property>
    
    
    <property name="MaximumPower2" type="double">1.0</property>
    <property name="LinePerRevolution2" type="double">104.0</property>
    <property name="ReductionRatio2" type="double">51.0</property>
    <property name="MaximumVelocity2" type="double">360.0</property>
    <property name="Acceleration2" type="double">360.0</property>
    <property name="MinimumPositionLimit2" type="double">-1000000.0</property>
    <property name="MaximumPositionLimit2" type="double">1000000.0</property>
    
    <property name="Kp2" type="unsigned short">100</property>
    <property name="Ki2" type="unsigned short">0</property>
    <property name="Kd2" type="unsigned short">400</property>
    <property name="ISum2" type="unsigned short">1000</property>
*/
