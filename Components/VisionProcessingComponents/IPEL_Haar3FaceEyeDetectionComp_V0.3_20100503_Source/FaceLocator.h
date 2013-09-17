// FaceDetection.h
#pragma once
#include "ObjectLocator.h"
#include <stdio.h>

#define MAXEYERAD 100
#define MINEYERAD 10

static int InitFlag = 0;
static int lastHeight, lastWidth;


/**
* 얼굴 위치 검출 클래스이다.
* 클래스내에 얼굴과 두 눈의 위치를 검출하기 위한 3개의 classifier를 따로 갖고 있다.
*/
class FaceLocator
	{
	private:		
		/**
		* 얼굴을 검출하는 검출클래스 변수이다.
		* ObjectLocator는 haar classifier를 통해 원하는 물체를 검출해 낸다.
		*/
		ObjectLocator* FaceDetector;
		/**
		* 왼쪽눈을 검출하는 검출클래스 변수이다.
		* ObjectLocator는 haar classifier를 통해 원하는 물체를 검출해 낸다.
		*/
		ObjectLocator* LeftEyeDetector;		
		/**
		* 오른쪽눈을 검출하는 검출클래스 변수이다.
		* ObjectLocator는 haar classifier를 통해 원하는 물체를 검출해 낸다.
		*/
		ObjectLocator* RightEyeDetector;		

		/**
		* 세가지 필요한 cascade 파일을 불러오는 함수이다.
		*   haarcascade_frontalface_alt.xml
		*   eyeR.xml
		*   eyeL.xml
		*/
		void InitCascades();

	public:	
		/**
		* 얼굴 검출 클래스의 생성자 함수 이다.
		*/
		FaceLocator(void);	
		
		/**
		* 얼굴 검출 클래스의 소멸자 함수이다.
		*/
		~FaceLocator(void);

		/**
		* 얼굴들을 검출하는 함수이다.
		* @param ImageData 얼굴 검출을 위한 입력영상으로 IplImage 타입이다.
		*/
		int DetectFaces(IplImage* ImageData);
		
		/**
		* 검출된 얼굴의 위치를 가져오는 함수이다.
		* @param index 검출된 얼굴의 순서 번호이다.
		* @param lx    검출된 얼굴의 왼쪽 상단의 x좌표이다.
		* @param ly    검출된 얼굴의 왼쪽 상단의 y좌표이다.
		* @param rx    검출된 얼굴의 오른쪽 하단의 x좌표이다.
		* @param ry    검출된 얼굴의 오른쪽 하단의 y좌표이다.
		* @return true:  정상적으로 정보를 가져온 경우
		*         false: 정보를 가져오지 못한 경우
		*/
		int GetFaceCordinates(int index, int &lx, int &ly, int &rx, int &ry);	

		/**
		* 검출된 해당 얼굴의 눈의 위치를 가져오는 함수이다.
		* @param ImageData 검출된 얼굴의 입력영상으로 IplImage 타입이다.
		* @param lx    검출된 왼쪽 눈의 왼쪽 상단 x좌표이다.
		* @param ly    검출된 왼쪽 눈의 왼쪽 상단 y좌표이다.
		* @param rx    검출된 오른쪽 눈의 오른쪽 하단 x좌표이다.
		* @param ry    검출된 오른쪽 눈의 오른쪽 하단 y좌표이다.
		* @return 2:   두 개의 눈을 검출한 경우
		*         1:   한 개의 눈을 검출한 경우
		*        -1:   모든 눈을 검출하지 못한 경우
		*/
		int GetEyeCordinates(IplImage* ImageData,int index, int &lx, int &ly, int &rx, int &ry);
	};
