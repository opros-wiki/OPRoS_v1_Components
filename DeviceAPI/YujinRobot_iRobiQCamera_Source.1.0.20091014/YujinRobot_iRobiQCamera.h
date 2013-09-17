#pragma once
#include <windows.h>
#include "Camera.h"

#include "taskdef.h"
#include "errdef.h"
#include "yjrobotdef.h"
#include "yjrobotapi.h"

using namespace OPRoS;

/**
 *	YujinRobot_iRobiQCamera는 (주) 유진로봇에서 개발한 iRobiQ의 카메라를 구동시키는 API이다.<br>
 *	이 API를 구동시키기 위해서는 CameraComponent의 표준 프로파일외에
 *	iRobiQ의 IP, Port, Service ID 정보가 추가되어야 한다.<br>
 *	이 API를 컴파일하기 위해서는 errdef.h, taskdef.h, yjrobotapi.h, yjrobotdef.h과 RobotInterface.lib 파일이 필요하다.
 *	실행시에는 ComLibrary.dll, RobotInterface.dll, StandardInterface.dll 파일이 있어야 한다.<br>
 *	본 문서는 (주)유진로봇의 로봇 인터페이스 API를 일부 인용하엿다.
 */
class YujinRobot_iRobiQCamera : public Camera
{
public:
	YujinRobot_iRobiQCamera(void);
	virtual ~YujinRobot_iRobiQCamera(void);

public:
	/**
	* bool initialize(OPRoS::Property parameter)
	* 카메라 장치를 생성하면 호출됩니다.
	* return - true : 카메라 장치 생성 성공
	*		 - false : 카메라 장치 생성 실패
	*/
	virtual bool initialize(OPRoS::Property parameter);

	/**
	* bool enable(void)
	* 카메라 장치를 활성화 합니다.
	* return - true : 카메라 활성화 성공
	*		 - false : 카메라 활성화 실패
	*/
	virtual bool enable(void);

	/**
	* bool disable(void)
	* 카메라 장치를 비활성화 합니다.
	* return - true : 카메라 비활성화 성공
	*		 - false : 카메라 비활성화 실패
	*/
	virtual bool disable(void);

	/**
	* bool finalize(void)
	* 종료할 때 호출되는 함수입니다.
	*/
	virtual bool finalize(void);

	/**
	* bool setParameter(OPRoS::Property parameter)
	* 카메라의 parameter(ID, width, height, pixelByte, flip)를 설정합니다.
	* return - true : 카메라 parameter 변경 성공
	*		 - false : 카메라 parameter 변경 실패
	*/
	virtual bool setParameter(OPRoS::Property parameter);

	/**
	* OPRoS::Property getParameter(void)
	* 카메라로부터 parameter(ID, width, height, pixelByte, flip) 정보를 가져옵니다.
	* return - true : 카메라 parameter 정보 획득 성공
	*		 - false : 카메라 parameter 정보 획득 실패
	*/
	virtual OPRoS::Property getParameter(void);

	virtual DEVICE_STATUS getStatus(void);

	/**
	* bool getImage(unsigned char *image)
	* 카메라에서 영상을 캡춰하여 결과 영상을 image에 저장합니다.
	* image : 영상을 저장할 배열의 포인터
	* return - true : 영상 캡춰 성공
	*		 - false : 영상 캡춰 실패
	*/
	virtual bool getImage(unsigned char *image);

private:
	Property parameter;
	LPROBOTINTERFACE pRI;
	bool isConnected;
	bool isEnabled;
	bool isStarted;

	int width;
	int height;
	int pixelBytes;
	int flip;
	int period;
	
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

	bool iRobiQ_EnableCamera(short resolution);
	bool iRobiQ_StartCapture(int period, short resolution, short format);
	bool iRobiQ_StopCapture(void);
	bool iRobiQ_DisableCamera(void);

	static void CALLBACK EventMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam);
	static void CALLBACK ResponseMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam);
	static void CALLBACK AckMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam);
};
