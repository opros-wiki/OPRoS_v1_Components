#ifndef _NavigationService_REQUIRED_PORT_H
#define _NavigationService_REQUIRED_PORT_H

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
 * NavigationService : public RequiredServicePort
 *
 */
class NavigationServiceRequired : public RequiredServicePort
{
protected:

	typedef RequiredMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef RequiredMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef RequiredMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef RequiredMethod<void> SetPositionFuncType;
	SetPositionFuncType *SetPositionFunc;

	typedef RequiredMethod<ObjectLocation> GetPositionFuncType;
	GetPositionFuncType *GetPositionFunc;

	typedef RequiredMethod<bool> NavigationToFuncType;
	NavigationToFuncType *NavigationToFunc;

	typedef RequiredMethod<bool> MoveFuncType;
	MoveFuncType *MoveFunc;

	typedef RequiredMethod<bool> RotateFuncType;
	RotateFuncType *RotateFunc;

	typedef RequiredMethod<void> AbortNavigationFuncType;
	AbortNavigationFuncType *AbortNavigationFunc;

	typedef RequiredMethod<bool> IsNavigationOngoingFuncType;
	IsNavigationOngoingFuncType *IsNavigationOngoingFunc;

public:
	//
	// Constructor
	//
	NavigationServiceRequired()
	{
		SetParameterFunc = NULL;
		GetParameterFunc = NULL;
		GetErrorFunc = NULL;
		SetPositionFunc = NULL;
		GetPositionFunc = NULL;
		NavigationToFunc = NULL;
		MoveFunc = NULL;
		RotateFunc = NULL;
		AbortNavigationFunc = NULL;
		IsNavigationOngoingFunc = NULL;

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

	void SetPosition(ObjectLocation position)
	{
		assert(SetPositionFunc != NULL);
		(*SetPositionFunc)(position);
	}

	ObjectLocation GetPosition()
	{
		assert(GetPositionFunc != NULL);
		return (*GetPositionFunc)();
	}

	bool NavigationTo(ObjectLocation targetPosition)
	{
		assert(NavigationToFunc != NULL);
		return (*NavigationToFunc)(targetPosition);
	}

	bool Move(double distance)
	{
		assert(MoveFunc != NULL);
		return (*MoveFunc)(distance);
	}

	bool Rotate(double degree)
	{
		assert(RotateFunc != NULL);
		return (*RotateFunc)(degree);
	}

	void AbortNavigation()
	{
		assert(AbortNavigationFunc != NULL);
		(*AbortNavigationFunc)();
	}

	bool IsNavigationOngoing()
	{
		assert(IsNavigationOngoingFunc != NULL);
		return (*IsNavigationOngoingFunc)();
	}

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeRequiredMethod(&NavigationServiceRequired::SetParameter,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&NavigationServiceRequired::GetParameter,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&NavigationServiceRequired::GetError,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&NavigationServiceRequired::SetPosition,"SetPosition");
		assert(ptr_method != NULL);
		addMethod("SetPosition",ptr_method);
		SetPositionFunc = reinterpret_cast<SetPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&NavigationServiceRequired::GetPosition,"GetPosition");
		assert(ptr_method != NULL);
		addMethod("GetPosition",ptr_method);
		GetPositionFunc = reinterpret_cast<GetPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&NavigationServiceRequired::NavigationTo,"NavigationTo");
		assert(ptr_method != NULL);
		addMethod("NavigationTo",ptr_method);
		NavigationToFunc = reinterpret_cast<NavigationToFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&NavigationServiceRequired::Move,"Move");
		assert(ptr_method != NULL);
		addMethod("Move",ptr_method);
		MoveFunc = reinterpret_cast<MoveFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&NavigationServiceRequired::Rotate,"Rotate");
		assert(ptr_method != NULL);
		addMethod("Rotate",ptr_method);
		RotateFunc = reinterpret_cast<RotateFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&NavigationServiceRequired::AbortNavigation,"AbortNavigation");
		assert(ptr_method != NULL);
		addMethod("AbortNavigation",ptr_method);
		AbortNavigationFunc = reinterpret_cast<AbortNavigationFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&NavigationServiceRequired::IsNavigationOngoing,"IsNavigationOngoing");
		assert(ptr_method != NULL);
		addMethod("IsNavigationOngoing",ptr_method);
		IsNavigationOngoingFunc = reinterpret_cast<IsNavigationOngoingFuncType *>(ptr_method);
		ptr_method = NULL;
	}
};
#endif
