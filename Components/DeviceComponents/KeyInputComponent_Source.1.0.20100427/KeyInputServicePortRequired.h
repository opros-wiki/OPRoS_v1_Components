#ifndef _KeyInputServicePort_REQUIRED_PORT_H
#define _KeyInputServicePort_REQUIRED_PORT_H

#include <OPRosTypes.h>
#include <InputDataPort.h>
#include <OutputDataPort.h>
#include <InputEventPort.h>
#include <OutputEventPort.h>
#include <ProvidedServicePort.h>
#include <RequiredServicePort.h>
#include <ProvidedMethod.h>
#include <RequiredMethod.h>

/**
*	�� Ŭ������ NavigationComponent�� ���� ��Ʈ�� ȣ���ϱ� ���� ���Ǵ� Ŭ�����̴�.<br>
*	�� Ŭ������ ���ؼ� �ܺ��� �ٸ� ������Ʈ���� NavigationComponent�� ���� ��Ʈ�� ȣ���� �� �ִ�.
*/
class KeyInputServicePortRequired	: public RequiredServicePort
{
protected:

	typedef RequiredMethod<bool> setParameterFuncType;
	setParameterFuncType *setParameterFunc;

	typedef RequiredMethod<bool> getParameterFuncType;
	getParameterFuncType *getParameterFunc;

	typedef ProvidedMethod<int> getKeyInputFuncType;
	getKeyInputFuncType *getKeyInputFunc;

public:
	/**
	*	KeyInputServicePortRequired�� �������̴�.<br>
	*	���� ��Ʈ�� �ʱ�ȭ�ϴ� �Լ��� ȣ���Ѵ�.
	*/
	KeyInputServicePortRequired()
	{
		setParameterFunc = NULL;
		getParameterFunc = NULL;
		getKeyInputFunc = NULL;

		setup();
	}

	bool setParameter(OPRoS::Property parameter)
	{
		assert(setParameterFunc != NULL);
		return (*setParameterFunc)(parameter);
	}

	bool getParameter(Property *parameter)
	{
		assert(getParameterFunc != NULL);
		return (*getParameterFunc)(parameter);
	}

	virtual bool getKeyInput(HWND hWnd)
	{
		assert(getKeyInputFunc != NULL);
		return (*getKeyInputFunc)(hWnd);
	}


	/**
	*	���� ��Ʈ�� �����Ѵ�. NavigationComponent�� ���� ��Ʈ�� ����Ѵ�.	
	*/
	virtual void setup()
	{
		Method *ptr_method;

		ptr_method = makeRequiredMethod(&KeyInputServicePortRequired::setParameter,"setParameter");
		assert(ptr_method != NULL);
		addMethod("setParameter",ptr_method);
		setParameterFunc = reinterpret_cast<setParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeRequiredMethod(&KeyInputServicePortRequired::getParameter,"getParameter");
		assert(ptr_method != NULL);
		addMethod("getParameter",ptr_method);
		getParameterFunc = reinterpret_cast<getParameterFuncType *>(ptr_method);
		ptr_method = NULL;

		ptr_method = makeProvidedMethod(&KeyInputServicePortRequired::getKeyInput,"getKeyInput");
		assert(ptr_method != NULL);
		addMethod("getKeyInput",ptr_method);
		getKeyInputFunc = reinterpret_cast<getKeyInputFuncType *>(ptr_method);
		ptr_method = NULL;
	}
};
#endif
