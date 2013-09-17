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
	 *	iRobiQ�� ������ �Ǿ����� Ȯ���ϱ� ���� �÷����̴�. iRobiQ_Connect �������̽�����
	 *	iRobiQ�� ���������� ���ӵǾ��� �� true�� �����ȴ�.
	 */
	bool isConnected;

	/**
	 *	iRobiQ�� �̵��ΰ� �̵����¸� �����ϱ� ���� �÷����̴�.
	 */
	bool isRunning;

	/**
	 *	iRobiQ�� ���� 2���� ������ X, Y, Theta ��ġ�� �����ϴ� �����̴�.
	 */
	ObjectLocation location;

	/**
	 *	iRobiQ�� �̵����¸� Ȯ���ϱ� ���� �����̴�.
	 */
	unsigned long startTime;

	/**
	 *	iRobiQ�� �̵����¸� Ȯ���ϱ� ���� �����̴�.
	 */
	unsigned long runTime;

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

	/**
	 *	iRobiQ�� ������������ �̵���Ų��. ���ڷ� �޴� distance �Ÿ�(m)��ŭ time(s) �ð����� �̵���Ų��.
	 *	time�� distance / time�� 0.3���� Ŭ ���� �������� �ʴ´�.
	 *	@param	distance �̵��� �Ÿ�, distance�� ������ ����(m)�̴�.<br>
	 *	@param	time �̵� �ð�, time�� ������ ��(s)�̴�.
	 *	@return	true ���������� iRobiQ�� �̵��� ���<br>
	 *			false �̵��� ������ ���, pRI�� NULL�̰ų� isConnected�� false�� ��� ������ �����Ѵ�.
	 */
	bool iRobiQ_MoveWheel(double distance, int time);

	/**
	 *	iRobiQ�� ȸ����Ų��. ���ڷ� ���� degree��ŭ time �ð� ���ȿ� ȸ����Ų��.
	 *	@return	true ���������� iRobiQ�� ȸ���� ���<br>
	 *			false ȸ���� ������ ���, pRI�� NULL�̰ų� isConnected�� false�� ��쿡�� ������ �����Ѵ�.
	 */
	bool iRobiQ_RotateWheel(double degree, int time);

	/**
	 *	iRobiQ�� ������Ű��.
	 *	@return	true ���������� iRobiQ�� ���� ���<br>
	 *			false iRobiQ�� ���ߴ� ���� ������ ���
	 */
	bool iRobiQ_StopWheel(void);

	/**
	 *	iRobiQ�� ���� �����̰� �ִ��� Ȯ���Ѵ�.
	 *	@return	true iRobiQ�� �����̰� �ִ� ���<br>
	 *			false iRobiQ�� �����ִ� ���
	 */
	bool iRobiQ_CheckRunningState(void);

	/**
	 *	�κ��� ��û�� ��ɿ� ���� �κ����κ����� Event �޽����� �����ϱ� ���� ���ø����̼� ���� call-back �Լ��̴�.
	 *	EVENTPROC Ÿ���� �� call-back �Լ��� ���� �������̴�. �� call-back �Լ��� ���ø����̼ǿ��� �����Ͽ� ����Ѵ�.
	 *	@param	lpRobotInterface �κ� �������̽� ��ü�� ������
	 *	@param	dwTaskID �½�ũ ��û ���̵�, �Ϲ������� �κ��� �½�ũ�� ��û�ϴ� �Լ��� ���̵��̴�.
	 *	@param	wCmdID �½�ũ ��û�� ���ø����̼ǿ��� �ο��� ��û�� command ID�̴�. �� ���̵�μ� ��û ����� command�� ������ �� �ִ�.
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
