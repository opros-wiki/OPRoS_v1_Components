#ifndef _InverseKinematicsService_REQUIRED_PORT_H
#define _InverseKinematicsService_REQUIRED_PORT_H

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
 * InverseKinematicsService : public RequiredServicePort
 *
 */
class InverseKinematicsServiceRequired
:public RequiredServicePort
{
protected:
	typedef RequiredMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef RequiredMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef RequiredMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef RequiredMethod<bool> SetJointPositionFuncType;
	SetJointPositionFuncType *SetJointPositionFunc;

	typedef RequiredMethod<vector<double>> GetJointPositionFuncType;
	GetJointPositionFuncType *GetJointPositionFunc;

	typedef RequiredMethod<bool> SetDesiredPositionFuncType;
	SetDesiredPositionFuncType *SetDesiredPositionFunc;

	typedef RequiredMethod<ObjectPosition> GetCurrentPositionFuncType;
	GetCurrentPositionFuncType *GetCurrentPositionFunc;

public:
	//
	// Constructor
	//
	InverseKinematicsServiceRequired()
	{
		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		SetJointPositionFunc = NULL;
		GetJointPositionFunc = NULL;
		SetDesiredPositionFunc = NULL;
		GetCurrentPositionFunc = NULL;

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

	bool SetDesiredPosition(ObjectPosition desiredPosition)
	{
		assert(SetDesiredPositionFunc != NULL);

		return (*SetDesiredPositionFunc)(desiredPosition);
	}

	ObjectPosition GetCurrentPosition()
	{
		assert(GetCurrentPositionFunc != NULL);

		return (*GetCurrentPositionFunc)();
	}

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeRequiredMethod(&InverseKinematicsServiceRequired::SetParameter,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&InverseKinematicsServiceRequired::GetParameter,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&InverseKinematicsServiceRequired::GetError,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&InverseKinematicsServiceRequired::SetJointPosition,"SetJointPosition");
		assert(ptr_method != NULL);
		addMethod("SetJointPosition",ptr_method);
		SetJointPositionFunc = reinterpret_cast<SetJointPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&InverseKinematicsServiceRequired::GetJointPosition,"GetJointPosition");
		assert(ptr_method != NULL);
		addMethod("GetJointPosition",ptr_method);
		GetJointPositionFunc = reinterpret_cast<GetJointPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&InverseKinematicsServiceRequired::SetDesiredPosition,"SetDesiredPosition");
		assert(ptr_method != NULL);
		addMethod("SetDesiredPosition",ptr_method);
		SetDesiredPositionFunc = reinterpret_cast<SetDesiredPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&InverseKinematicsServiceRequired::GetCurrentPosition,"GetCurrentPosition");
		assert(ptr_method != NULL);
		addMethod("GetCurrentPosition",ptr_method);
		GetCurrentPositionFunc = reinterpret_cast<GetCurrentPositionFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
