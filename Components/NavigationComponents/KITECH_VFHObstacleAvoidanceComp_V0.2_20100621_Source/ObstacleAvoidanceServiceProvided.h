#ifndef _ObstacleAvoidanceService_PROVIDED_PORT_H
#define _ObstacleAvoidanceService_PROVIDED_PORT_H

#include <OPRoSTypes.h>
#include <InputDataPort.h>
#include <OutputDataPort.h>
#include <InputEventPort.h>
#include <OutputEventPort.h>
#include <ProvidedServicePort.h>
#include <RequiredServicePort.h>
#include <ProvidedMethod.h>
#include <RequiredMethod.h>

#include "ApiTypes.h"
#include "Property.h"
			

/*
 * IObstacleAvoidanceService
 *
 * The comonent inherits this class and implements methods. 
*/
class IObstacleAvoidanceService
{
public:
	virtual bool SetParameter(Property parameter)=0;
	virtual Property GetParameter()=0;
	virtual int GetError()=0;
	virtual void SetPosition(ObjectLocation position)=0;
	virtual WheelControlVelocity Avoid(ObjectLocation currentPosition,ObjectLocation targetPosition)=0;
};

/*
 * 
 * ObstacleAvoidanceService : public ProvidedServicePort
 *
 */
class ObstacleAvoidanceServiceProvided : public ProvidedServicePort, public IObstacleAvoidanceService
{
protected:
	IObstacleAvoidanceService *pcom;

	typedef ProvidedMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef ProvidedMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef ProvidedMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef ProvidedMethod<void> SetPositionFuncType;
	SetPositionFuncType *SetPositionFunc;

	typedef ProvidedMethod<WheelControlVelocity> AvoidFuncType;
	AvoidFuncType *AvoidFunc;


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

	virtual void SetPosition(ObjectLocation position)
	{
		assert(SetPositionFunc != NULL);
		(*SetPositionFunc)(position);
	}

	virtual WheelControlVelocity Avoid(ObjectLocation currentPosition,ObjectLocation targetPosition)
	{
		assert(AvoidFunc != NULL);
		return (*AvoidFunc)(currentPosition,targetPosition);
	}

public:
	//
	// Constructor
	//
	ObstacleAvoidanceServiceProvided(IObstacleAvoidanceService *fn)
	{
		pcom = fn;

		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		SetPositionFunc = NULL;
		AvoidFunc = NULL;

		setup();
	}

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeProvidedMethod(&IObstacleAvoidanceService::SetParameter,pcom,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IObstacleAvoidanceService::GetParameter,pcom,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IObstacleAvoidanceService::GetError,pcom,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IObstacleAvoidanceService::SetPosition,pcom,"SetPosition");
		assert(ptr_method != NULL);
		addMethod("SetPosition",ptr_method);
		SetPositionFunc = reinterpret_cast<SetPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IObstacleAvoidanceService::Avoid,pcom,"Avoid");
		assert(ptr_method != NULL);
		addMethod("Avoid",ptr_method);
		AvoidFunc = reinterpret_cast<AvoidFuncType *>(ptr_method);
		ptr_method = NULL;
	}
};
#endif
