#ifndef _ServoActuatorService_PROVIDED_PORT_H
#define _ServoActuatorService_PROVIDED_PORT_H

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
 * IServoActuatorService
 *
 * The comonent inherits this class and implements methods. 
*/
class IServoActuatorService
{
public:
	virtual bool SetParameter(Property parameter)=0;
	virtual Property GetParameter()=0;
	virtual int GetError()=0;
	virtual bool SetPower(double power,unsigned long time)=0;
	virtual double GetPower()=0;
	virtual bool SetVelocity(double velocity,unsigned long time)=0;
	virtual double GetVelocity()=0;
	virtual bool SetPosition(double position,unsigned long time)=0;
	virtual double GetPosition()=0;
};

/*
 * 
 * ServoActuatorService : public ProvidedServicePort
 *
 */
class ServoActuatorServiceProvided : public ProvidedServicePort, public IServoActuatorService
{
protected:
	IServoActuatorService *pcom;

	typedef ProvidedMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef ProvidedMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef ProvidedMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef ProvidedMethod<bool> SetPowerFuncType;
	SetPowerFuncType *SetPowerFunc;

	typedef ProvidedMethod<double> GetPowerFuncType;
	GetPowerFuncType *GetPowerFunc;

	typedef ProvidedMethod<bool> SetVelocityFuncType;
	SetVelocityFuncType *SetVelocityFunc;

	typedef ProvidedMethod<double> GetVelocityFuncType;
	GetVelocityFuncType *GetVelocityFunc;

	typedef ProvidedMethod<bool> SetPositionFuncType;
	SetPositionFuncType *SetPositionFunc;

	typedef ProvidedMethod<double> GetPositionFuncType;
	GetPositionFuncType *GetPositionFunc;

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

	virtual bool SetPower(double power,unsigned long time)
	{
		assert(SetPowerFunc != NULL);

		return (*SetPowerFunc)(power,time);
	}

	virtual double GetPower()
	{
		assert(GetPowerFunc != NULL);

		return (*GetPowerFunc)();
	}

	virtual bool SetVelocity(double velocity,unsigned long time)
	{
		assert(SetVelocityFunc != NULL);

		return (*SetVelocityFunc)(velocity,time);
	}

	virtual double GetVelocity()
	{
		assert(GetVelocityFunc != NULL);

		return (*GetVelocityFunc)();
	}

	virtual bool SetPosition(double position,unsigned long time)
	{
		assert(SetPositionFunc != NULL);

		return (*SetPositionFunc)(position,time);
	}

	virtual double GetPosition()
	{
		assert(GetPositionFunc != NULL);

		return (*GetPositionFunc)();
	}


public:
    //
    // Constructor
    //
    ServoActuatorServiceProvided(IServoActuatorService *fn)
    {
		pcom = fn;

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

    // generated setup function
    virtual void setup()
    {
		Method *ptr_method;

		ptr_method = makeProvidedMethod(&IServoActuatorService::SetParameter,pcom,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IServoActuatorService::GetParameter,pcom,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IServoActuatorService::GetError,pcom,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IServoActuatorService::SetPower,pcom,"SetPower");
		assert(ptr_method != NULL);
		addMethod("SetPower",ptr_method);
		SetPowerFunc = reinterpret_cast<SetPowerFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IServoActuatorService::GetPower,pcom,"GetPower");
		assert(ptr_method != NULL);
		addMethod("GetPower",ptr_method);
		GetPowerFunc = reinterpret_cast<GetPowerFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IServoActuatorService::SetVelocity,pcom,"SetVelocity");
		assert(ptr_method != NULL);
		addMethod("SetVelocity",ptr_method);
		SetVelocityFunc = reinterpret_cast<SetVelocityFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IServoActuatorService::GetVelocity,pcom,"GetVelocity");
		assert(ptr_method != NULL);
		addMethod("GetVelocity",ptr_method);
		GetVelocityFunc = reinterpret_cast<GetVelocityFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IServoActuatorService::SetPosition,pcom,"SetPosition");
		assert(ptr_method != NULL);
		addMethod("SetPosition",ptr_method);
		SetPositionFunc = reinterpret_cast<SetPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IServoActuatorService::GetPosition,pcom,"GetPosition");
		assert(ptr_method != NULL);
		addMethod("GetPosition",ptr_method);
		GetPositionFunc = reinterpret_cast<GetPositionFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
