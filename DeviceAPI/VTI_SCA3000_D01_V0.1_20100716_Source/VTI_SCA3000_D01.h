#pragma once

#include "AccelerationSensor.h"
#include "UART.h"

#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

class VTI_SCA3000_D01 : public AccelerationSensor
{
public:
	VTI_SCA3000_D01(void);
	virtual ~VTI_SCA3000_D01(void);

public:
	int Initialize(Property parameter);
	int Finalize(void);
	int Enable(void);
	int Disable(void);
	int SetParameter(Property parameter);
	int GetParameter(Property &parameter);
	int GetAccelerationSensorData(vector<double> &accelerationSensorData);

private:
	Property parameter;
	UART *_uart;
	double _offset[3];	//x, y, z (offset acceleration)
	bool	_isCalibrated;

#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	int InitializeUART(Property parameter);

	/*
	@brief		SCA3000 DEMO Kit�� ����ϱ� ���� �ʱ�ȭ ��� ����
	@remark		SCA3000 DEMO ���� ���ο� MACRO ���ó������� ����.
				�ʱ��Լ��� ȣ���ϸ� ���� �ð� �������� �����͸� �ֱ������� ������.
	@return		����.
	*/
	void Initialize();

	/*
	@brief		���� �����϶�� ����� ����
	@remark		�� ��ɿ� �ѹ� nSample��ŭ ���ø��� �����͸� ������
	@return		��û�� �������� size
	*/
	int RequestData(int nSample);

	/*
	@brief		����̽��κ��� �����͸� ����
	@remark		data���ۿ� �ְ� ���ŵ� size�� �����Ѵ�.
	@return		������ �������� size
	*/
	int ReceivePacket(unsigned char *rcvBufferdata, int rcvBufferdataSize);

	/*
	@brief		���ŵ� �����ͷκ��� �����͸� �и��Ѵ�.
	@remark		�и��� �����͸� parseData�� �Ѱ��ش�.
	@return		�и��� �������� ������
	*/
	bool DecodePacket(unsigned char *data, int dataSize, vector<double> &convData);
};
