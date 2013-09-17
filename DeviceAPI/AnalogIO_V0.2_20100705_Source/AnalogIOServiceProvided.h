#ifndef _AnalogIOService_PROVIDED_PORT_H
#define _AnalogIOService_PROVIDED_PORT_H

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
 * IAnalogIOService
 *
 * The comonent inherits this class and implements methods. 
*/
class IAnalogIOService
{
public:
	virtual bool SetParameter(Property parameter)=0;
	virtual Property GetParameter()=0;
	virtual int GetError()=0;
	virtual bool SetAnalogOutputData(vector<double> analogOutputData)=0;
	virtual vector<double> GetAnalogInputData()=0;
 };

/*
 * 
 * AnalogIOService : public ProvidedServicePort
 *
 */
class AnalogIOServiceProvided
	:public ProvidedServicePort, public IAnalogIOService
{
protected:
	IAnalogIOService *pcom;

	typedef ProvidedMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef ProvidedMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef ProvidedMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef ProvidedMethod<bool> SetAnalogOutputDataFuncType;
	SetAnalogOutputDataFuncType *SetAnalogOutputDataFunc;

	typedef ProvidedMethod< vector<double> > GetAnalogInputDataFuncType;
	GetAnalogInputDataFuncType *GetAnalogInputDataFunc;

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

	virtual bool SetAnalogOutputData(vector<double> analogOutputData)
	{
		assert(SetAnalogOutputDataFunc != NULL);

		return (*SetAnalogOutputDataFunc)(analogOutputData);
	}

	virtual vector<double> GetAnalogInputData()
	{
		assert(GetAnalogInputDataFunc != NULL);

		return (*GetAnalogInputDataFunc)();
	}

public:
    //
    // Constructor
    //
	AnalogIOServiceProvided(IAnalogIOService *fn)
	{
		pcom = fn;

		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		SetAnalogOutputDataFunc = NULL;
		GetAnalogInputDataFunc = NULL;

		setup();
	}

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeProvidedMethod(&IAnalogIOService::SetParameter,pcom,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IAnalogIOService::GetParameter,pcom,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IAnalogIOService::GetError,pcom,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IAnalogIOService::SetAnalogOutputData,pcom,"SetAnalogOutputData");
		assert(ptr_method != NULL);
		addMethod("SetAnalogOutputData",ptr_method);
		SetAnalogOutputDataFunc = reinterpret_cast<SetAnalogOutputDataFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IAnalogIOService::GetAnalogInputData,pcom,"GetAnalogInputData");
		assert(ptr_method != NULL);
		addMethod("GetAnalogInputData",ptr_method);
		GetAnalogInputDataFunc = reinterpret_cast<GetAnalogInputDataFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
