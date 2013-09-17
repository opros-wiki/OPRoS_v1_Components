#ifndef _ActuatorService_PROVIDED_PORT_H
#define _ActuatorService_PROVIDED_PORT_H

#include <OPRoSTypes.h>
#include <InputDataPort.h>
#include <OutputDataPort.h>
#include <InputEventPort.h>
#include <OutputEventPort.h>
#include <ProvidedServicePort.h>
#include <RequiredServicePort.h>
#include <ProvidedMethod.h>
#include <RequiredMethod.h>

/*
 * IActuatorService
 *
 * The comonent inherits this class and implements methods. 
*/
class IActuatorService
{
public:
	virtual bool SetParameter(Property parameter) = 0;
	virtual Property GetParameter() = 0;
	virtual int GetError() = 0;
	virtual bool SetPower(double power,unsigned long time) = 0;
	virtual double GetPower() = 0;
};

/*
 * 
 * ActuatorService : public ProvidedServicePort
 *
 */
class ActuatorServiceProvided : public ProvidedServicePort, public IActuatorService
{
protected:
	IActuatorService *pcom;

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

public:
    //
    // Constructor
    //
	ActuatorServiceProvided(IActuatorService *fn)
	{
		pcom = fn;

		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		SetPowerFunc = NULL;
		GetPowerFunc = NULL;

		setup();
	}

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeProvidedMethod(&IActuatorService::SetParameter,pcom,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IActuatorService::GetParameter,pcom,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IActuatorService::GetError,pcom,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IActuatorService::SetPower,pcom,"SetPower");
		assert(ptr_method != NULL);
		addMethod("SetPower",ptr_method);
		SetPowerFunc = reinterpret_cast<SetPowerFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IActuatorService::GetPower,pcom,"GetPower");
		assert(ptr_method != NULL);
		addMethod("GetPower",ptr_method);
		GetPowerFunc = reinterpret_cast<GetPowerFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
