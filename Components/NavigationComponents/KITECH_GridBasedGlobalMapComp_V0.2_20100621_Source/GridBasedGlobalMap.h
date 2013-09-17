#pragma once
#if defined(WIN32)
#include <windows.h>
#endif
#include <vector>
#include <string.h>
#include "OprosMath.h"
#include "GridMap.h"

using namespace std;


class GridBasedGlobalMap : public GridMap<unsigned char>
{
private:
	unsigned char _palette[256][4];

	void InitPalette();

public:
	double _cellWidth;

	inline int M2CUx(double x_)	{ return INTEGER(x_ / _cellWidth - _offsetX); }
	inline int M2CUy(double y_)	{ return INTEGER(y_ / _cellWidth - _offsetY); }
	inline double CU2Mx(int x_)	{ return (x_ + _offsetX) * _cellWidth; }
	inline double CU2My(int y_)	{ return (y_ + _offsetY) * _cellWidth; }

	inline bool IsIn (double x_, double y_)
	{
		int x = M2CUx(x_);
		int y = M2CUy(y_);
		return IsInCELL (x, y);
	}

	inline void SetPixel (double x_, double y_, unsigned char c)
	{
		int x = M2CUx(x_);
		int y = M2CUy(y_);
		assert (_cp && 0 <= x && x < _width && 0 <= y && y < _height);
		SetPixelCELL (x, y, c);
	}

	inline unsigned char GetPixel (double x_, double y_)
	{
		int x = M2CUx(x_);
		int y = M2CUy(y_);
		assert (_cp && 0 <= x && x < _width && 0 <= y && y < _height);
		return GetPixelCELL (x, y);
	}

	void DrawLine (double x1_, double y1_, double x2_, double y2_, unsigned char c)
	{
		int x1 = M2CUx(x1_);
		int y1 = M2CUy(y1_);
		int x2 = M2CUx(x2_);
		int y2 = M2CUy(y2_);
		DrawLineCELL (x1, y1, x2, y2, c);
	}

	bool IsIntersect (double x1_, double y1_, double &x2_, double &y2_, unsigned char cm)
	{
		int x1 = M2CUx(x1_);
		int y1 = M2CUy(y1_);
		int x2 = M2CUx(x2_);
		int y2 = M2CUy(y2_);
		if (IsIntersectCELL (x1, y1, x2, y2, cm)) {
			x2_ = CU2Mx(x2);
			y2_ = CU2My(y2);
			return true;
		}
		return false;
	}

public:
	GridBasedGlobalMap(int width, int height, double _cellWidth);
	GridBasedGlobalMap(const char *fileName, double _cellWidth);
	~GridBasedGlobalMap ();

	bool LoadGridMap(const char *fileName, double _cellWidth);
};
 
