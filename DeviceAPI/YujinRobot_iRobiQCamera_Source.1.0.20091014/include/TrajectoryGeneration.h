#ifndef _TRAJECTORY_GENERATION_H_
#define _TRAJECTORY_GENERATION_H_

#include "Application.h"
#include "OprosApiTypes.h"

#include <vector>
#include <valarray>

using namespace std;

namespace OPRoS
{

// 개요
/**
 *	궤적 생성 (Trajectory Generation) API는 매니퓰레이터가 지나가는 경유점들을 추가하여 궤적을 생성한다.
 *	궤적 생성 API에는 경유점을 추가하는 addViaPoint 인터페이스와 추가한 경유점을 삭제하는 clearViaPoint
 *	인터페이스, 그리고 추가된 경유점들을 보간해주는 interpolation 인터페이스가 구현되어 있다.
 */
class TrajectoryGeneration : public Application
{
public:
	TrajectoryGeneration(void) { };
	virtual ~TrajectoryGeneration(void) { };

public:
	/**
	 *	TrajectoryGeneration API를 초기화 하는 표준 함수이다.
	 *  컴포넌트로부터 파라미터를 받아 TrajectoryGeneration API의 변수 및 메모리를 초기화 한다. 
	 *	@param parameter 초기화에 필요한 파라미터.
	 *	@return true - 초기화 성공<br>
	 *			false - 초기화 실패<br>
	 */
	virtual bool initialize(Property parameter) = 0;

	/**
	 *	TrajectoryGeneration API를 종료 하는 표준 함수이다.
	 *  TrajectoryGeneration API에서 사용하는 메모리나 다른 라이브러리를 해제한다.
	 *	@return true - 종료 성공<br>
	 *			false - 종료 실패<br>
	 */
	virtual bool finalize(void) = 0;

	/**
	 *	TrajectoryGeneration API를 활성화 하는 표준 함수이다.
	 *	@return true - 활성화 성공<br>
	 *			false - 활성화 실패<br>
	 */
	virtual bool enable(void) = 0;

	/**
	 *	TrajectoryGeneration API를 비활성화 하는 표준 함수이다.
	 *	@return true - 비활성화 성공<br>
	 *			false - 비활성화 실패<br>
	 */
	virtual bool disable(void) = 0;

	/**
	 *	TrajectoryGeneration API의 파리미터를 설정하는 표준 함수이다.
	 *	@param parameter TrajectoryGeneration API에 필요한 파라미터.
	 *	@return true - 파리미터 설정 성공<br>
	 *			false - 파라미터 설정 실패<br>
	 */
	virtual bool setParameter(Property parameter) = 0;

	/**
	 *	TrajectoryGeneration API의 파리미터를 얻는 표준 함수이다.
	 *	@return parameter - TrajectoryGeneration API의 파라미터<br>
	 */
	virtual Property getParameter(void) = 0;

public:
	/**
	 *	경유점들을 보간한다. (Joint space상에서의 보간)
	 *	@param deltatime 경유점들을 보간(Interpolation)할 단위시간
	 *	@return 시간에 대한 경유 지점들을 보간한 데이터<br>
	 */
	virtual std::vector<std::valarray<double>> interpolation(double deltatime) = 0;

	/**
	 *	기준시간으로부터의 시간(time)과 위치(point)로 경유점을 추가한다.
	 *	@param time 기준시간으로부터의 시간
	 *	@param point 기준시간으로부터의 위치
	 *	@return true - 명령 수행을 성공했을 때 true 값을 반환한다.<br>
	 *			false - 명령 수행을 실패했을 때 false 값을 반환한다.<br>
	 */
	virtual bool addViaPoint(double time, valarray<double> point) = 0;

	/**
	 *	입력된 경로점들을 모두 삭제한다.
	 */
	virtual void clearViaPoint(void) = 0;
};


};


#endif
