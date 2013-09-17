#ifndef _BatteryManagementSystemService_REQUIRED_PORT_H
#define _BatteryManagementSystemService_REQUIRED_PORT_H

#include <OPRoSTypes.h>
#include <InputDataPort.h>
#include <OutputDataPort.h>
#include <InputEventPort.h>
#include <OutputEventPort.h>
#include <ProvidedServicePort.h>
#include <RequiredServicePort.h>
#include <ProvidedMethod.h>
#include <RequiredMethod.h>

#include "Property.h"
#include "ApiTypes.h"

/*
 * 
 * BatteryManagementSystemService : public RequiredServicePort
 *
 */
class BatteryManagementSystemServiceRequired
   :public RequiredServicePort
{
protected:
	typedef RequiredMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef RequiredMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef RequiredMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef RequiredMethod<double> GetBatteryVoltageFuncType;
	GetBatteryVoltageFuncType *GetBatteryVoltageFunc;

	typedef RequiredMethod< vector<double> > GetCellVoltageFuncType;
	GetCellVoltageFuncType *GetCellVoltageFunc;

public:
	//
	// Constructor
	//
	BatteryManagementSystemServiceRequired()
	{
		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		GetBatteryVoltageFunc = NULL;
		GetCellVoltageFunc = NULL;

		setup();
	}

	// method implementation for required method
	bool SetParameter(Property parameter)
	{
		assert(SetParameterFunc != NULL);

		return (*SetParameterFunc)(parameter);
	}

	Property GetParameter()
	{
		assert(GetParameterFunc != NULL);

		return (*GetParameterFunc)();
	}

	int GetError()
	{
		assert(GetErrorFunc != NULL);

		return (*GetErrorFunc)();
	}

	double GetBatteryVoltage()
	{
		assert(GetBatteryVoltageFunc != NULL);

		return (*GetBatteryVoltageFunc)();
	}

	vector<double> GetCellVoltage()
	{
		assert(GetCellVoltageFunc != NULL);

		return (*GetCellVoltageFunc)();
	}

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeRequiredMethod(&BatteryManagementSystemServiceRequired::SetParameter,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&BatteryManagementSystemServiceRequired::GetParameter,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&BatteryManagementSystemServiceRequired::GetError,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&BatteryManagementSystemServiceRequired::GetBatteryVoltage,"GetBatteryVoltage");
		assert(ptr_method != NULL);
		addMethod("GetBatteryVoltage",ptr_method);
		GetBatteryVoltageFunc = reinterpret_cast<GetBatteryVoltageFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&BatteryManagementSystemServiceRequired::GetCellVoltage,"GetCellVoltage");
		assert(ptr_method != NULL);
		addMethod("GetCellVoltage",ptr_method);
		GetCellVoltageFunc = reinterpret_cast<GetCellVoltageFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
