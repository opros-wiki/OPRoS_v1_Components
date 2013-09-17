#ifndef	_SERVO_ACTUATOR_H_
#define	_SERVO_ACTUATOR_H_

#include "Actuator.h"

namespace OPRoS
{

// 개요
/**
 *	서보 액추에이터 API는 모터 등과 같은 구동부를 위한 인터페이스이다.
 *	모든 서보 액추에이터는 ServoActuator 인터페이스를 이용해야 한다.
 *	Actuator는 power만으로 제어하는 구동부인 반면에, Servo Actuator는 속도제어 위치제어도
 *	가능한 구동부이다. setParameter 인터페이스가 호출되면 내부적으로 서보 액추에이터의
 *	최대출력, 최대속도, 가속도, 위치 제한을 설정해야 한다.
 *	<center><table border=0><tr><td colspan=3><center><b>GlobalMap API에서 사용하는 Parameter</b></center></td></tr>
 *	<tr><td bgcolor=#dddddd><center><b>Index</b></center></td><td bgcolor=#dddddd><center><b>Type of Value</b></center></td><td bgcolor=#dddddd><center><b>Description</b></center></td></tr>
 *	<tr><td><b>maximumPower</b></td><td>double</td><td>서보 액추에이터의 최대출력</td></tr>
 *	<tr><td><b>powerUnit</b></td><td>int</td><td>서보 액추에이터 출력의 단위를 설정한다. 0은 토크(Nm), 1은 파워(W), 2는 전류(A), 3은 비율(%) 을 나타낸다.</td></tr>
 *	<tr><td><b>type</b></td><td>int</td><td>서보 액추에이터의 타입을 설정한다. 0은 회전(Revolute) 타입이고, 1은 직선(Prismatic) 타입이다.</td></tr>
 *	<tr><td><b>encoderResolution</b></td><td>double</td><td>서보 액추에이터의 속도 및 위치를 계산하기 위해 사용되는 센서의 해상도를 나타낸다. type이 0일 때는 감속비 전단에서 측정되는 360도 당 측정되는 센서의 값이다.
 *	예를 들어 모터의 엔코더가 한바퀴 돌 때 2000펄스가 측정되면 encoderResolution은 2000이 된다. type이 1일 때는 1미터당 측정되는 센서의 값을 설정한다.</td></tr>
 *	<tr><td><b>reductionRatio</b></td><td>double</td><td>서보 액추에이터의 감속비(기어비)를 나타낸다. 모터에 감속비가 100:1로 연결되면 reduction Ratio는 100으로 설정한다.</td></tr>
 *	<tr><td><b>maximumVelocity</b></td><td>double</td><td>서보 액추에이터의 최대속도이다. type이 0인 경우 degree/s 단위로 설정하고, type이 1인 경우 m/s 단위로 설정한다.</td></tr>
 *	<tr><td><b>acceleration</b></td><td>double</td><td>서보 액추에이터의 가속도이다. type이 0인 경우 degree/s2d로 설정하고, type이 1인 경우 m/s2d로 설정한다.</td></tr>
 *	<tr><td><b>minimumPositionLimit</b></td><td>double</td><td>서보 액추에이터의 최소 위치 제한 파라미터이다. 서보 액추에이터는 설정된 값 이하로 위치를 설정할 수 없다.</td></tr>
 *	<tr><td><b>maximumPositionLimit</b></td><td>double</td><td>서보 액추에이터의 최대 위치 제한 파라미터이다. 액추에이터는 설정한 값 이상으로 위치를 설정할 수 없다.</td></tr>
 *	</table></center>
 */
class ServoActuator : public Actuator
{
public:
	ServoActuator(void) { };
	virtual ~ServoActuator(void) { };

public:
	/**
	 *	서보 액추에이터의 속도를 제어한다. type이 0인 경우 단위가 degree/s이고 1인 경우 단위가 m/s이다.
	 *	@param velocity 서보 액추에이터의 속도
	 *	@param time ms 단위의 출력 시간, time이 0인 경우 다른 명령이 입력되지 전까지 설정된 값을 유지 한다.
	 *	@return true - 성공적으로 서보 액츄에이터의 속도를 설정한 경우 true 값을 반환한다.<br>
	 *			false - 서보 액츄에이터의 속도를 설정하는 도중 에러가 발생한 경우 false 값을 반환한다.<br>
	 */
	virtual bool setVelocity(double velocity, unsigned long time = 0) = 0;

	/**
	 *	서보 액추에이터의 속도를 읽는다. type이 0인 경우 단위가 degree/s이고 1인 경우 단위가 m/s이다.
	 *	@param velocity 서보 액추에이터의 속도가 저장될 변수
	 *	@return true - 성공적으로 서보 액츄에이터의 속도를 읽어온 경우 true 값을 반환한다.<br>
	 *			false - 서보 액츄에이터의 속도를 읽어오는 도중 에러가 발생한 경우 false 값을 반환한다.<br>
	 */
	virtual bool getVelocity(double *velocity) = 0;

	/**
	 *	서보 액추에이터의 위치를 제어한다. 이 인터페이스는 time 시간 동안 position 위치로 이동시킨다.
	 *	time이 너무 작아서 서보 액추에이터에서 지원하는 속도보다 빠른 속도로 움직여야한 목표 위치로
	 *	이동할 수 있는 경우 에러를 반환한다. type이 0인 경우 단위가 degree이고, 1인 경우 단위가 m 이다.
	 *	@param position 서보 액추에이터의 위치
	 *	@param time ms 단위의 출력 시간, time이 0인 경우 다른 명령이 입력되지 전까지 설정된 값을 유지 한다.
	 *	@return true - 성공적으로 서보 액츄에이터의 위치를 설정한 경우 true 값을 반환한다.<br>
	 *			false - 서보 액츄에이터의 위치를 설정하는 도중 에러가 발생한 경우 false 값을 반환한다.<br>
	 */
	virtual bool setPosition(double position, unsigned long time = 0) = 0;

	/**
	 *	서보 액추에이터의 위치를 읽어온다. type이 0인 경우 단위가 각도(degree)이고, 1인 경우 단위가 거리(m)이다.
	 *	@param position 서보 액추에이터의 현재 위치가 저장될 변수
	 *	@return true - 성공적으로 서보 액츄에이터의 현재 위치를 읽어온 경우 true 값을 반환한다.<br>
	 *			false - 서보 액츄에이터의 현재 위치를 읽어오는 도중 에러가 발생한 경우 false 값을 반환한다.<br>
	 */
	virtual bool getPosition(double *position) = 0;
};

};

#endif	//	_SERVO_ACTUATOR_H_