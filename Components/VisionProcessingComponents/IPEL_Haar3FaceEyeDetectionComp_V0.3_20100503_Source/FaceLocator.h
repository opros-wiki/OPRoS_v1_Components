// FaceDetection.h
#pragma once
#include "ObjectLocator.h"
#include <stdio.h>

#define MAXEYERAD 100
#define MINEYERAD 10

static int InitFlag = 0;
static int lastHeight, lastWidth;


/**
* �� ��ġ ���� Ŭ�����̴�.
* Ŭ�������� �󱼰� �� ���� ��ġ�� �����ϱ� ���� 3���� classifier�� ���� ���� �ִ�.
*/
class FaceLocator
	{
	private:		
		/**
		* ���� �����ϴ� ����Ŭ���� �����̴�.
		* ObjectLocator�� haar classifier�� ���� ���ϴ� ��ü�� ������ ����.
		*/
		ObjectLocator* FaceDetector;
		/**
		* ���ʴ��� �����ϴ� ����Ŭ���� �����̴�.
		* ObjectLocator�� haar classifier�� ���� ���ϴ� ��ü�� ������ ����.
		*/
		ObjectLocator* LeftEyeDetector;		
		/**
		* �����ʴ��� �����ϴ� ����Ŭ���� �����̴�.
		* ObjectLocator�� haar classifier�� ���� ���ϴ� ��ü�� ������ ����.
		*/
		ObjectLocator* RightEyeDetector;		

		/**
		* ������ �ʿ��� cascade ������ �ҷ����� �Լ��̴�.
		*   haarcascade_frontalface_alt.xml
		*   eyeR.xml
		*   eyeL.xml
		*/
		void InitCascades();

	public:	
		/**
		* �� ���� Ŭ������ ������ �Լ� �̴�.
		*/
		FaceLocator(void);	
		
		/**
		* �� ���� Ŭ������ �Ҹ��� �Լ��̴�.
		*/
		~FaceLocator(void);

		/**
		* �󱼵��� �����ϴ� �Լ��̴�.
		* @param ImageData �� ������ ���� �Է¿������� IplImage Ÿ���̴�.
		*/
		int DetectFaces(IplImage* ImageData);
		
		/**
		* ����� ���� ��ġ�� �������� �Լ��̴�.
		* @param index ����� ���� ���� ��ȣ�̴�.
		* @param lx    ����� ���� ���� ����� x��ǥ�̴�.
		* @param ly    ����� ���� ���� ����� y��ǥ�̴�.
		* @param rx    ����� ���� ������ �ϴ��� x��ǥ�̴�.
		* @param ry    ����� ���� ������ �ϴ��� y��ǥ�̴�.
		* @return true:  ���������� ������ ������ ���
		*         false: ������ �������� ���� ���
		*/
		int GetFaceCordinates(int index, int &lx, int &ly, int &rx, int &ry);	

		/**
		* ����� �ش� ���� ���� ��ġ�� �������� �Լ��̴�.
		* @param ImageData ����� ���� �Է¿������� IplImage Ÿ���̴�.
		* @param lx    ����� ���� ���� ���� ��� x��ǥ�̴�.
		* @param ly    ����� ���� ���� ���� ��� y��ǥ�̴�.
		* @param rx    ����� ������ ���� ������ �ϴ� x��ǥ�̴�.
		* @param ry    ����� ������ ���� ������ �ϴ� y��ǥ�̴�.
		* @return 2:   �� ���� ���� ������ ���
		*         1:   �� ���� ���� ������ ���
		*        -1:   ��� ���� �������� ���� ���
		*/
		int GetEyeCordinates(IplImage* ImageData,int index, int &lx, int &ly, int &rx, int &ry);
	};
