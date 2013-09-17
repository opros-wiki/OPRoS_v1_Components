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
	@brief		SCA3000 DEMO Kit를 사용하기 위한 초기화 명령 전송
	@remark		SCA3000 DEMO 보드 내부에 MACRO 명령처리기능이 있음.
				초기함수를 호출하면 일정 시간 간격으로 데이터를 주기적으로 전송함.
	@return		없음.
	*/
	void Initialize();

	/*
	@brief		값을 전송하라는 명령을 보냄
	@remark		한 명령에 한번 nSample만큼 샘플링된 데이터를 전송함
	@return		요청한 데이터의 size
	*/
	int RequestData(int nSample);

	/*
	@brief		디바이스로부터 데이터를 수신
	@remark		data버퍼에 넣고 수신된 size를 리턴한다.
	@return		수신한 데이터의 size
	*/
	int ReceivePacket(unsigned char *rcvBufferdata, int rcvBufferdataSize);

	/*
	@brief		수신된 데이터로부터 데이터를 분리한다.
	@remark		분리한 데이터를 parseData로 넘겨준다.
	@return		분리된 데이터의 포인터
	*/
	bool DecodePacket(unsigned char *data, int dataSize, vector<double> &convData);
};
