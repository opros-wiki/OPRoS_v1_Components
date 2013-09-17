#pragma once
#include <windows.h>
#include "Camera.h"

#include "taskdef.h"
#include "errdef.h"
#include "yjrobotdef.h"
#include "yjrobotapi.h"

using namespace OPRoS;

/**
 *	YujinRobot_iRobiQCamera�� (��) �����κ����� ������ iRobiQ�� ī�޶� ������Ű�� API�̴�.<br>
 *	�� API�� ������Ű�� ���ؼ��� CameraComponent�� ǥ�� �������Ͽܿ�
 *	iRobiQ�� IP, Port, Service ID ������ �߰��Ǿ�� �Ѵ�.<br>
 *	�� API�� �������ϱ� ���ؼ��� errdef.h, taskdef.h, yjrobotapi.h, yjrobotdef.h�� RobotInterface.lib ������ �ʿ��ϴ�.
 *	����ÿ��� ComLibrary.dll, RobotInterface.dll, StandardInterface.dll ������ �־�� �Ѵ�.<br>
 *	�� ������ (��)�����κ��� �κ� �������̽� API�� �Ϻ� �ο��Ͽ���.
 */
class YujinRobot_iRobiQCamera : public Camera
{
public:
	YujinRobot_iRobiQCamera(void);
	virtual ~YujinRobot_iRobiQCamera(void);

public:
	/**
	* bool initialize(OPRoS::Property parameter)
	* ī�޶� ��ġ�� �����ϸ� ȣ��˴ϴ�.
	* return - true : ī�޶� ��ġ ���� ����
	*		 - false : ī�޶� ��ġ ���� ����
	*/
	virtual bool initialize(OPRoS::Property parameter);

	/**
	* bool enable(void)
	* ī�޶� ��ġ�� Ȱ��ȭ �մϴ�.
	* return - true : ī�޶� Ȱ��ȭ ����
	*		 - false : ī�޶� Ȱ��ȭ ����
	*/
	virtual bool enable(void);

	/**
	* bool disable(void)
	* ī�޶� ��ġ�� ��Ȱ��ȭ �մϴ�.
	* return - true : ī�޶� ��Ȱ��ȭ ����
	*		 - false : ī�޶� ��Ȱ��ȭ ����
	*/
	virtual bool disable(void);

	/**
	* bool finalize(void)
	* ������ �� ȣ��Ǵ� �Լ��Դϴ�.
	*/
	virtual bool finalize(void);

	/**
	* bool setParameter(OPRoS::Property parameter)
	* ī�޶��� parameter(ID, width, height, pixelByte, flip)�� �����մϴ�.
	* return - true : ī�޶� parameter ���� ����
	*		 - false : ī�޶� parameter ���� ����
	*/
	virtual bool setParameter(OPRoS::Property parameter);

	/**
	* OPRoS::Property getParameter(void)
	* ī�޶�κ��� parameter(ID, width, height, pixelByte, flip) ������ �����ɴϴ�.
	* return - true : ī�޶� parameter ���� ȹ�� ����
	*		 - false : ī�޶� parameter ���� ȹ�� ����
	*/
	virtual OPRoS::Property getParameter(void);

	virtual DEVICE_STATUS getStatus(void);

	/**
	* bool getImage(unsigned char *image)
	* ī�޶󿡼� ������ ĸ���Ͽ� ��� ������ image�� �����մϴ�.
	* image : ������ ������ �迭�� ������
	* return - true : ���� ĸ�� ����
	*		 - false : ���� ĸ�� ����
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
	 *	iRobiQ�� ��ȣ�ۿ��� ���� �κ� �������̽� ��ü�� �����ϰ�, Event �Լ�, Response �Լ�, Acknowledge �Լ��� ����Ѵ�. 
	 *	@return	true ���������� �ʱ�ȭ�� ��Ų ���<br>
	 *			false �κ� �������̽� ��ü�� �������� �� �ϰų�, Event �Լ�, Response �Լ�, Acknowledge �Լ��� ����� �� ���� ���
	 */
	bool iRobiQ_Initialize(void);

	/**
	 *	iRobiQ�� ��ȣ�ۿ��� ���� �κ� �������̽� ��ü�� �Ҹ��Ų��. isConnected ������ ���� true�� ��� iRobiQ_Disconnect�Լ��� ȣ���Ͽ�
	 *	iRobiQ���� ������ ������Ų �� �κ� �������̽��� ��ü�� �Ҹ��Ų��.
	 *	@return	true ���������� �κ� �������̽� ��ü�� �Ҹ��Ų ���
	 *			false �κ� �������̽� ��ü�� �Ҹ��Ű�� ���� ������ �߻��� ���
	 */
	bool iRobiQ_Finalize(void);

	/**
	 *	���ڷ� �޴� IP, Port, Service ID�� ������ ������ iRobiQ�� �����Ѵ�. iRobiQ�� ���ø����̼� �������Ͽ� �����ϰ��� �ϴ�
	 *	Port�� Service ID�� �����Ǿ� �־�� �Ѵ�. ���������� iRobiQ�� ���ӵ� ��� isConnected ������ ���� true�� ����ȴ�.
	 *	@param	IP ������ iRobiQ�� IP �ּ�
	 *	@param	Port ������ iRobiQ�� Port ��ȣ
	 *	@param	serviceId ������ iRobiQ�� Service ID
	 *	@return	true ���������� iRobiQ�� ������ ���
	 *			flase iRobiQ ���ӿ� ������ ���, iRobiQ�� ������ IP, Port, Service ID�� ���ڷ� ���� ���� �ٸ� ��� �߻��Ѵ�.<br>
	 *			�Ǵ� �� API�� �ʱ�ȭ���� �ʾ� pRI ������ NULL�� ��쿡�� ������ �����Ѵ�.
	 */
	bool iRobiQ_Connect(std::string ip, unsigned int port, unsigned short serviceId);

	/**
	 *	iRobiQ���� ������ �����Ѵ�.
	 *	@return	true ���������� ������ ������Ų ���
	 *			false ���������� ������ ���, pRI ������ NULL�� ��쿡�� ������ �����Ѵ�.
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
