#ifndef _TrackingControlService_REQUIRED_PORT_H
#define _TrackingControlService_REQUIRED_PORT_H

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
 * TrackingControlService : public RequiredServicePort
 *
 */
class TrackingControlServiceRequired
   :public RequiredServicePort
{
protected:
	typedef RequiredMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef RequiredMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef RequiredMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef RequiredMethod<bool> SetJointAccelerationFuncType;
	SetJointAccelerationFuncType *SetJointAccelerationFunc;

	typedef RequiredMethod< vector<double> > GetJointAccelerationFuncType;
	GetJointAccelerationFuncType *GetJointAccelerationFunc;

	typedef RequiredMethod<bool> SetJointVelocityFuncType;
	SetJointVelocityFuncType *SetJointVelocityFunc;

	typedef RequiredMethod< vector<double> > GetJointVelocityFuncType;
	GetJointVelocityFuncType *GetJointVelocityFunc;

	typedef RequiredMethod<bool> SetJointPositionFuncType;
	SetJointPositionFuncType *SetJointPositionFunc;

	typedef RequiredMethod< vector<double> > GetJointPositionFuncType;
	GetJointPositionFuncType *GetJointPositionFunc;

	typedef RequiredMethod<bool> SetDesiredJointAccelerationFuncType;
	SetDesiredJointAccelerationFuncType *SetDesiredJointAccelerationFunc;

	typedef RequiredMethod< vector<double> > GetDesiredJointAccelerationFuncType;
	GetDesiredJointAccelerationFuncType *GetDesiredJointAccelerationFunc;

	typedef RequiredMethod<bool> SetDesiredJointVelocityFuncType;
	SetDesiredJointVelocityFuncType *SetDesiredJointVelocityFunc;

	typedef RequiredMethod< vector<double> > GetDesiredJointVelocityFuncType;
	GetDesiredJointVelocityFuncType *GetDesiredJointVelocityFunc;

	typedef RequiredMethod<bool> SetDesiredJointPositionFuncType;
	SetDesiredJointPositionFuncType *SetDesiredJointPositionFunc;

	typedef RequiredMethod< vector<double> > GetDesiredJointPositionFuncType;
	GetDesiredJointPositionFuncType *GetDesiredJointPositionFunc;

	typedef RequiredMethod< vector<double> > SloveTrackingControlFuncType;
	SloveTrackingControlFuncType *SloveTrackingControlFunc;

public:
	//
	// Constructor
	//
	TrackingControlServiceRequired()
	{
		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		SetJointAccelerationFunc = NULL;
		GetJointAccelerationFunc = NULL;
		SetJointVelocityFunc = NULL;
		GetJointVelocityFunc = NULL;
		SetJointPositionFunc = NULL;
		GetJointPositionFunc = NULL;
		SetDesiredJointAccelerationFunc = NULL;
		GetDesiredJointAccelerationFunc = NULL;
		SetDesiredJointVelocityFunc = NULL;
		GetDesiredJointVelocityFunc = NULL;
		SetDesiredJointPositionFunc = NULL;
		GetDesiredJointPositionFunc = NULL;
		SloveTrackingControlFunc = NULL;

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

	bool SetJointAcceleration(vector<double> jointAcceleration)
	{
		assert(SetJointAccelerationFunc != NULL);

		return (*SetJointAccelerationFunc)(jointAcceleration);
	}

	vector<double> GetJointAcceleration()
	{
		assert(GetJointAccelerationFunc != NULL);

		return (*GetJointAccelerationFunc)();
	}

	bool SetJointVelocity(vector<double> jointVelocity)
	{
		assert(SetJointVelocityFunc != NULL);

		return (*SetJointVelocityFunc)(jointVelocity);
	}

	vector<double> GetJointVelocity()
	{
		assert(GetJointVelocityFunc != NULL);

		return (*GetJointVelocityFunc)();
	}

	bool SetJointPosition(vector<double> jointPosition)
	{
		assert(SetJointPositionFunc != NULL);

		return (*SetJointPositionFunc)(jointPosition);
	}

	vector<double> GetJointPosition()
	{
		assert(GetJointPositionFunc != NULL);

		return (*GetJointPositionFunc)();
	}

	bool SetDesiredJointAcceleration(vector<double> desiredJointAcceleration)
	{
		assert(SetDesiredJointAccelerationFunc != NULL);

		return (*SetDesiredJointAccelerationFunc)(desiredJointAcceleration);
	}

	vector<double> GetDesiredJointAcceleration()
	{
		assert(GetDesiredJointAccelerationFunc != NULL);

		return (*GetDesiredJointAccelerationFunc)();
	}

	bool SetDesiredJointVelocity(vector<double> desiredJointVelocity)
	{
		assert(SetDesiredJointVelocityFunc != NULL);

		return (*SetDesiredJointVelocityFunc)(desiredJointVelocity);
	}

	vector<double> GetDesiredJointVelocity()
	{
		assert(GetDesiredJointVelocityFunc != NULL);

		return (*GetDesiredJointVelocityFunc)();
	}

	bool SetDesiredJointPosition(vector<double> desiredJointPosition)
	{
		assert(SetDesiredJointPositionFunc != NULL);

		return (*SetDesiredJointPositionFunc)(desiredJointPosition);
	}

	vector<double> GetDesiredJointPosition()
	{
		assert(GetDesiredJointPositionFunc != NULL);

		return (*GetDesiredJointPositionFunc)();
	}

	vector<double> SloveTrackingControl()
	{
		assert(SloveTrackingControlFunc != NULL);

		return (*SloveTrackingControlFunc)();
	}

    // generated setup function
    virtual void setup()
    {
		Method *ptr_method;

		ptr_method = makeRequiredMethod(&TrackingControlServiceRequired::SetParameter,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&TrackingControlServiceRequired::GetParameter,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&TrackingControlServiceRequired::GetError,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&TrackingControlServiceRequired::SetJointAcceleration,"SetJointAcceleration");
		assert(ptr_method != NULL);
		addMethod("SetJointAcceleration",ptr_method);
		SetJointAccelerationFunc = reinterpret_cast<SetJointAccelerationFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&TrackingControlServiceRequired::GetJointAcceleration,"GetJointAcceleration");
		assert(ptr_method != NULL);
		addMethod("GetJointAcceleration",ptr_method);
		GetJointAccelerationFunc = reinterpret_cast<GetJointAccelerationFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&TrackingControlServiceRequired::SetJointVelocity,"SetJointVelocity");
		assert(ptr_method != NULL);
		addMethod("SetJointVelocity",ptr_method);
		SetJointVelocityFunc = reinterpret_cast<SetJointVelocityFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&TrackingControlServiceRequired::GetJointVelocity,"GetJointVelocity");
		assert(ptr_method != NULL);
		addMethod("GetJointVelocity",ptr_method);
		GetJointVelocityFunc = reinterpret_cast<GetJointVelocityFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&TrackingControlServiceRequired::SetJointPosition,"SetJointPosition");
		assert(ptr_method != NULL);
		addMethod("SetJointPosition",ptr_method);
		SetJointPositionFunc = reinterpret_cast<SetJointPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&TrackingControlServiceRequired::GetJointPosition,"GetJointPosition");
		assert(ptr_method != NULL);
		addMethod("GetJointPosition",ptr_method);
		GetJointPositionFunc = reinterpret_cast<GetJointPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&TrackingControlServiceRequired::SetDesiredJointAcceleration,"SetDesiredJointAcceleration");
		assert(ptr_method != NULL);
		addMethod("SetDesiredJointAcceleration",ptr_method);
		SetDesiredJointAccelerationFunc = reinterpret_cast<SetDesiredJointAccelerationFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&TrackingControlServiceRequired::GetDesiredJointAcceleration,"GetDesiredJointAcceleration");
		assert(ptr_method != NULL);
		addMethod("GetDesiredJointAcceleration",ptr_method);
		GetDesiredJointAccelerationFunc = reinterpret_cast<GetDesiredJointAccelerationFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&TrackingControlServiceRequired::SetDesiredJointVelocity,"SetDesiredJointVelocity");
		assert(ptr_method != NULL);
		addMethod("SetDesiredJointVelocity",ptr_method);
		SetDesiredJointVelocityFunc = reinterpret_cast<SetDesiredJointVelocityFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&TrackingControlServiceRequired::GetDesiredJointVelocity,"GetDesiredJointVelocity");
		assert(ptr_method != NULL);
		addMethod("GetDesiredJointVelocity",ptr_method);
		GetDesiredJointVelocityFunc = reinterpret_cast<GetDesiredJointVelocityFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&TrackingControlServiceRequired::SetDesiredJointPosition,"SetDesiredJointPosition");
		assert(ptr_method != NULL);
		addMethod("SetDesiredJointPosition",ptr_method);
		SetDesiredJointPositionFunc = reinterpret_cast<SetDesiredJointPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&TrackingControlServiceRequired::GetDesiredJointPosition,"GetDesiredJointPosition");
		assert(ptr_method != NULL);
		addMethod("GetDesiredJointPosition",ptr_method);
		GetDesiredJointPositionFunc = reinterpret_cast<GetDesiredJointPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&TrackingControlServiceRequired::SloveTrackingControl,"SloveTrackingControl");
		assert(ptr_method != NULL);
		addMethod("SloveTrackingControl",ptr_method);
		SloveTrackingControlFunc = reinterpret_cast<SloveTrackingControlFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
