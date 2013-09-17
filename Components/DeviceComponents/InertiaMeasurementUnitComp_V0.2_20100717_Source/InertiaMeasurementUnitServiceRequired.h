#ifndef _InertiaMeasurementUnitService_REQUIRED_PORT_H
#define _InertiaMeasurementUnitService_REQUIRED_PORT_H

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
 * InertiaMeasurementUnitService : public RequiredServicePort
 *
 */
class InertiaMeasurementUnitServiceRequired
   :public RequiredServicePort
{
protected:
	typedef RequiredMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef RequiredMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef RequiredMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef RequiredMethod< vector<ObjectPosture> > GetInertiaMeasurementUnitDataFuncType;
	GetInertiaMeasurementUnitDataFuncType *GetInertiaMeasurementUnitDataFunc;

public:
	//
	// Constructor
	//
	InertiaMeasurementUnitServiceRequired()
	{
		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		GetInertiaMeasurementUnitDataFunc = NULL;

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

	vector<ObjectPosture> GetInertiaMeasurementUnitData()
	{
		assert(GetInertiaMeasurementUnitDataFunc != NULL);

		return (*GetInertiaMeasurementUnitDataFunc)();
	}

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeRequiredMethod(&InertiaMeasurementUnitServiceRequired::SetParameter,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&InertiaMeasurementUnitServiceRequired::GetParameter,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&InertiaMeasurementUnitServiceRequired::GetError,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&InertiaMeasurementUnitServiceRequired::GetInertiaMeasurementUnitData,"GetInertiaMeasurementUnitData");
		assert(ptr_method != NULL);
		addMethod("GetInertiaMeasurementUnitData",ptr_method);
		GetInertiaMeasurementUnitDataFunc = reinterpret_cast<GetInertiaMeasurementUnitDataFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
