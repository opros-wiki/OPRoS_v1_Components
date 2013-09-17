#ifndef _LaserScannerService_REQUIRED_PORT_H
#define _LaserScannerService_REQUIRED_PORT_H

#include <OPRoSTypes.h>
#include <InputDataPort.h>
#include <OutputDataPort.h>
#include <InputEventPort.h>
#include <OutputEventPort.h>
#include <ProvidedServicePort.h>
#include <RequiredServicePort.h>
#include <ProvidedMethod.h>
#include <RequiredMethod.h>

/*
 * 
 * LaserScannerService : public RequiredServicePort
 *
 */
class LaserScannerServiceRequired
   :public RequiredServicePort
{
protected:
	typedef RequiredMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef RequiredMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef RequiredMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef RequiredMethod< vector<double> > GetLaserScannerDataFuncType;
	GetLaserScannerDataFuncType *GetLaserScannerDataFunc;

public:
	//
	// Constructor
	//
	LaserScannerServiceRequired()
	{
		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		GetLaserScannerDataFunc = NULL;

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

	vector<double> GetLaserScannerData()
	{
		assert(GetLaserScannerDataFunc != NULL);

		return (*GetLaserScannerDataFunc)();
	}

    // generated setup function
    virtual void setup()
    {
		Method *ptr_method;

		ptr_method = makeRequiredMethod(&LaserScannerServiceRequired::SetParameter,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&LaserScannerServiceRequired::GetParameter,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&LaserScannerServiceRequired::GetError,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&LaserScannerServiceRequired::GetLaserScannerData,"GetLaserScannerData");
		assert(ptr_method != NULL);
		addMethod("GetLaserScannerData",ptr_method);
		GetLaserScannerDataFunc = reinterpret_cast<GetLaserScannerDataFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
