#pragma once

#include "Manipulator.h"
#include "UCMC.h"
#include "CAN.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

class UCMC_Profile : public ManipulatorProfile
{
public:
	UCMC_Profile(void) 
	{
		ucmc = NULL;
		zeroSearchVelocity = 0;
		switchSearchVelocity = 0;
		homeOffset = 0.0;
	}
	virtual ~UCMC_Profile(void)
	{
		if(ucmc != NULL) {
			ucmc->UCMC_ResetVariables();
			delete ucmc;
		}
	}

	UCMC *ucmc;
	short zeroSearchVelocity;
	short switchSearchVelocity;
	double homeOffset;
};

class RND_ModularArm : public Manipulator
{
public:
	RND_ModularArm(void);
	virtual ~RND_ModularArm(void);

protected:
	Property parameter;
	vector<UCMC_Profile> _manipulator;
	CAN *can;
	bool isHome;

#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif

	int InitializeCAN(Property parameter);

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
};

/*	Profile Information
	<property name="APIName" type="string">RND_ModularArm</property>
	<property name="Size" type="int">14</property>
	
	<!-- Left Arm -->
	<property name="ID0" type="long">1</property>
	<property name="MaximumPower0" type="double">0.0</property>
    <property name="LinePerRevolution0" type="double">2048.0</property>
    <property name="ReductionRatio0" type="double">400.0</property>
    <property name="MaximumVelocity0" type="double">45.0</property>
    <property name="Acceleration0" type="double">45.0</property>
    <property name="MinimumPositionLimit0" type="double">-110.0</property>
    <property name="MaximumPositionLimit0" type="double">110.0</property>
    <property name="ZeroSearchVelocity0" type="short">500</property>
    <property name="SwitchSearchVelocity0" type="short">-100</property>
    <property name="HomeOffset0" type="double">0.0</property>
    
    <property name="ID1" type="long">3</property>
    <property name="MaximumPower1" type="double">0.0</property>
    <property name="LinePerRevolution1" type="double">2048.0</property>
    <property name="ReductionRatio1" type="double">400.0</property>
    <property name="MaximumVelocity1" type="double">45.0</property>
    <property name="Acceleration1" type="double">45.0</property>
    <property name="MinimumPositionLimit1" type="double">0.0</property>
    <property name="MaximumPositionLimit1" type="double">150.0</property>
    <property name="ZeroSearchVelocity1" type="short">500</property>
    <property name="SwitchSearchVelocity1" type="short">-100</property>
    <property name="HomeOffset1" type="double">-90.0</property>
    
    <property name="ID2" type="long">5</property>
    <property name="MaximumPower2" type="double">0.0</property>
    <property name="LinePerRevolution2" type="double">2048.0</property>
    <property name="ReductionRatio2" type="double">-400.0</property>
    <property name="MaximumVelocity2" type="double">45.0</property>
    <property name="Acceleration2" type="double">45.0</property>
    <property name="MinimumPositionLimit2" type="double">-100.0</property>
    <property name="MaximumPositionLimit2" type="double">100.0</property>
    <property name="ZeroSearchVelocity2" type="short">500</property>
    <property name="SwitchSearchVelocity2" type="short">-100</property>
    <property name="HomeOffset2" type="double">0.0</property>
    
    <property name="ID3" type="long">7</property>
    <property name="MaximumPower3" type="double">0.0</property>
    <property name="LinePerRevolution3" type="double">2048.0</property>
    <property name="ReductionRatio3" type="double">-400.0</property>
    <property name="MaximumVelocity3" type="double">45.0</property>
    <property name="Acceleration3" type="double">45.0</property>
    <property name="MinimumPositionLimit3" type="double">-100.0</property>
    <property name="MaximumPositionLimit3" type="double">100.0</property>
    <property name="ZeroSearchVelocity3" type="short">500</property>
    <property name="SwitchSearchVelocity3" type="short">-100</property>
    <property name="HomeOffset3" type="double">0.0</property>
    
    <property name="ID4" type="long">9</property>
    <property name="MaximumPower4" type="double">0.0</property>
    <property name="LinePerRevolution4" type="double">2048.0</property>
    <property name="ReductionRatio4" type="double">-400.0</property>
    <property name="MaximumVelocity4" type="double">45.0</property>
    <property name="Acceleration4" type="double">45.0</property>
    <property name="MinimumPositionLimit4" type="double">-100.0</property>
    <property name="MaximumPositionLimit4" type="double">100.0</property>
    <property name="ZeroSearchVelocity4" type="short">-500</property>
    <property name="SwitchSearchVelocity4" type="short">100</property>
    <property name="HomeOffset4" type="double">0.0</property>
    
    <property name="ID5" type="long">11</property>
    <property name="MaximumPower5" type="double">0.0</property>
    <property name="LinePerRevolution5" type="double">2048.0</property>
    <property name="ReductionRatio5" type="double">100.0</property>
    <property name="MaximumVelocity5" type="double">45.0</property>
    <property name="Acceleration5" type="double">45.0</property>
    <property name="MinimumPositionLimit5" type="double">-85.0</property>
    <property name="MaximumPositionLimit5" type="double">85.0</property>
    <property name="ZeroSearchVelocity5" type="short">500</property>
    <property name="SwitchSearchVelocity5" type="short">-100</property>
    <property name="HomeOffset5" type="double">0.0</property>
    
    <property name="ID6" type="long">13</property>
    <property name="MaximumPower6" type="double">0.0</property>
    <property name="LinePerRevolution6" type="double">2048.0</property>
    <property name="ReductionRatio6" type="double">100.0</property>
    <property name="MaximumVelocity6" type="double">45.0</property>
    <property name="Acceleration6" type="double">45.0</property>
    <property name="MinimumPositionLimit6" type="double">-90.0</property>
    <property name="MaximumPositionLimit6" type="double">90.0</property>
    <property name="ZeroSearchVelocity6" type="short">500</property>
    <property name="SwitchSearchVelocity6" type="short">-100</property>
    <property name="HomeOffset6" type="double">0.0</property>
    
    <!-- Right Arm -->
	<property name="ID7" type="long">15</property>
	<property name="MaximumPower7" type="double">0.0</property>
    <property name="LinePerRevolution7" type="double">2048.0</property>
    <property name="ReductionRatio7" type="double">-400.0</property>
    <property name="MaximumVelocity7" type="double">45.0</property>
    <property name="Acceleration7" type="double">45.0</property>
    <property name="MinimumPositionLimit7" type="double">-110.0</property>
    <property name="MaximumPositionLimit7" type="double">110.0</property>
    <property name="ZeroSearchVelocity7" type="short">500</property>
    <property name="SwitchSearchVelocity7" type="short">-100</property>
    <property name="HomeOffset7" type="double">0.0</property>
    
    <property name="ID8" type="long">17</property>
    <property name="MaximumPower8" type="double">0.0</property>
    <property name="LinePerRevolution8" type="double">2048.0</property>
    <property name="ReductionRatio8" type="double">400.0</property>
    <property name="MaximumVelocity8" type="double">45.0</property>
    <property name="Acceleration8" type="double">45.0</property>
    <property name="MinimumPositionLimit8" type="double">-180.0</property>
    <property name="MaximumPositionLimit8" type="double">0.0</property>
    <property name="ZeroSearchVelocity8" type="short">-500</property>
    <property name="SwitchSearchVelocity8" type="short">100</property>
    <property name="HomeOffset8" type="double">90.0</property>
    
    <property name="ID9" type="long">19</property>
    <property name="MaximumPower9" type="double">0.0</property>
    <property name="LinePerRevolution9" type="double">2048.0</property>
    <property name="ReductionRatio9" type="double">-400.0</property>
    <property name="MaximumVelocity9" type="double">45.0</property>
    <property name="Acceleration9" type="double">45.0</property>
    <property name="MinimumPositionLimit9" type="double">-100.0</property>
    <property name="MaximumPositionLimit9" type="double">100.0</property>
    <property name="ZeroSearchVelocity9" type="short">500</property>
    <property name="SwitchSearchVelocity9" type="short">-100</property>
    <property name="HomeOffset9" type="double">0.0</property>
    
    <property name="ID10" type="long">21</property>
    <property name="MaximumPower10" type="double">0.0</property>
    <property name="LinePerRevolution10" type="double">2048.0</property>
    <property name="ReductionRatio10" type="double">400.0</property>
    <property name="MaximumVelocity10" type="double">45.0</property>
    <property name="Acceleration10" type="double">45.0</property>
    <property name="MinimumPositionLimit10" type="double">-100.0</property>
    <property name="MaximumPositionLimit10" type="double">100.0</property>
    <property name="ZeroSearchVelocity10" type="short">-500</property>
    <property name="SwitchSearchVelocity10" type="short">100</property>
    <property name="HomeOffset10" type="double">0.0</property>
    
    <property name="ID11" type="long">23</property>
    <property name="MaximumPower11" type="double">0.0</property>
    <property name="LinePerRevolution11" type="double">2048.0</property>
    <property name="ReductionRatio11" type="double">-400.0</property>
    <property name="MaximumVelocity11" type="double">45.0</property>
    <property name="Acceleration11" type="double">45.0</property>
    <property name="MinimumPositionLimit11" type="double">-100.0</property>
    <property name="MaximumPositionLimit11" type="double">100.0</property>
    <property name="ZeroSearchVelocity11" type="short">-500</property>
    <property name="SwitchSearchVelocity11" type="short">100</property>
    <property name="HomeOffset11" type="double">0.0</property>
    
    <property name="ID12" type="long">25</property>
    <property name="MaximumPower12" type="double">0.0</property>
    <property name="LinePerRevolution12" type="double">2048.0</property>
    <property name="ReductionRatio12" type="double">-100.0</property>
    <property name="MaximumVelocity12" type="double">45.0</property>
    <property name="Acceleration12" type="double">45.0</property>
    <property name="MinimumPositionLimit12" type="double">-85.0</property>
    <property name="MaximumPositionLimit12" type="double">85.0</property>
    <property name="ZeroSearchVelocity12" type="short">500</property>
    <property name="SwitchSearchVelocity12" type="short">-100</property>
    <property name="HomeOffset12" type="double">0.0</property>
    
    <property name="ID13" type="long">27</property>
    <property name="MaximumPower13" type="double">0.0</property>
    <property name="LinePerRevolution13" type="double">2048.0</property>
    <property name="ReductionRatio13" type="double">100.0</property>
    <property name="MaximumVelocity13" type="double">45.0</property>
    <property name="Acceleration13" type="double">45.0</property>
    <property name="MinimumPositionLimit13" type="double">-90.0</property>
    <property name="MaximumPositionLimit13" type="double">90.0</property>
    <property name="ZeroSearchVelocity13" type="short">500</property>
    <property name="SwitchSearchVelocity13" type="short">-100</property>
    <property name="HomeOffset13" type="double">0.0</property>
    
    <property name="CANAPIName" type="string">Kvaser_CAN.dll</property>
	<property name="TimeOut" type="unsigned long">30</property>
	<property name="Channel" type="int">0</property>
	<property name="BitRate" type="unsigned long">1000000</property>
	<property name="AcceptanceMask" type="unsigned long">0</property>
	<property name="AcceptanceCode" type="unsigned long">0</property>
	<property name="Mode" type="int">0</property>
*/