#ifndef _COLORRECOGNITION_H_
#define _COLORRECOGNITION_H_

#include "OprosApi.h"

// 개요
/**
 *	색상인식 API는 이미지 정보를 입력받아 특정한 색상을 인식하는 인터페이스이다.
 *	<center><table border=0><tr><td colspan=3><center><b>GlobalMap API에서 사용하는 Parameter</b></center></td></tr>
 *	<tr><td bgcolor=#dddddd><center><b>Index</b></center></td><td bgcolor=#dddddd><center><b>Type of Value</b></center></td><td bgcolor=#dddddd><center><b>Description</b></center></td></tr>
 *	<tr><td><b>dbName</b></td><td>string</td><td>색상인식 API에서 사용할 데이터베이스 파일로서 컬러와 색 영역 정보가 포함되어 있다.</td></tr>
 *	</table></center>
 */
class ColorRecognition : public OprosApi
{
public:
	ColorRecognition(void) { };
	virtual ~ColorRecognition(void) { };

public:
	/**
	 *	이미지에서 색을 인식한다.
	 *	@param image 인식할 색상이 있는 이미지
	 *	@param width 이미지의 폭
	 *	@param height 이미지의 높이
	 *	@param pixelByte 한 픽셀을 저장할 메모리의 크기
	 *	@return 색상 인식의 결과를 VisionRecognitionResult형식으로 반환한다.<br>
	 */
	virtual std::valarray<VisionRecognitionResult> recognize(unsigned char *image, int width, int height, int pixelbyte) = 0;

	/**
	 *	Database에 색 데이터를 추가한다.
	 *	@param image 인식할 물체가 있는 이미지
	 *	@param name 색 정보의 이름
	 *	@param min1 첫번째 채널(Hue)의 최소 영역
	 *	@param max1 첫번째 채널(Hue)의 최대 영역
	 *	@param min2 두번째 채널(Saturation)의 최소 영역
	 *	@param max2 두번째 채널(Saturation)의 최대 영역
	 *	@param min3 세번째 채널(Value)의 최소 영역
	 *	@param max3 세번째 채널(Value)의 최대 영역
	 *	@return true - 성공적으로 색 정보를 저장한 경우 true 값을 반환한다.<br>
	 *			false - 색 정보 저장을 실패한 경우 false 값을 반환한다.<br>
	 */
	virtual bool addItem(std::string name, unsigned char min1, unsigned char max1, unsigned char min2, unsigned char max2, unsigned char min3, unsigned char max3) = 0;

	/**
	 *	색 Database에서 addItem에서 입력되었던 name의 색 데이터를 삭제한다.
	 *	@param name 지울 색 데이터의 이름
	 *	@return true - 성공적으로 색 정보를 삭제한 경우 true 값을 반환한다.<br>
	 *			false - 색 정보 삭제를 실패한 경우 false 값을 반환한다.<br>
	 */
	virtual bool removeItem(std::string name) = 0;

	/**
	 *	색 Database에서 addItem에서 입력되었던 name의 색 데이터를 삭제한다.
	 *	@param name 지울 색 데이터의 이름
	 *	@return true - 성공적으로 색 정보 데이터베이스를 초기화한 경우 true 값을 반환한다.<br>
	 *			false - 색 정보 데이터베이스의 초기화를 실패한 경우 false 값을 반환한다.<br>
	 */
	virtual bool cleanUpItems(void) = 0;
};


#endif
