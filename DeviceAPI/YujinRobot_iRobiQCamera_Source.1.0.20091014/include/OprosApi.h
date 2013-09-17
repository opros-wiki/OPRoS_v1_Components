#ifndef	_OPROS_API_H_
#define	_OPROS_API_H_

#include "OprosApiTypes.h"

namespace OPRoS
{

/**
 *	OprosApi는 OPRoS 표준 API의 최상의 클래스로 모든 OPRoS API는 이 API에서 상속되어 구현된다.
 *	이 API의 모든 인터페이스는 순수가상함수로 구현되어 있어서 이 API를 상속받아 구현되는 모든
 *	API는 모든 인터페이스를 반드시 재정의(구현)하여 사용해야 한다.
 */
class OprosApi
{
public:
	/**
	 *	OprosApi의 기본 생성자이다.
	 */
	OprosApi(void) { };

	/**
	 *	OprosApi의 기본 소멸자이다.
	 */
	virtual ~OprosApi(void) { };

protected:
	/**
	 *	API에서 필요한 설정정보를 저장하는 변수.
	 */
	Property parameter;

public:
	/**
	 *	API를 초기화한다.
	 */
	virtual bool initialize(Property parameter) = 0;

	/**
	 *	API를 종료시킨다.
	 */
	virtual bool finalize(void) = 0;

	/**
	 *	API를 활성화시킨다.
	 */
	virtual bool enable(void) = 0;

	/**
	 *	API를 비활성화 시킨다.
	 */
	virtual bool disable(void) = 0;
	
	/**
	 *	API의 파라미터를 설정한다.
	 */
	virtual bool setParameter(Property parameter) = 0;

	/**
	 *	API의 파라미터를 읽는다.
	 */
	virtual Property getParameter(void) = 0;
};

typedef	OPRoS::OprosApi *(*GET_OPROS_API)();

using namespace OPRoS;

};


#endif