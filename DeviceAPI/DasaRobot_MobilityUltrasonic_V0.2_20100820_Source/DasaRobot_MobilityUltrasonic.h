#pragma once

#include "UltrasonicSensor.h"
#include "UART.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

class DasaRobot_MobilityUltrasonic : public UltrasonicSensor
{
public:
	DasaRobot_MobilityUltrasonic(void);
	virtual ~DasaRobot_MobilityUltrasonic(void);

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);
	int GetUltrasonicSensorData(vector<double> &ultrasonicSensorData);

private:
	Property parameter;
	UART *uart;

	vector<double> cellsVoltage;
	double minimumVoltageLimit;
	double maximumVoltageLimit;
	double minimumCellVoltageLimit;
	double maximumCellVoltageLimit;

#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif

	int InitializeUART(Property parameter);

	unsigned char DasaRobot_Ultrasonic_MakeLrc(unsigned char data[], int size);
	unsigned long DasaRobot_Ultrasonic_Pow(int i, int j);
	void DasaRobot_Ultrasonic_Str2Int(unsigned char data[], unsigned int distance[]);
	int DasaRobot_Ultrasonic_SendPack(unsigned char data[], int size);
	int DasaRobot_Ultrasonic_RecvPack(unsigned char data[]);
	int DasaRobot_Ultrasonic_SetMode(int mode);
	int DasaRobot_Ultrasonic_GetSensorValue(double value[], int size);
};
