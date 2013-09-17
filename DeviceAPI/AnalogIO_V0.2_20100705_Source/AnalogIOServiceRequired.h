#ifndef _AnalogIOService_REQUIRED_PORT_H
#define _AnalogIOService_REQUIRED_PORT_H

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
 * 
 * AnalogIOService : public RequiredServicePort
 *
 */
class AnalogIOServiceRequired
   :public RequiredServicePort
{
protected:
	typedef RequiredMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef RequiredMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef RequiredMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef RequiredMethod<bool> SetAnalogOutputDataFuncType;
	SetAnalogOutputDataFuncType *SetAnalogOutputDataFunc;

	typedef RequiredMethod< vector<double> > GetAnalogInputDataFuncType;
	GetAnalogInputDataFuncType *GetAnalogInputDataFunc;

public:
	//
	// Constructor
	//
	AnalogIOServiceRequired()
	{
		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		SetAnalogOutputDataFunc = NULL;
		GetAnalogInputDataFunc = NULL;

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

	bool SetAnalogOutputData(vector<double> analogOutputData)
	{
		assert(SetAnalogOutputDataFunc != NULL);

		return (*SetAnalogOutputDataFunc)(analogOutputData);
	}

	vector<double> GetAnalogInputData()
	{
		assert(GetAnalogInputDataFunc != NULL);

		return (*GetAnalogInputDataFunc)();
	}

    // generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeRequiredMethod(&AnalogIOServiceRequired::SetParameter,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&AnalogIOServiceRequired::GetParameter,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&AnalogIOServiceRequired::GetError,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&AnalogIOServiceRequired::SetAnalogOutputData,"SetAnalogOutputData");
		assert(ptr_method != NULL);
		addMethod("SetAnalogOutputData",ptr_method);
		SetAnalogOutputDataFunc = reinterpret_cast<SetAnalogOutputDataFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&AnalogIOServiceRequired::GetAnalogInputData,"GetAnalogInputData");
		assert(ptr_method != NULL);
		addMethod("GetAnalogInputData",ptr_method);
		GetAnalogInputDataFunc = reinterpret_cast<GetAnalogInputDataFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
