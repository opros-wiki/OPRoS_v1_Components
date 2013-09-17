#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dxf_parse.h"

#if defined(WIN32)
#pragma warning (disable:4996)
#else
#define INT_MIN     (-2147483647 - 1) /* minimum (signed) int value */
#define INT_MAX       2147483647    /* maximum (signed) int value */
#endif

#define BUFSIZE	2048

static int groupcode;
static char linbuf[BUFSIZE];
static char curobj[80];
static int curcolor;
// static double curthick;
static double xcoords[10];
static double ycoords[10];
static double zcoords[10];
static double floats[10];
static double angles[10];
static int ints[10];
static double max_x, max_y, max_z, min_x, min_y, min_z;

// read a group code and the next line from infile
int getline(FILE *infile)		
{
	fgets(linbuf, BUFSIZE, infile);	// get a line from .DXF
	if (feof(infile)) {
		return 1;
	}
	groupcode = atoi (linbuf);
	fgets(linbuf, BUFSIZE, infile);	// get a line from .DXF
	if (feof(infile)) {
		return 1;
	}
	return 0;
}

void writeobj(vector<DXF_ENTITY_ITEM> *items)	// dump out current object we should have all info on
{
	if (strstr(curobj, "LINE"))	{	
		// a VERY skinny triangle!
		DXF_ENTITY_ITEM e;
		e.type  = ET_LINE;
		e.x0 = xcoords[0], e.y0 = ycoords[0], e.z0 = zcoords[0];
		e.x1 = xcoords[1], e.y1 = ycoords[1], e.z1 = zcoords[1];
		items->push_back (e);

		//debug ("DXF LD: LINE <%g %g %g> <%g %g %g>", 
		//	xcoords[0], ycoords[0], zcoords[0], xcoords[1], ycoords[1], zcoords[1]);
		return;
	}
	else if (strstr(curobj, "POINT")) {
		// an itty, bitty sphere!
		//debug ("DXF LD: POINT <%g %g %g>",  
		//	xcoords[0], ycoords[0], zcoords[0]);
		return;
	}
	else if (strstr(curobj, "CIRCLE")) {
		// a VERY short cylinder!
		//debug ("DXF LD: CIRCLE <%g %g %g> <%g>", xcoords[0], ycoords[0], zcoords[0], floats[0]);
		return;
	}
	else if (strstr(curobj, "ARC"))	{
		// not implemented for now
		return;
	}
	else if (strstr(curobj, "TRACE")) {
		// 2 back-to-back triangles
		//debug ("DXF LD: TRACE <%g %g %g> <%g %g %g> <%g %g %g> <%g %g %g>", 
		//	xcoords[0], ycoords[0], zcoords[0], xcoords[1], ycoords[1], zcoords[1], xcoords[2], ycoords[2], zcoords[2], xcoords[3], ycoords[3], zcoords[3]);
		return;
	}
	else if (strstr(curobj, "SOLID")) {
		// 1 or 2 triangles
		//debug ("DXF LD: SOLID <%g %g %g> <%g %g %g> <%g %g %g> <%g %g %g>", 
		//	xcoords[0], ycoords[0], zcoords[0], xcoords[1], ycoords[1], zcoords[1], xcoords[2], ycoords[2], zcoords[2], xcoords[3], ycoords[3], zcoords[3]);
		return;
	}
	else if (strstr(curobj, "TEXT")) {	
		// not implemented for now
		return;
	}
	else if (strstr(curobj, "SHAPE")) {
		// these look very hard
		return;
	}
	else if (strstr(curobj, "BLOCK")) {
		// these look very hard
		return;
	}
	else if (strstr(curobj, "ENDBLK")) {
		// these look very hard
		return;
	}
	else if (strstr(curobj, "INSERT")) {
		// these look very hard
		return;
	}
	else if (strstr(curobj, "ATTDEF")) {
		// not implemented for now
		return;
	}
	else if (strstr(curobj, "ATTRIB")) {
		// not implemented for now
		return;
	}
	else if (strstr(curobj, "POLYLINE")) {
		// these look fairly hard
		return;
	}
	else if (strstr(curobj, "VERTEX")) {
		// these look fairly hard
		return;
	}
	else if (strstr(curobj, "SEQEND")) {
		// these look fairly hard
		return;
	}
	else if (strstr(curobj, "3DLINE")) {
		// a VERY skinny triangle!
		//debug ("DXF LD: 3DLINE <%g %g %g> <%g %g %g>", 
		//	xcoords[0], ycoords[0], zcoords[0], xcoords[1], ycoords[1], zcoords[1]);
		return;
	}
	else if (strstr(curobj, "3DFACE")) {
		// 1 or 2 triangles
		//debug ("DXF LD: 3DFACE <%g %g %g> <%g %g %g> <%g %g %g> <%g %g %g>", 
		//	xcoords[0], ycoords[0], zcoords[0], xcoords[1], ycoords[1], zcoords[1], xcoords[2], ycoords[2], zcoords[2], xcoords[3], ycoords[3], zcoords[3]);
		return;
	}
	else if (strstr(curobj, "DIMENSION")) {
		// not implemented for now
		return;
	}
	return;	// no current object defined...
}

int load_dxf(const char *file_name, vector<DXF_ENTITY_ITEM> *items)
{
	FILE *infile;

	if (!(infile = fopen(file_name, "r"))) {
		// debug ("DXF LD: Cannot open input file %s!", file_name);
		return -1;
	}
	
	curobj[0] = '\0';	// not working on any object currently
	curcolor = 7;		// and it also doesn't have a color yet...
	max_x = max_y = max_z = (double)INT_MIN;	// init bounding limits
	min_x = min_y = min_z = (double)INT_MAX;
	
find:	
	while (!feof(infile)) {
		// run file up to the "ENTITIES" section
		if (getline(infile)) {		
			// get a group code and a line
			goto stopit;
		}
		if (groupcode == 0) {
			// file section mark
			if (strstr(linbuf, "EOF")) {
				goto stopit;
			}
			if (strstr(linbuf, "SECTION")) {
				if (getline(infile)) {
					goto stopit;
				}
				if (groupcode != 2) {
					continue;
				}
				if (strstr(linbuf, "ENTITIES")) {
					break;
				}
			}
		}
	}
	while (!feof(infile)) {		
		// scan ENTITIES section
		if (getline(infile)) {
			// get a group code and a line
			break;
		}
		if (groupcode < 10) {	
			// cardinal group codes
			switch(groupcode) {
			case 0: // start of entity, table, file sep
				if (strstr(linbuf, "EOF")) {
					writeobj(items); // dump object
					goto stopit;
				}
				if (strstr(linbuf, "ENDSEC")) {
					writeobj(items); // dump object
					goto find;
				}
				writeobj(items);	// dump old object
				curobj[0] = '\0'; // reset object
				curcolor = 7;
				strcpy(curobj, linbuf);	// get new
				break;
			case 1:	// primary text value for entity (?)*/
				break;
			case 2: // block name, attribute tag, etc
			case 3:	// other names
			case 4:
				break;
			case 5:	// entity handle (hex string)
				break;
			case 6: // line type name
				break;
			case 7: // text style name
				break;
			case 8: // layer name
				break;
			case 9: // variable name ID (only in header)*/
				break;
			}
		}
		else if (groupcode >= 10 && groupcode < 19) {
			// Some X coord
			xcoords[groupcode-10] = atof(linbuf);
		}
		else if (groupcode >= 20 && groupcode < 29) {
			// Some Y coord
			ycoords[groupcode-20] = atof(linbuf);
		}
		else if (groupcode >= 30 && groupcode < 38) {
			// Some Z coord
			zcoords[groupcode-30] = atof(linbuf);
		}
		else if (groupcode == 38) {
			// entity elevation if nonzero
		}
		else if (groupcode == 39) {
			// entity thickness if nonzero
		}
		else if (groupcode >= 40 && groupcode < 49) {
			// misc floats
			floats[groupcode-40] = atof(linbuf);
		}
		else if (groupcode == 49) {
			// repeated value groups
		}
		else if (groupcode >= 50 && groupcode < 59) {
			// misc angles
			angles[groupcode-50] = atof(linbuf);
		}
		else if (groupcode == 62) {
			// Color number
			curcolor = atoi(linbuf);
		}
		else if (groupcode == 66) {
			// "entities follow" flag
		}
		else if (groupcode >= 70 && groupcode < 79) {
			// misc ints
			ints[groupcode-70] = atoi(linbuf);
		}
		else if (groupcode == 210 || groupcode == 220 || groupcode == 230) {	
			// X, Y, Z components of extrusion direction
		}
	}

stopit: 
	return 0;
}
