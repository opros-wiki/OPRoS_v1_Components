//////////////////////////////////////////////////////
// Topological Map files for Robot applications
// 
// Copyright (c) 2002-2008. All Rights Reserved.
// Division of Applied Robot Technology KITECH
// Web: http://dart.kitech.re.kr
// Written by SooKyung Son<sukaa79@gmail.com>
//

#if defined(WIN32)
#pragma warning (disable:4996)
#endif

#include <string.h>
#include "Thinning.h"
#include "ThinningMaskTable.h"

CThinning::CThinning ()
{
}

CThinning::~CThinning()
{
}

int CThinning::MakeThinning (BYTE *OutImage, BYTE *InputImage, int width, int height)
{
	int cont;
	int y, x;

	BYTE *img_buf1 = new BYTE [width*height];
	BYTE *img_buf2 = new BYTE [width*height];

	memcpy (img_buf1, InputImage, width*height);
	memset (img_buf2, 0, width*height);

	while (1){
		cont = 0;
		for (y = 1; y < (height - 1); y++) {
			for (x = 1; x < (width - 1); x++) {
				if (GetPixel (img_buf1, width, height, x, y)) {
				    BYTE a[8];
					int ar = GetNeighborhoodPixel(img_buf1, width, height, x, y, a);
					if (FindELM (ar, a) && !FindPSV (img_buf1, width, height, x, y)){
						SetPixel(img_buf2, width, height, x, y, 255);
						cont++;
					}
					else{
						SetPixel(img_buf2, width, height, x, y, 0);
					}
				}
				else {
					SetPixel(img_buf2, width, height, x, y, 0);
				}
			}
		}

		// extra pixel의 제거
		if (cont > 0){
			for (y = 1; y < height-1; y++) {
				for (x = 1; x < width-1; x++) {
					if (GetPixel (img_buf1, width, height, x, y) && GetPixel (img_buf2, width, height, x, y)) {
						SetPixel (img_buf1, width, height, x, y, 0);
					}
				}
			}
		}
		else{
			break;
		}
	}

	memcpy (OutImage, img_buf1, width*height);

	delete [] img_buf1;
	delete [] img_buf2;
	return 0;
}

int CThinning::GetNeighborhoodPixel (BYTE *image, int width, int height, int x, int y, BYTE a[8])
{
	int i;
	int count = 0;

	a[0] = GetPixel(image, width, height, x, y-1);
	a[1] = GetPixel(image, width, height, x+1, y-1);
	a[2] = GetPixel(image, width, height, x+1, y);
	a[3] = GetPixel(image, width, height, x+1, y+1);
	a[4] = GetPixel(image, width, height, x, y+1);
	a[5] = GetPixel(image, width, height, x-1, y+1);
	a[6] = GetPixel(image, width, height, x-1, y);
	a[7] = GetPixel(image, width, height, x-1, y-1);

	for (i = 0; i < 8; i++){
		if (a[i]){
			count++;
		}
	}

	return count;
}

bool CThinning::FindELM (int count, BYTE a[8])
{
	int i;
	bool ret = false;

	switch(count)
	{
		case 2:
			for (i = 0; i < ELM_PATTERN2_SIZE; i++){
				if (CompELMPattern(a, (BYTE *)_elmPattern2[i])){ ret = true; break; }
			}
			break;
		case 3:
			for (i = 0; i < ELM_PATTERN3_SIZE; i++){
				if (CompELMPattern(a, (BYTE *)_elmPattern3[i])){ ret = true; break; }
			}
			break;
		case 4:
			for (i = 0; i < ELM_PATTERN4_SIZE; i++){
				if (CompELMPattern(a, (BYTE *)_elmPattern4[i])){ ret = true; break; }
			}
			break;
		case 5:
			for (i = 0; i < ELM_PATTERN5_SIZE; i++){
				if (CompELMPattern(a, (BYTE *)_elmPattern5[i])){ ret = true; break; }
			}
			break;
		case 6:
			for (i = 0; i < ELM_PATTERN6_SIZE; i++){
				if (CompELMPattern(a, (BYTE *)_elmPattern6[i])){ ret = true; break; }
			}
			break;
		case 7:
			for (i = 0; i < ELM_PATTERN7_SIZE; i++){
				if (CompELMPattern(a, (BYTE *)_elmPattern7[i])){ ret = true; break; }
			}
			break;
		default:
			break;
	}

	return ret;
}

bool CThinning::CompELMPattern (BYTE a[8], BYTE b[8])
{
	int i;
	bool equality = true;

	for (i = 0; i < 8; i++){
		if(!(((a[i] > 0) == (b[i] > 0)) || ((a[i] == 0) == (b[i] == 0)))){
			equality = false;
			break;
		}
	}
	
	return equality;
}

bool CThinning::FindPSV (BYTE *image, int width, int height, int x, int y)
{
	if (((x-1) >= 0 && (y-1) >= 0) && (((x+1) < width) && ((y+2) < height))){		// PSV Pattern 1,3 인 경우
		if (CompPSVPattern(image, width, height, x-1, y-1, x+1, y+2, (BYTE *)_psvPattern1)) {
			return true;
		}
		if(CompPSVPattern(image, width, height, x-1, y-1, x+1, y+2, (BYTE *)_psvPattern3)) {
			return true;
		}
	}
	if (((x-1) >= 0 && (y-2) >= 0) && (((x+1) < width) && ((y+1) < height))){	// PSV Pattern 2 인 경우
		if (CompPSVPattern(image, width, height, x-1, y-2, x+1, y+1, (BYTE *)_psvPattern2)){
			return true;	
		}
	}
	if (((x-1) >= 0 && (y-1) >= 0) && (((x+2) < width) && ((y+1) < height))){	// PSV Pattern 4,5 인 경우
		if (CompPSVPattern(image, width, height, x-1, y-1, x+2, y+1, (BYTE *)_psvPattern4)){
			return true;
		}
		if (CompPSVPattern(image, width, height, x-1, y-1, x+2, y+1, (BYTE *)_psvPattern5)) {
			return true;
		}
	}
	if (((x-2) >= 0 && (y-1) >= 0) && (((x+1) < width) && ((y+1) < height))){	// PSV Pattern 6 인 경우
		if (CompPSVPattern(image, width, height, x-2, y-1, x+1, y+1, (BYTE *)_psvPattern6)){
			return true;
		}
	}
	if (((x-1) >= 0 && (y-1) >= 0) && (((x+2) < width) && ((y+2) < height))){	// PSV Pattern 7 인 경우
		if (CompPSVPattern(image, width, height, x-1, y-1, x+2, y+2, (BYTE *)_psvPattern7)){
			return true;
		}
	}

	return false;
}

bool CThinning::CompPSVPattern (BYTE *image, int width, int height, int x1, int y1, int x2, int y2, BYTE *pattern)
{
	int x, y;
	int index = 0;
	bool equality = true;

	for (y = y1; y <= y2; y++){
		for (x = x1; x <= x2; x++){
			BYTE p = *(pattern + index);
			BYTE i = GetPixel (image, width, height, x, y);
			if (!(((p == 0) && (i == 0)) || ((p == 1) && (i > 0)) || (p == 3))){
				equality = false;
				break;
			}
			index++;
		}
		if (equality == false){
			break;
		}
	}
	
	return equality;
}
