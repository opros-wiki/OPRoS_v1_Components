#ifndef _TrackingControlService_PROVIDED_PORT_H
#define _TrackingControlService_PROVIDED_PORT_H

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
 * ITrackingControlService
 *
 * The comonent inherits this class and implements methods. 
*/
class ITrackingControlService
{
public:
	virtual bool SetParameter(Property parameter)=0;
	virtual Property GetParameter()=0;
	virtual int GetError()=0;
	virtual bool SetJointAcceleration(vector<double> jointAcceleration)=0;
	virtual vector<double> GetJointAcceleration()=0;
	virtual bool SetJointVelocity(vector<double> jointVelocity)=0;
	virtual vector<double> GetJointVelocity()=0;
	virtual bool SetJointPosition(vector<double> jointPosition)=0;
	virtual vector<double> GetJointPosition()=0;
	virtual bool SetDesiredJointAcceleration(vector<double> desiredJointAcceleration)=0;
	virtual vector<double> GetDesiredJointAcceleration()=0;
	virtual bool SetDesiredJointVelocity(vector<double> desiredJointVelocity)=0;
	virtual vector<double> GetDesiredJointVelocity()=0;
	virtual bool SetDesiredJointPosition(vector<double> desiredJointPosition)=0;
	virtual vector<double> GetDesiredJointPosition()=0;
	virtual vector<double> SloveTrackingControl()=0;
};

/*
 * 
 * TrackingControlService : public ProvidedServicePort
 *
 */
class TrackingControlServiceProvided
	:public ProvidedServicePort, public ITrackingControlService
{
protected:
    ITrackingControlService *pcom;

	typedef ProvidedMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef ProvidedMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef ProvidedMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef ProvidedMethod<bool> SetJointAccelerationFuncType;
	SetJointAccelerationFuncType *SetJointAccelerationFunc;

	typedef ProvidedMethod< vector<double> > GetJointAccelerationFuncType;
	GetJointAccelerationFuncType *GetJointAccelerationFunc;

	typedef ProvidedMethod<bool> SetJointVelocityFuncType;
	SetJointVelocityFuncType *SetJointVelocityFunc;

	typedef ProvidedMethod< vector<double> > GetJointVelocityFuncType;
	GetJointVelocityFuncType *GetJointVelocityFunc;

	typedef ProvidedMethod<bool> SetJointPositionFuncType;
	SetJointPositionFuncType *SetJointPositionFunc;

	typedef ProvidedMethod< vector<double> > GetJointPositionFuncType;
	GetJointPositionFuncType *GetJointPositionFunc;

	typedef ProvidedMethod<bool> SetDesiredJointAccelerationFuncType;
	SetDesiredJointAccelerationFuncType *SetDesiredJointAccelerationFunc;

	typedef ProvidedMethod< vector<double> > GetDesiredJointAccelerationFuncType;
	GetDesiredJointAccelerationFuncType *GetDesiredJointAccelerationFunc;

	typedef ProvidedMethod<bool> SetDesiredJointVelocityFuncType;
	SetDesiredJointVelocityFuncType *SetDesiredJointVelocityFunc;

	typedef ProvidedMethod< vector<double> > GetDesiredJointVelocityFuncType;
	GetDesiredJointVelocityFuncType *GetDesiredJointVelocityFunc;

	typedef ProvidedMethod<bool> SetDesiredJointPositionFuncType;
	SetDesiredJointPositionFuncType *SetDesiredJointPositionFunc;

	typedef ProvidedMethod< vector<double> > GetDesiredJointPositionFuncType;
	GetDesiredJointPositionFuncType *GetDesiredJointPositionFunc;

	typedef ProvidedMethod< vector<double> > SloveTrackingControlFuncType;
	SloveTrackingControlFuncType *SloveTrackingControlFunc;

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

	virtual bool SetJointAcceleration(vector<double> jointAcceleration)
	{
		assert(SetJointAccelerationFunc != NULL);

		return (*SetJointAccelerationFunc)(jointAcceleration);
	}

	virtual vector<double> GetJointAcceleration()
	{
		assert(GetJointAccelerationFunc != NULL);

		return (*GetJointAccelerationFunc)();
	}

	virtual bool SetJointVelocity(vector<double> jointVelocity)
	{
		assert(SetJointVelocityFunc != NULL);

		return (*SetJointVelocityFunc)(jointVelocity);
	}

	virtual vector<double> GetJointVelocity()
	{
		assert(GetJointVelocityFunc != NULL);

		return (*GetJointVelocityFunc)();
	}

	virtual bool SetJointPosition(vector<double> jointPosition)
	{
		assert(SetJointPositionFunc != NULL);

		return (*SetJointPositionFunc)(jointPosition);
	}

	virtual vector<double> GetJointPosition()
	{
		assert(GetJointPositionFunc != NULL);

		return (*GetJointPositionFunc)();
	}

	virtual bool SetDesiredJointAcceleration(vector<double> desiredJointAcceleration)
	{
		assert(SetDesiredJointAccelerationFunc != NULL);

		return (*SetDesiredJointAccelerationFunc)(desiredJointAcceleration);
	}

	virtual vector<double> GetDesiredJointAcceleration()
	{
		assert(GetDesiredJointAccelerationFunc != NULL);

		return (*GetDesiredJointAccelerationFunc)();
	}

	virtual bool SetDesiredJointVelocity(vector<double> desiredJointVelocity)
	{
		assert(SetDesiredJointVelocityFunc != NULL);

		return (*SetDesiredJointVelocityFunc)(desiredJointVelocity);
	}

	virtual vector<double> GetDesiredJointVelocity()
	{
		assert(GetDesiredJointVelocityFunc != NULL);

		return (*GetDesiredJointVelocityFunc)();
	}

	virtual bool SetDesiredJointPosition(vector<double> desiredJointPosition)
	{
		assert(SetDesiredJointPositionFunc != NULL);

		return (*SetDesiredJointPositionFunc)(desiredJointPosition);
	}

	virtual vector<double> GetDesiredJointPosition()
	{
		assert(GetDesiredJointPositionFunc != NULL);

		return (*GetDesiredJointPositionFunc)();
	}

	virtual vector<double> SloveTrackingControl()
	{
		assert(SloveTrackingControlFunc != NULL);

		return (*SloveTrackingControlFunc)();
	}

public:
    //
    // Constructor
    //
    TrackingControlServiceProvided(ITrackingControlService *fn)
    {
		pcom = fn;

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

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeProvidedMethod(&ITrackingControlService::SetParameter,pcom,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&ITrackingControlService::GetParameter,pcom,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&ITrackingControlService::GetError,pcom,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&ITrackingControlService::SetJointAcceleration,pcom,"SetJointAcceleration");
		assert(ptr_method != NULL);
		addMethod("SetJointAcceleration",ptr_method);
		SetJointAccelerationFunc = reinterpret_cast<SetJointAccelerationFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&ITrackingControlService::GetJointAcceleration,pcom,"GetJointAcceleration");
		assert(ptr_method != NULL);
		addMethod("GetJointAcceleration",ptr_method);
		GetJointAccelerationFunc = reinterpret_cast<GetJointAccelerationFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&ITrackingControlService::SetJointVelocity,pcom,"SetJointVelocity");
		assert(ptr_method != NULL);
		addMethod("SetJointVelocity",ptr_method);
		SetJointVelocityFunc = reinterpret_cast<SetJointVelocityFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&ITrackingControlService::GetJointVelocity,pcom,"GetJointVelocity");
		assert(ptr_method != NULL);
		addMethod("GetJointVelocity",ptr_method);
		GetJointVelocityFunc = reinterpret_cast<GetJointVelocityFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&ITrackingControlService::SetJointPosition,pcom,"SetJointPosition");
		assert(ptr_method != NULL);
		addMethod("SetJointPosition",ptr_method);
		SetJointPositionFunc = reinterpret_cast<SetJointPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&ITrackingControlService::GetJointPosition,pcom,"GetJointPosition");
		assert(ptr_method != NULL);
		addMethod("GetJointPosition",ptr_method);
		GetJointPositionFunc = reinterpret_cast<GetJointPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&ITrackingControlService::SetDesiredJointAcceleration,pcom,"SetDesiredJointAcceleration");
		assert(ptr_method != NULL);
		addMethod("SetDesiredJointAcceleration",ptr_method);
		SetDesiredJointAccelerationFunc = reinterpret_cast<SetDesiredJointAccelerationFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&ITrackingControlService::GetDesiredJointAcceleration,pcom,"GetDesiredJointAcceleration");
		assert(ptr_method != NULL);
		addMethod("GetDesiredJointAcceleration",ptr_method);
		GetDesiredJointAccelerationFunc = reinterpret_cast<GetDesiredJointAccelerationFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&ITrackingControlService::SetDesiredJointVelocity,pcom,"SetDesiredJointVelocity");
		assert(ptr_method != NULL);
		addMethod("SetDesiredJointVelocity",ptr_method);
		SetDesiredJointVelocityFunc = reinterpret_cast<SetDesiredJointVelocityFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&ITrackingControlService::GetDesiredJointVelocity,pcom,"GetDesiredJointVelocity");
		assert(ptr_method != NULL);
		addMethod("GetDesiredJointVelocity",ptr_method);
		GetDesiredJointVelocityFunc = reinterpret_cast<GetDesiredJointVelocityFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&ITrackingControlService::SetDesiredJointPosition,pcom,"SetDesiredJointPosition");
		assert(ptr_method != NULL);
		addMethod("SetDesiredJointPosition",ptr_method);
		SetDesiredJointPositionFunc = reinterpret_cast<SetDesiredJointPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&ITrackingControlService::GetDesiredJointPosition,pcom,"GetDesiredJointPosition");
		assert(ptr_method != NULL);
		addMethod("GetDesiredJointPosition",ptr_method);
		GetDesiredJointPositionFunc = reinterpret_cast<GetDesiredJointPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&ITrackingControlService::SloveTrackingControl,pcom,"SloveTrackingControl");
		assert(ptr_method != NULL);
		addMethod("SloveTrackingControl",ptr_method);
		SloveTrackingControlFunc = reinterpret_cast<SloveTrackingControlFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
