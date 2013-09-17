#pragma once

#include <Windows.h>
#include <string>

#include "taskdef.h"
#include "errdef.h"
#include "yjrobotdef.h"
#include "yjrobotapi.h"

using namespace std;

class iRobiQPanTilt
{
public:
	iRobiQPanTilt(void);
	virtual ~iRobiQPanTilt(void);

private:
	LPROBOTINTERFACE pRI;
	bool isConnected;

public:
	unsigned long startTime[2];
	unsigned long runTime[2];
	double startAngle[2];
	double targetAngle[2];

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

	bool iRobiQ_SetPan(double degree, int time);
	bool iRobiQ_GetPan(double *degree);
	bool iRobiQ_SetTilt(double degree, int time);
	bool iRobiQ_GetTilt(double *degree);
	void iRobiQ_CalculateAngle(int index, double *degree);

	static void CALLBACK EventMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam);
	static void CALLBACK ResponseMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam);
	static void CALLBACK AckMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam);
};
