#ifndef _FORWARD_KINEMATICS_H_
#define _FORWARD_KINEMATICS_H_

#include "Application.h"
#include "OprosApiTypes.h"

#include <valarray>

using namespace std;

namespace OPRoS
{

// 개요
/**
 *	정기구학은 매니퓰레이터가 어떤 자세에 있을 때, 그 말단장치(End Effector)에 해당하는 장치가
 *	어떤 위치에 있게 되는지에 대해 계산하는 것이다. 본 문서에서는 매니퓰레이터의 모션 제어를 위한
 *	정기구학을 계산하는 인터페이스를 다룬다.
 */
class ForwardKinematics : public Application
{
public:
	ForwardKinematics(void) { };
	virtual ~ForwardKinematics(void) { };

public:
	/**
	 *	ForwardKinematics API를 초기화 하는 표준 함수이다.
	 *  컴포넌트로부터 파라미터를 받아 ForwardKinematics API의 변수 및 메모리를 초기화 한다. 
	 *	@param parameter 초기화에 필요한 파라미터.
	 *	@return true - 초기화 성공<br>
	 *			false - 초기화 실패<br>
	 */
	virtual bool initialize(Property parameter) = 0;

	/**
	 *	ForwardKinematics API를 종료 하는 표준 함수이다.
	 *  ForwardKinematics API에서 사용하는 메모리나 다른 라이브러리를 해제한다.
	 *	@return true - 종료 성공<br>
	 *			false - 종료 실패<br>
	 */
	virtual bool finalize(void) = 0;

	/**
	 *	ForwardKinematics API를 활성화 하는 표준 함수이다.
	 *	@return true - 활성화 성공<br>
	 *			false - 활성화 실패<br>
	 */
	virtual bool enable(void) = 0;

	/**
	 *	ForwardKinematics API를 비활성화 하는 표준 함수이다.
	 *	@return true - 비활성화 성공<br>
	 *			false - 비활성화 실패<br>
	 */
	virtual bool disable(void) = 0;

	/**
	 *	ForwardKinematics API의 파리미터를 설정하는 표준 함수이다.
	 *	@param parameter ForwardKinematics API에 필요한 파라미터.
	 *	@return true - 파리미터 설정 성공<br>
	 *			false - 파라미터 설정 실패<br>
	 */
	virtual bool setParameter(Property parameter) = 0;

	/**
	 *	ForwardKinematics API의 파리미터를 얻는 표준 함수이다.
	 *	@return parameter - ForwardKinematics API의 파라미터<br>
	 */
	virtual Property getParameter(void) = 0;

public:
	/**
	 *	매니퓰레이터의 정기구학(Forward Kinematics)를 계산한다.
	 *	@param jointPosition 현재 관절의 각도(단위: degree)
	 *	@param endEffectorPosition 말단장치의 현재 위치(x,y,z,roll,pitch,yaw)데이터
	 *	@return true - 명령 수행을 성공했을 때 true 값을 반환한다.<br>
	 *			false - 명령 수행을 실패했을 때 false 값을 반환한다.<br>
	 */
	virtual bool solveForwardKinematics(valarray<double> jointPosition, ObjectPosition *endEffectorPosition) = 0;
	
};


};


#endif
