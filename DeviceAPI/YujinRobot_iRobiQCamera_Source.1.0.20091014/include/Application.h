#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "OprosApi.h"

namespace OPRoS
{

/**
 *	Application는 표준 응용 API의 상위 클래스이다. 모든 표준 응용 API는 Application을 상속 받아
 *	구현해야 한다.
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
	 *	응용 API를 초기화 하는 표준 함수이다.
	 *  컴포넌트로부터 파라미터를 받아 응용 API의 변수 및 메모리를 초기화 한다. 
	 *	@param parameter 초기화에 필요한 파라미터.
	 *	@return true - 초기화 성공<br>
	 *			false - 초기화 실패<br>
	 */
	virtual bool initialize(Property parameter) = 0;

	/**
	 *	응용 API를 종료 하는 표준 함수이다.
	 *  응용 API에서 사용하는 메모리나 다른 라이브러리를 해제한다.
	 *	@return true - 종료 성공<br>
	 *			false - 종료 실패<br>
	 */
	virtual bool finalize(void) = 0;

	/**
	 *	응용 API를 활성화 하는 표준 함수이다.
	 *	@return true - 활성화 성공<br>
	 *			false - 활성화 실패<br>
	 */
	virtual bool enable(void) = 0;

	/**
	 *	응용 API를 비활성화 하는 표준 함수이다.
	 *	@return true - 비활성화 성공<br>
	 *			false - 비활성화 실패<br>
	 */
	virtual bool disable(void) = 0;

	/**
	 *	응용 API의 파리미터를 설정하는 표준 함수이다.
	 *	@param parameter 응용 API에 필요한 파라미터.
	 *	@return true - 파리미터 설정 성공<br>
	 *			false - 파라미터 설정 실패<br>
	 */
	virtual bool setParameter(Property parameter) = 0;

	/**
	 *	응용 API의 파리미터를 얻는 표준 함수이다.
	 *	@return 응용 API의 파라미터<br>
	 */
	virtual Property getParameter(void) = 0;
};


};


#endif
