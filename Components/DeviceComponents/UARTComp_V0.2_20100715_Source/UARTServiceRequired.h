#ifndef _UARTService_REQUIRED_PORT_H
#define _UARTService_REQUIRED_PORT_H

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
 * UARTService : public RequiredServicePort
 *
 */
class UARTServiceRequired
   :public RequiredServicePort
{
protected:
	typedef RequiredMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef RequiredMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef RequiredMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef RequiredMethod<int> WriteDataFuncType;
	WriteDataFuncType *WriteDataFunc;

	typedef RequiredMethod< vector<unsigned char> > ReadDataFuncType;
	ReadDataFuncType *ReadDataFunc;

	typedef RequiredMethod<bool> LockFuncType;
	LockFuncType *LockFunc;

	typedef RequiredMethod<bool> UnlockFuncType;
	UnlockFuncType *UnlockFunc;

public:
	//
	// Constructor
	//
	UARTServiceRequired()
	{
		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		WriteDataFunc = NULL;
		ReadDataFunc = NULL;
		LockFunc = NULL;
		UnlockFunc = NULL;

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

	int WriteData(vector<unsigned char> data)
	{
		assert(WriteDataFunc != NULL);

		return (*WriteDataFunc)(data);
	}

	vector<unsigned char> ReadData(int size)
	{
		assert(ReadDataFunc != NULL);

		return (*ReadDataFunc)(size);
	}

	bool Lock()
	{
		assert(LockFunc != NULL);

		return (*LockFunc)();
	}

	bool Unlock()
	{
		assert(UnlockFunc != NULL);

		return (*UnlockFunc)();
	}

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeRequiredMethod(&UARTServiceRequired::SetParameter,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&UARTServiceRequired::GetParameter,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&UARTServiceRequired::GetError,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&UARTServiceRequired::WriteData,"WriteData");
		assert(ptr_method != NULL);
		addMethod("WriteData",ptr_method);
		WriteDataFunc = reinterpret_cast<WriteDataFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&UARTServiceRequired::ReadData,"ReadData");
		assert(ptr_method != NULL);
		addMethod("ReadData",ptr_method);
		ReadDataFunc = reinterpret_cast<ReadDataFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&UARTServiceRequired::Lock,"Lock");
		assert(ptr_method != NULL);
		addMethod("Lock",ptr_method);
		LockFunc = reinterpret_cast<LockFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&UARTServiceRequired::Unlock,"Unlock");
		assert(ptr_method != NULL);
		addMethod("Unlock",ptr_method);
		UnlockFunc = reinterpret_cast<UnlockFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif