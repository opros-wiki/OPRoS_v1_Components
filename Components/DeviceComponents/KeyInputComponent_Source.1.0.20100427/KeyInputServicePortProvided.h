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
*	�� Ŭ������ KeyInputComponent�� ǥ�� �������̽��� ������ Ŭ�����̴�.<br>
*	KeyInputServicePortProvided Ŭ������ KeyInputComponent�� Ŭ������ �� Ŭ������ ��ӹ޾� �����ȴ�.
*/
class IKeyInputServicePort
{
public:
	virtual bool setParameter(Property parameter) = 0;
	virtual bool getParameter(Property *parameter) = 0;
};

/**
*	�� Ŭ������ NavigationComponent�� ���� ��Ʈ�� ������ Ŭ�����̴�.<br>
*	�� Ŭ������ ���ؼ� �ܺ��� �ٸ� ������Ʈ���� NavigationComponent�� ���� ��Ʈ�� ȣ���� �� �ִ�.
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
	*	KeyInputServicePortProvided�� �������̴�.<br>
	*	�� �����ڰ� ȣ��Ǹ� NavigationComponent�� ���� �������̽��� ȣ��ȴ�.
	*/
	KeyInputServicePortProvided(IKeyInputServicePort *fn)
	{
		pcom = fn;

		setParameterFunc = NULL;
		getParameterFunc = NULL;

		setup();
	}

	/**
	*	���� ��Ʈ�� ����Ѵ�.
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
