#ifndef _ActuatorService_REQUIRED_PORT_H
#define _ActuatorService_REQUIRED_PORT_H

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

/*
 * 
 * ActuatorService : public RequiredServicePort
 *
 */
class ActuatorServiceRequired : public RequiredServicePort
{
protected:
	typedef RequiredMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef RequiredMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef RequiredMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef RequiredMethod<bool> SetPowerFuncType;
	SetPowerFuncType *SetPowerFunc;

	typedef RequiredMethod<double> GetPowerFuncType;
	GetPowerFuncType *GetPowerFunc;

public:
	//
	// Constructor
	//
	ActuatorServiceRequired()
	{
		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		SetPowerFunc = NULL;
		GetPowerFunc = NULL;

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

	bool SetPower(double power,unsigned long time)
	{
		assert(SetPowerFunc != NULL);

		return (*SetPowerFunc)(power,time);
	}

	double GetPower()
	{
		assert(GetPowerFunc != NULL);

		return (*GetPowerFunc)();
	}

    // generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeRequiredMethod(&ActuatorServiceRequired::SetParameter,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ActuatorServiceRequired::GetParameter,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ActuatorServiceRequired::GetError,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ActuatorServiceRequired::SetPower,"SetPower");
		assert(ptr_method != NULL);
		addMethod("SetPower",ptr_method);
		SetPowerFunc = reinterpret_cast<SetPowerFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ActuatorServiceRequired::GetPower,"GetPower");
		assert(ptr_method != NULL);
		addMethod("GetPower",ptr_method);
		GetPowerFunc = reinterpret_cast<GetPowerFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
