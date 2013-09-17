#ifndef _USBService_PROVIDED_PORT_H
#define _USBService_PROVIDED_PORT_H

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
 * IUSBService
 *
 * The comonent inherits this class and implements methods. 
*/
class IUSBService
{
public:
	virtual bool SetParameter(Property parameter)=0;
	virtual Property GetParameter()=0;
	virtual int GetError()=0;
	virtual int WriteData(vector<unsigned char> data)=0;
	virtual vector<unsigned char> ReadData(int size)=0;
	virtual bool Lock()=0;
	virtual bool Unlock()=0;
};

/*
 * 
 * USBService : public ProvidedServicePort
 *
 */
class USBServiceProvided
	:public ProvidedServicePort, public IUSBService
{
protected:
    IUSBService *pcom;

	typedef ProvidedMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef ProvidedMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef ProvidedMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef ProvidedMethod<int> WriteDataFuncType;
	WriteDataFuncType *WriteDataFunc;

	typedef ProvidedMethod< vector<unsigned char> > ReadDataFuncType;
	ReadDataFuncType *ReadDataFunc;

	typedef ProvidedMethod<bool> LockFuncType;
	LockFuncType *LockFunc;

	typedef ProvidedMethod<bool> UnlockFuncType;
	UnlockFuncType *UnlockFunc;

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

	virtual int WriteData(vector<unsigned char> data)
	{
		assert(WriteDataFunc != NULL);

		return (*WriteDataFunc)(data);
	}

	virtual vector<unsigned char> ReadData(int size)
	{
		assert(ReadDataFunc != NULL);

		return (*ReadDataFunc)(size);
	}

	virtual bool Lock()
	{
		assert(LockFunc != NULL);

		return (*LockFunc)();
	}

	virtual bool Unlock()
	{
		assert(UnlockFunc != NULL);

		return (*UnlockFunc)();
	}

public:
    //
    // Constructor
    //
	USBServiceProvided(IUSBService *fn)
	{
		pcom = fn;

		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		WriteDataFunc = NULL;
		ReadDataFunc = NULL;
		LockFunc = NULL;
		UnlockFunc = NULL;

		setup();
	}

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeProvidedMethod(&IUSBService::SetParameter,pcom,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IUSBService::GetParameter,pcom,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IUSBService::GetError,pcom,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IUSBService::WriteData,pcom,"WriteData");
		assert(ptr_method != NULL);
		addMethod("WriteData",ptr_method);
		WriteDataFunc = reinterpret_cast<WriteDataFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IUSBService::ReadData,pcom,"ReadData");
		assert(ptr_method != NULL);
		addMethod("ReadData",ptr_method);
		ReadDataFunc = reinterpret_cast<ReadDataFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IUSBService::Lock,pcom,"Lock");
		assert(ptr_method != NULL);
		addMethod("Lock",ptr_method);
		LockFunc = reinterpret_cast<LockFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IUSBService::Unlock,pcom,"Unlock");
		assert(ptr_method != NULL);
		addMethod("Unlock",ptr_method);
		UnlockFunc = reinterpret_cast<UnlockFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
