// AI classifier class
// ANN�� SVM�� �̿��Ͽ� classifier�� ���Ѵ�.


#include "aiclassifier.h"


AIClassifier::AIClassifier(const wchar_t* fname) : m_status(-1), m_ann(0), m_svm(0)
{
	m_svm = new SVMachine(fname);
	m_status = m_svm->status();
	if (m_status == 0) return;

	m_ann = new ANNetwork(fname);
	m_status = m_ann->status();
	if (m_status == 0) return;
}

AIClassifier::~AIClassifier()
{
	if (m_ann != 0) delete m_ann;
	if (m_svm != 0) delete m_svm;
}