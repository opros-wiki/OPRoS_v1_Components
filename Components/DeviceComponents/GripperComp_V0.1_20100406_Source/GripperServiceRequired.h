#ifndef _GripperService_REQUIRED_PORT_H
#define _GripperService_REQUIRED_PORT_H

#include <OPRoSTypes.h>
#include <InputDataPort.h>
#include <OutputDataPort.h>
#include <InputEventPort.h>
#include <OutputEventPort.h>
#include <ProvidedServicePort.h>
#include <RequiredServicePort.h>
#include <ProvidedMethod.h>
#include <RequiredMethod.h>

#include <vector>
#include "Property.h"

using namespace std;

/*
 * 
 * GripperService : public RequiredServicePort
 *
 */
class GripperServiceRequired : public RequiredServicePort
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

	typedef RequiredMethod<vector<double>> GetPowerFuncType;
	GetPowerFuncType *GetPowerFunc;

	typedef RequiredMethod<bool> SetVelocityFuncType;
	SetVelocityFuncType *SetVelocityFunc;

	typedef RequiredMethod<vector<double>> GetVelocityFuncType;
	GetVelocityFuncType *GetVelocityFunc;

	typedef RequiredMethod<bool> SetPositionFuncType;
	SetPositionFuncType *SetPositionFunc;

	typedef RequiredMethod<vector<double>> GetPositionFuncType;
	GetPositionFuncType *GetPositionFunc;

	typedef RequiredMethod<bool> StartGrippingFuncType;
	StartGrippingFuncType *StartGrippingFunc;

	typedef RequiredMethod<bool> StopGrippingFuncType;
	StopGrippingFuncType *StopGrippingFunc;

	typedef RequiredMethod<bool> IsGrippedFuncType;
	IsGrippedFuncType *IsGrippedFunc;

public:
	//
	// Constructor
	//
	GripperServiceRequired()
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
		StartGrippingFunc = NULL;
		StopGrippingFunc = NULL;
		IsGrippedFunc = NULL;

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

	bool StartGripping()
	{
		assert(StartGrippingFunc != NULL);

		return (*StartGrippingFunc)();
	}

	bool StopGripping()
	{
		assert(StopGrippingFunc != NULL);

		return (*StopGrippingFunc)();
	}

	bool IsGripped()
	{
		assert(IsGrippedFunc != NULL);

		return (*IsGrippedFunc)();
	}

    // generated setup function
    virtual void setup()
    {
		Method *ptr_method;

		ptr_method = makeRequiredMethod(&GripperServiceRequired::SetParameter,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&GripperServiceRequired::GetParameter,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&GripperServiceRequired::GetError,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&GripperServiceRequired::Stop,"Stop");
		assert(ptr_method != NULL);
		addMethod("Stop",ptr_method);
		StopFunc = reinterpret_cast<StopFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&GripperServiceRequired::SetPower,"SetPower");
		assert(ptr_method != NULL);
		addMethod("SetPower",ptr_method);
		SetPowerFunc = reinterpret_cast<SetPowerFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&GripperServiceRequired::GetPower,"GetPower");
		assert(ptr_method != NULL);
		addMethod("GetPower",ptr_method);
		GetPowerFunc = reinterpret_cast<GetPowerFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&GripperServiceRequired::SetVelocity,"SetVelocity");
		assert(ptr_method != NULL);
		addMethod("SetVelocity",ptr_method);
		SetVelocityFunc = reinterpret_cast<SetVelocityFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&GripperServiceRequired::GetVelocity,"GetVelocity");
		assert(ptr_method != NULL);
		addMethod("GetVelocity",ptr_method);
		GetVelocityFunc = reinterpret_cast<GetVelocityFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&GripperServiceRequired::SetPosition,"SetPosition");
		assert(ptr_method != NULL);
		addMethod("SetPosition",ptr_method);
		SetPositionFunc = reinterpret_cast<SetPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&GripperServiceRequired::GetPosition,"GetPosition");
		assert(ptr_method != NULL);
		addMethod("GetPosition",ptr_method);
		GetPositionFunc = reinterpret_cast<GetPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&GripperServiceRequired::StartGripping,"StartGripping");
		assert(ptr_method != NULL);
		addMethod("StartGripping",ptr_method);
		StartGrippingFunc = reinterpret_cast<StartGrippingFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&GripperServiceRequired::StopGripping,"StopGripping");
		assert(ptr_method != NULL);
		addMethod("StopGripping",ptr_method);
		StopGrippingFunc = reinterpret_cast<StopGrippingFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&GripperServiceRequired::IsGripped,"IsGripped");
		assert(ptr_method != NULL);
		addMethod("IsGripped",ptr_method);
		IsGrippedFunc = reinterpret_cast<IsGrippedFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
