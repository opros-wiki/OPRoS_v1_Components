#ifndef _CameraComponent_COMPONENT_H
#define _CameraComponent_COMPONENT_H
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

#include <Property.h>
#include "CameraCompServiceProvided.h"
#include "Camera.h"
#include "RawImage.h"
	

// 개요
/**
 *	<table><tr><td>
 *	CameraComp는 로봇에서 vision의 역할을 하는 카메라를 위한 컴포넌트이다.
 *	이를 이용하여 개체인식, 위치인식 등의  시각적인 인지가 가능하다. CameraComp는
 *	CameraComp.xml, CameraCompServiceProvided.h가 포함되어야하며,
 *	CameraComp.xml에는 CameraComp의 프로파일이 저장되어 있다.
 *	CameraCompServiceProvided.h는 이 컴포넌트에서 제공하는 서비스 포트를 호출할 수 있는
 *	인터페이스를 제공한다.
 *	</td></tr><tr><td>
 *	<center><img src="../../images/uml/UML_Camera.jpg"></center>
 *	</td></tr></table>
 * 이 컴포넌트를 실행하기 위해서는 OpenCV 라이브러리의 Lib 디렉토리에 있는
 * cv200.dll cvaux200.dll cxcore200.dll highgui200.dll 파일을 실행파일이 있는 폴더에 두어야 한다.
*/
class CameraComp : public Component, public ICameraService
{
protected:
	// 속성
	//	Variables for CameraComp
	/**
	 *	Camera API DLL의 핸들이 저장될 변수이다. 
	*/
#if defined(WIN32)
	HMODULE hOprosAPI;
#else
	void *hOprosAPI;
#endif
	
	/**
	 *	Camera의 API 핸들로써, Camera API DLL에서 생성된
	 *	Camera클래스의 포인터를 저장하는 변수이다.
	*/
	Camera *camera;

	/**
	 *	CameraComp의 프로파일정보를 저장하는 변수이다.<br>
	 *	<!-- [표] Parameter -->
	 *	<table border=1>
	 *	<tr><td bgcolor="#EEEEEE"><center><b>이름</b></center></td> <td bgcolor="#EEEEEE"><center><b>타입</b></center></td> <td bgcolor="#EEEEEE" colspan=2><center><b>설명</b></center></td></tr>
	 *	<tr><td><b>ApiName</b></td> <td>std::string</td> <td>컴포넌트에서 사용할 dll파일의 이름이다.</td></tr>
	 *	<tr><td><b>CameraID</b></td> <td>int</td> <td>영상을 입력받을 카메라의 아이디이다.</td></tr>
	 *	<tr><td><b>Width</b></td> <td>int</td> <td>영상 입력데이터의 너비(단위:pixel)이다.</td></tr>
	 *	<tr><td><b>Height</b></td> <td>int</td> <td>영상 입력데이터의 높이(단위:pixel)이다.</td></tr>
	 *	<tr><td><b>PixelBytes</b></td> <td>int</td> <td>한 픽셀당 필요한 byte 수이다. 색 공간에 따라 달라진다. RGB는 3byte가 필요하다.</td></tr>
	 *	<tr><td><b>Flip</b></td> <td>int</td> <td>영상을 수평 또는 수직으로 뒤집는다. 0일 때는 아무 변환도 하지 않는다. 1일 때는 x축을 기준으로 반전(상하반전),
	 *	2일 때는 y축을 기준으로 반전(좌우반전), 3일 때는 x,y축을 기준으로 반전(상하좌우반전)이다. 3인 경우, 영상을 반전시키지 않고 180도 회전시킨 상태와 같다.</td></tr>
	 *	</table>
	*/
	Property parameter;

	/**
	 *	이미지 데이터를 임시로 저장할 버퍼이다. 카메라로부터 받은 데이터가 저장되며,
	 *	출력데이터 포트를 통해서 다른 컴포넌트로 전달한다.
	 */
	std::vector<unsigned char> imageBuffer;
	
	// 데이터포트
	/**
	 *	이미지 데이터를 전송할 출력 데이터포트이다.
	 *	이 포트를 통해 카메라로부터 받은 데이터가 다른 컴포넌트로 전달된다.
	 */
	OutputDataPort< vector<unsigned char> > imageData;

public:
	CameraComp();
	CameraComp(const std::string &compId);
	virtual ~CameraComp();
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
	 *	리셋작업을 수행할 때 API호출 순서는 Finalize, Initialize, Enable순이다.
	 *	사용하는 모든 API에 대해 같은 작업을 수행한다.
	 *	호출에 실패할 경우 에러를 리턴 한다. Enable호출에 실패하면 다시 Finalize를 호출한다.
	 *	@return OPROS_SUCCESS - 컴포넌트 리셋 성공<br>
	 *			OPROS_PRECONDITION_NOT_MET - API핸들이 NULL인 상태<br>
	 *			OPROS_RESET_API_ERROR - API리셋 도중 에러발생<br>
	 */
	virtual ReturnType onReset();

	/**
	 *	컴포넌트에 에러가 발생했을 때 호출되는 콜백함수이다.
	 *	에러가 발생하면 API의 Disable을 호출하여 비활성화 시킨다.
	 *	사용하는 모든 API에 대해 같은 작업을 수행한다.
	 *	@return OPROS_SUCCESS - 에러발생 후 비활성화 성공<br>
	 *			OPROS_PRECONDITION_NOT_MET - API핸들이 NULL인 상태<br>
	 *			OPROS_DISABLE_API_ERROR - API비활성화 도중 에러발생<br>
	 */
	virtual ReturnType onError();

	/**
	 *	컴포넌트의 에러를 복구할 때 호출되는 콜백함수이다.
	 *	에러 복구 시 API호출 순서는 Finalize, Initialize순이다.
	 *	사용하는 모든 API에 대해 같은 작업을 수행한다.
	 *	@return OPROS_SUCCESS - 에러복구 성공<br>
	 *			OPROS_PRECONDITION_NOT_MET - API핸들이 NULL인 상태<br>
	 *			OPROS_RECOVER_API_ERROR - API복구 도중 에러발생<br>
	 */
	virtual ReturnType onRecover();

	/**
	 *	컴포넌트가 종료될 때 호출되는 콜백함수이다.
	 *	Finalize를 호출하여 API를 종료하고, API핸들과 DLL핸들을 삭제한다.
	 *	사용하는 모든 API에 대해 같은 작업을 수행한다.
	 *	@return OPROS_SUCCESS - 컴포넌트 종료 성공<br>
	 *			OPROS_PRECONDITION_NOT_MET - API핸들이 NULL인 상태<br>
	 *			OPROS_FINALIZE_API_ERROR - API종료 도중 에러발생<br>
	 */
	virtual ReturnType onDestroy();

public:
	/**
	 *	컴포넌트가 이벤트를 받았을 때 호출되는 콜백함수이다.
	 *	CameraComp에서는 사용되지 않음.
	 *	@return OPROS_SUCCESS &nbsp;
	 */
	virtual ReturnType onEvent(Event *evt);

	/**
	 *	컴포넌트가 주기적으로 동작할 때 호출되는 콜백함수이다.
	 *	API의 GetImage를 호출하여 카메라로 부터 이미지를 가져와서
	 *	데이터포트로 push한다.
	 *	@return OPROS_SUCCESS - 동작성공<br>
	 *			OPROS_PRECONDITION_NOT_MET - API핸들이 NULL인 상태<br>
	 *			OPROS_CALL_API_ERROR - API호출 도중 에러 발생<br>
	 */
	virtual ReturnType onExecute();

	/**
	 *	컴포넌트가 주기적으로 동작할 때 호출되는 콜백함수이다.
	 *	CameraComp에서는 사용되지 않음.
	 *	@return OPROS_SUCCESS &nbsp;
	 */
	virtual ReturnType onUpdated();

	/**
	 *	컴포넌트의 동작 주기가 변경되었을 때 호출되는 콜백함수이다.
	 *	CameraComp에서는 사용되지 않음.
	 *	@return OPROS_SUCCESS &nbsp;
	 */
	virtual ReturnType onPeriodChanged();


	// 서비스포트
	/**
	 *	CameraComp의 프로파일을 변경한다.
	 *	다른 컴포넌트에서 이 컴포넌트의 프로파일을 변경할 때 사용된다.
	 *	API의 SetParameter를 호출하여 그 결과를 리턴한다.
	 *	@param parameter 설정할 파라미터 정보
	 *	@return true - 파라미터 데이터설정 성공<br>
	 *			false - 파라미터 데이터설정을 실패했거나, API핸들이 NULL인 경우, 또는<br>
	 * &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; 컴포넌트의 상태가 ACTIVE, INACTIVE가 아닌 다른 상태인 경우<br>
	 */
	virtual bool SetParameter(Property parameter);

	/**
	 *	CameraComp의 프로파일을 다른 컴포넌트에서 가져갈 때 사용된다.
	 *	CameraComp에서는 사용되지 않음.
	 *	@return parameter 파라미터정보
	 */
	virtual Property GetParameter();

	virtual int GetError();

	/**
	 *	카메라로부터 이미지 데이터를 가져온다.
	 *	버퍼의 크기를 파라미터정보를 이용하여 필요한 크기로 조정하고,
	 *	API의 GetImage를 호출하여 카메라에서 이미지 데이터를 가져와서
	 *	버퍼에 저장한다. 버퍼에서 필요한 size가 0이하인 경우,
	 *	false를 리턴 함과 동시에 에러 메시지를 출력한다.
	 *	CameraComp에서는 사용되지 않음.
	 *	@return 이미지 데이터
	 */
	virtual vector<unsigned char> GetImage();

private:
	int error;
};

#endif

