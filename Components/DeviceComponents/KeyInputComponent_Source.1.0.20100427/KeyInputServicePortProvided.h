#ifndef _KeyInputServicePort_PROVIDED_PORT_H
#define _KeyInputServicePort_PROVIDED_PORT_H

#include <OPRoSTypes.h>
#include <InputDataPort.h>
#include <OutputDataPort.h>
#include <InputEventPort.h>
#include <OutputEventPort.h>
#include <ProvidedServicePort.h>
#include <RequiredServicePort.h>
#include <ProvidedMethod.h>
#include <RequiredMethod.h>

#include "OprosApiTypes.h"

using namespace OPRoS;

/**
*	이 클래스는 KeyInputComponent의 표준 인터페이스를 정의한 클래스이다.<br>
*	KeyInputServicePortProvided 클래스와 KeyInputComponent는 클래스는 이 클래스를 상속받아 구현된다.
*/
class IKeyInputServicePort
{
public:
	virtual bool setParameter(Property parameter) = 0;
	virtual bool getParameter(Property *parameter) = 0;
};

/**
*	이 클래스는 NavigationComponent의 서비스 포트를 정의한 클래스이다.<br>
*	이 클래스를 통해서 외부의 다른 컴포넌트들이 NavigationComponent의 서비스 포트를 호출할 수 있다.
*/
class KeyInputServicePortProvided : public ProvidedServicePort, virtual IKeyInputServicePort
{
protected:
	IKeyInputServicePort *pcom;

	typedef ProvidedMethod<bool> setParameterFuncType;
	setParameterFuncType *setParameterFunc;

	typedef ProvidedMethod<bool> getParameterFuncType;
	getParameterFuncType *getParameterFunc;


public:
	virtual bool setParameter(Property parameter)
	{
		assert(setParameterFunc != NULL);
		return (*setParameterFunc)(parameter);
	}

	virtual bool getParameter(Property *parameter)
	{
		assert(getParameterFunc != NULL);
		return (*getParameterFunc)(parameter);
	}


public:
	/**
	*	KeyInputServicePortProvided의 생성자이다.<br>
	*	이 생성자가 호출되면 NavigationComponent의 서비스 인터페이스가 호출된다.
	*/
	KeyInputServicePortProvided(IKeyInputServicePort *fn)
	{
		pcom = fn;

		setParameterFunc = NULL;
		getParameterFunc = NULL;

		setup();
	}

	/**
	*	서비스 포트를 등록한다.
	*/
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeProvidedMethod(&IKeyInputServicePort::setParameter,pcom,"setParameter");
		assert(ptr_method != NULL);
		addMethod("setParameter",ptr_method);
		setParameterFunc = reinterpret_cast<setParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&IKeyInputServicePort::getParameter,pcom,"getParameter");
		assert(ptr_method != NULL);
		addMethod("getParameter",ptr_method);
		getParameterFunc = reinterpret_cast<getParameterFuncType *>(ptr_method);
		ptr_method = NULL;

	}
};
#endif
