#ifndef _DigitalIOService_PROVIDED_PORT_H
#define _DigitalIOService_PROVIDED_PORT_H

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
 * IDigitalIOService
 *
 * The comonent inherits this class and implements methods. 
*/
class IDigitalIOService
{
public:
	virtual bool SetParameter(Property parameter)=0;
	virtual Property GetParameter()=0;
	virtual int GetError()=0;
	virtual bool SetDigitalOutputData(vector<bool> digitalOutputData)=0;
	virtual vector<bool> GetDigitalInputData()=0;
};

/*
 * 
 * DigitalIOService : public ProvidedServicePort
 *
 */
class DigitalIOServiceProvided
	:public ProvidedServicePort, public IDigitalIOService
{
protected:
	IDigitalIOService *pcom;

	typedef ProvidedMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef ProvidedMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef ProvidedMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef ProvidedMethod<bool> SetDigitalOutputDataFuncType;
	SetDigitalOutputDataFuncType *SetDigitalOutputDataFunc;

	typedef ProvidedMethod< vector<bool> > GetDigitalInputDataFuncType;
	GetDigitalInputDataFuncType *GetDigitalInputDataFunc;

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

	virtual bool SetDigitalOutputData(vector<bool> digitalOutputData)
	{
		assert(SetDigitalOutputDataFunc != NULL);

		return (*SetDigitalOutputDataFunc)(digitalOutputData);
	}

	virtual vector<bool> GetDigitalInputData()
	{
		assert(GetDigitalInputDataFunc != NULL);

		return (*GetDigitalInputDataFunc)();
	}

public:
    //
    // Constructor
    //
	DigitalIOServiceProvided(IDigitalIOService *fn)
	{
		pcom = fn;

		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		SetDigitalOutputDataFunc = NULL;
		GetDigitalInputDataFunc = NULL;

		setup();
	}

    // generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeProvidedMethod(&IDigitalIOService::SetParameter,pcom,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IDigitalIOService::GetParameter,pcom,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IDigitalIOService::GetError,pcom,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IDigitalIOService::SetDigitalOutputData,pcom,"SetDigitalOutputData");
		assert(ptr_method != NULL);
		addMethod("SetDigitalOutputData",ptr_method);
		SetDigitalOutputDataFunc = reinterpret_cast<SetDigitalOutputDataFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IDigitalIOService::GetDigitalInputData,pcom,"GetDigitalInputData");
		assert(ptr_method != NULL);
		addMethod("GetDigitalInputData",ptr_method);
		GetDigitalInputDataFunc = reinterpret_cast<GetDigitalInputDataFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
