#pragma once

#include "BatteryManagementSystem.h"
#include "UART.h"
#include "OprosLock.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

class Kokam_BMS : public BatteryManagementSystem
{
public:
	Kokam_BMS(void);
	virtual ~Kokam_BMS(void);

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);
	int GetBatteryVoltage(double &batteryVoltage);
	int GetCellVoltage(vector<double> &cellVoltage);

private:
	Property parameter;
	UART *uart;
	OprosLock lock;

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

	boost::thread *pThread;
	bool threadOn;
	void ThreadFunc();

	int InitializeUART(Property parameter);

	int recv_packet (unsigned char *buff, int len);
	unsigned char ChkSum (unsigned char *pBuff, int size);
	int FourAscii2Int (unsigned char *ascii);
	int GetRawValue (int cell, double *measure);
};
