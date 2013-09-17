#ifndef _TouchSensorService_PROVIDED_PORT_H
#define _TouchSensorService_PROVIDED_PORT_H

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
 * ITouchSensorService
 *
 * The comonent inherits this class and implements methods. 
*/
class ITouchSensorService
{
public:
    virtual bool SetParameter(Property parameter) = 0;
    virtual Property GetParameter()=0;
    virtual int GetError()=0;
    virtual vector<bool> GetTouchSensorData()=0;
 };

/*
 * 
 * TouchSensorService : public ProvidedServicePort
 *
 */
class TouchSensorServiceProvided : public ProvidedServicePort, public ITouchSensorService
{
protected:
	ITouchSensorService *pcom;

	typedef ProvidedMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef ProvidedMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef ProvidedMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef ProvidedMethod< vector<bool> > GetTouchSensorDataFuncType;
	GetTouchSensorDataFuncType *GetTouchSensorDataFunc;

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

	virtual vector<bool> GetTouchSensorData()
	{
		assert(GetTouchSensorDataFunc != NULL);

		return (*GetTouchSensorDataFunc)();
	}

public:
    //
    // Constructor
    //
	TouchSensorServiceProvided(ITouchSensorService *fn)
	{
		pcom = fn;

		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		GetTouchSensorDataFunc = NULL;

		setup();
	}

    // generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeProvidedMethod(&ITouchSensorService::SetParameter,pcom,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&ITouchSensorService::GetParameter,pcom,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&ITouchSensorService::GetError,pcom,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&ITouchSensorService::GetTouchSensorData,pcom,"GetTouchSensorData");
		assert(ptr_method != NULL);
		addMethod("GetTouchSensorData",ptr_method);
		GetTouchSensorDataFunc = reinterpret_cast<GetTouchSensorDataFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
