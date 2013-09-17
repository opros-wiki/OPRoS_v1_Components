#ifndef _InfraredSensorService_PROVIDED_PORT_H
#define _InfraredSensorService_PROVIDED_PORT_H

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
 * IInfraredSensorService
 *
 * The comonent inherits this class and implements methods. 
*/
class IInfraredSensorService
{
public:
	virtual bool SetParameter(Property parameter)=0;
	virtual Property GetParameter()=0;
	virtual int GetError()=0;
	virtual vector<double> GetInfraredData()=0;
};

/*
 * 
 * InfraredSensorService : public ProvidedServicePort
 *
 */
class InfraredSensorServiceProvided
	:public ProvidedServicePort, public IInfraredSensorService
{
protected:
    IInfraredSensorService *pcom;

	typedef ProvidedMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef ProvidedMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef ProvidedMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef ProvidedMethod< vector<double> > GetInfraredDataFuncType;
	GetInfraredDataFuncType *GetInfraredDataFunc;

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

	virtual vector<double> GetInfraredData()
	{
		assert(GetInfraredDataFunc != NULL);

		return (*GetInfraredDataFunc)();
	}

public:
	//
	// Constructor
	//
	InfraredSensorServiceProvided(IInfraredSensorService *fn)
	{
		pcom = fn;

		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		GetInfraredDataFunc = NULL;

		setup();
	}

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeProvidedMethod(&IInfraredSensorService::SetParameter,pcom,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IInfraredSensorService::GetParameter,pcom,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IInfraredSensorService::GetError,pcom,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IInfraredSensorService::GetInfraredData,pcom,"GetInfraredData");
		assert(ptr_method != NULL);
		addMethod("GetInfraredData",ptr_method);
		GetInfraredDataFunc = reinterpret_cast<GetInfraredDataFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
