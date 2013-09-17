#ifndef _GripperService_PROVIDED_PORT_H
#define _GripperService_PROVIDED_PORT_H

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
 * IGripperService
 *
 * The comonent inherits this class and implements methods. 
*/
class IGripperService
{
public:
	virtual bool SetParameter(Property parameter)=0;
	virtual Property GetParameter()=0;
	virtual int GetError()=0;
	virtual bool Stop()=0;
	virtual bool SetPower(vector<double> power,vector<unsigned long> time)=0;
	virtual vector<double> GetPower()=0;
	virtual bool SetVelocity(vector<double> velocity,vector<unsigned long> time)=0;
	virtual vector<double> GetVelocity()=0;
	virtual bool SetPosition(vector<double> position,vector<unsigned long> time)=0;
	virtual vector<double> GetPosition()=0;
	virtual bool StartGripping()=0;
	virtual bool StopGripping()=0;
	virtual bool IsGripped()=0;
};

/*
 * 
 * GripperService : public ProvidedServicePort
 *
 */
class GripperServiceProvided : public ProvidedServicePort, public IGripperService
{
protected:
	IGripperService *pcom;

	typedef ProvidedMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef ProvidedMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef ProvidedMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef ProvidedMethod<bool> StopFuncType;
	StopFuncType *StopFunc;

	typedef ProvidedMethod<bool> SetPowerFuncType;
	SetPowerFuncType *SetPowerFunc;

	typedef ProvidedMethod< vector<double> > GetPowerFuncType;
	GetPowerFuncType *GetPowerFunc;

	typedef ProvidedMethod<bool> SetVelocityFuncType;
	SetVelocityFuncType *SetVelocityFunc;

	typedef ProvidedMethod< vector<double> > GetVelocityFuncType;
	GetVelocityFuncType *GetVelocityFunc;

	typedef ProvidedMethod<bool> SetPositionFuncType;
	SetPositionFuncType *SetPositionFunc;

	typedef ProvidedMethod< vector<double> > GetPositionFuncType;
	GetPositionFuncType *GetPositionFunc;

	typedef ProvidedMethod<bool> StartGrippingFuncType;
	StartGrippingFuncType *StartGrippingFunc;

	typedef ProvidedMethod<bool> StopGrippingFuncType;
	StopGrippingFuncType *StopGrippingFunc;

	typedef ProvidedMethod<bool> IsGrippedFuncType;
	IsGrippedFuncType *IsGrippedFunc;

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

	virtual bool Stop()
	{
		assert(StopFunc != NULL);

		return (*StopFunc)();
	}

	virtual bool SetPower(vector<double> power,vector<unsigned long> time)
	{
		assert(SetPowerFunc != NULL);

		return (*SetPowerFunc)(power,time);
	}

	virtual vector<double> GetPower()
	{
		assert(GetPowerFunc != NULL);

		return (*GetPowerFunc)();
	}

	virtual bool SetVelocity(vector<double> velocity,vector<unsigned long> time)
	{
		assert(SetVelocityFunc != NULL);

		return (*SetVelocityFunc)(velocity,time);
	}

	virtual vector<double> GetVelocity()
	{
		assert(GetVelocityFunc != NULL);

		return (*GetVelocityFunc)();
	}

	virtual bool SetPosition(vector<double> position,vector<unsigned long> time)
	{
		assert(SetPositionFunc != NULL);

		return (*SetPositionFunc)(position,time);
	}

	virtual vector<double> GetPosition()
	{
		assert(GetPositionFunc != NULL);

		return (*GetPositionFunc)();
	}

	virtual bool StartGripping()
	{
		assert(StartGrippingFunc != NULL);

		return (*StartGrippingFunc)();
	}

	virtual bool StopGripping()
	{
		assert(StopGrippingFunc != NULL);

		return (*StopGrippingFunc)();
	}

	virtual bool IsGripped()
	{
		assert(IsGrippedFunc != NULL);

		return (*IsGrippedFunc)();
	}

public:
    //
    // Constructor
    //
	GripperServiceProvided(IGripperService *fn)
	{
		pcom = fn;

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

    // generated setup function
    virtual void setup()
    {
		Method *ptr_method;

		ptr_method = makeProvidedMethod(&IGripperService::SetParameter,pcom,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IGripperService::GetParameter,pcom,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IGripperService::GetError,pcom,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IGripperService::Stop,pcom,"Stop");
		assert(ptr_method != NULL);
		addMethod("Stop",ptr_method);
		StopFunc = reinterpret_cast<StopFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IGripperService::SetPower,pcom,"SetPower");
		assert(ptr_method != NULL);
		addMethod("SetPower",ptr_method);
		SetPowerFunc = reinterpret_cast<SetPowerFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IGripperService::GetPower,pcom,"GetPower");
		assert(ptr_method != NULL);
		addMethod("GetPower",ptr_method);
		GetPowerFunc = reinterpret_cast<GetPowerFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IGripperService::SetVelocity,pcom,"SetVelocity");
		assert(ptr_method != NULL);
		addMethod("SetVelocity",ptr_method);
		SetVelocityFunc = reinterpret_cast<SetVelocityFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IGripperService::GetVelocity,pcom,"GetVelocity");
		assert(ptr_method != NULL);
		addMethod("GetVelocity",ptr_method);
		GetVelocityFunc = reinterpret_cast<GetVelocityFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IGripperService::SetPosition,pcom,"SetPosition");
		assert(ptr_method != NULL);
		addMethod("SetPosition",ptr_method);
		SetPositionFunc = reinterpret_cast<SetPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IGripperService::GetPosition,pcom,"GetPosition");
		assert(ptr_method != NULL);
		addMethod("GetPosition",ptr_method);
		GetPositionFunc = reinterpret_cast<GetPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IGripperService::StartGripping,pcom,"StartGripping");
		assert(ptr_method != NULL);
		addMethod("StartGripping",ptr_method);
		StartGrippingFunc = reinterpret_cast<StartGrippingFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IGripperService::StopGripping,pcom,"StopGripping");
		assert(ptr_method != NULL);
		addMethod("StopGripping",ptr_method);
		StopGrippingFunc = reinterpret_cast<StopGrippingFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IGripperService::IsGripped,pcom,"IsGripped");
		assert(ptr_method != NULL);
		addMethod("IsGripped",ptr_method);
		IsGrippedFunc = reinterpret_cast<IsGrippedFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
