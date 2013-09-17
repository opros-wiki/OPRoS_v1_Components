#ifndef _LOCALIZATION_H_
#define _LOCALIZATION_H_

#include "Application.h"
#include "GlobalMap.h"
#include "OprosApiTypes.h"

namespace OPRoS
{
// 개요
/**
 *	Localization API는 이동 로봇의 자율 주행을 위한 로봇의 위치를 추정하는 표준 API이다. 
 *	모든 위치 추정하는 API는 이 클래스를 상속받아 구현되어야 한다.
 *	Localization API는 OPRoS Navigation Component를 통해 수행된다. 
 *	Localization API는 Navigation Component로부터 파리미터를 받아 변수 및 메모리를 초기화 한다.
 *	Localization API는 동적 라이브러리로 생성되며 Navigation Component에서 로드하여 사용된다.
 *	<center><table border=0>
 *	<tr><td colspan=3><center><b>Localization API에서 사용하는 Parameter</b></center></td></tr>
 *	<tr><td bgcolor=#dddddd><center><b>Index</b></center></td><td bgcolor=#dddddd><center><b>Type of Value</b></center></td><td bgcolor=#dddddd><center><b>Description</b></center></td></tr>
 *	<tr><td><b>mapFile</b></td> <td>std::string</td> <td>globalMap API에서 로드될 맵 파일의 이름이다.</td></tr>
 *	<tr><td><b>cellWidth</b></td> <td>double</td> <td>맵에 있는 각 픽셀의 실측 너비이다.(단위:m)</td></tr>
 *	<tr><td><b>varianceDistance</b></td> <td>double</td> <td>모빌리티 파라미터에서 가져오는 직선거리상의 오차이다.</td></tr>
 *	<tr><td><b>varianceDirection</b></td> <td>double</td> <td>모빌리티 파라미터에서 가져오는 방향각도상의 오차이다.</td></tr>
 *	<tr><td><b>safeRadius</b></td> <td>double</td> <td>모빌리티 파라미터에서 가져오는 안전영역의 반지름이다.</td></tr>
 *	<tr><td><b>maximumVelocity</b></td> <td>double</td> <td>모빌리티 파라미터에서 가져오는 최고속도 제한이다.</td></tr>
 *	<tr><td><b>acceleration</b></td> <td>double</td> <td>모빌리티 파라미터에서 가져오는 가속도이다.</td></tr>
 *	<tr><td><b>startAngle</b></td> <td>double</td> <td>레이저스캐너 파라미터에서 가져오는 측정시작 각도이다.</td></tr>
 *	<tr><td><b>endAngle</b></td> <td>double</td> <td>레이저스캐너 파라미터에서 가져오는 마지막 측정각도이다.</td></tr>
 *	<tr><td><b>minimumRange</b></td> <td>double</td> <td>레이저스캐너 파라미터에서 가져오는 측정범위 최소치이다.</td></tr>
 *	<tr><td><b>maximumRange</b></td> <td>double</td> <td>레이저스캐너 파라미터에서 가져오는 측정범위 최대치이다.</td></tr>
 *	<tr><td><b>sensorCount</b></td> <td>int</td> <td>레이저스캐너의 실제 측정 스텝 개수이다.</td></tr>
 *	<tr><td><b>sensorVariance</b></td> <td>double</td> <td>레이저스캐너 파라미터에서 가져오는 장치 에러율이다.</td></tr>
 *	<tr><td><b>x</b></td> <td>double</td> <td>레이저스캐너 파라미터에서 가져오는 상대적위치정보이다.</td></tr>
 *	<tr><td><b>y</b></td> <td>double</td> <td>레이저스캐너 파라미터에서 가져오는 상대적위치정보이다.</td></tr>
 *	<tr><td><b>theta</b></td> <td>double</td> <td>레이저스캐너 파라미터에서 가져오는 상대적방향정보이다.
 *	NavigationComponent에서는 방향정보 roll, pitch, yaw 중 yaw만 유효하므로 yaw값을 theta에 넣는다.</td></tr>
 *	<tr><td><b>startPositionX</b></td> <td>double</td> <td>전역 맵에서의 모빌리티 시작 위치를 나타낸다.</td></tr>
 *	<tr><td><b>startPositionY</b></td> <td>double</td> <td>전역 맵에서의 모빌리티 시작 위치를 나타낸다.</td></tr>
 *	<tr><td><b>startPositionTheta</b></td> <td>double</td> <td>전역 맵에서의 모빌리티 시작 방향을 나타낸다.</td></tr>
 *	</table></center>
 */
class Localization : public Application
{
public:
	Localization(void) { };
	virtual ~Localization(void) { };

public:
	/**
	 *	Localization API를 초기화 하는 표준 함수이다.
	 *  컴포넌트로부터 파라미터를 받아 Localization API의 변수 및 메모리를 초기화 한다. 
	 *	@param parameter 초기화에 필요한 파라미터.
	 *	@return true - 초기화 성공<br>
	 *			false - 초기화 실패<br>
	 */
	virtual bool initialize(Property parameter) = 0;

	/**
	 *	Localization API를 종료 하는 표준 함수이다.
	 *  Localization API에서 사용하는 메모리나 다른 라이브러리를 해제한다.
	 *	@return true - 종료 성공<br>
	 *			false - 종료 실패<br>
	 */
	virtual bool finalize(void) = 0;

	/**
	 *	Localization API를 활성화 하는 표준 함수이다.
	 *	@return true - 활성화 성공<br>
	 *			false - 활성화 실패<br>
	 */
	virtual bool enable(void) = 0;

	/**
	 *	Localization API를 비활성화 하는 표준 함수이다.
	 *	@return true - 비활성화 성공<br>
	 *			false - 비활성화 실패<br>
	 */	
	virtual bool disable(void) = 0;

	/**
	 *	Localization API의 파리미터를 설정하는 표준 함수이다.
	 *	@param parameter Localization API에 필요한 파라미터.
	 *	@return true - 파리미터 설정 성공<br>
	 *			false - 파라미터 설정 실패<br>
	 */
	virtual bool setParameter(Property parameter) = 0;

	/**
	 *	Localization API의 파리미터를 얻는 표준 함수이다.
	 *	@return parameter - Localization API의 파라미터<br>
	 */
	virtual Property getParameter(void) = 0;

	/**
	 *	로봇의 현재 위치를 설정하는 표준 함수이다.
	 *	@param position 로봇의 현재 위치(x, y, theta).
	 *	@return 없음.
	 */
	virtual void setPosition(ObjectLocation position) = 0;

	/**
	 *	추정된 로봇의 현재 위치를 얻는 표준 함수이다.
	 *	@param position 추정된 로봇의 현재 위치(x, y, theta).
	 *	@return true - 유효한 값.
	 *			false - 유효하지 않은 값.
	 */
	virtual bool getPosition(ObjectLocation *position) = 0;

	/**
	 *	전역맵과 레이져 스캐너 센서 데이터, 모빌리티의 이동량을 이용해 로봇의 위치를 추정하는 표준 함수이다.
	 *	@param globalMap 전역맵.
	 *	@param laserData 레이져 스캐너 센서의 스캔된 데이터.
	 *	@param forwardDelta 로봇의 전진량.
	 *	@param angularDelta 로봇의 회전량.
	 *	@return 없음.
	 */
	virtual void localize(GlobalMap *globalMap, double laserData[], double deltaForward, double deltaAngular) = 0;

	/**
	 *	전역맵과 레이져 스캐너 센서 데이터, 모빌리티의 오도메트리를 이용해 로봇의 위치를 추정하는 표준 함수이다.
	 *	@param globalMap 전역맵.
	 *	@param laserData 레이져 스캐너 센서의 스캔된 데이터.
	 *	@param robotPosition 모빌리티로부터 얻은 로봇의 현재 위치.
	 *	@return 없음.
	 */
	virtual void localize(GlobalMap *globalMap, double laserData[], ObjectLocation robotPosition) = 0;
};

};

#endif