
#ifndef SVMachine_H
#define SVMachine_H

#include <vector>
#include "vec2d.h"

#define TYPESIZE 256

using namespace std;

/*
* 기본적인 분류를 위한 SVM 은 입력공간에 maximum-margin hyperplane을 만든다. 
* yes 또는 no 값이 주어진 training sample 이 주어지고, 가장 가까이 있는 
* example (margin) 에서 hyperplane 까지의 거리가 최대가 되도록 training sample 들을 
* yes 와 no 로 나누게 되며, 그것이 maximum-margin hyperplane 이다.
*/
class SVMachine
{
public:
	/*
	* SVMachine 클래스의 생성자 함수이다.
	* training된 데이터 파일을 읽어 들인다.
	* @param fname: training 데이터 명
	*/
	SVMachine(const wchar_t* fname);
	/*
	* SVMachine 클래스의 소멸자 함수이다.
	* 생성된 벡터 파라미터들을 소멸한다.
	*/
	~SVMachine();

	enum SVMTYPE { LINEAR, RBF, POLY };

// Operations
	int classify(const float* x, double& y) const;
	int classify(const vec2D& x, double& y) const;  //row vector (MMX wise)
	
// Access
	inline unsigned int dimension() const;		 //support vector dimensionality
	
// Inquiry
	inline int status() const;			     //0-OK, -1,-2,-3,... errs

protected:	       
private:
	SVMachine(const SVMachine& svm);
	const SVMachine& operator=(const SVMachine& svm);

	int m_status;		   //1-OK, -1 file err

	unsigned int m_dimension;       //sv dimensionality
	unsigned int m_svsNum;	  //sv's number
	enum SVMTYPE m_svmType;	 //lin,rbf,poly

	double m_svmParam;	      //ploynomial - d,  (x*sv + 1) .^ d
					//rbf - gamma,  exp(-gamma * norm(s-sv))

	vector<double> m_weights;     //col vector w = alpha * y
	vector<vec2D*> m_svs;	 //support vectors, row vectors

	double m_bias;		//bias

	vec2D* m_scalar;	  //temp scalar vector 1x1
	vec2D* m_xInput;	  //temp x input vector 1xdim
	vec2D* m_rbfSub;	  //rbf sub operation

	inline int sign(double x) const;

};


/*
   SVMachine svm(L"file.svm");
    y = svm.classify(x);    //1 or -1



   file format
    dimesion
    sv's num
    type (linear,rbf,...)

    bias

    w1
    sv1      //col vector

    w2
    sv2      //col vector

    ...



    f(x) = sign( sum(w(i)*kern(x,sv(i)) ) + bias )
*/


inline int SVMachine::status() const
{
	return m_status;
}

inline unsigned int SVMachine::dimension() const
{
	return m_dimension;
}

inline int SVMachine::sign(double x) const
{
	return (x >= 0.0) ? 1 : -1;
}


#endif