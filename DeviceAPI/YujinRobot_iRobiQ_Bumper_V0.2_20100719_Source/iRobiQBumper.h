#pragma once

#include <windows.h>
#include <string>

#include "taskdef.h"
#include "errdef.h"
#include "yjrobotdef.h"
#include "yjrobotapi.h"

using namespace std;

class iRobiQBumper
{
public:
	iRobiQBumper(void);
	virtual ~iRobiQBumper(void);

private:
	LPROBOTINTERFACE pRI;

public:
	/**
	*	�����κ� iRobiQ���� TCP/IP ���� ������ ��Ÿ���� �����̴�.
	*	true�̸� ����� �����̰�, false�̸� ������ ������ �����̴�.
	*/
	bool isConnected;
	
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
	bool iRobiQ_Connect(string ip, unsigned int port, unsigned short serviceId);
	
	/**
	 *	iRobiQ���� ������ �����Ѵ�.
	 *	@return	true ���������� ������ ������Ų ���
	 *			false ���������� ������ ���, pRI ������ NULL�� ��쿡�� ������ �����Ѵ�.
	 */
	bool iRobiQ_Disconnect(void);
	/**
	*	�����κ� iRobiQ�� ���� ������ Ȱ��ȭ�Ѵ�.
	* 	@return true - Ȱ��ȭ ����<br>
	* 			false - Ȱ��ȭ ����<br>
	*/
	bool iRobiQBumper_Enable(void);
	/**
	*	�����κ� iRobiQ�� ���� ������ ��Ȱ��ȭ�Ѵ�.
	* 	@return true - ��Ȱ��ȭ ����<br>
	* 			false - ��Ȱ��ȭ ����<br>
	*/
	bool iRobiQBumper_Disable(void);

	bool iRobiQBumper_GetBumperState();

	static void CALLBACK EventMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam);
	static void CALLBACK ResponseMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam);
	static void CALLBACK AckMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam);
};
