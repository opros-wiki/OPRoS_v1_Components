//////////////////////////////////////////////////////
// Vector and Matrix files for Robotics applications
// 
// Copyright (c) 2002-2010. All Rights Reserved.
// Division of Applied Robot Technology, KITECH
// Web: http://www.orobot.net
// Written by KwangWoong Yang<page365@gmail.com>
//
// Collection of Mathematical functions

#pragma	once

#define _NO_EXCEPTION
#include <assert.h>

#include "matrix.h"

class dMatrix : public math::matrix<double> 
{
public:
	dMatrix (matrix<double> &m): matrix (m) { }
	dMatrix (size_t row = 1, size_t col = 1): matrix (row, col) { }

	size_t rowno () const { return RowNo(); }
	size_t colno () const { return ColNo(); }
	size_t size()   const { return RowNo()*ColNo(); }

	void unit () { Unit (); }
};

class dVector : public math::matrix<double> 
{
public:
	dVector (matrix<double> &m): matrix (m) { }
	dVector (size_t size = 3): matrix (size, 1) { }

	size_t size()   const { return RowNo()*ColNo(); }

	double operator[] (size_t i)  const 
	{
		assert (ColNo() == 1);

		return (*this)(i,0);
	}

	double& operator[] (size_t i)
	{
		assert (ColNo() == 1);

		return (*this)(i,0);
	}
};


// dVector의 내적(dot product)을 계산한다.
inline double Dot (const dVector &v1, const dVector &v2)
{
	if(v1.size() != 3 || v2.size() != 3) 
		assert (0 && "ERROR: Dot(): Inconsistent vector size in Inner Product !");

	double	v = 0.;
	for(unsigned int i=0; i<3; ++i)
		v += v1[i] * v2[i];

	return v;
}

// dVector의 외적(cross product)을 계산한다.
inline dVector Cross (const dVector &v1, const dVector &v2)
{
	if(v1.size() != 3 || v2.size() != 3) 
		assert (0 && "ERROR: Cross(): dVector dimension should be 3 in Cross Product !");

	dVector v(3);
	v[0] = v1[1]*v2[2] - v1[2]*v2[1];
	v[1] = v1[2]*v2[0] - v1[0]*v2[2];
	v[2] = v1[0]*v2[1] - v1[1]*v2[0];

	return v;
}

// Vector의 크기를 2-norm으로 계산한다
inline double Norm2 (const dVector &v)
{
	double s = 0.;
	for (int i=0; i<(int)v.size(); ++i) {
		s += v[i]*v[i];
	}
	return sqrt(s);
}

