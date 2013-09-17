//////////////////////////////////////////////////////
// Topological Map files for Robot applications
// 
// Copyright (c) 2002-2008. All Rights Reserved.
// Division of Applied Robot Technology KITECH
// Web: http://dart.kitech.re.kr
// Written by SooKyung Son<sukaa79@gmail.com>
//
#ifndef _THINNING_H_
#define _THINNING_H_

#include <deque>
#include <vector>

typedef unsigned char BYTE;

class CThinning
{
public:
	CThinning ();
	~CThinning();

	int MakeThinning (BYTE *OutImage, BYTE *InputImage, int width, int height);	

private:
	inline BYTE GetPixel (BYTE *image, int width, int height, int x, int y)	{ return *(image + width * y + x); }
	inline void SetPixel (BYTE *image, int width, int height, int x, int y, BYTE pixel)	{ *(image + width * y + x) = pixel; }
	int GetNeighborhoodPixel (BYTE *image, int width, int height, int x, int y, BYTE a[8]);

	bool FindELM (int count, BYTE a[8]);
	bool CompELMPattern (BYTE a[8], BYTE b[8]);
	bool FindPSV (BYTE *image, int width, int height, int x, int y);
	bool CompPSVPattern (BYTE *image, int width, int height, int x1, int y1, int x2, int y2, BYTE *pattern);
};

#endif