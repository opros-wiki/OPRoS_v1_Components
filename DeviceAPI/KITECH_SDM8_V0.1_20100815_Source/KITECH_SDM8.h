#pragma once

#include "Manipulator.h"
#include "UART.h"
#include "RobotisDynamixelUART.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

class DynamixelProfile : public ManipulatorProfile
{
public:
	DynamixelProfile(void)
	{
		dynamixel = NULL;
	}
	virtual ~DynamixelProfile(void)
	{
		if(dynamixel != NULL) {
			delete dynamixel;
			dynamixel = NULL;
		}
	}

public:
	RobotisDynamixelUART *dynamixel;

	int id;
	double deg2rpm;
	double deg2pulse;
};

class KITECH_SDM8 : public Manipulator
{
public:
	KITECH_SDM8(void);
	virtual ~KITECH_SDM8(void);

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

	virtual int SetPower(vector<double> power, vector<unsigned long> time) { return API_NOT_SUPPORTED; }
	virtual int GetPower(vector<double> &power) { return API_NOT_SUPPORTED; }
	virtual int SetVelocity(vector<double> velocity, vector<unsigned long> time) { return API_NOT_SUPPORTED; }
	virtual int GetVelocity(vector<double> &velocity) { return API_NOT_SUPPORTED; }

	int SetPosition(vector<double> position, vector<unsigned long> time);
	int GetPosition(vector<double> &position);

private:
#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	UART *uart;
	Property parameter;

	vector<DynamixelProfile> joints;

	int InitializeUART(Property parameter);
	int FinalizeUART(void);
};

/*	Profile
	<property name="APIName" type="string">KITECH_SDM8</property>
  	<property name="Size" type="string">8</property>
  	
  	<property name="ID0" type="int">0</property>
	<property name="MaximumPower0" type="double">1023.0</property>
    <property name="LinePerRevolution0" type="double">1.0</property>
    <property name="ReductionRatio0" type="double">-1.0</property>
    <property name="MaximumVelocity0" type="double">1.0</property>
    <property name="Acceleration0" type="double">1.0</property>
    <property name="MinimumPositionLimit0" type="double">-145.0</property>
    <property name="MaximumPositionLimit0" type="double">145.0</property>
    
    <property name="ID1" type="int">1</property>
	<property name="MaximumPower1" type="double">1023.0</property>
	<property name="LinePerRevolution1" type="double">1.0</property>
    <property name="ReductionRatio1" type="double">1.0</property>
    <property name="MaximumVelocity1" type="double">1.0</property>
    <property name="Acceleration1" type="double">1.0</property>
    <property name="MinimumPositionLimit1" type="double">-35.0</property>
    <property name="MaximumPositionLimit1" type="double">35.0</property>
    
    <property name="ID2" type="int">2</property>
    <property name="MaximumPower2" type="double">1023.0</property>
	<property name="LinePerRevolution2" type="double">1.0</property>
    <property name="ReductionRatio2" type="double">-1.0</property>
    <property name="MaximumVelocity2" type="double">1.0</property>
    <property name="Acceleration2" type="double">1.0</property>
    <property name="MinimumPositionLimit2" type="double">-45.0</property>
    <property name="MaximumPositionLimit2" type="double">45.0</property>
        
	<property name="ID3" type="int">3</property>
	<property name="MaximumPower3" type="double">1023.0</property>
	<property name="LinePerRevolution3" type="double">1.0</property>
    <property name="ReductionRatio3" type="double">-1.0</property>
    <property name="MaximumVelocity3" type="double">1.0</property>
    <property name="Acceleration3" type="double">1.0</property>
    <property name="MinimumPositionLimit3" type="double">-145.0</property>
    <property name="MaximumPositionLimit3" type="double">145.0</property>
    	
	<property name="ID4" type="int">4</property>
	<property name="MaximumPower4" type="double">1023.0</property>
	<property name="LinePerRevolution4" type="double">1.0</property>
    <property name="ReductionRatio4" type="double">1.0</property>
    <property name="MaximumVelocity4" type="double">1.0</property>
    <property name="Acceleration4" type="double">1.0</property>
    <property name="MinimumPositionLimit4" type="double">-90.0</property>
    <property name="MaximumPositionLimit4" type="double">90.0</property>
    
	<property name="ID5" type="int">5</property>
	<property name="MaximumPower5" type="double">1023.0</property>
	<property name="LinePerRevolution5" type="double">1.0</property>
    <property name="ReductionRatio5" type="double">1.0</property>
    <property name="MaximumVelocity5" type="double">1.0</property>
    <property name="Acceleration5" type="double">1.0</property>
    <property name="MinimumPositionLimit5" type="double">-90.0</property>
    <property name="MaximumPositionLimit5" type="double">90.0</property>
    
	<property name="ID6" type="int">6</property>
	<property name="MaximumPower6" type="double">1023.0</property>
	<property name="LinePerRevolution6" type="double">1.0</property>
    <property name="ReductionRatio6" type="double">1.0</property>
    <property name="MaximumVelocity6" type="double">1.0</property>
    <property name="Acceleration6" type="double">1.0</property>
    <property name="MinimumPositionLimit6" type="double">-90.0</property>
    <property name="MaximumPositionLimit6" type="double">90.0</property>
    
	<property name="ID7" type="int">7</property>
	<property name="MaximumPower7" type="double">1023.0</property>
	<property name="LinePerRevolution7" type="double">1.0</property>
    <property name="ReductionRatio7" type="double">1.0</property>
    <property name="MaximumVelocity7" type="double">1.0</property>
    <property name="Acceleration7" type="double">1.0</property>
    <property name="MinimumPositionLimit7" type="double">-90.0</property>
    <property name="MaximumPositionLimit7" type="double">90.0</property>
    
	<property name="UARTAPIName" type="string">SerialCommunication.dll</property>
	<property name="PortName" type="string">COM4</property>
	<property name="TimeOut" type="int">2</property>
	<property name="BaudRate" type="int">250000</property>
	<property name="DataBits" type="int">8</property>
	<property name="StopBits" type="int">0</property>
	<property name="Parity" type="int">0</property>
	<property name="FlowControl" type="int">0</property>
*/