#ifndef _NavigationService_PROVIDED_PORT_H
#define _NavigationService_PROVIDED_PORT_H

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
 * INavigationService
 *
 * The comonent inherits this class and implements methods. 
*/
class INavigationService
{
public:
	virtual bool SetParameter(Property parameter)=0;
	virtual Property GetParameter()=0;
	virtual int GetError()=0;
	virtual void SetPosition(ObjectLocation position)=0;
	virtual ObjectLocation GetPosition()=0;
	virtual bool NavigationTo(ObjectLocation targetPosition)=0;
	virtual bool Move(double distance)=0;
	virtual bool Rotate(double degree)=0;
	virtual void AbortNavigation()=0;
	virtual bool IsNavigationOngoing()=0;
};

/*
 * 
 * NavigationService : public ProvidedServicePort
 *
 */
class NavigationServiceProvided : public ProvidedServicePort, public INavigationService
{
protected:
	INavigationService *pcom;

	typedef ProvidedMethod<bool> SetParameterFuncType;
	SetParameterFuncType *SetParameterFunc;

	typedef ProvidedMethod<Property> GetParameterFuncType;
	GetParameterFuncType *GetParameterFunc;

	typedef ProvidedMethod<int> GetErrorFuncType;
	GetErrorFuncType *GetErrorFunc;

	typedef ProvidedMethod<void> SetPositionFuncType;
	SetPositionFuncType *SetPositionFunc;

	typedef ProvidedMethod<ObjectLocation> GetPositionFuncType;
	GetPositionFuncType *GetPositionFunc;

	typedef ProvidedMethod<bool> NavigationToFuncType;
	NavigationToFuncType *NavigationToFunc;

	typedef ProvidedMethod<bool> MoveFuncType;
	MoveFuncType *MoveFunc;

	typedef ProvidedMethod<bool> RotateFuncType;
	RotateFuncType *RotateFunc;

	typedef ProvidedMethod<void> AbortNavigationFuncType;
	AbortNavigationFuncType *AbortNavigationFunc;

	typedef ProvidedMethod<bool> IsNavigationOngoingFuncType;
	IsNavigationOngoingFuncType *IsNavigationOngoingFunc;

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

	virtual void SetPosition(ObjectLocation position)
	{
		assert(SetPositionFunc != NULL);
		(*SetPositionFunc)(position);
	}

	virtual ObjectLocation GetPosition()
	{
		assert(GetPositionFunc != NULL);
		return (*GetPositionFunc)();
	}

	virtual bool NavigationTo(ObjectLocation targetPosition)
	{
		assert(NavigationToFunc != NULL);
		return (*NavigationToFunc)(targetPosition);
	}

	virtual bool Move(double distance)
	{
		assert(MoveFunc != NULL);
		return (*MoveFunc)(distance);
	}

	virtual bool Rotate(double degree)
	{
		assert(RotateFunc != NULL);
		return (*RotateFunc)(degree);
	}

	virtual void AbortNavigation()
	{
		assert(AbortNavigationFunc != NULL);
		(*AbortNavigationFunc)();
	}

	virtual bool IsNavigationOngoing()
	{
		assert(IsNavigationOngoingFunc != NULL);
		return (*IsNavigationOngoingFunc)();
	}

public:
	//
	// Constructor
	//
	NavigationServiceProvided(INavigationService *fn)
	{
		pcom = fn;

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

	// generated setup function
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeProvidedMethod(&INavigationService::SetParameter,pcom,"SetParameter");
		assert(ptr_method != NULL);
		addMethod("SetParameter",ptr_method);
		SetParameterFunc = reinterpret_cast<SetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&INavigationService::GetParameter,pcom,"GetParameter");
		assert(ptr_method != NULL);
		addMethod("GetParameter",ptr_method);
		GetParameterFunc = reinterpret_cast<GetParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&INavigationService::GetError,pcom,"GetError");
		assert(ptr_method != NULL);
		addMethod("GetError",ptr_method);
		GetErrorFunc = reinterpret_cast<GetErrorFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&INavigationService::SetPosition,pcom,"SetPosition");
		assert(ptr_method != NULL);
		addMethod("SetPosition",ptr_method);
		SetPositionFunc = reinterpret_cast<SetPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&INavigationService::GetPosition,pcom,"GetPosition");
		assert(ptr_method != NULL);
		addMethod("GetPosition",ptr_method);
		GetPositionFunc = reinterpret_cast<GetPositionFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&INavigationService::NavigationTo,pcom,"NavigationTo");
		assert(ptr_method != NULL);
		addMethod("NavigationTo",ptr_method);
		NavigationToFunc = reinterpret_cast<NavigationToFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&INavigationService::Move,pcom,"Move");
		assert(ptr_method != NULL);
		addMethod("Move",ptr_method);
		MoveFunc = reinterpret_cast<MoveFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&INavigationService::Rotate,pcom,"Rotate");
		assert(ptr_method != NULL);
		addMethod("Rotate",ptr_method);
		RotateFunc = reinterpret_cast<RotateFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&INavigationService::AbortNavigation,pcom,"AbortNavigation");
		assert(ptr_method != NULL);
		addMethod("AbortNavigation",ptr_method);
		AbortNavigationFunc = reinterpret_cast<AbortNavigationFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&INavigationService::IsNavigationOngoing,pcom,"IsNavigationOngoing");
		assert(ptr_method != NULL);
		addMethod("IsNavigationOngoing",ptr_method);
		IsNavigationOngoingFunc = reinterpret_cast<IsNavigationOngoingFuncType *>(ptr_method);
		ptr_method = NULL;
	}
};
#endif
