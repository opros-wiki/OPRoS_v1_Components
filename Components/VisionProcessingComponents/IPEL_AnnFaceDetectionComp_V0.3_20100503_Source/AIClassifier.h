// AI classifier class
// ANN�� SVM�� �̿��Ͽ� classifier�� ���Ѵ�.

#ifndef AICLASSIFIER_H_
#define AICLASSIFIER_H_


#include "annlayer.h"
#include "annetwork.h"
#include "svm.h"

/*
* AIClassifier�� Artificial intelligent classifier�� �����̴�.
* ������ classifer�ϱ� ���� ���Ǵ� Ŭ�����̴�.
* ���⼭ ���� �� �˰����� Artifical Neural Network�� 
* Support Vector Machine �˰����̴�.
*/
class AIClassifier
{
public:
	/*
	* AIClassifier Ŭ������ ������ �Լ��̴�.
	* SVM�� ANN Ŭ������ �����ϴ� �����̴�.
	* @param fname: svm�� ann�� ������ ���ϸ��̴�.
	*/
	AIClassifier(const wchar_t* fname);

	/*
	* AIClassifier Ŭ������ �Ҹ��� �Լ��̴�.
	* SVM�� ANN Ŭ������ �Ҹ��ϴ� �����̴�.
	*/
	~AIClassifier();

// Operations
	/*
	* classify�� �����ϴ� �Լ��̴�.
	* @param x: ��ġ x �����̴�.
	* @param y: ��ġ y �����̴�.
	* @return  0: 
	*/
	inline int classify(const float* x, float* y);

// Access	
	/*
	* �� �Լ��� ���� ó�� ���¸� �����Ѵ�.
	* @return  1: ���� ����
	*         -1: ���� ������
	*/
	inline int status() const;

	/*
	* �Է� dimension ���� �����Ѵ�.
	* @return  0�̿��� ��: svm�� dimension �Ǵ� ann�� dimension ���� �����Ѵ�.
	*          0: dimension ���� 0�̴�.
	*/
	inline unsigned int input_dimension() const;

protected:

private:
	/*
	* AIClassifier Ŭ������ ������ �Լ��̴�.
	* SVM�� ANN Ŭ������ �����ϴ� �����̴�.
	*/
	AIClassifier(const AIClassifier& classifier);

// Operators
	/*
	* ���۷����� = �Լ��̴�.
	*/
	const AIClassifier& operator=(const AIClassifier& classifier);

	/*
	* svm�� ann�� ó�� ���¸� ��Ÿ����.
	* �� 1: ���� ����, -1: ���� ������
	*/
	int m_status;

	/*
	* ANN �˰��� Ŭ�����̴�.
	* ���� �з���� ���ȴ�.
	*/
	ANNetwork* m_ann;
	
	/*
	* SVM �˰��� Ŭ�����̴�.
	* ���� �з���� ���ȴ�.
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

