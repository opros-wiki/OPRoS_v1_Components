#ifndef _WheelControllerService_PROVIDED_PORT_H
#define _WheelControllerService_PROVIDED_PORT_H

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
 * IWheelControllerService
 *
 * The comonent inherits this class and implements methods. 
*/
class IWheelControllerService
{
public:
	virtual bool SetParameter(Property parameter)=0;
	virtual Property GetParameter()=0;
	virtual int GetError()=0;
	virtual bool SetPosition(ObjectLocation position)=0;
	virtual ObjectLocation GetPosition()=0;
	virtual bool DriveWheel(WheelControlVelocity velocity)=0;
	virtual bool MoveWheel(double distance)=0;
	virtual bool RotateWheel(double degree)=0;
	virtual bool StopWheel()=0;
	virtual bool IsWheelRunning()=0;
};

/*
 * 
 * WheelControllerService : public ProvidedServicePort
 *
 */
class WheelControllerServiceProvided : public ProvidedServicePort, public IWheelControllerService
{
protected:
	IWheelControllerService *pcom;

	typedef ProvidedMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef ProvidedMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef ProvidedMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef ProvidedMethod<bool> SetPositionFuncType;
	SetPositionFuncType *SetPositionFunc;

	typedef ProvidedMethod<ObjectLocation> GetPositionFuncType;
	GetPositionFuncType *GetPositionFunc;

	typedef ProvidedMethod<bool> DriveWheelFuncType;
	DriveWheelFuncType *DriveWheelFunc;

	typedef ProvidedMethod<bool> MoveWheelFuncType;
	MoveWheelFuncType *MoveWheelFunc;

	typedef ProvidedMethod<bool> RotateWheelFuncType;
	RotateWheelFuncType *RotateWheelFunc;

	typedef ProvidedMethod<bool> StopWheelFuncType;
	StopWheelFuncType *StopWheelFunc;

	typedef ProvidedMethod<bool> IsWheelRunningFuncType;
	IsWheelRunningFuncType *IsWheelRunningFunc;

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

	virtual bool SetPosition(ObjectLocation position)
	{
		assert(SetPositionFunc != NULL);

		return (*SetPositionFunc)(position);
	}

	virtual ObjectLocation GetPosition()
	{
		assert(GetPositionFunc != NULL);

		return (*GetPositionFunc)();
	}

	virtual bool DriveWheel(WheelControlVelocity velocity)
	{
		assert(DriveWheelFunc != NULL);

		return (*DriveWheelFunc)(velocity);
	}

	virtual bool MoveWheel(double distance)
	{
		assert(MoveWheelFunc != NULL);

		return (*MoveWheelFunc)(distance);
	}

	virtual bool RotateWheel(double degree)
	{
		assert(RotateWheelFunc != NULL);

		return (*RotateWheelFunc)(degree);
	}

	virtual bool StopWheel()
	{
		assert(StopWheelFunc != NULL);

		return (*StopWheelFunc)();
	}

	virtual bool IsWheelRunning()
	{
		assert(IsWheelRunningFunc != NULL);

		return (*IsWheelRunningFunc)();
	}

public:
    //
    // Constructor
    //
    WheelControllerServiceProvided(IWheelControllerService *fn)
    {
		pcom = fn;

		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		SetPositionFunc = NULL;
		GetPositionFunc = NULL;
		DriveWheelFunc = NULL;
		MoveWheelFunc = NULL;
		RotateWheelFunc = NULL;
		StopWheelFunc = NULL;
		IsWheelRunningFunc = NULL;

		setup();
	}

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeProvidedMethod(&IWheelControllerService::SetParameter,pcom,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IWheelControllerService::GetParameter,pcom,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IWheelControllerService::GetError,pcom,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IWheelControllerService::SetPosition,pcom,"SetPosition");
		assert(ptr_method != NULL);
		addMethod("SetPosition",ptr_method);
		SetPositionFunc = reinterpret_cast<SetPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IWheelControllerService::GetPosition,pcom,"GetPosition");
		assert(ptr_method != NULL);
		addMethod("GetPosition",ptr_method);
		GetPositionFunc = reinterpret_cast<GetPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IWheelControllerService::DriveWheel,pcom,"DriveWheel");
		assert(ptr_method != NULL);
		addMethod("DriveWheel",ptr_method);
		DriveWheelFunc = reinterpret_cast<DriveWheelFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IWheelControllerService::MoveWheel,pcom,"MoveWheel");
		assert(ptr_method != NULL);
		addMethod("MoveWheel",ptr_method);
		MoveWheelFunc = reinterpret_cast<MoveWheelFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IWheelControllerService::RotateWheel,pcom,"RotateWheel");
		assert(ptr_method != NULL);
		addMethod("RotateWheel",ptr_method);
		RotateWheelFunc = reinterpret_cast<RotateWheelFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IWheelControllerService::StopWheel,pcom,"StopWheel");
		assert(ptr_method != NULL);
		addMethod("StopWheel",ptr_method);
		StopWheelFunc = reinterpret_cast<StopWheelFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IWheelControllerService::IsWheelRunning,pcom,"IsWheelRunning");
		assert(ptr_method != NULL);
		addMethod("IsWheelRunning",ptr_method);
		IsWheelRunningFunc = reinterpret_cast<IsWheelRunningFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
