/*************************************************************

 file: KeyInputComponent.h
 author: S.G. Bang
 begin: April 20 2010
 copyright: (c) 2010 KNU, OPRoS
 email: hspark@kangwon.ac.kr

***************************************************************

OPRoS source code is provided under a dual license mode:
 LGPL and OPRoS individually.

LGPL: You can redistribute it and/or modify it under the terms
 of the Less GNU General Public License as published by the Free
 Software Foundation, either version 3 of the License.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of 
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 Less GNU General Public License for more details. 

 You should have received a copy of the Less GNU General Public
 License along with this program. If not, see 
 <http://www.gnu.org/licenses/>.

OPRoS individual license: An individual license is a license for
 modifying the source code of OPRoS and distiributing it in a
 closed format for commercial purposes.

 If you are interested in this option, please see 
 <http://www.opros.or.kr>.

This license policy may be changed without prior notice.

***************************************************************/

#ifndef _KeyInputComponent_COMPONENT_H
#define _KeyInputComponent_COMPONENT_H
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
#include <OPRosTypes.h>

#include "Component.h"
#include "KeyInputServicePortProvided.h"
#include <Windows.h>
// 개요
/**
*	<table><tr><td>
*	KeyInputComponent는 키보드 입력을 위한 컴포넌트이다.
*	KeyInputComponent는 KeyInputComponent.xml,
*	KeyInputComponentServicePortProvided.h가 포함되어야하며, KeyInputComponentComponent.xml에는
*	KeyInputComponent의 프로파일이 저장되어 있다. KeyInputComponentServicePortProvided.h는
*	이 컴포넌트에서 제공하는 서비스 포트를 호출할 수 있는 인터페이스를 제공한다.
*/
class KeyInputComponent: public Component, IKeyInputServicePort
{
protected:
	// 속성
	//	Variables for KeyInputComponent

	IKeyInputServicePort *ptrKeyInputServicePort;

public:
	/**
	*	KeyInputComponent 클래스의 기본 생성자이다.<br>
	*	포트를 초기화시키는 함수를 호출한다.
	*/
	KeyInputComponent();
	/**
	*	KeyInputComponent 클래스의 전달인자를 포함한 생성자이다.<br>
	*	포트를 초기화시키는 함수를 호출한다.
	*	@param compId 컴포넌트의 ID.
	*/
	KeyInputComponent(const std::string &compId);
	/**
	*	KeyInputComponent 클래스의 기본 소멸자이다.
	*/
	virtual ~KeyInputComponent();
	/**
	*	KeyInputComponent에서 제공하는 서비스 포트를 초기화하고 등록한다.
	*/
	virtual void portSetup();

protected:
	// Callback API
	/**
	*	컴포넌트가 초기화될 때 호출되는 콜백함수이다.
	*	XML에 저장된 프로퍼티정보를 읽어서 DLL을 로드하고,
	*	필요한 API를 로드한 후 초기화 한다.
	*	@return OPROS_SUCCESS - 컴포넌트 초기화 성공<br>
	*			OPROS_FIND_PROPERTY_ERROR - 프로퍼티정보에 DLL파일이름이 없음<br>
	*			OPROS_FIND_DLL_ERROR - DLL을 찾을 수 없음<br>
	*			OPROS_LOAD_DLL_ERROR - DLL을 로드할 수 없음<br>
	*			OPROS_INITIALIZE_API_ERROR - API초기화 도중 에러발생<br>
	*/
	virtual ReturnType onInitialize();

	/**
	*	컴포넌트가 활성화될 때 호출되는 콜백함수이다.
	*	@return OPROS_SUCCESS - 컴포넌트 활성화 성공<br>
	*			OPROS_PRECONDITION_NOT_MET - API핸들이 NULL이거나 컴포넌트의 상태가 READY또는 INACTIVE 상태가 아님<br>
	*			OPROS_ENABLE_API_ERROR - API활성화 도중 에러발생<br>
	*/
	virtual ReturnType onStart();

	/**
	*	컴포넌트가 비활성화될 때 호출되는 콜백함수이다.
	*	@return OPROS_SUCCESS - 컴포넌트 비활성화 성공<br>
	*			OPROS_PRECONDITION_NOT_MET - API핸들이 NULL이거나 컴포넌트의 상태가 ACTIVE 상태가 아님<br>
	*			OPROS_DISABLE_API_ERROR - API비활성화 도중 에러발생<br>
	*/
	virtual ReturnType onStop();

	/**
	*	컴포넌트가 리셋 될 때 호출되는 콜백함수이다.
	*	리셋작업을 수행할 때 API호출 순서는 finalize, initialize, enable순이다.
	*	사용하는 모든 API에 대해 같은 작업을 수행한다.
	*	호출에 실패할 경우 에러를 리턴 한다. enable호출에 실패하면 다시 finalize를 호출한다.
	*	@return OPROS_SUCCESS - 컴포넌트 리셋 성공<br>
	*			OPROS_PRECONDITION_NOT_MET - API핸들이 NULL인 상태<br>
	*			OPROS_RESET_API_ERROR - API리셋 도중 에러발생<br>
	*/
	virtual ReturnType onReset();

	/**
	*	컴포넌트에 에러가 발생했을 때 호출되는 콜백함수이다.
	*	에러가 발생하면 API의 disable을 호출하여 비활성화 시킨다.
	*	사용하는 모든 API에 대해 같은 작업을 수행한다.
	*	@return OPROS_SUCCESS - 에러발생 후 비활성화 성공<br>
	*			OPROS_PRECONDITION_NOT_MET - API핸들이 NULL인 상태<br>
	*			OPROS_DISABLE_API_ERROR - API비활성화 도중 에러발생<br>
	*/
	virtual ReturnType onError();

	/**
	*	컴포넌트의 에러를 복구할 때 호출되는 콜백함수이다.
	*	에러 복구 시 API호출 순서는 finalize, initialize순이다.
	*	사용하는 모든 API에 대해 같은 작업을 수행한다.
	*	@return OPROS_SUCCESS - 에러복구 성공<br>
	*			OPROS_PRECONDITION_NOT_MET - API핸들이 NULL인 상태<br>
	*			OPROS_RECOVER_API_ERROR - API복구 도중 에러발생<br>
	*/
	virtual ReturnType onRecover();

	/**
	*	컴포넌트가 종료될 때 호출되는 콜백함수이다.
	*	finalize를 호출하여 API를 종료하고, API핸들과 DLL핸들을 삭제한다.
	*	사용하는 모든 API에 대해 같은 작업을 수행한다.
	*	@return OPROS_SUCCESS - 컴포넌트 종료 성공<br>
	*			OPROS_PRECONDITION_NOT_MET - API핸들이 NULL인 상태<br>
	*			OPROS_FINALIZE_API_ERROR - API종료 도중 에러발생<br>
	*/
	virtual ReturnType onDestroy();

public:
	/**
	*	컴포넌트가 이벤트를 받았을 때 호출되는 콜백함수이다.
	*	KeyInputComponent에서는 사용되지 않음.
	*	@return OPROS_SUCCESS &nbsp;
	*/
	virtual ReturnType onEvent(Event *evt);

	/**
	*	컴포넌트가 주기적으로 동작할 때 호출되는 콜백함수이다.
	*	API의 execute를 호출하여 동작을 수행한다.
	*	@return OPROS_SUCCESS - 컴포넌트 동작 성공<br>
	*			OPROS_CALLER_ERROR - 컴포넌트 동작 실패, 또는 API핸들이 NULL인 경우<br>
	*/
	virtual ReturnType onExecute();

	/**
	*	컴포넌트가 주기적으로 동작할 때 호출되는 콜백함수이다.
	*	KeyInputComponent에서는 사용되지 않음.
	*	@return OPROS_SUCCESS &nbsp;
	*/
	virtual ReturnType onUpdated();

	/**
	*	컴포넌트의 동작 주기가 변경되었을 때 호출되는 콜백함수이다.
	*	KeyInputComponent에서는 사용되지 않음.
	*	@return OPROS_SUCCESS &nbsp;
	*/
	virtual ReturnType onPeriodChanged();
public:

	// 서비스포트
	/**
	*	KeyInputComponent의 프로파일을 변경한다.
	*	다른 컴포넌트에서 이 컴포넌트의 프로파일을 변경할 때 사용된다.
	*	API의 setParameter를 호출하여 그 결과를 리턴한다.
	*	@param parameter 설정할 파라미터 정보
	*	@return true - 파라미터 데이터설정 성공<br>
	*			false - 파라미터 데이터설정을 실패했거나, API핸들이 NULL인 경우, 또는<br>
	* &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 컴포넌트의 상태가 ACTIVE, INACTIVE가 아닌 다른 상태인 경우<br>
	*/
	virtual bool setParameter(Property parameter);

	/**
	*	KeyInputComponent의 프로파일을 다른 컴포넌트에서 가져갈 때 사용된다.
	*	@param parameter 파라미터정보가 저장됨
	*	@return true - 파라미터 데이터 가져오기 성공<br>
	*			false - API핸들이 NULL인 경우<br>
	*/
	virtual bool getParameter(Property *parameter);

	/**
	*	키보드 입력 처리하는 함수이다.
	*	@return ret - update에서 체크한 키보드의 종류에 따라서 리턴값이 정해짐<BR>
		*/
	virtual int getKeyInput();//HWND hWnd);
private:
//	HWND hWnd;
	int ret;

};

#endif

