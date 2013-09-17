// facedetect.h : main header file for the FACEDETECT DLL
//
#pragma warning(disable : 4793)
#pragma once

#include <cv.h>

#define MAXOBJECTCOUNT 5
#define MaxValue 32000

#pragma  


/**
* 하나의 물체 검출을 위한 클래스이다.
* 주어진 classifier cascade에 의해 물체를 검출한다.
* OpenCV에서 제공하는 CvHaarClassifierCascade를 사용한다.
*/
class ObjectLocator 
{
public:
	/**
	* 물체를 검출하는 클래스의 생성자 함수이다.
	* 스케일 값과 cascade, 위치정보에 대해 초기값을 설정한다.
	*/
	ObjectLocator();

	/**
	* 물체를 검출하는 클래스의 소멸자 함수이다.
	* storage, cascade, 영상 메모리를 초기화 한다.
	*/
	~ObjectLocator();

private:
	/**
	* 주어진 물체 영상의 크기를 나타낸다. 
	* width는 영상의 넓이이고, height는 영상의 높이를 의미한다.
	*/
	int width,height;

	/**
	* OpenCV에서 제공하는 haar classifier cascade 클래스를 사용한다.
	* cascade 명은 보통 xml 형태로 구성된다.
	*/
	CvHaarClassifierCascade* cascade;

	/**
	* 물체 검출을 위해 사용되는 내부 메모리 변수 이다.
	* 물체 검출시 데이터를 저장하는 변수로 사용된다.
	*/
	CvMemStorage* storage;

	/** 
	* 물체 위치를 저장하는 변수이다.
	* MAXOBJECTCOUNT는 최대 물체 개수로 정의되어 있다.
	* 각 물체위치는 하나의 물체당 4개로 할당되어 있다. 
	* 여기에 (x1,y1), (x2,y2) 정보가 들어간다.
	*/
	int object_location[MAXOBJECTCOUNT][4];
	
	/**
	* index 값에 따라 순차적 요소를 찾아 되돌려 준다.
	* @param seq: 정보가 저장되어 있는 시퀀스 데이터이다.
	* @param index: 정보에 해당하는 index 순서 값이다.
	* @return  해당한 요소의 char 데이터를 되돌려 준다.
	*/
	signed char* Helper( const CvSeq *seq, int index )
	{
		CvSeqBlock block;
		int count, total = seq->total;

		if( (unsigned)index >= (unsigned)total )
		{
			index += index < 0 ? total : 0;
			index -= index >= total ? total : 0;
			if( (unsigned)index >= (unsigned)total )
				return 0;
		}

		block = *seq->first;
		if( index + index <= total )
		{
			while( index >= (count = block.count) )
			{
				block = *block.next;
				index -= count;
			}
		}
		else
		{
			do
			{
				block = *block.prev;
				total -= block.count;
			}
			while( index < total );
			index -= total;
		}

		return block.data + index * seq->elem_size;
	}

private:
	/**
	* 물체 스케일 값이다.
	* 스케일 값이 커짐에 따라 처리할 영상의 크기는 반대로 작아지며 속도가 빨라진다.
	*/
	double m_Scale;

public:
	/**
	* 물체 스케일 값을 정하는 함수이다.
	* 스케일 값이 커짐에 따라 처리할 영상의 크기는 반대로 작아지며 속도가 빨라진다.
	*/
	void SetScale(float scale);

	/**
	* 검출된 얼굴 영역을 영상에서 지정하는 함수이다.
	* @param index: 검출된 해당 얼굴 번호이다.
	*/
	void SetFaceROI(int index);

	/**
	* 검출된 얼굴 영역을 영상에서 해제는 함수이다.
	* SetFaceROI()함수와 같이 사용한다.
	*/
	void UnSetFaceROI();

	/**
	* 설정된 영상의 메모리를 해제한다.
	* 여기서는 small 영상과 big 영상에 대한 처리를 수행한다.
	*/
	void UnInitImageStorage();

	/**
	* 물체 검출을 위해 영상의 메모리를 설정한다.
	* 영상은 small 영상과 big 영상에 대한 메모리를 설정핸다.
	* small 영상은 m_Scale에 의해 크기가 정해진다.
	*/
	void InitImageStorage(int img_width, int img_height);
	
	/**
	* 물체 검출을 위한 영상 전처리 함수이다.
	* 물체 영상의 크기를 설정하고, 히스토그램 평활화를 수행한다.
	*/
	void ImagePreProcessForFaceDetection();
		
	/**
	* 관리된 영상을 관리되지 않은 영상에 보내는 함수이다.
	* @param Src: 관리되지 않은 원 영상이다.
	* 이함수는 높은 프레임 rate에 대해 더블 버퍼링을 위해 사용된다.
	*/
	void ManagedImagetoUnManagedImage(IplImage* Src);

	/**
	* 검출된 물체의 개수이다.
	*/
	int NoOfObjects;

	/**
	* 검출된 물체의 위치를 얻는 함수이다.
	* @param oNum: 검출된 물체의 색인 번호이다.
	* @param tx: 검출된 물체의 왼쪽 상단의 x좌표이다.
	* @param ty: 검출된 물체의 왼쪽 상단의 y좌표이다.
	* @param bx: 검출된 물체의 오른쪽 하단의 x좌표이다.
	* @param by: 검출된 물체의 오른쪽 하단의 y좌표이다.
	* @return true: 정상적으로 위치를 얻은 경우
	*         false: 위치 정보를 얻지 못한 경우
	*/
	bool GetObjectCoordinates(int oNum, int &tx, int &ty, int &bx, int &by);

	/**
	* 검출된 물체의 위치를 얻는 함수이다. 단 스케일 값을 적용한다.
	* @param oNum: 검출된 물체의 색인 번호이다.
	* @param tx: 검출된 물체의 왼쪽 상단의 x좌표이다.
	* @param ty: 검출된 물체의 왼쪽 상단의 y좌표이다.
	* @param bx: 검출된 물체의 오른쪽 하단의 x좌표이다.
	* @param by: 검출된 물체의 오른쪽 하단의 y좌표이다.
	* @param scale: 물체 위치에 대한 스케일 값을 적용한다.
	* @return true: 정상적으로 위치를 얻은 경우
	*         false: 위치 정보를 얻지 못한 경우
	*/
	bool GetObjectCoordinates(int oNum, int &tx, int &ty, int &bx, int &by,double scale);

	/**
	* 물체 검출을 수행하는 함수이다.
	* Haar-like features 알고리즘을 이용해 물체를 검출한다.
	* 내부에서 사용된 함수로는 cvHaarDetectObjects() 함수를 사용한다.
	*/
	int DetectObjects();

	/**
	* 물체 검출을 위해 초기화 하는 함수이다.
	* @param cascadename: cascade 명을 입력한다.
	* 이 함수는 메모리 저장 변수를 할당하고, cascade를 불러온다.
	* @return 0: cascade를 불러오지 못했을 경우 리턴된다.
	*         1: 정상적으로 불러왔을 경우 리턴된다.
	*/
	int InitObjectDetect(char* cascadename);	

};

