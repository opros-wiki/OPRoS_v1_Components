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

	bool iRobiQ_SetPan(double degree, int time);
	bool iRobiQ_GetPan(double *degree);
	bool iRobiQ_SetTilt(double degree, int time);
	bool iRobiQ_GetTilt(double *degree);
	void iRobiQ_CalculateAngle(int index, double *degree);

	static void CALLBACK EventMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam);
	static void CALLBACK ResponseMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam);
	static void CALLBACK AckMsgProc(LPROBOTINTERFACE pRI, DWORD dwTaskID, WORD wCmdID, WPARAM wParam, LPARAM lParam);
};
