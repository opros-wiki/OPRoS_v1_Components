#pragma once
#include <math.h>
#include <windows.h>
#include <float.h>
#include <valarray>

#define M_PI		3.14159265358979323846	// pi 
#define M_E			2.7182818284590452354	// e 
#define M_LOG2E		1.4426950408889634074	// log_2 e 
#define M_LOG10E	0.43429448190325182765 	// log_10 e 
#define M_LN2		0.69314718055994530942 	// log_e 2 
#define M_LN10		2.30258509299404568402 	// log_e 10 
#define M_PI_2		1.57079632679489661923 	// pi/2 
#define M_PI_4		0.78539816339744830962 	// pi/4 
#define M_1_PI		0.31830988618379067154 	// 1/pi 
#define M_2_PI		0.63661977236758134308 	// 2/pi 
#define M_SQRTPI	1.77245385090551602729 	// sqrt(pi) [4.0.2] 
#define M_2_SQRTPI	1.12837916709551257390 	// 2/sqrt(pi) 
#define M_SQRT2		1.41421356237309504880 	// sqrt[2] 
#define M_SQRT3		1.73205080756887729352 	// sqrt[3] [4.0.2] 
#define M_SQRT1_2	0.70710678118654752440 	// 1/sqrt[2] 
#define M_LNPI		1.14472988584940017414 	// log_e(pi) [4.0.2] 
#define M_EULER		0.57721566490153286061 	// Euler constant [4.0.2] 

#define _RAD2DEG	(180./M_PI)
#define _DEG2RAD	(M_PI/180.)

static const unsigned long NaN_[2] = {0xFFFFFFFF, 0x7FFFFFFF};
const double NaN = *( double* )NaN_;

inline double RAD2DEG(double x)
{
	return x*_RAD2DEG;
}

inline double DEG2RAD(double x)
{
	return x*_DEG2RAD;
}

template<typename T>
inline T min_val(T v1, T v2)
{
	return (v1 < v2) ? v1 : v2;
}

template<typename T>
inline T max_val(T v1, T v2)
{
	return (v1 > v2) ? v1 : v2;
}

template<typename T>
inline T bound(T x, T l, T u)
{
	if (x <= l) return l;
	if (x >= u) return u;
	return x;
}

template<typename T>
inline void Swap(T &v1, T &v2)
{
	T temp = v1;
	v1 = v2;
	v2 = temp;
}

inline void Rotate (double result[3], const double src[3], double rad)
{
	double cos_r = cos (rad);
	double sin_r = sin (rad);
	double x, y;
	
	x = src[0] * cos_r - src[1] * sin_r;
	y = src[0] * sin_r + src[1] * cos_r;
	result[0] = x;
	result[1] = y;
}

inline double GaussRand()
{
    static double u, v;
    static int phase = 0;
    double z;
	
    if (phase == 0) {
		u = (rand() + 1.) / (RAND_MAX + 2.);
		v = rand() / (RAND_MAX + 1.);
		z = sqrt(-2 * log(u)) * sin(2 * M_PI * v);
    }
    else {
		z = sqrt(-2 * log(u)) * cos(2 * M_PI * v);
	}
    phase = 1 - phase;
    return z;
}

inline int INTEGER (const double a)
{
	// return (long)floor (a + 0.5);
	return (0 < a)? (int)(a + 0.5) : (int)(a - 0.5);
}

inline double Sign (const double v)
{
	return (0 < v) ? +1. : -1.;
}

inline int DeltaDeg (int ang1, int ang2)
{
	int da = ang1 - ang2;
	if (-180 < da && da < 180) return da;
	else {
		da %= 360;
		if (180 <= da) return da - 360;
		else if (da <= -180) return da + 360;
		else return da;
	}
}

inline double DeltaDeg (double ang1, double ang2)
{
	double da = ang1 - ang2;
	if (-180 < da && da < 180) return da;
	else {
		da = fmod (da, 360);
		if (180 <= da) return da - 360;
		else if (da <= -180) return da + 360;
		else return da;
	}
	return da;
}

inline double DeltaRad (double ang1, double ang2)
{
	double da = ang1 - ang2;
	if (-M_PI < da && da < M_PI) return da;
	else {
		da = fmod (da, 2*M_PI);
		if (M_PI <= da) return da - 2*M_PI;
		else if (da <= -M_PI) return da + 2*M_PI;
		else return da;
	}
	return da;
}

inline double Length (double x, double y)
{
	return sqrt (x*x + y*y);
}

inline double Distance (double x1, double y1, double x2, double y2)
{
	double dx = x2 - x1;
	double dy = y2 - y1;

	return sqrt (dx*dx + dy*dy);
}

inline int Distance (int x1, int y1, int x2, int y2)
{
	double dx = x2 - x1;
	double dy = y2 - y1;

	return INTEGER(sqrt (dx*dx + dy*dy));
}

inline bool IsNum (double num)
{
	return !_isnan(num);
}

inline int CountNum (std::valarray<double> &v) 
{
	int count = 0;	
	for (int i=0, n=v.size (); i<n; ++i) {
		if (IsNum(v[i])) ++count;	
	}
	return count;
}

inline std::valarray<double> FilterNaN (std::valarray<double> &v) 
{
	for (int i=0, n=v.size (); i<n; ++i) {
		if (!IsNum(v[i])) v[i] = 0.;
	}
	return v;
}