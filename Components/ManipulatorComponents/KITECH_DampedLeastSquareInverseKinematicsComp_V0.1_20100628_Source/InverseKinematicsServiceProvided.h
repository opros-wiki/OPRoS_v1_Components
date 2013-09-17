#ifndef _InverseKinematicsService_PROVIDED_PORT_H
#define _InverseKinematicsService_PROVIDED_PORT_H

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
 * IInverseKinematicsService
 *
 * The comonent inherits this class and implements methods. 
*/
class IInverseKinematicsService
{
public:
	virtual bool SetParameter(Property parameter)=0;
	virtual Property GetParameter()=0;
	virtual int GetError()=0;
	virtual bool SetJointPosition(vector<double> jointPosition)=0;
	virtual vector<double> GetJointPosition()=0;
	virtual bool SetDesiredPosition(ObjectPosition desiredPosition)=0;
	virtual ObjectPosition GetCurrentPosition()=0;
};

/*
 * 
 * InverseKinematicsService : public ProvidedServicePort
 *
 */
class InverseKinematicsServiceProvided
	:public ProvidedServicePort, public IInverseKinematicsService
{
protected:
    IInverseKinematicsService *pcom;

	typedef ProvidedMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef ProvidedMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef ProvidedMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef ProvidedMethod<bool> SetJointPositionFuncType;
	SetJointPositionFuncType *SetJointPositionFunc;

	typedef ProvidedMethod< vector<double> > GetJointPositionFuncType;
	GetJointPositionFuncType *GetJointPositionFunc;

	typedef ProvidedMethod<bool> SetDesiredPositionFuncType;
	SetDesiredPositionFuncType *SetDesiredPositionFunc;

	typedef ProvidedMethod<ObjectPosition> GetCurrentPositionFuncType;
	GetCurrentPositionFuncType *GetCurrentPositionFunc;

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
	
	virtual bool SetDesiredPosition(ObjectPosition desiredPosition)
	{
		assert(SetDesiredPositionFunc != NULL);

		return (*SetDesiredPositionFunc)(desiredPosition);
	}

	virtual ObjectPosition GetCurrentPosition()
	{
		assert(GetCurrentPositionFunc != NULL);

		return (*GetCurrentPositionFunc)();
	}

public:
    //
    // Constructor
    //
	InverseKinematicsServiceProvided(IInverseKinematicsService *fn)
	{
		pcom = fn;

		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		SetJointPositionFunc = NULL;
		GetJointPositionFunc = NULL;
		SetDesiredPositionFunc = NULL;
		GetCurrentPositionFunc = NULL;

		setup();
	}

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeProvidedMethod(&IInverseKinematicsService::SetParameter,pcom,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IInverseKinematicsService::GetParameter,pcom,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IInverseKinematicsService::GetError,pcom,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IInverseKinematicsService::SetJointPosition,pcom,"SetJointPosition");
		assert(ptr_method != NULL);
		addMethod("SetJointPosition",ptr_method);
		SetJointPositionFunc = reinterpret_cast<SetJointPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IInverseKinematicsService::GetJointPosition,pcom,"GetJointPosition");
		assert(ptr_method != NULL);
		addMethod("GetJointPosition",ptr_method);
		GetJointPositionFunc = reinterpret_cast<GetJointPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IInverseKinematicsService::SetDesiredPosition,pcom,"SetDesiredPosition");
		assert(ptr_method != NULL);
		addMethod("SetDesiredPosition",ptr_method);
		SetDesiredPositionFunc = reinterpret_cast<SetDesiredPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IInverseKinematicsService::GetCurrentPosition,pcom,"GetCurrentPosition");
		assert(ptr_method != NULL);
		addMethod("GetCurrentPosition",ptr_method);
		GetCurrentPositionFunc = reinterpret_cast<GetCurrentPositionFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
