#ifndef _TrajectoryGenerationService_REQUIRED_PORT_H
#define _TrajectoryGenerationService_REQUIRED_PORT_H

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
 * TrajectoryGenerationService : public RequiredServicePort
 *
 */
class TrajectoryGenerationServiceRequired
   :public RequiredServicePort
{
protected:

	typedef RequiredMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef RequiredMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef RequiredMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef RequiredMethod<bool> GenerateTrajectoryFuncType;
	GenerateTrajectoryFuncType *GenerateTrajectoryFunc;

	typedef RequiredMethod< vector< valarray<double> > > GetAccelerationFuncType;
	GetAccelerationFuncType *GetAccelerationFunc;

	typedef RequiredMethod< vector< valarray<double> > > GetVelocityFuncType;
	GetVelocityFuncType *GetVelocityFunc;

	typedef RequiredMethod< vector< valarray<double> > > GetPositionFuncType;
	GetPositionFuncType *GetPositionFunc;

public:
	//
	// Constructor
	//
	TrajectoryGenerationServiceRequired()
	{
		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		GenerateTrajectoryFunc = NULL;
		GetAccelerationFunc = NULL;
		GetVelocityFunc = NULL;
		GetPositionFunc = NULL;

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

	bool GenerateTrajectory(vector < valarray<double> > pathData)
	{
		assert(GenerateTrajectoryFunc != NULL);

		return (*GenerateTrajectoryFunc)(pathData);
	}

	vector< valarray<double> > GetAcceleration()
	{
		assert(GetAccelerationFunc != NULL);

		return (*GetAccelerationFunc)();
	}

	vector< valarray<double> > GetVelocity()
	{
		assert(GetVelocityFunc != NULL);

		return (*GetVelocityFunc)();
	}

	vector< valarray<double> > GetPosition()
	{
		assert(GetPositionFunc != NULL);

		return (*GetPositionFunc)();
	}

    // generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeRequiredMethod(&TrajectoryGenerationServiceRequired::SetParameter,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&TrajectoryGenerationServiceRequired::GetParameter,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&TrajectoryGenerationServiceRequired::GetError,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&TrajectoryGenerationServiceRequired::GenerateTrajectory,"GenerateTrajectory");
		assert(ptr_method != NULL);
		addMethod("GenerateTrajectory",ptr_method);
		GenerateTrajectoryFunc = reinterpret_cast<GenerateTrajectoryFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&TrajectoryGenerationServiceRequired::GetAcceleration,"GetAcceleration");
		assert(ptr_method != NULL);
		addMethod("GetAcceleration",ptr_method);
		GetAccelerationFunc = reinterpret_cast<GetAccelerationFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&TrajectoryGenerationServiceRequired::GetVelocity,"GetVelocity");
		assert(ptr_method != NULL);
		addMethod("GetVelocity",ptr_method);
		GetVelocityFunc = reinterpret_cast<GetVelocityFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&TrajectoryGenerationServiceRequired::GetPosition,"GetPosition");
		assert(ptr_method != NULL);
		addMethod("GetPosition",ptr_method);
		GetPositionFunc = reinterpret_cast<GetPositionFuncType *>(ptr_method);
		ptr_method = NULL;
    }
};
#endif
