#ifndef _PositionSensorService_REQUIRED_PORT_H
#define _PositionSensorService_REQUIRED_PORT_H

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
 * 
 * PositionSensorService : public RequiredServicePort
 *
 */
class PositionSensorServiceRequired : public RequiredServicePort
{
protected:
	typedef RequiredMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef RequiredMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef RequiredMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef RequiredMethod< vector<ObjectPosition> > GetPositionSensorDataFuncType;
	GetPositionSensorDataFuncType *GetPositionSensorDataFunc;

public:
	//
	// Constructor
	//
	PositionSensorServiceRequired()
	{
		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		GetPositionSensorDataFunc = NULL;

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

	vector<ObjectPosition> GetPositionSensorData()
	{
		assert(GetPositionSensorDataFunc != NULL);

		return (*GetPositionSensorDataFunc)();
	}

    // generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeRequiredMethod(&PositionSensorServiceRequired::SetParameter,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&PositionSensorServiceRequired::GetParameter,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&PositionSensorServiceRequired::GetError,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&PositionSensorServiceRequired::GetPositionSensorData,"GetPositionSensorData");
		assert(ptr_method != NULL);
		addMethod("GetPositionSensorData",ptr_method);
		GetPositionSensorDataFunc = reinterpret_cast<GetPositionSensorDataFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
