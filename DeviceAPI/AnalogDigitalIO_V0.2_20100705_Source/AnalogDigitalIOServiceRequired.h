#ifndef _AnalogDigitalIOService_REQUIRED_PORT_H
#define _AnalogDigitalIOService_REQUIRED_PORT_H

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
 * AnalogDigitalIOService : public RequiredServicePort
 *
 */
class AnalogDigitalIOServiceRequired
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

	typedef RequiredMethod<bool> SetDigitalOutputDataFuncType;
	SetDigitalOutputDataFuncType *SetDigitalOutputDataFunc;

	typedef RequiredMethod< vector<bool> > GetDigitalInputDataFuncType;
	GetDigitalInputDataFuncType *GetDigitalInputDataFunc;

public:
	//
	// Constructor
	//
	AnalogDigitalIOServiceRequired()
	{
		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		SetAnalogOutputDataFunc = NULL;
		GetAnalogInputDataFunc = NULL;
		SetDigitalOutputDataFunc = NULL;
		GetDigitalInputDataFunc = NULL;

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

	bool SetDigitalOutputData(vector<bool> digitalOutputData)
	{
		assert(SetDigitalOutputDataFunc != NULL);

		return (*SetDigitalOutputDataFunc)(digitalOutputData);
	}

	vector<bool> GetDigitalInputData()
	{
		assert(GetDigitalInputDataFunc != NULL);

		return (*GetDigitalInputDataFunc)();
	}

    // generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeRequiredMethod(&AnalogDigitalIOServiceRequired::SetParameter,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&AnalogDigitalIOServiceRequired::GetParameter,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&AnalogDigitalIOServiceRequired::GetError,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&AnalogDigitalIOServiceRequired::SetAnalogOutputData,"SetAnalogOutputData");
		assert(ptr_method != NULL);
		addMethod("SetAnalogOutputData",ptr_method);
		SetAnalogOutputDataFunc = reinterpret_cast<SetAnalogOutputDataFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&AnalogDigitalIOServiceRequired::GetAnalogInputData,"GetAnalogInputData");
		assert(ptr_method != NULL);
		addMethod("GetAnalogInputData",ptr_method);
		GetAnalogInputDataFunc = reinterpret_cast<GetAnalogInputDataFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&AnalogDigitalIOServiceRequired::SetDigitalOutputData,"SetDigitalOutputData");
		assert(ptr_method != NULL);
		addMethod("SetDigitalOutputData",ptr_method);
		SetDigitalOutputDataFunc = reinterpret_cast<SetDigitalOutputDataFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&AnalogDigitalIOServiceRequired::GetDigitalInputData,"GetDigitalInputData");
		assert(ptr_method != NULL);
		addMethod("GetDigitalInputData",ptr_method);
		GetDigitalInputDataFunc = reinterpret_cast<GetDigitalInputDataFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
