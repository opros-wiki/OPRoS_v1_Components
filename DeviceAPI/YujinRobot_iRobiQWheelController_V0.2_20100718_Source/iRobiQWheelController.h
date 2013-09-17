#pragma once

#include <windows.h>

#include "taskdef.h"
#include "errdef.h"
#include "yjrobotdef.h"
#include "yjrobotapi.h"
#include "ApiTypes.h"

class iRobiQWheelController
{
public:
	iRobiQWheelController(void);
	virtual ~iRobiQWheelController(void);

	LPROBOTINTERFACE pRI;

	/**
	 *	iRobiQ와 접속이 되었는지 확인하기 위한 플래그이다. iRobiQ_Connect 인터페이스에서
	 *	iRobiQ에 성공적으로 접속되었을 때 true로 설정된다.
	 */
	bool isConnected;

	/**
	 *	iRobiQ의 이동부가 이동상태를 저장하기 위한 플래그이다.
	 */
	bool isRunning;

	/**
	 *	iRobiQ의 현재 2차원 평면상의 X, Y, Theta 위치를 저장하는 변수이다.
	 */
	ObjectLocation location;

	/**
	 *	iRobiQ의 이동상태를 확인하기 위한 변수이다.
	 */
	unsigned long startTime;

	/**
	 *	iRobiQ의 이동상태를 확인하기 위한 변수이다.
	 */
	unsigned long runTime;

	/**
	 *	iRobiQ와 상호작용을 위한 로봇 인터페이스 개체를 생성하고, Event 함수, Response 함수, Acknowledge 함수를 등록한다. 
	 *	@return	true 성공적으로 초기화를 시킨 경우<br>
	 *			false 로봇 인터페이스 개체를 생성하지 못 하거나, Event 함수, Response 함수, Acknowledge 함수를 등록할 수 없는 경우
	 */
	bool iRobiQ_Initialize(void);

	/**
	 *	iRobiQ와 상호작용을 위한 로봇 인터페이스 개체를 소멸시킨다. isConnected 변수의 값이 true인 경우 iRobiQ_Disconnect함수를 호출하여
	 *	iRobiQ와의 접속을 해지시킨 후 로봇 인터페이스의 객체를 소멸시킨다.
	 *	@return	true 성공적으로 로봇 인터페이스 객체를 소멸시킨 경우
	 *			false 로봇 인터페이스 객체를 소멸시키는 도중 에러가 발생한 경우
	 */
	bool iRobiQ_Finalize(void);

	/**
	 *	인자로 받는 IP, Port, Service ID를 정보를 가지고 iRobiQ에 접속한다. iRobiQ의 어플리케이션 프로파일에 접속하고자 하는
	 *	Port와 Service ID가 설정되어 있어야 한다. 성공적으로 iRobiQ에 접속된 경우 isConnected 변수의 값이 true로 변경된다.
	 *	@param	IP 접속할 iRobiQ의 IP 주소
	 *	@param	Port 접속할 iRobiQ의 Port 번호
	 *	@param	serviceId 접속할 iRobiQ의 Service ID
	 *	@return	true 성공적으로 iRobiQ에 접속한 경우
	 *			flase iRobiQ 접속에 실패한 경우, iRobiQ에 설정된 IP, Port, Service ID와 인자로 받은 값이 다를 경우 발생한다.<br>
	 *			또는 이 API가 초기화되지 않아 pRI 변수가 NULL인 경우에도 에러를 리턴한다.
	 */
	bool iRobiQ_Connect(std::string ip, unsigned int port, unsigned short serviceId);

	/**
	 *	iRobiQ와의 접속을 해제한다.
	 *	@return	true 성공적으로 접속을 해제시킨 경우
	 *			false 접속해제에 실패한 경우, pRI 변수가 NULL인 경우에도 에러를 리턴한다.
	 */
	bool iRobiQ_Disconnect(void);

	/**
	 *	iRobiQ를 직선방향으로 이동시킨다. 인자로 받는 distance 거리(m)만큼 time(s) 시간동안 이동시킨다.
	 *	time이 distance / time이 0.3보다 클 경우는 지원하지 않는다.
	 *	@param	distance 이동할 거리, distance의 단위는 미터(m)이다.<br>
	 *	@param	time 이동 시간, time의 단위는 초(s)이다.
	 *	@return	true 성공적으로 iRobiQ가 이동한 경우<br>
	 *			false 이동을 실패한 경우, pRI가 NULL이거나 isConnected가 false인 경우 에러를 리턴한다.
	 */
	bool iRobiQ_MoveWheel(double distance, int time);

	/**
	 *	iRobiQ를 회전시킨다. 인자로 받은 degree만큼 time 시간 동안에 회전시킨다.
	 *	@return	true 성공적으로 iRobiQ가 회전한 경우<br>
	 *			false 회전에 실패한 경우, pRI가 NULL이거나 isConnected가 false인 경우에도 에러를 리턴한다.
	 */
	bool iRobiQ_RotateWheel(double degree, int time);

	/**
	 *	iRobiQ를 정지시키다.
	 *	@return	true 성공적으로 iRobiQ가 멈춘 경우<br>
	 *			false iRobiQ를 멈추는 것을 실패한 경우
	 */
	bool iRobiQ_StopWheel(void);

	/**
	 *	iRobiQ가 현재 움직이고 있는지 확인한다.
	 *	@return	true iRobiQ가 움직이고 있는 경우<br>
	 *			false iRobiQ가 멈춰있는 경우
	 */
	bool iRobiQ_CheckRunningState(void);

	/**
	 *	로봇에 요청한 명령에 따른 로봇으로부터의 Event 메시지를 수신하기 위한 어플리케이션 정의 call-back 함수이다.
	 *	EVENTPROC 타입은 본 call-back 함수에 대한 포인터이다. 본 call-back 함수는 어플리케이션에서 정의하여 사용한다.
	 *	@param	lpRobotInterface 로봇 인터페이스 개체의 포인터
	 *	@param	dwTaskID 태스크 요청 아이디, 일반적으로 로봇에 태스크를 요청하는 함수의 아이디이다.
	 *	@param	wCmdID 태스크 요청시 어플리케이션에서 부여한 요청의 command ID이다. 이 아이디로서 요청 당시의 command를 구분할 수 있다.
	 */
	static void CALLBACK EventMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam);

	/**
	 *
	 */
	static void CALLBACK ResponseMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam);

	/**
	 *
	 */
	static void CALLBACK AckMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam);
};
