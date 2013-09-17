#ifndef _InertiaMeasurementUnitService_PROVIDED_PORT_H
#define _InertiaMeasurementUnitService_PROVIDED_PORT_H

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
 * IInertiaMeasurementUnitService
 *
 * The comonent inherits this class and implements methods. 
*/
class IInertiaMeasurementUnitService
{
public:
	virtual bool SetParameter(Property parameter)=0;
	virtual Property GetParameter()=0;
	virtual int GetError()=0;
	virtual vector<ObjectPosture> GetInertiaMeasurementUnitData()=0;
};

/*
 * 
 * InertiaMeasurementUnitService : public ProvidedServicePort
 *
 */
class InertiaMeasurementUnitServiceProvided
	:public ProvidedServicePort, public IInertiaMeasurementUnitService
{
protected:
	IInertiaMeasurementUnitService *pcom;

	typedef ProvidedMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef ProvidedMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef ProvidedMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef ProvidedMethod< vector<ObjectPosture> > GetInertiaMeasurementUnitDataFuncType;
	GetInertiaMeasurementUnitDataFuncType *GetInertiaMeasurementUnitDataFunc;

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

	virtual vector<ObjectPosture> GetInertiaMeasurementUnitData()
	{
		assert(GetInertiaMeasurementUnitDataFunc != NULL);

		return (*GetInertiaMeasurementUnitDataFunc)();
	}

public:
	//
	// Constructor
	//
	InertiaMeasurementUnitServiceProvided(IInertiaMeasurementUnitService *fn)
	{
		pcom = fn;

		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		GetInertiaMeasurementUnitDataFunc = NULL;

		setup();
	}

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeProvidedMethod(&IInertiaMeasurementUnitService::SetParameter,pcom,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IInertiaMeasurementUnitService::GetParameter,pcom,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IInertiaMeasurementUnitService::GetError,pcom,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IInertiaMeasurementUnitService::GetInertiaMeasurementUnitData,pcom,"GetInertiaMeasurementUnitData");
		assert(ptr_method != NULL);
		addMethod("GetInertiaMeasurementUnitData",ptr_method);
		GetInertiaMeasurementUnitDataFunc = reinterpret_cast<GetInertiaMeasurementUnitDataFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
