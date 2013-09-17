#ifndef _ObstacleAvoidanceService_REQUIRED_PORT_H
#define _ObstacleAvoidanceService_REQUIRED_PORT_H

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
 * 
 * ObstacleAvoidanceService : public RequiredServicePort
 *
 */
class ObstacleAvoidanceServiceRequired : public RequiredServicePort
{
protected:

	typedef RequiredMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef RequiredMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef RequiredMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef RequiredMethod<void> SetPositionFuncType;
	SetPositionFuncType *SetPositionFunc;

	typedef RequiredMethod<WheelControlVelocity> AvoidFuncType;
	AvoidFuncType *AvoidFunc;

public:
	//
	// Constructor
	//
	ObstacleAvoidanceServiceRequired()
	{
		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		SetPositionFunc = NULL;
		AvoidFunc = NULL;

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

	void SetPosition(ObjectLocation position)
	{
		assert(SetPositionFunc != NULL);
		(*SetPositionFunc)(position);
	}

	WheelControlVelocity Avoid(ObjectLocation currentPosition,ObjectLocation targetPosition)
	{
		assert(AvoidFunc != NULL);
		return (*AvoidFunc)(currentPosition,targetPosition);
	}

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeRequiredMethod(&ObstacleAvoidanceServiceRequired::SetParameter,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ObstacleAvoidanceServiceRequired::GetParameter,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ObstacleAvoidanceServiceRequired::GetError,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ObstacleAvoidanceServiceRequired::SetPosition,"SetPosition");
		assert(ptr_method != NULL);
		addMethod("SetPosition",ptr_method);
		SetPositionFunc = reinterpret_cast<SetPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&ObstacleAvoidanceServiceRequired::Avoid,"Avoid");
		assert(ptr_method != NULL);
		addMethod("Avoid",ptr_method);
		AvoidFunc = reinterpret_cast<AvoidFuncType *>(ptr_method);
		ptr_method = NULL;
	}
};
#endif
