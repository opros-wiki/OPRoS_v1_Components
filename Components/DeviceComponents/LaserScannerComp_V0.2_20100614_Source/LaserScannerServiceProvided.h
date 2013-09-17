#ifndef _LaserScannerService_PROVIDED_PORT_H
#define _LaserScannerService_PROVIDED_PORT_H

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
 * ILaserScannerService
 *
 * The comonent inherits this class and implements methods. 
*/
class ILaserScannerService
{
public:
	virtual bool SetParameter(Property parameter)=0;
	virtual Property GetParameter()=0;
	virtual int GetError()=0;
	virtual vector<double> GetLaserScannerData()=0;
};

/*
 * 
 * LaserScannerService : public ProvidedServicePort
 *
 */
class LaserScannerServiceProvided : public ProvidedServicePort, public ILaserScannerService
{
protected:
	ILaserScannerService *pcom;

	typedef ProvidedMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef ProvidedMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef ProvidedMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef ProvidedMethod< vector<double> > GetLaserScannerDataFuncType;
	GetLaserScannerDataFuncType *GetLaserScannerDataFunc;

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

	virtual vector<double> GetLaserScannerData()
	{
		assert(GetLaserScannerDataFunc != NULL);

		return (*GetLaserScannerDataFunc)();
	}

public:
    //
    // Constructor
    //
	LaserScannerServiceProvided(ILaserScannerService *fn)
	{
		pcom = fn;

		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		GetLaserScannerDataFunc = NULL;

		setup();
	}

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeProvidedMethod(&ILaserScannerService::SetParameter,pcom,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&ILaserScannerService::GetParameter,pcom,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&ILaserScannerService::GetError,pcom,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&ILaserScannerService::GetLaserScannerData,pcom,"GetLaserScannerData");
		assert(ptr_method != NULL);
		addMethod("GetLaserScannerData",ptr_method);
		GetLaserScannerDataFunc = reinterpret_cast<GetLaserScannerDataFuncType *>(ptr_method);
		ptr_method = NULL;
	}
};
#endif
