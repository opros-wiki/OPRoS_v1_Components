#ifndef _MOBILITY_H_
#define _MOBILITY_H_

#include "Application.h"
#include "OprosApiTypes.h"

namespace OPRoS
{
// 개요
/**
 *	Mobility API는 이동 로봇을 구동시키는 표준 API이다. 모든 Mobility는 이 클래스를 상속받아 구현되어야 하며,
 *	Mobility API는OPRoS Mobility Component를 통해 수행된다. 
 *	Mobility API는 Mobility Component로부터 파리미터를 받아 변수 및 메모리를 초기화 하고, Mobility 하드웨어까지 초기화를 수행한다. 
 *	Mobility API는 동적 라이브러리로 생성되며 Mobility Component에서 로드하여 사용된다.
 *	<center><table border=0>
 *	<tr><td colspan=3><center><b>Mobility API에서 사용하는 Parameter</b></center></td></tr>
 *	<tr><td bgcolor=#dddddd><center><b>Index</b></center></td><td bgcolor=#dddddd><center><b>Type of Value</b></center></td><td bgcolor=#dddddd><center><b>Description</b></center></td></tr>
 *	<tr><td><b>wheelDiameter</b></td><td>double</td><td>이동 장치에 사용될 바퀴의 지름이다.(단위:m)</td></tr>
 *	<tr><td><b>axleDistance</b></td><td>double</td><td>하나의 축 상에 있는 두 바퀴간의 거리이다.(단위:m)</td></tr>
 *	<tr><td><b>varianceDistance</b></td><td>double</td><td>10m 이동하였을 때 발생하는 직선거리상의 오차이다.(단위:m)</td></tr>
 *	<tr><td><b>varianceDirection</b></td><td>double</td><td>360도 회전하였을 때 발생하는 방향각도상의 오차이다.(단위:degree)</td></tr>
 *	<tr><td><b>safeRadius</b></td><td>double</td><td>이동하는 주체인 로봇이 차지하는 영역이 반지름이다.(단위:m)</td></tr>
 *	<tr><td><b>maximumVelocity</b></td><td>double</td><td>이동 장치의 최고속도 제한이다.</td></tr>
 *	<tr><td><b>acceleration</b></td><td>double</td><td>이동 장치의 가속도이다.</td></tr>
 *	</table></center>
 */
class Mobility : public Application
{
public:
	Mobility(void) { };
	virtual ~Mobility(void) { };

public:
	/**
	 *	Mobility API를 초기화 하는 표준 함수이다.
	 *  Mobility Component로부터 파라미터를 받아 Mobility API의 변수 및 메모리를 초기화 하고,
	 *	Mobility API에서 사용하는 라이브러리등을 초기화 한다.
	 *	@param parameter 초기화에 필요한 파라미터.
	 *	@return true - 초기화 성공<br>
	 *			false - 초기화 실패<br>
	 */
	virtual bool initialize(Property parameter) = 0;

	/**
	 *	Mobility API를 종료 하는 표준 함수이다.
	 *  Mobility API에서 사용하는 메모리나 다른 라이브러리를 해제한다.
	 *	@return true - 종료 성공<br>
	 *			false - 종료 실패<br>
	 */
	virtual bool finalize(void) = 0;

	/**
	 *	Mobility API를 활성화 하는 표준 함수이다.
	 *	이 함수가 호출되면 Mobility의 actuator를 servo on하게 되고 Mobility를 움직일 수 있다.
	 *	@return true - 활성화 성공<br>
	 *			false - 활성화 실패<br>
	 */
	virtual bool enable(void) = 0;

	/**
	 *	Mobility API를 비활성화 하는 표준 함수이다.
	 *	이 함수가 호출되면 Mobility의 actuatorf를 servo off하게 되고 Mobility를 움직일 수 없다.
	 *	@return true - 비활성화 성공<br>
	 *			false - 비활성화 실패<br>
	 */	
	virtual bool disable(void) = 0;

	/**
	 *	Mobility API의 파리미터를 설정하는 표준 함수이다.
	 *	Mobility의 파리미터를 설정함과 동시에 최대속도, 가속도 등의 설정값들이 actuator에 반영이 된다.
	 *	@param parameter Mobility API에 필요한 파라미터.
	 *	@return true - 파리미터 설정 성공<br>
	 *			false - 파라미터 설정 실패<br>
	 */
	virtual bool setParameter(Property parameter) = 0;

	/**
	 *	Mobility API가 가지고 있는 파리미터 정보를 얻는 표준 함수이다.
	 *	@return parameter - Mobility API의 파라미터<br>
	 */
	virtual Property getParameter(void) = 0;

	/**
	 *	로봇의 위치를 설정하는 표준 함수이다.
	 *	@param position 로봇의 위치.
	 *	@return true - 설정 성공<br>
	 *			false - 설정 실패<br>
	 */
	virtual bool setPosition(ObjectLocation position) = 0;

	/**
	 *	로봇의 위치를 얻는 표준 함수이다.
	 *	@param position 로봇의 위치.
	 *	@return true - 유효한 데이터<br>
	 *			false - 유효하지 않은 데이터<br>
	 */
	virtual bool getPosition(ObjectLocation *position) = 0;

	/**
	 *	로봇의 양쪽 바퀴에 대한 누적된 회전량 얻는 표준 함수이다.
	 *	@param leftEncoder 누적된 왼쪽 바퀴의 회전량.
	 *	@param rightEncoder 누적된 오른쪽 바퀴의 회전량.
	 *	@return true - 유효한 데이터<br>
	 *			false - 유효하지 않은 데이터<br>
	 */
	virtual bool readEncoder(long *leftEncoder, long *rightEncoder) = 0;

	/**
	 *	입력 거리만큼 로봇을 전진시키는 표준 함수이다.
	 *	@param distance 전진 거리(단위:m).
	 *	@return true - 명령 수행의 성공<br>
	 *			false - 명령 수행의 실패<br>
	 */
	virtual bool move(double distance) = 0;

	/**
	 *	입력 거리만큼 로봇을 회전시키는 표준 함수이다.
	 *	@param degree 회전 각도(단위:도).
	 *	@return true - 명령 수행의 성공<br>
	 *			false - 명령 수행의 실패<br>
	 */
	virtual bool rotate(double degree) = 0;

	/**
	 *	입력 전진속도, 회전속도로 로봇을 움직이는 표준 함수이다.
	 *	@param forwardVelocity 전진 속도(m/s).
	 *	@param angularVelocity 회전 속도(rad/s).
	 *	@return true - 명령 수행의 성공<br>
	 *			false - 명령 수행의 실패<br>
	 */
	virtual bool drive(double forwardVelocity, double angularVelocity) = 0;

	/**
	 *	Mobility를 멈추는 표준 함수이다.
	 *	이 함수는 Mobility에 설정되어 있는 가속도로 감속하기 때문에 감속해서 멈출때 까지의 거리를 고려해야한다.
	 *	@return true - 명령 수행의 성공.<br>
	 *			false - 명령 수행의 실패.<br>	
	 */
	virtual bool stop(void) = 0;

	/**
	 *	Mobility가 움직이고 있는지를 확인하는 표준 함수이다.
	 *	@return true - 움직이고 있는 상태.<br>
	 *			false - 멈춰있는 상태.<br>	
	 */
	virtual bool isWheelRunning(void) = 0;

	/**
	 *	Mobility에서 주기적으로 수행할 수 있게금 지원하는 표준 callback 함수이다.
	 *	수행 주기는 Mobility Component의 수행주기와 동일하며, 이 함수는 none blocking 형태가 되어야 한다.
	 *	@return true - 수행의 성공.<br>
	 *			false - 수행의 실패.<br>	
	 */
	virtual bool execute(void) = 0;

	/**
	 *	Mobility에서 주기적으로 갱신할 수 있게금 지원하는 표준 callback 함수이다.
	 *	갱신 주기는 Mobility Component의 갱신주기와 동일하며 수행주기와 동일하다.
	 *	이 함수는 none blocking 형태가 되어야 한다.
	 *	@return true - 갱신의 성공.<br>
	 *			false - 갱신의 실패.<br>	
	 */
	virtual bool update(void) = 0;
};

};

#endif
