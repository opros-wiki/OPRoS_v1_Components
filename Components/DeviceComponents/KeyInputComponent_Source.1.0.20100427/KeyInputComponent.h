/*************************************************************

 file: KeyInputComponent.h
 author: S.G. Bang
 begin: April 20 2010
 copyright: (c) 2010 KNU, OPRoS
 email: hspark@kangwon.ac.kr

***************************************************************

OPRoS source code is provided under a dual license mode:
 LGPL and OPRoS individually.

LGPL: You can redistribute it and/or modify it under the terms
 of the Less GNU General Public License as published by the Free
 Software Foundation, either version 3 of the License.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of 
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 Less GNU General Public License for more details. 

 You should have received a copy of the Less GNU General Public
 License along with this program. If not, see 
 <http://www.gnu.org/licenses/>.

OPRoS individual license: An individual license is a license for
 modifying the source code of OPRoS and distiributing it in a
 closed format for commercial purposes.

 If you are interested in this option, please see 
 <http://www.opros.or.kr>.

This license policy may be changed without prior notice.

***************************************************************/

#ifndef _KeyInputComponent_COMPONENT_H
#define _KeyInputComponent_COMPONENT_H
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
#include <OPRosTypes.h>

#include "Component.h"
#include "KeyInputServicePortProvided.h"
#include <Windows.h>
// ����
/**
*	<table><tr><td>
*	KeyInputComponent�� Ű���� �Է��� ���� ������Ʈ�̴�.
*	KeyInputComponent�� KeyInputComponent.xml,
*	KeyInputComponentServicePortProvided.h�� ���ԵǾ���ϸ�, KeyInputComponentComponent.xml����
*	KeyInputComponent�� ���������� ����Ǿ� �ִ�. KeyInputComponentServicePortProvided.h��
*	�� ������Ʈ���� �����ϴ� ���� ��Ʈ�� ȣ���� �� �ִ� �������̽��� �����Ѵ�.
*/
class KeyInputComponent: public Component, IKeyInputServicePort
{
protected:
	// �Ӽ�
	//	Variables for KeyInputComponent

	IKeyInputServicePort *ptrKeyInputServicePort;

public:
	/**
	*	KeyInputComponent Ŭ������ �⺻ �������̴�.<br>
	*	��Ʈ�� �ʱ�ȭ��Ű�� �Լ��� ȣ���Ѵ�.
	*/
	KeyInputComponent();
	/**
	*	KeyInputComponent Ŭ������ �������ڸ� ������ �������̴�.<br>
	*	��Ʈ�� �ʱ�ȭ��Ű�� �Լ��� ȣ���Ѵ�.
	*	@param compId ������Ʈ�� ID.
	*/
	KeyInputComponent(const std::string &compId);
	/**
	*	KeyInputComponent Ŭ������ �⺻ �Ҹ����̴�.
	*/
	virtual ~KeyInputComponent();
	/**
	*	KeyInputComponent���� �����ϴ� ���� ��Ʈ�� �ʱ�ȭ�ϰ� ����Ѵ�.
	*/
	virtual void portSetup();

protected:
	// Callback API
	/**
	*	������Ʈ�� �ʱ�ȭ�� �� ȣ��Ǵ� �ݹ��Լ��̴�.
	*	XML�� ����� ������Ƽ������ �о DLL�� �ε��ϰ�,
	*	�ʿ��� API�� �ε��� �� �ʱ�ȭ �Ѵ�.
	*	@return OPROS_SUCCESS - ������Ʈ �ʱ�ȭ ����<br>
	*			OPROS_FIND_PROPERTY_ERROR - ������Ƽ������ DLL�����̸��� ����<br>
	*			OPROS_FIND_DLL_ERROR - DLL�� ã�� �� ����<br>
	*			OPROS_LOAD_DLL_ERROR - DLL�� �ε��� �� ����<br>
	*			OPROS_INITIALIZE_API_ERROR - API�ʱ�ȭ ���� �����߻�<br>
	*/
	virtual ReturnType onInitialize();

	/**
	*	������Ʈ�� Ȱ��ȭ�� �� ȣ��Ǵ� �ݹ��Լ��̴�.
	*	@return OPROS_SUCCESS - ������Ʈ Ȱ��ȭ ����<br>
	*			OPROS_PRECONDITION_NOT_MET - API�ڵ��� NULL�̰ų� ������Ʈ�� ���°� READY�Ǵ� INACTIVE ���°� �ƴ�<br>
	*			OPROS_ENABLE_API_ERROR - APIȰ��ȭ ���� �����߻�<br>
	*/
	virtual ReturnType onStart();

	/**
	*	������Ʈ�� ��Ȱ��ȭ�� �� ȣ��Ǵ� �ݹ��Լ��̴�.
	*	@return OPROS_SUCCESS - ������Ʈ ��Ȱ��ȭ ����<br>
	*			OPROS_PRECONDITION_NOT_MET - API�ڵ��� NULL�̰ų� ������Ʈ�� ���°� ACTIVE ���°� �ƴ�<br>
	*			OPROS_DISABLE_API_ERROR - API��Ȱ��ȭ ���� �����߻�<br>
	*/
	virtual ReturnType onStop();

	/**
	*	������Ʈ�� ���� �� �� ȣ��Ǵ� �ݹ��Լ��̴�.
	*	�����۾��� ������ �� APIȣ�� ������ finalize, initialize, enable���̴�.
	*	����ϴ� ��� API�� ���� ���� �۾��� �����Ѵ�.
	*	ȣ�⿡ ������ ��� ������ ���� �Ѵ�. enableȣ�⿡ �����ϸ� �ٽ� finalize�� ȣ���Ѵ�.
	*	@return OPROS_SUCCESS - ������Ʈ ���� ����<br>
	*			OPROS_PRECONDITION_NOT_MET - API�ڵ��� NULL�� ����<br>
	*			OPROS_RESET_API_ERROR - API���� ���� �����߻�<br>
	*/
	virtual ReturnType onReset();

	/**
	*	������Ʈ�� ������ �߻����� �� ȣ��Ǵ� �ݹ��Լ��̴�.
	*	������ �߻��ϸ� API�� disable�� ȣ���Ͽ� ��Ȱ��ȭ ��Ų��.
	*	����ϴ� ��� API�� ���� ���� �۾��� �����Ѵ�.
	*	@return OPROS_SUCCESS - �����߻� �� ��Ȱ��ȭ ����<br>
	*			OPROS_PRECONDITION_NOT_MET - API�ڵ��� NULL�� ����<br>
	*			OPROS_DISABLE_API_ERROR - API��Ȱ��ȭ ���� �����߻�<br>
	*/
	virtual ReturnType onError();

	/**
	*	������Ʈ�� ������ ������ �� ȣ��Ǵ� �ݹ��Լ��̴�.
	*	���� ���� �� APIȣ�� ������ finalize, initialize���̴�.
	*	����ϴ� ��� API�� ���� ���� �۾��� �����Ѵ�.
	*	@return OPROS_SUCCESS - �������� ����<br>
	*			OPROS_PRECONDITION_NOT_MET - API�ڵ��� NULL�� ����<br>
	*			OPROS_RECOVER_API_ERROR - API���� ���� �����߻�<br>
	*/
	virtual ReturnType onRecover();

	/**
	*	������Ʈ�� ����� �� ȣ��Ǵ� �ݹ��Լ��̴�.
	*	finalize�� ȣ���Ͽ� API�� �����ϰ�, API�ڵ�� DLL�ڵ��� �����Ѵ�.
	*	����ϴ� ��� API�� ���� ���� �۾��� �����Ѵ�.
	*	@return OPROS_SUCCESS - ������Ʈ ���� ����<br>
	*			OPROS_PRECONDITION_NOT_MET - API�ڵ��� NULL�� ����<br>
	*			OPROS_FINALIZE_API_ERROR - API���� ���� �����߻�<br>
	*/
	virtual ReturnType onDestroy();

public:
	/**
	*	������Ʈ�� �̺�Ʈ�� �޾��� �� ȣ��Ǵ� �ݹ��Լ��̴�.
	*	KeyInputComponent������ ������ ����.
	*	@return OPROS_SUCCESS &nbsp;
	*/
	virtual ReturnType onEvent(Event *evt);

	/**
	*	������Ʈ�� �ֱ������� ������ �� ȣ��Ǵ� �ݹ��Լ��̴�.
	*	API�� execute�� ȣ���Ͽ� ������ �����Ѵ�.
	*	@return OPROS_SUCCESS - ������Ʈ ���� ����<br>
	*			OPROS_CALLER_ERROR - ������Ʈ ���� ����, �Ǵ� API�ڵ��� NULL�� ���<br>
	*/
	virtual ReturnType onExecute();

	/**
	*	������Ʈ�� �ֱ������� ������ �� ȣ��Ǵ� �ݹ��Լ��̴�.
	*	KeyInputComponent������ ������ ����.
	*	@return OPROS_SUCCESS &nbsp;
	*/
	virtual ReturnType onUpdated();

	/**
	*	������Ʈ�� ���� �ֱⰡ ����Ǿ��� �� ȣ��Ǵ� �ݹ��Լ��̴�.
	*	KeyInputComponent������ ������ ����.
	*	@return OPROS_SUCCESS &nbsp;
	*/
	virtual ReturnType onPeriodChanged();
public:

	// ������Ʈ
	/**
	*	KeyInputComponent�� ���������� �����Ѵ�.
	*	�ٸ� ������Ʈ���� �� ������Ʈ�� ���������� ������ �� ���ȴ�.
	*	API�� setParameter�� ȣ���Ͽ� �� ����� �����Ѵ�.
	*	@param parameter ������ �Ķ���� ����
	*	@return true - �Ķ���� �����ͼ��� ����<br>
	*			false - �Ķ���� �����ͼ����� �����߰ų�, API�ڵ��� NULL�� ���, �Ǵ�<br>
	* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; ������Ʈ�� ���°� ACTIVE, INACTIVE�� �ƴ� �ٸ� ������ ���<br>
	*/
	virtual bool setParameter(Property parameter);

	/**
	*	KeyInputComponent�� ���������� �ٸ� ������Ʈ���� ������ �� ���ȴ�.
	*	@param parameter �Ķ���������� �����
	*	@return true - �Ķ���� ������ �������� ����<br>
	*			false - API�ڵ��� NULL�� ���<br>
	*/
	virtual bool getParameter(Property *parameter);

	/**
	*	Ű���� �Է� ó���ϴ� �Լ��̴�.
	*	@return ret - update���� üũ�� Ű������ ������ ���� ���ϰ��� ������<BR>
		*/
	virtual int getKeyInput();//HWND hWnd);
private:
//	HWND hWnd;
	int ret;

};

#endif

