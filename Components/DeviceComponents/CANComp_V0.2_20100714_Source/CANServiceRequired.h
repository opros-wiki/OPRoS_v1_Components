#ifndef _CANService_REQUIRED_PORT_H
#define _CANService_REQUIRED_PORT_H

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
 * 
 * CANService : public RequiredServicePort
 *
 */
class CANServiceRequired
   :public RequiredServicePort
{
protected:
	typedef RequiredMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef RequiredMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef RequiredMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef RequiredMethod<bool> WriteCANObjectFuncType;
	WriteCANObjectFuncType *WriteCANObjectFunc;

	typedef RequiredMethod<CANObject> ReadCANObjectFuncType;
	ReadCANObjectFuncType *ReadCANObjectFunc;

public:
	//
	// Constructor
	//
	CANServiceRequired()
	{
		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		WriteCANObjectFunc = NULL;
		ReadCANObjectFunc = NULL;

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

	bool WriteCANObject(CANObject canObject)
	{
		assert(WriteCANObjectFunc != NULL);

		return (*WriteCANObjectFunc)(canObject);
	}

	CANObject ReadCANObject()
	{
		assert(ReadCANObjectFunc != NULL);

		return (*ReadCANObjectFunc)();
	}

    // generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeRequiredMethod(&CANServiceRequired::SetParameter,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&CANServiceRequired::GetParameter,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&CANServiceRequired::GetError,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&CANServiceRequired::WriteCANObject,"WriteCANObject");
		assert(ptr_method != NULL);
		addMethod("WriteCANObject",ptr_method);
		WriteCANObjectFunc = reinterpret_cast<WriteCANObjectFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&CANServiceRequired::ReadCANObject,"ReadCANObject");
		assert(ptr_method != NULL);
		addMethod("ReadCANObject",ptr_method);
		ReadCANObjectFunc = reinterpret_cast<ReadCANObjectFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
