#ifndef _I2CService_REQUIRED_PORT_H
#define _I2CService_REQUIRED_PORT_H

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
 * I2CService : public RequiredServicePort
 *
 */
class I2CServiceRequired
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
	I2CServiceRequired()
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

	int WriteData(unsigned long address,vector<unsigned char> data)
	{
		assert(WriteDataFunc != NULL);

		return (*WriteDataFunc)(address,data);
	}

	vector<unsigned char> ReadData(unsigned long address,int size)
	{
		assert(ReadDataFunc != NULL);

		return (*ReadDataFunc)(address,size);
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

		ptr_method = makeRequiredMethod(&I2CServiceRequired::SetParameter,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&I2CServiceRequired::GetParameter,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&I2CServiceRequired::GetError,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&I2CServiceRequired::WriteData,"WriteData");
		assert(ptr_method != NULL);
		addMethod("WriteData",ptr_method);
		WriteDataFunc = reinterpret_cast<WriteDataFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&I2CServiceRequired::ReadData,"ReadData");
		assert(ptr_method != NULL);
		addMethod("ReadData",ptr_method);
		ReadDataFunc = reinterpret_cast<ReadDataFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&I2CServiceRequired::Lock,"Lock");
		assert(ptr_method != NULL);
		addMethod("Lock",ptr_method);
		LockFunc = reinterpret_cast<LockFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&I2CServiceRequired::Unlock,"Unlock");
		assert(ptr_method != NULL);
		addMethod("Unlock",ptr_method);
		UnlockFunc = reinterpret_cast<UnlockFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
