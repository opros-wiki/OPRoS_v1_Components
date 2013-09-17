#ifndef	_INERTIA_MEASUREMENT_UNIT_H_
#define	_INERTIA_MEASUREMENT_UNIT_H_

#include "Sensor.h"

class InertiaMeasurementUnit : public Sensor
{
public:
	InertiaMeasurementUnit(void) { };
	virtual ~InertiaMeasurementUnit(void) { };

public:
	virtual int GetInertiaMeasurementUnitData(vector<ObjectPosture> &inertiaMeasurementUnitData) { return API_NOT_SUPPORTED; };
};

#endif	//	_INERTIA_MEASUREMENT_UNIT_H_
