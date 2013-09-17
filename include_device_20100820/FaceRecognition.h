#ifndef _FACERECOGNITION_H_
#define _FACERECOGNITION_H_

#include "OprosApi.h"

// 개요
/**
 *	안면인식 API는 이미지 정보를 입력받아 안면을 인식하는 인터페이스이다.
 *	<center><table border=0><tr><td colspan=3><center><b>GlobalMap API에서 사용하는 Parameter</b></center></td></tr>
 *	<tr><td bgcolor=#dddddd><center><b>Index</b></center></td><td bgcolor=#dddddd><center><b>Type of Value</b></center></td><td bgcolor=#dddddd><center><b>Description</b></center></td></tr>
 *	<tr><td><b>dbName</b></td><td>string</td><td>안면인식 API에서 사용할 데이터베이스 파일로서 얼굴에 대한 정보가 포함되어 있다.</td></tr>
 *	</table></center>
 */
class FaceRecognition : public OprosApi
{
public:
	FaceRecognition(void) { };
	virtual ~FaceRecognition(void) { };

public:
	/**
	 *	이미지에서 안면을 인식한다.
	 *	@param image 인식할 얼굴이 있는 이미지
	 *	@param width 이미지의 폭
	 *	@param height 이미지의 높이
	 *	@param pixelByte 한 픽셀을 저장할 메모리의 크기
	 *	@return 안면 인식의 결과를 VisionRecognitionResult형식으로 반환한다.<br>
	 */
	virtual std::valarray<VisionRecognitionResult>recognize(unsigned char *image, int width, int height, int pixelbyte) = 0;

	/**
	 *	Database에 안면 데이터를 추가한다.
	 *	@param fileName 안면 데이터를 저장 할 데이터베이스
	 *	@return true - 성공적으로 얼굴인식 정보를 저장한 경우 true 값을 반환한다.<br>
	 *			false - 얼굴인식 정보 저장을 실패한 경우 false 값을 반환한다.<br>
	 */
	virtual bool addItem(std::string fileName) = 0;

	/**
	 *	안면 Database에서 addItem에서 입력되었던 name의 안면 데이터를 삭제한다.
	 *	@param name 지울 안면 데이터의 이름
	 *	@return true - 성공적으로 얼굴인식 정보를 삭제한 경우 true 값을 반환한다.<br>
	 *			false - 얼굴인식 정보 삭제를 실패한 경우 false 값을 반환한다.<br>
	 */
	virtual bool removeItem(std::string name) = 0;

	/**
	 *	안면 Database를 모두 제거한다.
	 *	@return true - 성공적으로 얼굴인식 정보 데이터베이스를 초기화한 경우 true 값을 반환한다.<br>
	 *			false - 얼굴인식 정보 데이터베이스의 초기화를 실패한 경우 false 값을 반환한다.<br>
	 */
	virtual bool cleanUpItems(void) = 0;
};


#endif
