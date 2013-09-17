#if defined(WIN32)
#pragma warning (Disable:4996)
#endif

#include <stdio.h>
#include "OprosMath.h"
#include "bmp256.h"
#include "GridBasedGlobalMap.h"

GridBasedGlobalMap::GridBasedGlobalMap(int width, int height, double cellWidth)
: _cellWidth(cellWidth), GridMap<unsigned char> (0, 0, width, height)
{
	InitPalette ();
}

GridBasedGlobalMap::GridBasedGlobalMap(const char *fileName, double cellWidth)
{
	LoadGridMap (fileName, cellWidth);
	InitPalette ();
}

GridBasedGlobalMap::~GridBasedGlobalMap ()
{

}

void GridBasedGlobalMap::InitPalette()
{
	for (int i=0; i<256; ++i) {
		unsigned char c = (unsigned char)(unsigned int)(255 - i);
		_palette[i][0] = c;
		_palette[i][1] = c;
		_palette[i][2] = c;
		_palette[i][3] = 0;
	}
	_palette[1][0] = 240;	// B
	_palette[1][1] = 240;	// G
	_palette[1][2] = 255;	// R
	_palette[1][3] = 0;

	_palette[2][0] = 0;		// B
	_palette[2][1] = 90;	// G
	_palette[2][2] = 0;		// R
	_palette[2][3] = 0;

	_palette[3][0] = 0;		// B
	_palette[3][1] = 210;	// G
	_palette[3][2] = 205;	// R
	_palette[3][3] = 0;

	_palette[4][0] = 90;	//B
	_palette[4][1] = 0;		//G
	_palette[4][2] = 0;		//R
	_palette[4][3] = 0;
}

bool GridBasedGlobalMap::LoadGridMap(const char *fileName, double cellWidth)
{
	_cellWidth = cellWidth;

	int bmpWidth, bmpHeight;
	unsigned char *image_bmp256 = ReadBmp256 (fileName, bmpWidth, bmpHeight, _palette);
	if (!image_bmp256) {
		printf ("ERROR: Bitmap Map loading failed: %s %g\n", fileName, cellWidth);
		return false;
	} 
	Reallocate (0, 0, bmpWidth, bmpHeight);
	Clear (0);


//그림판 색상표에 따른 픽셀값(256컬러로 설정했을 때)
//      1   2   3   4   5   6   7   8   9  10  11  12  13  14
//-----------------------------------------------------------
//1 |   0 164   1   3   2   6   4   5 100  80 224 144 196  20
//2 | 255   7 249 251 250 254 252 253 191 184   9 228 135 103


	for (int y=_height-1; 0<=y; y--) {
		unsigned char *p = image_bmp256 + bmpWidth * (_height-1-y);
		for (int x=0; x<_width; ++x) {
			if (*p == 0x00) {			//black
				SetPixelCELL(x, y, 20);
			}
			else if (*p == 0x01) {		//dark red
				SetPixelCELL(x, y, 1);
			}
			else if (*p == 0x02) {		// green
				SetPixelCELL(x, y, 2);
			}
			else if (*p == 0x04) {
				SetPixelCELL(x, y, 4);
			}
			else if (*p == 0x03) {		// 차선
				SetPixelCELL(x, y, 3);
			}
			else {
				SetPixelCELL(x, y, 0);
			}
			++p;
		}
	}
	FreeImage (image_bmp256);
	return true;
}
