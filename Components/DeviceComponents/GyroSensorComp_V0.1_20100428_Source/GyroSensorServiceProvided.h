#ifndef _GyroSensorService_PROVIDED_PORT_H
#define _GyroSensorService_PROVIDED_PORT_H

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
 * IGyroSensorService
 *
 * The comonent inherits this class and implements methods. 
*/
class IGyroSensorService
{
public:
	virtual bool SetParameter(Property parameter)=0;
	virtual Property GetParameter()=0;
	virtual int GetError()=0;
	virtual vector<ObjectLocation> GetGyroSensorData()=0;
};

/*
 * 
 * GyroSensorService : public ProvidedServicePort
 *
 */
class GyroSensorServiceProvided	: public ProvidedServicePort, public IGyroSensorService
{
protected:
	IGyroSensorService *pcom;

	typedef ProvidedMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef ProvidedMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef ProvidedMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef ProvidedMethod< vector<ObjectLocation> > GetGyroSensorDataFuncType;
	GetGyroSensorDataFuncType *GetGyroSensorDataFunc;

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

	virtual vector<ObjectLocation> GetGyroSensorData()
	{
		assert(GetGyroSensorDataFunc != NULL);

		return (*GetGyroSensorDataFunc)();
	}

public:
	//
	// Constructor
	//
	GyroSensorServiceProvided(IGyroSensorService *fn)
	{
		pcom = fn;

		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		GetGyroSensorDataFunc = NULL;

		setup();
	}

    // generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeProvidedMethod(&IGyroSensorService::SetParameter,pcom,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IGyroSensorService::GetParameter,pcom,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IGyroSensorService::GetError,pcom,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IGyroSensorService::GetGyroSensorData,pcom,"GetGyroSensorData");
		assert(ptr_method != NULL);
		addMethod("GetGyroSensorData",ptr_method);
		GetGyroSensorDataFunc = reinterpret_cast<GetGyroSensorDataFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
