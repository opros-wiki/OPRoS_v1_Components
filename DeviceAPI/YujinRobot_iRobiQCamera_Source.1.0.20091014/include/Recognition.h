#ifndef _RECOGNITION_H_
#define _RECOGNITION_H_

#include "Application.h"
#include "OprosApiTypes.h"

namespace OPRoS
{

// 개요
/**
 *	인식 API는 주변 환경의 이미지 정보를 카메라로 입력받은 후 이를 분석하여 특정한 물체의
 *	이름, 영역, 위치 그리고 틀어진 각도 등의 정보를 인식하는데 필요한 인터페이스를 말한다.
 */
class Recognition : public Application
{
public:
	Recognition(void) { };
	virtual ~Recognition(void) { };

public:
	/**
	 *	데이터베이스에 새로운 물체 데이터를 추가한다.
	 *	@param fileName 물체 데이터를 저장 할 데이터베이스
	 *	@return true - 성공적으로 데이터를 저장한 경우 true 값을 반환한다.<br>
	 *			false - 인식 데이터 저장을 실패한 경우 false 값을 반환한다.<br>
	 */
	virtual bool add(const char *fileName) = 0;

	/**
	 *	이미지에서 대상을 인식한다.
	 *	@param image 인식할 대상이 있는 이미지
	 *	@param width 이미지의 폭
	 *	@param height 이미지의 높이
	 *	@param pixelByte 한 픽셀을 저장할 메모리의 크기
	 *	@return 대상 인식의 결과를 VisionRecognitionResult형식으로 반환한다.<br>
	 */
	virtual std::valarray<VisionRecognitionResult>recognize(unsigned char *image, int width, int height, int pixelbyte) = 0;

	/**
	 *	데이터베이스에서 특정 대상의 데이터를 지운다.
	 *	@param name 지울 데이터의 이름
	 *	@return true - 성공적으로 인식 정보를 삭제한 경우 true 값을 반환한다.<br>
	 *			false - 인식 정보 삭제를 실패한 경우 false 값을 반환한다.<br>
	 */
	virtual bool remove(const char *name) = 0;

	/**
	 *	데이터베이스를 초기화한다.
	 *	@return true - 성공적으로 인식 정보 데이터베이스를 초기화한 경우 true 값을 반환한다.<br>
	 *			false - 인식 정보 데이터베이스의 초기화를 실패한 경우 false 값을 반환한다.<br>
	 */
	virtual bool cleanUp(void) = 0;
};

};

#endif
