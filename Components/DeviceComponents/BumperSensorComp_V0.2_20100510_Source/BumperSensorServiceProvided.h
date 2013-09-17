#ifndef _BumperSensorService_PROVIDED_PORT_H
#define _BumperSensorService_PROVIDED_PORT_H

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
 * IBumperSensorService
 *
 * The comonent inherits this class and implements methods. 
*/
class IBumperSensorService
{
public:
	virtual bool SetParameter(Property parameter)=0;
	virtual Property GetParameter()=0;
	virtual int GetError()=0;
	virtual vector<bool> GetBumperSensorData()=0;
};

/*
 * 
 * BumperSensorService : public ProvidedServicePort
 *
 */
class BumperSensorServiceProvided : public ProvidedServicePort, public IBumperSensorService
{
protected:
	IBumperSensorService *pcom;

	typedef ProvidedMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef ProvidedMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef ProvidedMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef ProvidedMethod< vector<bool> > GetBumperSensorDataFuncType;
	GetBumperSensorDataFuncType *GetBumperSensorDataFunc;

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

	virtual vector<bool> GetBumperSensorData()
	{
		assert(GetBumperSensorDataFunc != NULL);

		return (*GetBumperSensorDataFunc)();
	}

public:
    //
    // Constructor
    //
	BumperSensorServiceProvided(IBumperSensorService *fn)
	{
		pcom = fn;

		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		GetBumperSensorDataFunc = NULL;

		setup();
	}

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeProvidedMethod(&IBumperSensorService::SetParameter,pcom,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IBumperSensorService::GetParameter,pcom,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IBumperSensorService::GetError,pcom,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IBumperSensorService::GetBumperSensorData,pcom,"GetBumperSensorData");
		assert(ptr_method != NULL);
		addMethod("GetBumperSensorData",ptr_method);
		GetBumperSensorDataFunc = reinterpret_cast<GetBumperSensorDataFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
