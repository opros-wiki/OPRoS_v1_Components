#ifndef _WheelControllerService_REQUIRED_PORT_H
#define _WheelControllerService_REQUIRED_PORT_H

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
 * WheelControllerService : public RequiredServicePort
 *
 */
class WheelControllerServiceRequired : public RequiredServicePort
{
protected:
	typedef RequiredMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef RequiredMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef RequiredMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef RequiredMethod<bool> SetPositionFuncType;
	SetPositionFuncType *SetPositionFunc;

	typedef RequiredMethod<ObjectLocation> GetPositionFuncType;
	GetPositionFuncType *GetPositionFunc;

	typedef RequiredMethod<bool> DriveWheelFuncType;
	DriveWheelFuncType *DriveWheelFunc;

	typedef RequiredMethod<bool> MoveWheelFuncType;
	MoveWheelFuncType *MoveWheelFunc;

	typedef RequiredMethod<bool> RotateWheelFuncType;
	RotateWheelFuncType *RotateWheelFunc;

	typedef RequiredMethod<bool> StopWheelFuncType;
	StopWheelFuncType *StopWheelFunc;

	typedef RequiredMethod<bool> IsWheelRunningFuncType;
	IsWheelRunningFuncType *IsWheelRunningFunc;

public:
	//
	// Constructor
	//
	WheelControllerServiceRequired()
	{
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

	bool SetPosition(ObjectLocation position)
	{
		assert(SetPositionFunc != NULL);
	
		return (*SetPositionFunc)(position);
	}

	ObjectLocation GetPosition()
	{
		assert(GetPositionFunc != NULL);

		return (*GetPositionFunc)();
	}

	bool DriveWheel(WheelControlVelocity velocity)
	{
		assert(DriveWheelFunc != NULL);

		return (*DriveWheelFunc)(velocity);
	}

	bool MoveWheel(double distance)
	{
		assert(MoveWheelFunc != NULL);

		return (*MoveWheelFunc)(distance);
	}

	bool RotateWheel(double degree)
	{
		assert(RotateWheelFunc != NULL);

		return (*RotateWheelFunc)(degree);
	}

	bool StopWheel()
	{
		assert(StopWheelFunc != NULL);

		return (*StopWheelFunc)();
	}

	bool IsWheelRunning()
	{
		assert(IsWheelRunningFunc != NULL);

		return (*IsWheelRunningFunc)();
	}

    // generated setup function
    virtual void setup()
    {
		Method *ptr_method;

		ptr_method = makeRequiredMethod(&WheelControllerServiceRequired::SetParameter,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&WheelControllerServiceRequired::GetParameter,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&WheelControllerServiceRequired::GetError,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&WheelControllerServiceRequired::SetPosition,"SetPosition");
		assert(ptr_method != NULL);
		addMethod("SetPosition",ptr_method);
		SetPositionFunc = reinterpret_cast<SetPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&WheelControllerServiceRequired::GetPosition,"GetPosition");
		assert(ptr_method != NULL);
		addMethod("GetPosition",ptr_method);
		GetPositionFunc = reinterpret_cast<GetPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&WheelControllerServiceRequired::DriveWheel,"DriveWheel");
		assert(ptr_method != NULL);
		addMethod("DriveWheel",ptr_method);
		DriveWheelFunc = reinterpret_cast<DriveWheelFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&WheelControllerServiceRequired::MoveWheel,"MoveWheel");
		assert(ptr_method != NULL);
		addMethod("MoveWheel",ptr_method);
		MoveWheelFunc = reinterpret_cast<MoveWheelFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&WheelControllerServiceRequired::RotateWheel,"RotateWheel");
		assert(ptr_method != NULL);
		addMethod("RotateWheel",ptr_method);
		RotateWheelFunc = reinterpret_cast<RotateWheelFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&WheelControllerServiceRequired::StopWheel,"StopWheel");
		assert(ptr_method != NULL);
		addMethod("StopWheel",ptr_method);
		StopWheelFunc = reinterpret_cast<StopWheelFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&WheelControllerServiceRequired::IsWheelRunning,"IsWheelRunning");
		assert(ptr_method != NULL);
		addMethod("IsWheelRunning",ptr_method);
		IsWheelRunningFunc = reinterpret_cast<IsWheelRunningFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
