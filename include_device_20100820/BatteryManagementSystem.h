#ifndef	_BATTERY_MANAGEMENT_SYSTEM_H_
#define	_BATTERY_MANAGEMENT_SYSTEM_H_

#include "Sensor.h"

class BatteryManagementSystem : public Sensor
{
public:
	BatteryManagementSystem(void) { };
	virtual ~BatteryManagementSystem(void) { };

public:
	virtual int GetBatteryVoltage(double &batteryVoltage) { return API_NOT_SUPPORTED; };
	virtual int GetCellVoltage(vector<double> &cellVoltage) { return API_NOT_SUPPORTED; };
};

#endif	//	_BATTERY_MANAGEMENT_SYSTEM_H_