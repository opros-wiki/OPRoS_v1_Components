#ifndef _UltrasonicSensorService_PROVIDED_PORT_H
#define _UltrasonicSensorService_PROVIDED_PORT_H

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
 * IUltrasonicSensorService
 *
 * The comonent inherits this class and implements methods. 
*/
class IUltrasonicSensorService
{
public:
	virtual bool SetParameter(Property parameter)=0;
	virtual Property GetParameter()=0;
	virtual int GetError()=0;
	virtual vector<double> GetUltrasonicSensorData()=0;
};

/*
 * 
 * UltrasonicSensorService : public ProvidedServicePort
 *
 */
class UltrasonicSensorServiceProvided
	:public ProvidedServicePort, public IUltrasonicSensorService
{
protected:
	IUltrasonicSensorService *pcom;

	typedef ProvidedMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef ProvidedMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef ProvidedMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef ProvidedMethod< vector<double> > GetUltrasonicSensorDataFuncType;
	GetUltrasonicSensorDataFuncType *GetUltrasonicSensorDataFunc;


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

	virtual vector<double> GetUltrasonicSensorData()
	{
		assert(GetUltrasonicSensorDataFunc != NULL);

		return (*GetUltrasonicSensorDataFunc)();
	}

public:
	//
	// Constructor
	//
	UltrasonicSensorServiceProvided(IUltrasonicSensorService *fn)
	{
		pcom = fn;

		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		GetUltrasonicSensorDataFunc = NULL;

		setup();
	}

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeProvidedMethod(&IUltrasonicSensorService::SetParameter,pcom,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IUltrasonicSensorService::GetParameter,pcom,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IUltrasonicSensorService::GetError,pcom,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IUltrasonicSensorService::GetUltrasonicSensorData,pcom,"GetUltrasonicSensorData");
		assert(ptr_method != NULL);
		addMethod("GetUltrasonicSensorData",ptr_method);
		GetUltrasonicSensorDataFunc = reinterpret_cast<GetUltrasonicSensorDataFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
