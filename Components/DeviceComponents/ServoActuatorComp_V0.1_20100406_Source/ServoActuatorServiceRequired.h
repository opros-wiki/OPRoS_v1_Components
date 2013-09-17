#ifndef _ServoActuatorService_REQUIRED_PORT_H
#define _ServoActuatorService_REQUIRED_PORT_H

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
 * ServoActuatorService : public RequiredServicePort
 *
 */
class ServoActuatorServiceRequired : public RequiredServicePort
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

	typedef RequiredMethod<bool> SetVelocityFuncType;
	SetVelocityFuncType *SetVelocityFunc;

	typedef RequiredMethod<double> GetVelocityFuncType;
	GetVelocityFuncType *GetVelocityFunc;

	typedef RequiredMethod<bool> SetPositionFuncType;
	SetPositionFuncType *SetPositionFunc;

	typedef RequiredMethod<double> GetPositionFuncType;
	GetPositionFuncType *GetPositionFunc;

public:
	//
	// Constructor
	//
	ServoActuatorServiceRequired()
	{
		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		SetPowerFunc = NULL;
		GetPowerFunc = NULL;
		SetVelocityFunc = NULL;
		GetVelocityFunc = NULL;
		SetPositionFunc = NULL;
		GetPositionFunc = NULL;

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

	bool SetVelocity(double velocity,unsigned long time)
	{
		assert(SetVelocityFunc != NULL);

		return (*SetVelocityFunc)(velocity,time);
	}

	double GetVelocity()
	{
		assert(GetVelocityFunc != NULL);

		return (*GetVelocityFunc)();
	}

	bool SetPosition(double position,unsigned long time)
	{
		assert(SetPositionFunc != NULL);

		return (*SetPositionFunc)(position,time);
	}

	double GetPosition()
	{
		assert(GetPositionFunc != NULL);

		return (*GetPositionFunc)();
	}

    // generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeRequiredMethod(&ServoActuatorServiceRequired::SetParameter,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ServoActuatorServiceRequired::GetParameter,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ServoActuatorServiceRequired::GetError,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ServoActuatorServiceRequired::SetPower,"SetPower");
		assert(ptr_method != NULL);
		addMethod("SetPower",ptr_method);
		SetPowerFunc = reinterpret_cast<SetPowerFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ServoActuatorServiceRequired::GetPower,"GetPower");
		assert(ptr_method != NULL);
		addMethod("GetPower",ptr_method);
		GetPowerFunc = reinterpret_cast<GetPowerFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ServoActuatorServiceRequired::SetVelocity,"SetVelocity");
		assert(ptr_method != NULL);
		addMethod("SetVelocity",ptr_method);
		SetVelocityFunc = reinterpret_cast<SetVelocityFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ServoActuatorServiceRequired::GetVelocity,"GetVelocity");
		assert(ptr_method != NULL);
		addMethod("GetVelocity",ptr_method);
		GetVelocityFunc = reinterpret_cast<GetVelocityFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ServoActuatorServiceRequired::SetPosition,"SetPosition");
		assert(ptr_method != NULL);
		addMethod("SetPosition",ptr_method);
		SetPositionFunc = reinterpret_cast<SetPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ServoActuatorServiceRequired::GetPosition,"GetPosition");
		assert(ptr_method != NULL);
		addMethod("GetPosition",ptr_method);
		GetPositionFunc = reinterpret_cast<GetPositionFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
