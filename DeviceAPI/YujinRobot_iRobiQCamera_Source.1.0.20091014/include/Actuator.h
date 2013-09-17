#ifndef	_ACTUATOR_H_
#define	_ACTUATOR_H_

#include "Device.h"

namespace OPRoS
{

// 개요
/**
 *	로봇을 움직이기 위해서는 액추에이터를 제어해야한다.
 *	액추에이터에는 여러 가지 종류가 있고 제어방법도 여러 가지가 있다. 본문에서는 액추에이터를 제어하기 위해
 *	출력을 제어하는 인터페이스를 사용한다. 파라미터로는 액추에이터의 최대 출력과 출력 값의 단위가 필요하다.
 *	<center><table border=0><tr><td colspan=3><center><b>GlobalMap API에서 사용하는 Parameter</b></center></td></tr>
 *	<tr><td bgcolor=#dddddd><center><b>Index</b></center></td><td bgcolor=#dddddd><center><b>Type of Value</b></center></td><td bgcolor=#dddddd><center><b>Description</b></center></td></tr>
 *	<tr><td><b>maximumPower</b></td><td>double</td><td>액추에이터의 최대출력</td></tr>
 *	<tr><td><b>powerUnit</b></td><td>int</td><td>액추에이터 출력의 단위를 설정한다. 0은 토크(Nm), 1은 파워(W), 2는 전류(A), 3은 비율(%) 을 나타낸다.</td></tr>
 *	</table></center>
 */
#define	POWER_UNIT_TORQUE	0
#define	POWER_UNIT_POWER	1
#define	POWER_UNIT_CURRENT	2
#define	POWER_UNIT_RATE		3

class Actuator : public Device
{
public:
	Actuator(void) { };
	virtual ~Actuator(void) { };

public:
	/**
	 *	액추에이터의 출력을 제어한다.
	 *	@param power 액츄에이터의 출력값
	 *	@param time ms 단위의 출력 시간, time이 0인 경우 다른 명령이 입력되지 전까지 설정된 값을 유지 한다.
	 *	@return true - 성공적으로 액츄에이터의 출력을 설정한 경우 true 값을 반환한다.<br>
	 *			false - 액츄에이터의 출력을 제어하는 도중 에러가 발생한 경우 false 값을 반환한다.<br>
	 */
	virtual bool setPower(double power, unsigned long time = 0) = 0;

	/**
	 *	액추에이터의 출력을 읽어온다.
	 *	@param power 액츄에이터의 출력값이 저장될 변수
	 *	@return true - 성공적으로 액츄에이터의 출력을 읽어온 경우 true 값을 반환한다.<br>
	 *			false - 액츄에이터의 출력을 읽는 도중 에러가 발생한 경우 false 값을 반환한다.<br>
	 */
	virtual bool getPower(double *power) = 0;
};

};

#endif	//	_ACTUATOR_H_