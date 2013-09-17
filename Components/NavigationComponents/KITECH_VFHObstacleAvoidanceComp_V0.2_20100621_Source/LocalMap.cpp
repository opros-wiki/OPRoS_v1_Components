#include "OprosMath.h"
#include "LocalMap.h"
#include <string.h>

void CLocalMap::DrawLine (int x1, int y1, int x2, int y2, short mask)
{
	int deltax = abs(x2 - x1);        // The difference between the x's
	int deltay = abs(y2 - y1);        // The difference between the y's
	int x = x1;                       // Start x off at the first pixel
	int y = y1;                       // Start y off at the first pixel
	int xinc1, xinc2;
	int yinc1, yinc2;
	int den, num, numadd;
	int numpixels, curpixel;
	
	if (x2 >= x1)	xinc1 = 1,	xinc2 = 1;
	else			xinc1 = -1, xinc2 = -1;
	if (y2 >= y1) 	yinc1 = 1,	yinc2 = 1;
	else			yinc1 = -1,	yinc2 = -1;
	
	if (deltax >= deltay) {        // There is at least one x-value for every y-value
		xinc1 = 0;                  // Don't change the x when numerator >= denominator
		yinc2 = 0;                  // Don't change the y for every iteration
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;         // There are more x-values than y-values
	}
	else {                         // There is at least one y-value for every x-value
		xinc2 = 0;                  // Don't change the x for every iteration
		yinc1 = 0;                  // Don't change the y when numerator >= denominator
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;         // There are more y-values than x-values
	}
	mask = ~mask;
	
	for (curpixel = 0; curpixel <= numpixels; ++curpixel) {
		if (IsIn (x, y))	_cell[y][x] &= mask;
		else				break;

		num += numadd;              // Increase the numerator by the top of the fraction
		if (num >= den) {            // Check if numerator >= denominator
			num -= den;               // Calculate the new numerator value
			x += xinc1;               // Change the x as appropriate
			y += yinc1;               // Change the y as appropriate
		}
		x += xinc2;                 // Change the x as appropriate
		y += yinc2;                 // Change the y as appropriate
	}
}

void CLocalMap::Shift (int dx, int dy)
{
	int i;

	if (dx == 0 && dy == 0) { }
	else if (0 <= dy && dy < LOCALMAP_SIZE) {
		if (0 <= dx && dx < LOCALMAP_SIZE) {
			for (i=LOCALMAP_SIZE-1; dy<=i; i--) {
				memmove (&_cell[i][dx], &_cell[i-dy][0], (LOCALMAP_SIZE-dx)*sizeof(short));
				memset (&_cell[i][0], 0, dx*sizeof(short));
			}
			for (; 0<=i; i--) {
				memset (&_cell[i][0], 0, LOCALMAP_SIZE*sizeof(short));
			}
		}
		else if (-LOCALMAP_SIZE < dx && dx < 0) {
			dx = -dx;
			for (i=LOCALMAP_SIZE-1; dy<=i; i--) {
				memmove (&_cell[i][0], &_cell[i-dy][dx], (LOCALMAP_SIZE-dx)*sizeof(short));
				memset (&_cell[i][LOCALMAP_SIZE-dx], 0, dx*sizeof(short));
			}
			for (; 0<=i; i--) {
				memset (&_cell[i][0], 0, LOCALMAP_SIZE*sizeof(short));
			}
		}
	}
	else if (-LOCALMAP_SIZE < dy && dy < 0) {
		dy = -dy;
		if (0 <= dx && dx < LOCALMAP_SIZE) {
			for (i=0; i<LOCALMAP_SIZE-dy; ++i) {
				memmove (&_cell[i][dx], &_cell[i+dy][0], (LOCALMAP_SIZE-dx)*sizeof(short));
				memset (&_cell[i][0], 0, dx*sizeof(short));
			}
			for (; i<LOCALMAP_SIZE; ++i) {
				memset (&_cell[i][0], 0, LOCALMAP_SIZE*sizeof(short));
			}
		}
		else if (-LOCALMAP_SIZE < dx && dx < 0) {
			dx = -dx;
			for (i=0; i<LOCALMAP_SIZE-dy; ++i) {
				memmove (&_cell[i][0], &_cell[i+dy][dx], (LOCALMAP_SIZE-dx)*sizeof(short));
				memset (&_cell[i][LOCALMAP_SIZE-dx], 0, dx*sizeof(short));
			}
			for (; i<LOCALMAP_SIZE; ++i) {
				memset (&_cell[i][0], 0, LOCALMAP_SIZE*sizeof(short));
			}
		}
	}
}

void CLocalMap::Clear ()
{
	memset (_cell, 0, sizeof (_cell));
}

void CLocalMap::Predict (const ObjectLocation &estimatedPosition)
{
	_pos = estimatedPosition;

	int dx = INTEGER(CU(_pos.x) - _posPrev.x);
	int dy = INTEGER(CU(_pos.y) - _posPrev.y);

	_posPrev.x = CU(_pos.x);
	_posPrev.y = CU(_pos.y);

	Shift (-dx, -dy);
}

class line {
public:
	line () {};
	bool t;
	int sx, sy, ex, ey;
};

void CLocalMap::Update (double measuredValue[])
{
	double resolution = (_endAngle - _startAngle) / (double)(_sensorCount-1);

	int i;
	vector<line> obstacles;
	obstacles.reserve (_sensorCount);

	for (i = 0; i < _sensorCount; ++i) {
		double &v = measuredValue[i];
		if (_rangeMin < v) {
			ObjectLocation sensor (_sensorPosition);
			sensor.Rotate (_pos.theta);

			ObjectLocation obstacle (v, _pos.theta + _sensorPosition.theta + _startAngle + i*resolution);
			obstacle += sensor;
			
			line obs;
			obs.sx = INTEGER(M2CUx (sensor.x));
			obs.sy = INTEGER(M2CUy (sensor.y));
			obs.ex = INTEGER(M2CUx (obstacle.x));
			obs.ey = INTEGER(M2CUy (obstacle.y));
			obs.t = (v < _rangeMax);

			obstacles.push_back (obs);
		}
	}
	for (i = 0; i < (int)obstacles.size (); ++i) {
		DrawLine (obstacles[i].sx, obstacles[i].sy, obstacles[i].ex, obstacles[i].ey, 1);
	}
	for (i = 0; i < (int)obstacles.size (); ++i) {
		if (obstacles[i].t) SetPixel (obstacles[i].ex, obstacles[i].ey, 1);
	}
}

