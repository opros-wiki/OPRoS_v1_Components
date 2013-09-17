// AI classifier class
// ANN과 SVM을 이용하여 classifier를 행한다.

#ifndef AICLASSIFIER_H_
#define AICLASSIFIER_H_


#include "annlayer.h"
#include "annetwork.h"
#include "svm.h"

/*
* AIClassifier는 Artificial intelligent classifier의 약자이다.
* 정보를 classifer하기 위해 사용되는 클래스이다.
* 여기서 사용된 주 알고리즘은 Artifical Neural Network와 
* Support Vector Machine 알고리즘이다.
*/
class AIClassifier
{
public:
	/*
	* AIClassifier 클래스의 생성자 함수이다.
	* SVM과 ANN 클래스를 생성하는 과정이다.
	* @param fname: svm과 ann의 데이터 파일명이다.
	*/
	AIClassifier(const wchar_t* fname);

	/*
	* AIClassifier 클래스의 소멸자 함수이다.
	* SVM과 ANN 클래스를 소멸하는 과정이다.
	*/
	~AIClassifier();

// Operations
	/*
	* classify를 수행하는 함수이다.
	* @param x: 위치 x 정보이다.
	* @param y: 위치 y 정보이다.
	* @return  0: 
	*/
	inline int classify(const float* x, float* y);

// Access	
	/*
	* 이 함수는 현재 처리 상태를 리턴한다.
	* @return  1: 상태 정상
	*         -1: 상태 비정상
	*/
	inline int status() const;

	/*
	* 입력 dimension 값을 리턴한다.
	* @return  0이외의 값: svm의 dimension 또는 ann의 dimension 값을 리턴한다.
	*          0: dimension 값이 0이다.
	*/
	inline unsigned int input_dimension() const;

protected:

private:
	/*
	* AIClassifier 클래스의 생성자 함수이다.
	* SVM과 ANN 클래스를 생성하는 과정이다.
	*/
	AIClassifier(const AIClassifier& classifier);

// Operators
	/*
	* 오퍼레이터 = 함수이다.
	*/
	const AIClassifier& operator=(const AIClassifier& classifier);

	/*
	* svm과 ann의 처리 상태를 나타낸다.
	* 값 1: 상태 정상, -1: 상태 비정상
	*/
	int m_status;

	/*
	* ANN 알고리즘 클래스이다.
	* 패턴 분류기로 사용된다.
	*/
	ANNetwork* m_ann;
	
	/*
	* SVM 알고리즘 클래스이다.
	* 패턴 분류기로 사용된다.
	*/
	SVMachine* m_svm;  

	inline int sign(float x) const;
};

// Inlines
inline int AIClassifier::status() const
{
	return m_status;
}

inline unsigned int AIClassifier::input_dimension() const
{
	if (m_svm != 0 && m_svm->status() == 0) return m_svm->dimension();
	else if(m_ann != 0 && m_ann->status() == 0) return m_ann->dimension();
	else return 0;
}

inline int AIClassifier::sign(float x) const
{
	return (x >= 0.0f) ? 1 : -1;
}

inline int AIClassifier::classify(const float* x, float* y)
{
	double dy;
	int s = 0;
	
	if (m_ann != 0 && m_ann->status() == 0) {
		m_ann->classify(x, y);
		if (m_ann->activation_function() == AnnLayer::SIGMOID)
			s = sign(y[0] - 0.5f);
		else
			s = sign(y[0]);
	}
	else if (m_svm != 0 && m_svm->status() == 0) {
		s = m_svm->classify(x, dy);
		y[0] = float(dy);
	}
	else {
		y[0] = 0.0f;		
	}

	return s;
}



#endif //AICLASSIFIER_H_

