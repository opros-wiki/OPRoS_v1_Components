// facedetect.h : main header file for the FACEDETECT DLL
//
#pragma warning(disable : 4793)
#pragma once

#include <cv.h>

#define MAXOBJECTCOUNT 5
#define MaxValue 32000

#pragma  


/**
* �ϳ��� ��ü ������ ���� Ŭ�����̴�.
* �־��� classifier cascade�� ���� ��ü�� �����Ѵ�.
* OpenCV���� �����ϴ� CvHaarClassifierCascade�� ����Ѵ�.
*/
class ObjectLocator 
{
public:
	/**
	* ��ü�� �����ϴ� Ŭ������ ������ �Լ��̴�.
	* ������ ���� cascade, ��ġ������ ���� �ʱⰪ�� �����Ѵ�.
	*/
	ObjectLocator();

	/**
	* ��ü�� �����ϴ� Ŭ������ �Ҹ��� �Լ��̴�.
	* storage, cascade, ���� �޸𸮸� �ʱ�ȭ �Ѵ�.
	*/
	~ObjectLocator();

private:
	/**
	* �־��� ��ü ������ ũ�⸦ ��Ÿ����. 
	* width�� ������ �����̰�, height�� ������ ���̸� �ǹ��Ѵ�.
	*/
	int width,height;

	/**
	* OpenCV���� �����ϴ� haar classifier cascade Ŭ������ ����Ѵ�.
	* cascade ���� ���� xml ���·� �����ȴ�.
	*/
	CvHaarClassifierCascade* cascade;

	/**
	* ��ü ������ ���� ���Ǵ� ���� �޸� ���� �̴�.
	* ��ü ����� �����͸� �����ϴ� ������ ���ȴ�.
	*/
	CvMemStorage* storage;

	/** 
	* ��ü ��ġ�� �����ϴ� �����̴�.
	* MAXOBJECTCOUNT�� �ִ� ��ü ������ ���ǵǾ� �ִ�.
	* �� ��ü��ġ�� �ϳ��� ��ü�� 4���� �Ҵ�Ǿ� �ִ�. 
	* ���⿡ (x1,y1), (x2,y2) ������ ����.
	*/
	int object_location[MAXOBJECTCOUNT][4];
	
	/**
	* index ���� ���� ������ ��Ҹ� ã�� �ǵ��� �ش�.
	* @param seq: ������ ����Ǿ� �ִ� ������ �������̴�.
	* @param index: ������ �ش��ϴ� index ���� ���̴�.
	* @return  �ش��� ����� char �����͸� �ǵ��� �ش�.
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
	* ��ü ������ ���̴�.
	* ������ ���� Ŀ���� ���� ó���� ������ ũ��� �ݴ�� �۾����� �ӵ��� ��������.
	*/
	double m_Scale;

public:
	/**
	* ��ü ������ ���� ���ϴ� �Լ��̴�.
	* ������ ���� Ŀ���� ���� ó���� ������ ũ��� �ݴ�� �۾����� �ӵ��� ��������.
	*/
	void SetScale(float scale);

	/**
	* ����� �� ������ ���󿡼� �����ϴ� �Լ��̴�.
	* @param index: ����� �ش� �� ��ȣ�̴�.
	*/
	void SetFaceROI(int index);

	/**
	* ����� �� ������ ���󿡼� ������ �Լ��̴�.
	* SetFaceROI()�Լ��� ���� ����Ѵ�.
	*/
	void UnSetFaceROI();

	/**
	* ������ ������ �޸𸮸� �����Ѵ�.
	* ���⼭�� small ����� big ���� ���� ó���� �����Ѵ�.
	*/
	void UnInitImageStorage();

	/**
	* ��ü ������ ���� ������ �޸𸮸� �����Ѵ�.
	* ������ small ����� big ���� ���� �޸𸮸� �����ڴ�.
	* small ������ m_Scale�� ���� ũ�Ⱑ ��������.
	*/
	void InitImageStorage(int img_width, int img_height);
	
	/**
	* ��ü ������ ���� ���� ��ó�� �Լ��̴�.
	* ��ü ������ ũ�⸦ �����ϰ�, ������׷� ��Ȱȭ�� �����Ѵ�.
	*/
	void ImagePreProcessForFaceDetection();
		
	/**
	* ������ ������ �������� ���� ���� ������ �Լ��̴�.
	* @param Src: �������� ���� �� �����̴�.
	* ���Լ��� ���� ������ rate�� ���� ���� ���۸��� ���� ���ȴ�.
	*/
	void ManagedImagetoUnManagedImage(IplImage* Src);

	/**
	* ����� ��ü�� �����̴�.
	*/
	int NoOfObjects;

	/**
	* ����� ��ü�� ��ġ�� ��� �Լ��̴�.
	* @param oNum: ����� ��ü�� ���� ��ȣ�̴�.
	* @param tx: ����� ��ü�� ���� ����� x��ǥ�̴�.
	* @param ty: ����� ��ü�� ���� ����� y��ǥ�̴�.
	* @param bx: ����� ��ü�� ������ �ϴ��� x��ǥ�̴�.
	* @param by: ����� ��ü�� ������ �ϴ��� y��ǥ�̴�.
	* @return true: ���������� ��ġ�� ���� ���
	*         false: ��ġ ������ ���� ���� ���
	*/
	bool GetObjectCoordinates(int oNum, int &tx, int &ty, int &bx, int &by);

	/**
	* ����� ��ü�� ��ġ�� ��� �Լ��̴�. �� ������ ���� �����Ѵ�.
	* @param oNum: ����� ��ü�� ���� ��ȣ�̴�.
	* @param tx: ����� ��ü�� ���� ����� x��ǥ�̴�.
	* @param ty: ����� ��ü�� ���� ����� y��ǥ�̴�.
	* @param bx: ����� ��ü�� ������ �ϴ��� x��ǥ�̴�.
	* @param by: ����� ��ü�� ������ �ϴ��� y��ǥ�̴�.
	* @param scale: ��ü ��ġ�� ���� ������ ���� �����Ѵ�.
	* @return true: ���������� ��ġ�� ���� ���
	*         false: ��ġ ������ ���� ���� ���
	*/
	bool GetObjectCoordinates(int oNum, int &tx, int &ty, int &bx, int &by,double scale);

	/**
	* ��ü ������ �����ϴ� �Լ��̴�.
	* Haar-like features �˰����� �̿��� ��ü�� �����Ѵ�.
	* ���ο��� ���� �Լ��δ� cvHaarDetectObjects() �Լ��� ����Ѵ�.
	*/
	int DetectObjects();

	/**
	* ��ü ������ ���� �ʱ�ȭ �ϴ� �Լ��̴�.
	* @param cascadename: cascade ���� �Է��Ѵ�.
	* �� �Լ��� �޸� ���� ������ �Ҵ��ϰ�, cascade�� �ҷ��´�.
	* @return 0: cascade�� �ҷ����� ������ ��� ���ϵȴ�.
	*         1: ���������� �ҷ����� ��� ���ϵȴ�.
	*/
	int InitObjectDetect(char* cascadename);	

};

