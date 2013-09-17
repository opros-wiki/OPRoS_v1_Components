#ifndef __DXF_PARSE_H_
#define __DXF_PARSE_H_

#include <vector>

#include "OprosMath.h"

using namespace std;

enum eEntityType {
	ET_NONE = 0,
	ET_LINE,
	ET_POINT,
	ET_CIRCLE,
	ET_RECT,
};

typedef struct _DXF_ENTITY_ITEM_ {
	eEntityType type;
	double x0, y0, z0;
	double x1, y1, z1;
} DXF_ENTITY_ITEM;


struct MM_RECT {
	double x1, y1;
	double x2, y2;
	
	MM_RECT () 
	{}
	MM_RECT (double _x1, double _y1, double _x2, double _y2) 
	{ x1 = _x1; y1 = _y1; x2 = _x2; y2 = _y2; }
};

extern int load_dxf(const char *file_name, vector<DXF_ENTITY_ITEM> *items);


#endif

