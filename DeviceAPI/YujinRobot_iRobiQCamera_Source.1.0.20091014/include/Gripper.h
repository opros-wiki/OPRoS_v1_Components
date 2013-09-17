#ifndef	_GRIPPER_H_
#define	_GRIPPER_H_

#include "Device.h"
#include "OprosApiTypes.h"

namespace OPRoS
{

// 개요
/**
 *	그리퍼 (Gripper)는 임의의 사물을 잡을 수 있는 장치를 위한 컴포넌트이다.
 *	일반적으로 그리퍼는 매니퓰레이터 말단장치(end effector)의 종류 중 하나로 사용되어
 *	임의의 사물을 잡는 역할을 할 수 있게 된다. 본 문서에서는 그리퍼의 모션을 제어하는 인터페이스를 다룬다.
 *	그리퍼는 Mainpulator를 상속받았기 때문에 Manipulator API에서 제공하는 인터페이스를 제공한다.
 *	<tr><td><b>dllName</b></td> <td>std::string</td> <td colspan=2>컴포넌트에서 사용할 dll파일의 이름이다.</td></tr>
 *	<tr><td><b>size</b></td> <td>int</td> <td colspan=2>매니퓰레이터의 자유도를 결정짓는 관절(액츄에이터)의 개수이다. dllName, size를 제외한 나머지 파라미터들은 모든 관절이 각각 가지고 있으며, 그 값은 관절의 특징에 따라 달라진다.</td></tr>
 *	<tr><td><b>a</b></td> <td>double</td> <td>해당 관절에서 다음 관절까지 x축 방향의 거리이다.(단위:m)</td> <td rowspan=5><img src="../../images/DHParameter.jpg"></td></tr>
 *	<tr><td><b>b</b></td> <td>double</td> <td>해당 관절에서 다음 관절까지 y축 방향의 거리이다.(단위:m)</td></tr>
 *	<tr><td><b>alpha</b></td> <td>double</td> <td>연속된 관절의 뒤틀림 정도, 해당 관절 z축과 다음관절 z축 사이의 각도이다.(단위:degree)</td></tr>
 *	<tr><td><b>d</b></td> <td>double</td> <td>연속된 관절의 이탈정도, z축을 기준으로 해당 관절의 x축과 다음 관절의 x축 사이의 거리이다.(단위:m)</td></tr>
 *	<tr><td><b>theta</b></td> <td>double</td> <td>연속된 관절의 회전정도, z축을 기준으로 해당 관절의 x축과 다음 관절의 x축 사이의 각도이다.(단위:degree)</td></tr>
 *	<tr><td><b>direction</b></td> <td>int</td> <td colspan=2>매니퓰레이터의 회전방향 결정인자이다. 로봇이 대칭형 구조인 경우, 오른쪽 매니퓰레이터와 왼쪽 매니퓰레이터의 동작방향을 반대로 설정해주어야 할 때, 1또는 -1의 값을 넣어 사용된다.</td></tr>
 *	<tr><td><b>isVirtual</b></td> <td>bool</td> <td colspan=2>해당관절이 실제 축인지 가상의 축인지를 결정한다. 0은 실제 축, 1은 가상의 축을 나타낸다.</td></tr>
 *	<tr><td><b>jointType</b></td> <td>string</td> <td colspan=2>해당관절의 액츄에이터 종류를 결정한다. revolute는 회전타입, prismatic은 직선타입, fixed는 가상관절을 나타낸다.</td></tr>
 *	<tr><td><b>minimumRange</b></td> <td>double</td> <td colspan=2>해당관절의 최소 동작위치이다. maximumRange와 함께 동작범위를 지정한다.</td></tr>
 *	<tr><td><b>maximumRange</b></td> <td>double</td> <td colspan=2>해당관절의 최대 동작위치이다. minimumRange와 함께 동작범위를 지정한다.</td></tr>
 *	<tr><td><b>maximumVelocity</b></td> <td>double</td> <td colspan=2>해당관절의 최대 동작속도이다.</td></tr>
 *	<tr><td><b>acceleration</b></td> <td>double</td> <td colspan=2>해당관절의 가속도이다.</td></tr>
 *	<tr><td><b>id</b></td> <td>int</td> <td colspan=2>해당관절의 index를 지정해준다. 1부터 시작하여 index ID를 매길 수 있으며, 가상관절인 경우 0으로 표기한다.</td></tr>
 *	<tr><td><b>powerUnit</b></td> <td>int</td> <td colspan=2>power의 단위를 설정해준다. 0일 때는 torque(Nm), 1일 때는 파워(W), 2일 때는 전류(A), 3일 때는 비율(%)을 적용한다.</td></tr>
 *	</table></center>
 */
class Gripper : public Device
{
public:
	Gripper(void) { };
	virtual ~Gripper(void) { };

public:
	/**
	 *	액추에이터의 출력을 제어한다.
	 *	@param power 액츄에이터의 출력값
	 *	@param time ms 단위의 출력 시간, time이 0인 경우 다른 명령이 입력되지 전까지 설정된 값을 유지 한다.
	 *	@return true - 성공적으로 액츄에이터의 출력을 설정한 경우 true 값을 반환한다.<br>
				false - 액츄에이터의 출력을 제어하는 도중 에러가 발생한 경우 false 값을 반환한다.<br>
	 */
	virtual bool runGripping(void) = 0;
	virtual bool stopGripping(void) = 0;
	virtual bool isGripped(void) = 0;
	virtual bool isStopGripped(void) = 0;
};

};

#endif	//	_GRIPPER_H_