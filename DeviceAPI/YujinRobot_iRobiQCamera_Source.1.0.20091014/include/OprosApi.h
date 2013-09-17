#ifndef	_OPROS_API_H_
#define	_OPROS_API_H_

#include "OprosApiTypes.h"

namespace OPRoS
{

/**
 *	OprosApi�� OPRoS ǥ�� API�� �ֻ��� Ŭ������ ��� OPRoS API�� �� API���� ��ӵǾ� �����ȴ�.
 *	�� API�� ��� �������̽��� ���������Լ��� �����Ǿ� �־ �� API�� ��ӹ޾� �����Ǵ� ���
 *	API�� ��� �������̽��� �ݵ�� ������(����)�Ͽ� ����ؾ� �Ѵ�.
 */
class OprosApi
{
public:
	/**
	 *	OprosApi�� �⺻ �������̴�.
	 */
	OprosApi(void) { };

	/**
	 *	OprosApi�� �⺻ �Ҹ����̴�.
	 */
	virtual ~OprosApi(void) { };

protected:
	/**
	 *	API���� �ʿ��� ���������� �����ϴ� ����.
	 */
	Property parameter;

public:
	/**
	 *	API�� �ʱ�ȭ�Ѵ�.
	 */
	virtual bool initialize(Property parameter) = 0;

	/**
	 *	API�� �����Ų��.
	 */
	virtual bool finalize(void) = 0;

	/**
	 *	API�� Ȱ��ȭ��Ų��.
	 */
	virtual bool enable(void) = 0;

	/**
	 *	API�� ��Ȱ��ȭ ��Ų��.
	 */
	virtual bool disable(void) = 0;
	
	/**
	 *	API�� �Ķ���͸� �����Ѵ�.
	 */
	virtual bool setParameter(Property parameter) = 0;

	/**
	 *	API�� �Ķ���͸� �д´�.
	 */
	virtual Property getParameter(void) = 0;
};

typedef	OPRoS::OprosApi *(*GET_OPROS_API)();

using namespace OPRoS;

};


#endif