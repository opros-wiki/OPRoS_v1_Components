#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "OprosApi.h"

namespace OPRoS
{

/**
 *	Application�� ǥ�� ���� API�� ���� Ŭ�����̴�. ��� ǥ�� ���� API�� Application�� ��� �޾�
 *	�����ؾ� �Ѵ�.
 *	<table border=0>
 *	<tr><td colspan=1>
 *	<center><img src="../../images/uml/UML_Application.jpg"></center>
 *	</td></tr></table>
*/
class Application : public OprosApi
{
public:
	Application(void) { };
	virtual ~Application(void) { };

public:
	/**
	 *	���� API�� �ʱ�ȭ �ϴ� ǥ�� �Լ��̴�.
	 *  ������Ʈ�κ��� �Ķ���͸� �޾� ���� API�� ���� �� �޸𸮸� �ʱ�ȭ �Ѵ�. 
	 *	@param parameter �ʱ�ȭ�� �ʿ��� �Ķ����.
	 *	@return true - �ʱ�ȭ ����<br>
	 *			false - �ʱ�ȭ ����<br>
	 */
	virtual bool initialize(Property parameter) = 0;

	/**
	 *	���� API�� ���� �ϴ� ǥ�� �Լ��̴�.
	 *  ���� API���� ����ϴ� �޸𸮳� �ٸ� ���̺귯���� �����Ѵ�.
	 *	@return true - ���� ����<br>
	 *			false - ���� ����<br>
	 */
	virtual bool finalize(void) = 0;

	/**
	 *	���� API�� Ȱ��ȭ �ϴ� ǥ�� �Լ��̴�.
	 *	@return true - Ȱ��ȭ ����<br>
	 *			false - Ȱ��ȭ ����<br>
	 */
	virtual bool enable(void) = 0;

	/**
	 *	���� API�� ��Ȱ��ȭ �ϴ� ǥ�� �Լ��̴�.
	 *	@return true - ��Ȱ��ȭ ����<br>
	 *			false - ��Ȱ��ȭ ����<br>
	 */
	virtual bool disable(void) = 0;

	/**
	 *	���� API�� �ĸ����͸� �����ϴ� ǥ�� �Լ��̴�.
	 *	@param parameter ���� API�� �ʿ��� �Ķ����.
	 *	@return true - �ĸ����� ���� ����<br>
	 *			false - �Ķ���� ���� ����<br>
	 */
	virtual bool setParameter(Property parameter) = 0;

	/**
	 *	���� API�� �ĸ����͸� ��� ǥ�� �Լ��̴�.
	 *	@return ���� API�� �Ķ����<br>
	 */
	virtual Property getParameter(void) = 0;
};


};


#endif
