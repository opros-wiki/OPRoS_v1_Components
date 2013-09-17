#pragma once

#include "UltrasonicSensor.h"
#include "I2C.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

class Devantech_SRF08 : public UltrasonicSensor
{
public:
	Devantech_SRF08(void);
	virtual ~Devantech_SRF08(void);

	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);

	int GetUltrasonicSensorData(vector<double> &ultrasonicSensorData);

private:
	Property parameter;
	I2C *_i2c;

#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif

	int InitializeI2C(Property parameter);
	int FinalizeI2C(void);
};

/*	Profile
	<property name="APIName" type="string">Devantech_SRF08.dll</property>
    <property name="Size" type="int">1</property>
    <property name="X0" type="double">0.0</property>
    <property name="Y0" type="double">0.0</property>
    <property name="Z0" type="double">0.0</property>
    <property name="Roll0" type="double">0.0</property>
    <property name="Pitch0" type="double">0.0</property>
    <property name="Yaw0" type="double">0.0</property>
    
    <property name="I2CAPIName" type="string">Devantech_USBtoI2C.dll</property>
    <property name="AddressMode" type="int">0</property>
    
    <property name="UARTAPIName" type="string">SerialCommunication.dll</property>
    <property name="PortName" type="string">COM3</property>
    <property name="TimeOut" type="int">100</property>
    <property name="BaudRate" type="int">19200</property>
    <property name="DataBits" type="int">8</property>
    <property name="StopBits" type="int">0</property>
    <property name="Parity" type="int">0</property>
    <property name="FlowControl" type="int">0</property>
*/