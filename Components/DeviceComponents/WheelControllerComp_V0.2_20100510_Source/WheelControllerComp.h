#ifndef _WheelControllerComp_COMPONENT_H
#define _WheelControllerComp_COMPONENT_H
/*
 *  Generated sources by OPRoS Component Generator (OCG V2)
 *   
 */
#include <Component.h>
#include <InputDataPort.h>
#include <OutputDataPort.h>
#include <InputEventPort.h>
#include <OutputEventPort.h>
#include <Event.h>
#include <OPRoSTypes.h>
#if defined(WIN32)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

#include "WheelController.h"
#include "WheelControllerServiceProvided.h"
	

// 개요
/**
*	WheelControllerComp는 이동 로봇의 휠 제어를 위한 컴포넌트이다.
*	이 컴포넌트는 휠 제어을 위한 표준 인터페이스인 IWheelControllerCompService를 상속받아 구현된다.
*	동적 라이브러리로 생성되며 OPRoS API의 표준 인터페이스인 WheelController 클래스를 상속받아 구현된 OPRoS API 라이브러리를 로드하여 수행된다.
*	WheelController 클래스를 상속받아 구현된 OPRoS API 라이브러리는 동적 라이브러리로써 이동 로봇(하드웨어)에 종속적으로 이동 로봇 교체에 상관없이
*	본 컴포넌트는 재사용이 가능하다. OPRoS API 라이브러리를 사용하기 위해서는 본 컴포넌트의 xml 프로파일중 속성에 사용하고자 하는 OPRoS API
*	라이브러리 파일 이름과 OPRoS API에서 필요로 하는 파라미터 정보를 기입해야한다.
*/
class WheelControllerComp: public Component ,public IWheelControllerService
{
protected:
// data


//event


// method for provider


// method for required
	


public:
	WheelControllerComp();
	WheelControllerComp(const std::string &compId);
	virtual ~WheelControllerComp();
	virtual void portSetup();

protected:
	virtual ReturnType onInitialize();
	virtual ReturnType onStart();
	virtual ReturnType onStop();
	virtual ReturnType onReset();
	virtual ReturnType onError();
	virtual ReturnType onRecover();
	virtual ReturnType onDestroy();

public:
	virtual ReturnType onEvent(Event *evt);
	virtual ReturnType onExecute();
	virtual ReturnType onUpdated();
	virtual ReturnType onPeriodChanged();

	/**
	*	파리미터를 설정하는 표준 함수이다.
	*	@param parameter 파라미터.
	*	@return true - 파리미터 설정 성공<br>
	*			false - 파라미터 설정 실패<br>
	*/
	virtual bool SetParameter(Property parameter);

	/**
	*	파리미터를 얻는 표준 함수이다.
	*	@param parameter 파라미터.
	*	@return true - 파리미터 얻기 성공<br>
	*			false - 파라미터 얻기 실패<br>
	*/
	virtual Property GetParameter();

	virtual int GetError();

	/**
	*	로봇의 위치를 설정하는 표준 함수이다.
	*	@param position 로봇의 위치
	*	@return true - 설정 성공<br>
	*	        false - 설정 실패<br>
	*/
	virtual bool SetPosition(ObjectLocation position);

	/**
	*	추정된 로봇의 위치를 얻는 표준 함수이다.
	*	@param position 추정된 로봇의 위치
	*	@return true - 얻기 성공<br>
	*	        false - 얻기 실패<br>
	*/
	virtual ObjectLocation GetPosition();

	/**
	*	로봇을 속도로 제어하는 표준 함수이다.
	*	@param velocity 로봇의 속도(전진속도, 회전속도)
	*	@return true - 속도 제어 성공<br>
	*	        false - 속도 제어 실패<br>
	*/
	virtual bool DriveWheel(WheelControlVelocity velocity);

	/**
	*	로봇을 입력 거리만큼 전진시키는 표준 함수이다.
	*	@param distance 이동 거리(단위:m)
	*	@return true - 전진 성공<br>
	*	        false - 전진 제어 실패<br>
	*/
	virtual bool MoveWheel(double distance);

	/**
	*	로봇을 입력 각도만큼 회전시키는 표준 함수이다.
	*	@param degree 회전 각도(단위:degree)
	*	@return true - 회전 성공<br>
	*	        false - 회전 실패<br>
	*/
	virtual bool RotateWheel(double degree);

	/**
	*	이동 중인 로봇을 정지시키는 표준 함수이다.
	*	@return true - 정지 성공<br>
	*	        false - 정지 실패<br>
	*/
	virtual bool StopWheel();

	/**
	*	로봇이 이동 중인지를 반환하는 표준 함수이다.
	*	@return true - 이동 상태<br>
	*	        false - 정지 상태<br>
	*/
	virtual bool IsWheelRunning();

private:
	/**
	*	OPRoS API 라이브러리의 핸들 변수이다.
	*/
#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	/**
	*	OPRoS API 라이브러리로부터 얻어지는 WheelController의 클래스 포인터를 가지는 변수이다.
	*/
	WheelController *wheelController;

	int error;
};

#endif

