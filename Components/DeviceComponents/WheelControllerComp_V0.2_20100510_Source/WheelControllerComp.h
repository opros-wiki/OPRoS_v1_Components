#ifndef _WheelControllerComp_COMPONENT_H
#define _WheelControllerComp_COMPONENT_H
/*
 *  Generated sources by OPRoS Component Generator (OCG V2)
 *   
 */
#include <Component.h>
#include <InputDataPort.h>
#include <OutputDataPort.h>
#include <InputEventPort.h>
#include <OutputEventPort.h>
#include <Event.h>
#include <OPRoSTypes.h>
#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

#include "WheelController.h"
#include "WheelControllerServiceProvided.h"
	

// ����
/**
*	WheelControllerComp�� �̵� �κ��� �� ��� ���� ������Ʈ�̴�.
*	�� ������Ʈ�� �� ������ ���� ǥ�� �������̽��� IWheelControllerCompService�� ��ӹ޾� �����ȴ�.
*	���� ���̺귯���� �����Ǹ� OPRoS API�� ǥ�� �������̽��� WheelController Ŭ������ ��ӹ޾� ������ OPRoS API ���̺귯���� �ε��Ͽ� ����ȴ�.
*	WheelController Ŭ������ ��ӹ޾� ������ OPRoS API ���̺귯���� ���� ���̺귯���ν� �̵� �κ�(�ϵ����)�� ���������� �̵� �κ� ��ü�� �������
*	�� ������Ʈ�� ������ �����ϴ�. OPRoS API ���̺귯���� ����ϱ� ���ؼ��� �� ������Ʈ�� xml ���������� �Ӽ��� ����ϰ��� �ϴ� OPRoS API
*	���̺귯�� ���� �̸��� OPRoS API���� �ʿ�� �ϴ� �Ķ���� ������ �����ؾ��Ѵ�.
*/
class WheelControllerComp: public Component ,public IWheelControllerService
{
protected:
// data


//event


// method for provider


// method for required
	


public:
	WheelControllerComp();
	WheelControllerComp(const std::string &compId);
	virtual ~WheelControllerComp();
	virtual void portSetup();

protected:
	virtual ReturnType onInitialize();
	virtual ReturnType onStart();
	virtual ReturnType onStop();
	virtual ReturnType onReset();
	virtual ReturnType onError();
	virtual ReturnType onRecover();
	virtual ReturnType onDestroy();

public:
	virtual ReturnType onEvent(Event *evt);
	virtual ReturnType onExecute();
	virtual ReturnType onUpdated();
	virtual ReturnType onPeriodChanged();

	/**
	*	�ĸ����͸� �����ϴ� ǥ�� �Լ��̴�.
	*	@param parameter �Ķ����.
	*	@return true - �ĸ����� ���� ����<br>
	*			false - �Ķ���� ���� ����<br>
	*/
	virtual bool SetParameter(Property parameter);

	/**
	*	�ĸ����͸� ��� ǥ�� �Լ��̴�.
	*	@param parameter �Ķ����.
	*	@return true - �ĸ����� ��� ����<br>
	*			false - �Ķ���� ��� ����<br>
	*/
	virtual Property GetParameter();

	virtual int GetError();

	/**
	*	�κ��� ��ġ�� �����ϴ� ǥ�� �Լ��̴�.
	*	@param position �κ��� ��ġ
	*	@return true - ���� ����<br>
	*	        false - ���� ����<br>
	*/
	virtual bool SetPosition(ObjectLocation position);

	/**
	*	������ �κ��� ��ġ�� ��� ǥ�� �Լ��̴�.
	*	@param position ������ �κ��� ��ġ
	*	@return true - ��� ����<br>
	*	        false - ��� ����<br>
	*/
	virtual ObjectLocation GetPosition();

	/**
	*	�κ��� �ӵ��� �����ϴ� ǥ�� �Լ��̴�.
	*	@param velocity �κ��� �ӵ�(�����ӵ�, ȸ���ӵ�)
	*	@return true - �ӵ� ���� ����<br>
	*	        false - �ӵ� ���� ����<br>
	*/
	virtual bool DriveWheel(WheelControlVelocity velocity);

	/**
	*	�κ��� �Է� �Ÿ���ŭ ������Ű�� ǥ�� �Լ��̴�.
	*	@param distance �̵� �Ÿ�(����:m)
	*	@return true - ���� ����<br>
	*	        false - ���� ���� ����<br>
	*/
	virtual bool MoveWheel(double distance);

	/**
	*	�κ��� �Է� ������ŭ ȸ����Ű�� ǥ�� �Լ��̴�.
	*	@param degree ȸ�� ����(����:degree)
	*	@return true - ȸ�� ����<br>
	*	        false - ȸ�� ����<br>
	*/
	virtual bool RotateWheel(double degree);

	/**
	*	�̵� ���� �κ��� ������Ű�� ǥ�� �Լ��̴�.
	*	@return true - ���� ����<br>
	*	        false - ���� ����<br>
	*/
	virtual bool StopWheel();

	/**
	*	�κ��� �̵� �������� ��ȯ�ϴ� ǥ�� �Լ��̴�.
	*	@return true - �̵� ����<br>
	*	        false - ���� ����<br>
	*/
	virtual bool IsWheelRunning();

private:
	/**
	*	OPRoS API ���̺귯���� �ڵ� �����̴�.
	*/
#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	/**
	*	OPRoS API ���̺귯���κ��� ������� WheelController�� Ŭ���� �����͸� ������ �����̴�.
	*/
	WheelController *wheelController;

	int error;
};

#endif

