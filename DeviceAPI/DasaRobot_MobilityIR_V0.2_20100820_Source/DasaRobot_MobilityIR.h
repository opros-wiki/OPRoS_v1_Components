#pragma once

#include "InfraredSensor.h"
#include "UART.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

class DasaRobot_MobilityIR : public InfraredSensor
{
public:
	DasaRobot_MobilityIR(void);
	virtual ~DasaRobot_MobilityIR(void);

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);
	int GetInfraredSensorData(vector<double> &infraredSensorData);

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

	unsigned char DasaRobot_IR_MakeLrc(unsigned char data[], int size);
	unsigned long DasaRobot_IR_Pow(int i, int j);
	void DasaRobot_IR_Str2Int(unsigned char data[], unsigned int distance[]);
	int DasaRobot_IR_SendPack(unsigned char data[], int size);
	int DasaRobot_IR_RecvPack(unsigned char data[]);
	int DasaRobot_IR_SetMode(int mode);
	int DasaRobot_IR_GetSensorValue(double value[], int size);
};
