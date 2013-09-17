#ifndef _AccelerationSensorService_PROVIDED_PORT_H
#define _AccelerationSensorService_PROVIDED_PORT_H

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
 * IAccelerationSensorService
 *
 * The comonent inherits this class and implements methods. 
*/
class IAccelerationSensorService
{
public:
	virtual bool SetParameter(Property parameter)=0;
	virtual Property GetParameter()=0;
	virtual int GetError()=0;
	virtual vector<double> GetAccelerationData()=0;
};

/*
 * 
 * AccelerationSensorService : public ProvidedServicePort
 *
 */
class AccelerationSensorServiceProvided
	:public ProvidedServicePort, public IAccelerationSensorService
{
protected:
	IAccelerationSensorService *pcom;

	typedef ProvidedMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef ProvidedMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef ProvidedMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef ProvidedMethod< vector<double> > GetAccelerationDataFuncType;
	GetAccelerationDataFuncType *GetAccelerationDataFunc;


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

	virtual vector<double> GetAccelerationData()
	{
		assert(GetAccelerationDataFunc != NULL);

		return (*GetAccelerationDataFunc)();
	}

public:
	//
	// Constructor
	//
	AccelerationSensorServiceProvided(IAccelerationSensorService *fn)
	{
		pcom = fn;

		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		GetAccelerationDataFunc = NULL;

		setup();
	}

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeProvidedMethod(&IAccelerationSensorService::SetParameter,pcom,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IAccelerationSensorService::GetParameter,pcom,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IAccelerationSensorService::GetError,pcom,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IAccelerationSensorService::GetAccelerationData,pcom,"GetAccelerationData");
		assert(ptr_method != NULL);
		addMethod("GetAccelerationData",ptr_method);
		GetAccelerationDataFunc = reinterpret_cast<GetAccelerationDataFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
