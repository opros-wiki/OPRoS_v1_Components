#ifndef _BatteryManagementSystemService_PROVIDED_PORT_H
#define _BatteryManagementSystemService_PROVIDED_PORT_H

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
 * IBatteryManagementSystemService
 *
 * The comonent inherits this class and implements methods. 
*/
class IBatteryManagementSystemService
{
public:
	virtual bool SetParameter(Property parameter)=0;
	virtual Property GetParameter()=0;
	virtual int GetError()=0;
	virtual double GetBatteryVoltage()=0;
	virtual vector<double> GetCellVoltage()=0;
};

/*
 * 
 * BatteryManagementSystemService : public ProvidedServicePort
 *
 */
class BatteryManagementSystemServiceProvided
	:public ProvidedServicePort, public IBatteryManagementSystemService
{
protected:
	IBatteryManagementSystemService *pcom;

	typedef ProvidedMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef ProvidedMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef ProvidedMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef ProvidedMethod<double> GetBatteryVoltageFuncType;
	GetBatteryVoltageFuncType *GetBatteryVoltageFunc;

	typedef ProvidedMethod< vector<double> > GetCellVoltageFuncType;
	GetCellVoltageFuncType *GetCellVoltageFunc;

public: // default method
	virtual bool SetParameter(Property parameter)
	{
		assert(SetParameterFunc != NULL);

		return (*SetParameterFunc)(parameter);
	}

	virtual Property GetParameter()
	{
		assert(GetParameterFunc != NULL);

		return (*GetParameterFunc)();
	}

	virtual int GetError()
	{
		assert(GetErrorFunc != NULL);

		return (*GetErrorFunc)();
	}

	virtual double GetBatteryVoltage()
	{
		assert(GetBatteryVoltageFunc != NULL);

		return (*GetBatteryVoltageFunc)();
	}

	virtual vector<double> GetCellVoltage()
	{
		assert(GetCellVoltageFunc != NULL);

		return (*GetCellVoltageFunc)();
	}

public:
	//
	// Constructor
	//
	BatteryManagementSystemServiceProvided(IBatteryManagementSystemService *fn)
	{
		pcom = fn;

		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		GetBatteryVoltageFunc = NULL;
		GetCellVoltageFunc = NULL;

		setup();
	}

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeProvidedMethod(&IBatteryManagementSystemService::SetParameter,pcom,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IBatteryManagementSystemService::GetParameter,pcom,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IBatteryManagementSystemService::GetError,pcom,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IBatteryManagementSystemService::GetBatteryVoltage,pcom,"GetBatteryVoltage");
		assert(ptr_method != NULL);
		addMethod("GetBatteryVoltage",ptr_method);
		GetBatteryVoltageFunc = reinterpret_cast<GetBatteryVoltageFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IBatteryManagementSystemService::GetCellVoltage,pcom,"GetCellVoltage");
		assert(ptr_method != NULL);
		addMethod("GetCellVoltage",ptr_method);
		GetCellVoltageFunc = reinterpret_cast<GetCellVoltageFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
