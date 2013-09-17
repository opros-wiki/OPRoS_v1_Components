#ifndef _LocalizationService_REQUIRED_PORT_H
#define _LocalizationService_REQUIRED_PORT_H

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
 * LocalizationService : public RequiredServicePort
 *
 */
class LocalizationServiceRequired : public RequiredServicePort
{
protected:

	typedef RequiredMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef RequiredMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef RequiredMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef RequiredMethod<void> SetPositionFuncType;
	SetPositionFuncType *SetPositionFunc;

	typedef RequiredMethod<ObjectLocation> LocalizeFuncType;
	LocalizeFuncType *LocalizeFunc;

public:
	//
	// Constructor
	//
	LocalizationServiceRequired()
	{
		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		SetPositionFunc = NULL;
		LocalizeFunc = NULL;
            
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

	void SetPosition(ObjectLocation position)
	{
		assert(SetPositionFunc != NULL);
		(*SetPositionFunc)(position);
	}

	ObjectLocation Localize()
	{
		assert(LocalizeFunc != NULL);
		return (*LocalizeFunc)();
	}

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeRequiredMethod(&LocalizationServiceRequired::SetParameter,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&LocalizationServiceRequired::GetParameter,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&LocalizationServiceRequired::GetError,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&LocalizationServiceRequired::SetPosition,"SetPosition");
		assert(ptr_method != NULL);
		addMethod("SetPosition",ptr_method);
		SetPositionFunc = reinterpret_cast<SetPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&LocalizationServiceRequired::Localize,"Localize");
		assert(ptr_method != NULL);
		addMethod("Localize",ptr_method);
		LocalizeFunc = reinterpret_cast<LocalizeFuncType *>(ptr_method);
		ptr_method = NULL;
	}
};
#endif
