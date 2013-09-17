#ifndef _PositionSensorService_PROVIDED_PORT_H
#define _PositionSensorService_PROVIDED_PORT_H

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
 * IPositionSensorService
 *
 * The comonent inherits this class and implements methods. 
*/
class IPositionSensorService
{
public:
	virtual bool SetParameter(Property parameter)=0;
	virtual Property GetParameter()=0;
	virtual int GetError()=0;
	virtual vector<ObjectPosition> GetPositionSensorData()=0;
};

/*
 * 
 * PositionSensorService : public ProvidedServicePort
 *
 */
class PositionSensorServiceProvided : public ProvidedServicePort, public IPositionSensorService
{
protected:
	IPositionSensorService *pcom;

	typedef ProvidedMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef ProvidedMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef ProvidedMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef ProvidedMethod< vector<ObjectPosition> > GetPositionSensorDataFuncType;
	GetPositionSensorDataFuncType *GetPositionSensorDataFunc;

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

	virtual vector<ObjectPosition> GetPositionSensorData()
	{
		assert(GetPositionSensorDataFunc != NULL);

		return (*GetPositionSensorDataFunc)();
	}

public:
    //
    // Constructor
    //
	PositionSensorServiceProvided(IPositionSensorService *fn)
	{
		pcom = fn;

		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		GetPositionSensorDataFunc = NULL;

		setup();
	}

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeProvidedMethod(&IPositionSensorService::SetParameter,pcom,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IPositionSensorService::GetParameter,pcom,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IPositionSensorService::GetError,pcom,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IPositionSensorService::GetPositionSensorData,pcom,"GetPositionSensorData");
		assert(ptr_method != NULL);
		addMethod("GetPositionSensorData",ptr_method);
		GetPositionSensorDataFunc = reinterpret_cast<GetPositionSensorDataFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
