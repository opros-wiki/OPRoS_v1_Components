#ifndef _GLOBAL_MAP_H_
#define _GLOBAL_MAP_H_

#include "Application.h"

namespace OPRoS
{
// 개요
/**
 *	GlobalMap API는 이동 로봇의 자율 주행을 위한 전역맵 정보를 제어하는 표준 API이다. 
 *	모든 전역맵을 제어하는 API는 이 클래스를 상속받아 구현되어야 한다.
 *	GlobalMap API는 OPRoS Navigation Component를 통해 수행된다. 
 *	GlobalMap API는 Navigation Component로부터 파리미터를 받아 변수 및 메모리를 초기화 하고 로드맵 방식의 전역맵을 제어하는 API는 
 *	사전에 주어지는 전역맵 파일을 읽어 메모리에 적재시킨다. 
 *	GlobalMap API는 동적 라이브러리로 생성되며 Navigation Component에서 로드하여 사용된다.
 *	<center><table border=0><tr><td colspan=3><center><b>GlobalMap API에서 사용하는 Parameter</b></center></td></tr>
 *	<tr><td bgcolor=#dddddd><center><b>Index</b></center></td><td bgcolor=#dddddd><center><b>Type of Value</b></center></td><td bgcolor=#dddddd><center><b>Description</b></center></td></tr>
 *	<tr><td><b>cellWidth</b></td><td>double</td><td>전역맵 데이터 한 픽셀당 실제 거리를 의미한다.(단위:m)</td></tr>
 *	<tr><td><b>mapFile</b></td><td>double</td><td>전역맵의 가로폭을 의미한다. (단위:픽셀수)</td></tr>
 *	<tr><td><b>safeRadius</b></td><td>double</td><td>전역맵의 세로폭을 의미한다. (단위:픽셀수)</td></tr>
 *	</table></center>
 */
class GlobalMap : public Application
{
public:
	GlobalMap(void) { };
	virtual ~GlobalMap(void) { };

public:
	/**
	 *	전역맵 데이터의 한 픽셀이 가지는 실제 거리를 가지는 표준 변수이다.
	 *	단위 : m
	 */
	double cellWidth;

	/**
	 *	전역맵 데이터의 가로축 크기를 가지는 표준 변수이다.
	 *	단위 : pixel수
	 */
	int width;

	/**
	 *	전역맵 데이터의 세로축 크기를 가지는 표준 변수이다.
	 *	단위 : pixel수
	 */
	int height;

	/**
	 *	전역맵 데이터를 가지는 표준 변수이다.
	 *	단위 : 0~255의 값
	 */
	unsigned char *mapData;

	/**
	 *	GlobalMap API를 초기화 하는 표준 함수이다.
	 *  컴포넌트로부터 파라미터를 받아 GlobalMap API의 변수 및 메모리를 초기화 하고 맵파일로부터 데이터를 읽어들인다. 
	 *	@param parameter 초기화에 필요한 파라미터.
	 *	@return true - 초기화 성공<br>
	 *			false - 초기화 실패<br>
	 */
	virtual bool initialize(Property parameter) = 0;

	/**
	 *	GlobalMap API를 종료 하는 표준 함수이다.
	 *  GlobalMap API에서 사용하는 메모리나 다른 라이브러리를 해제한다.
	 *	@return true - 종료 성공<br>
	 *			false - 종료 실패<br>
	 */
	virtual bool finalize(void) = 0;

	/**
	 *	GlobalMap API를 활성화 하는 표준 함수이다.
	 *	@return true - 활성화 성공<br>
	 *			false - 활성화 실패<br>
	 */
	virtual bool enable(void) = 0;
	
	/**
	 *	GlobalMap API를 비활성화 하는 표준 함수이다.
	 *	@return true - 비활성화 성공<br>
	 *			false - 비활성화 실패<br>
	 */	
	virtual bool disable(void) = 0;

	/**
	 *	GlobalMap API의 파리미터를 설정하는 표준 함수이다.
	 *	@param parameter GlobalMap API에 필요한 파라미터.
	 *	@return true - 파리미터 설정 성공<br>
	 *			false - 파라미터 설정 실패<br>
	 */
	virtual bool setParameter(Property parameter) = 0;

	/**
	 *	GlobalMap API의 파리미터를 얻는 표준 함수이다.
	 *	@return parameter - GlobalMap API의 파라미터<br>
	 */
	virtual Property getParameter(void) = 0;

	/**
	 *	맵 파일을 읽어 GlobalMap API의 맵 데이터에 저장하는 표준 함수이다.
	 *	@param fileName 맵 파일의 이름.
	 *	@param cellWidth 맵 데이터의 한 픽셀에 대한 실제 거리.
	 *	@return true - 맵 파일 읽기 성공<br>
	 *			false - 맵 파일 읽기 실패<br>
	 */
	virtual bool loadMapFile(const char *fileName, double cellWidth) = 0;

	/**
	 *	GlobalMap API의 맵 데이터를 파일로 저장하는 표준 함수이다.
	 *	@param fileName 저장될 맵 파일의 이름.
	 *	@return true - 맵 파일 저장 성공<br>
	 *			false - 맵 파일 저장 실패<br>
	 */
	virtual bool saveMapFile(const char *fileName) = 0;

	/**
	 *	전역맵상에서 실제 위치의 장애물 데이터를 얻는 표준 함수이다.
	 *	@param x 전역맵 상에서 가로축으로 실제 위치.
	 *	@param y 전역맵 상에서 세로축으로 실제 위치.
	 *	@return data - 맵 데이터<br>
	 */
	virtual unsigned char getPixel(double x, double y) = 0;

	/**
	 *	전역맵상에서 픽셀 위치의 장애물 데이터를 얻는 표준 함수이다.
	 *	@param x 전역맵 상에서 가로축으로 픽셀 위치.
	 *	@param y 전역맵 상에서 세로축으로 픽셀 위치.
	 *	@return 맵 데이터<br>
	 */
	virtual unsigned char getPixelCell(int x, int y) = 0;

	/**
	 *	전역맵상의 실제 위치에 장애물에 대한 데이터를 기록하는 표준 함수한다.
	 *	@param x 전역맵 상에서 가로축으로 실제 위치.
	 *	@param y 전역맵 상에서 세로축으로 실제 위치.
	 *	@return data - 맵 데이터<br>
	 */
	virtual void setPixel(double x, double y, unsigned char data) = 0;

	/**
	 *	전역맵상의 픽셀 위치에 장애물에 대한 데이터를 기록하는 표준 함수한다.
	 *	@param x 전역맵 상에서 가로축으로 픽셀 위치.
	 *	@param y 전역맵 상에서 세로축으로 픽셀 위치.
	 *	@return data - 맵 데이터<br>
	 */
	virtual void setPixelCell(int x, int y, unsigned char data) = 0;

	/**
	 *	입력하는 실제 위치가 전역맵 상의 영역 안에 있는지를 확인하는 표준 함수한다.
	 *	@param x 전역맵 상에서 가로축으로 실제 위치.
	 *	@param y 전역맵 상에서 세로축으로 실제 위치.
	 *	@return true - 전역맵 영역 안에 있음<br>
	 *			false - 전역맵 영역 밖에 있음<br>
	 */
	virtual bool isIn(double x, double y) = 0;

	/**
	 *	입력하는 픽셀 위치가 전역맵 상의 영역 안에 있는지를 확인하는 표준 함수한다.
	 *	@param x 전역맵 상에서 가로축으로 픽셀 위치.
	 *	@param y 전역맵 상에서 세로축으로 픽셀 위치.
	 *	@return true - 전역맵 영역 안에 있음<br>
	 *			false - 전역맵 영역 밖에 있음<br>
	 */
	virtual bool isInCell(int x, int y) = 0;

	/**
	 *	전역맵 상에서 두 점의 실제 위치 선상에 문턱치 값보다 큰 장애물이 있는지를 확인하는 표준 함수한다.
	 *	@param x1 전역맵 상에서 한 점에 대한 가로축으로의 실제 위치.
	 *	@param y1 전역맵 상에서 한 점에 대한 세로축으로의 실제 위치.
	 *	@param x2 전역맵 상에서 다른 한 점에 대한 가로축으로의 실제 위치.
	 *	@param y2 전역맵 상에서 다른 한 점에 대한 세로축으로의 실제 위치.
	 *	@param data 장애물로 인식하기 위한 문턱치 값.
	 *	@return true - 장애물이 있음<br>
	 *			false - 장애물이 없음<br>
	 */
	virtual bool isIntersect(double x1, double y1, double x2, double y2, unsigned char data) = 0;

	/**
	 *	전역맵 상에서 두 점의 픽셀 위치 선상에 문턱치 값보다 큰 장애물이 있는지를 확인하는 표준 함수한다.
	 *	@param x1 전역맵 상에서 한 점에 대한 가로축으로의 픽셀 위치.
	 *	@param y1 전역맵 상에서 한 점에 대한 세로축으로의 픽셀 위치.
	 *	@param x2 전역맵 상에서 다른 한 점에 대한 가로축으로의 픽셀 위치.
	 *	@param y2 전역맵 상에서 다른 한 점에 대한 세로축으로의 픽셀 위치.
	 *	@param data 장애물로 인식하기 위한 문턱치 값.
	 *	@return true - 장애물이 있음<br>
	 *			false - 장애물이 없음<br>
	 */
	virtual bool isIntersectCell(int x1, int y1, int x2, int y2, unsigned char data) = 0;

	/**
	 *	전역맵 상에서 실제 위치의 두 점을 연결하는 선을 그리는 표준 함수한다.
	 *	@param x1 전역맵 상에서 한 점에 대한 가로축으로의 실제 위치.
	 *	@param y1 전역맵 상에서 한 점에 대한 세로축으로의 실제 위치.
	 *	@param x2 전역맵 상에서 다른 한 점에 대한 가로축으로의 실제 위치.
	 *	@param y2 전역맵 상에서 다른 한 점에 대한 세로축으로의 실제 위치.
	 *	@param data 전역맵에 저장할 장애물 값.
	 *	@return 없음<br>
	 */
	virtual void drawLine(double x1, double y1, double x2, double y2, unsigned char data) = 0;

	/**
	 *	전역맵 상에서 실제 위치의 두 점을 연결하는 선을 그리는 표준 함수한다.
	 *	@param x1 전역맵 상에서 한 점에 대한 가로축으로의 픽셀 위치.
	 *	@param y1 전역맵 상에서 한 점에 대한 세로축으로의 픽셀 위치.
	 *	@param x2 전역맵 상에서 다른 한 점에 대한 가로축으로의 픽셀 위치.
	 *	@param y2 전역맵 상에서 다른 한 점에 대한 세로축으로의 픽셀 위치.
	 *	@param data 전역맵에 저장할 장애물 값.
	 *	@return 없음<br>
	 */
	virtual void drawLineCell(int x1, int y1, int x2, int y2, unsigned char data) = 0;

	/**
	 *	전역맵의 장애물에 대해 문턱치 값보다 큰 장애물을 일정 영역만큼 확장하는 표준 함수한다.
	 *	@param bulge 확장시킬 영역크기.
	 *	@param threshold 확장시킬 장애물의 문턱치 값.
	 *	@param data 확장영역에 들어갈 장애물 데이터 값.
	 *	@return 없음<br>
	 */
	virtual void expandObstacle(int bulge, unsigned char threshold, unsigned char data) = 0;

	/**
	 *	전역맵의 메모리 영역을 재할당하는 표준 함수한다.
	 *	@param offsetX 가로축으로 시작 위치.
	 *	@param offsetY 세로축으로 시작 위치.
	 *	@param width 가로축 시작 위치로부터의 폭.
	 *	@param height 세로축 시작 위치로부터의 높이.
	 *	@return true - 전역맵의 메모리 할당 성공<br>
	 *			false - 전역맵의 메모리 할당 실패<br>
	 */
	virtual bool reallocate(int offsetX, int offsetY, int width, int height) = 0;

	/**
	 *	전역맵 상에서 가로축의 실제 위치를 픽셀 위치로 변환하는 표준 함수한다.
	 *	@param x 전역맵 상에서 가로축으로 실제 위치.
	 *	@return 전역맵 상에서 가로축으로 픽셀 위치<br>
	 */
	virtual int m2CUx(double x) = 0;

	/**
	 *	전역맵 상에서 세로축의 실제 위치를 픽셀 위치로 변환하는 표준 함수한다.
	 *	@param x 전역맵 상에서 세로축으로 실제 위치.
	 *	@return 전역맵 상에서 세로축으로 픽셀 위치<br>
	 */
	virtual int m2CUy(double y) = 0;

	/**
	 *	전역맵 상에서 가로축의 픽셀 위치를 실제 위치로 변환하는 표준 함수한다.
	 *	@param x 전역맵 상에서 가로축으로 픽셀 위치.
	 *	@return 전역맵 상에서 가로축으로 실제 위치<br>
	 */
	virtual double cu2Mx(int x) = 0;

	/**
	 *	전역맵 상에서 세로축의 픽셀 위치를 실제 위치로 변환하는 표준 함수한다.
	 *	@param x 전역맵 상에서 세로축으로 픽셀 위치.
	 *	@return 전역맵 상에서 세로축으로 실제 위치<br>
	 */
	virtual double cu2My(int y) = 0;
};

};

#endif
