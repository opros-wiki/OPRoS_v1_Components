#if defined(WIN32)
#pragma warning (disable:4996)
#endif

#include <stdio.h>
#include "OprosMath.h"
#include "bmp256.h"
#include "LineBasedGlobalMap.h"


LineBasedGlobalMap::LineBasedGlobalMap(int width, int height, double cellWidth) :
	_cellWidth(cellWidth), GridMap<unsigned char> (0, 0, width, height)
{
	InitPalette ();
}

LineBasedGlobalMap::LineBasedGlobalMap(const char *fileName, double cellWidth)
{
	LoadDxfMap (fileName, cellWidth);
	InitPalette ();
}

LineBasedGlobalMap::~LineBasedGlobalMap ()
{

}

void LineBasedGlobalMap::InitPalette()
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

bool LineBasedGlobalMap::LoadDxfMap (const char *fileName, double cellWidth)
{
	_cellWidth = cellWidth;

	vector<DXF_ENTITY_ITEM>::iterator ii;
	vector<DXF_ENTITY_ITEM> items;
	
	if (load_dxf(fileName, &items) < 0) {
		printf ("ERROR: DXF Map loading failed: %s %g\n", fileName, _cellWidth);
		return false;
	}

	double min_x = 1e10;
	double min_y = 1e10;
	double max_x = -1e10;
	double max_y = -1e10;
	for (ii=items.begin (); ii != items.end (); ++ii) {
		min_x = min (min_x, ii->x0);
		min_x = min (min_x, ii->x1);
		min_y = min (min_y, ii->y0);
		min_y = min (min_y, ii->y1);

		max_x = max (max_x, ii->x0);
		max_x = max (max_x, ii->x1);
		max_y = max (max_y, ii->y0);
		max_y = max (max_y, ii->y1);
	}
	
	min_x = min_x/1000. - _cellWidth*5;
	min_y = min_y/1000. - _cellWidth*5;
	max_x = max_x/1000. + _cellWidth*5;
	max_y = max_y/1000. + _cellWidth*5;
	//min_x = min_x/1000.;
	//min_y = min_y/1000.;
	//max_x = max_x/1000.;
	//max_y = max_y/1000.;

	printf ("Load dxf map: '%s' %d items, boundary (%g, %g ~ %g, %g)\n", fileName, items.size (), min_x, min_y, max_x, max_y);
	//RobotSaysF ("%s 맵을 읽었습니다.", file_name);

	line_items.clear ();
	Reallocate (INTEGER(min_x/_cellWidth), INTEGER(min_y/_cellWidth), INTEGER((max_x-min_x)/_cellWidth), INTEGER((max_y-min_y)/_cellWidth));
	Clear (0);

	line_items.reserve (items.size ());

	for (ii=items.begin (); ii != items.end (); ++ii) {
		MM_RECT l(ii->x0/1000., ii->y0/1000., ii->x1/1000., ii->y1/1000.);

		DrawLine (l.x1, l.y1, l.x2, l.y2, 20);
		line_items.push_back (l);
		// debug ("LINE: %g %g - %g %g", ii->x0/1000., ii->y0/1000., ii->x1/1000., ii->y1/1000.);
	}

	//printf ("Grid map generation: offset (%d, %d), size (%d, %d)",
	//	offset_x,	offset_y, width, height);

	return true;
}
