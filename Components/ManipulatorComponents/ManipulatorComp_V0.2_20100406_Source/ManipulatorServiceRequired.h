#ifndef _ManipulatorService_REQUIRED_PORT_H
#define _ManipulatorService_REQUIRED_PORT_H

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
 * ManipulatorService : public RequiredServicePort
 *
 */
class ManipulatorServiceRequired : public RequiredServicePort
{
protected:
	typedef RequiredMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef RequiredMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef RequiredMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef RequiredMethod<bool> StopFuncType;
	StopFuncType *StopFunc;

	typedef RequiredMethod<bool> SetPowerFuncType;
	SetPowerFuncType *SetPowerFunc;

	typedef RequiredMethod< vector<double> > GetPowerFuncType;
	GetPowerFuncType *GetPowerFunc;

	typedef RequiredMethod<bool> SetVelocityFuncType;
	SetVelocityFuncType *SetVelocityFunc;

	typedef RequiredMethod< vector<double> > GetVelocityFuncType;
	GetVelocityFuncType *GetVelocityFunc;

	typedef RequiredMethod<bool> SetPositionFuncType;
	SetPositionFuncType *SetPositionFunc;

	typedef RequiredMethod< vector<double> > GetPositionFuncType;
	GetPositionFuncType *GetPositionFunc;

public:
	//
	// Constructor
	//
	ManipulatorServiceRequired()
	{
		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		StopFunc = NULL;
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

	bool Stop()
	{
		assert(StopFunc != NULL);

		return (*StopFunc)();
	}

	bool SetPower(vector<double> power,vector<unsigned long> time)
	{
		assert(SetPowerFunc != NULL);

		return (*SetPowerFunc)(power,time);
	}

	vector<double> GetPower()
	{
		assert(GetPowerFunc != NULL);

		return (*GetPowerFunc)();
	}

	bool SetVelocity(vector<double> velocity,vector<unsigned long> time)
	{
		assert(SetVelocityFunc != NULL);

		return (*SetVelocityFunc)(velocity,time);
	}

	vector<double> GetVelocity()
	{
		assert(GetVelocityFunc != NULL);

		return (*GetVelocityFunc)();
	}

	bool SetPosition(vector<double> position,vector<unsigned long> time)
	{
		assert(SetPositionFunc != NULL);

		return (*SetPositionFunc)(position,time);
	}

	vector<double> GetPosition()
	{
		assert(GetPositionFunc != NULL);

		return (*GetPositionFunc)();
	}

    // generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeRequiredMethod(&ManipulatorServiceRequired::SetParameter,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ManipulatorServiceRequired::GetParameter,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ManipulatorServiceRequired::GetError,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ManipulatorServiceRequired::Stop,"Stop");
		assert(ptr_method != NULL);
		addMethod("Stop",ptr_method);
		StopFunc = reinterpret_cast<StopFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ManipulatorServiceRequired::SetPower,"SetPower");
		assert(ptr_method != NULL);
		addMethod("SetPower",ptr_method);
		SetPowerFunc = reinterpret_cast<SetPowerFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ManipulatorServiceRequired::GetPower,"GetPower");
		assert(ptr_method != NULL);
		addMethod("GetPower",ptr_method);
		GetPowerFunc = reinterpret_cast<GetPowerFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ManipulatorServiceRequired::SetVelocity,"SetVelocity");
		assert(ptr_method != NULL);
		addMethod("SetVelocity",ptr_method);
		SetVelocityFunc = reinterpret_cast<SetVelocityFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ManipulatorServiceRequired::GetVelocity,"GetVelocity");
		assert(ptr_method != NULL);
		addMethod("GetVelocity",ptr_method);
		GetVelocityFunc = reinterpret_cast<GetVelocityFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ManipulatorServiceRequired::SetPosition,"SetPosition");
		assert(ptr_method != NULL);
		addMethod("SetPosition",ptr_method);
		SetPositionFunc = reinterpret_cast<SetPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ManipulatorServiceRequired::GetPosition,"GetPosition");
		assert(ptr_method != NULL);
		addMethod("GetPosition",ptr_method);
		GetPositionFunc = reinterpret_cast<GetPositionFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
