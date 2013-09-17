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
*	이 클래스는 NavigationComponent의 서비스 포트를 호출하기 위해 사용되는 클래스이다.<br>
*	이 클래스를 통해서 외부의 다른 컴포넌트들이 NavigationComponent의 서비스 포트를 호출할 수 있다.
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
	*	KeyInputServicePortRequired의 생성자이다.<br>
	*	서비스 포트를 초기화하는 함수를 호출한다.
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
	*	서비스 포트를 설정한다. NavigationComponent의 서비스 포트를 등록한다.	
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
