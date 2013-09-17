#ifndef _LOCAL_MAP_H_
#define _LOCAL_MAP_H_
#include <vector>
#include <ApiTypes.h>

using namespace std;

#define LOCALMAP_CELL_SIZE	0.025
#define LOCALMAP_SIZE		201

class CLocalMap {
private:
	ObjectLocation _posPrev;

	double _startAngle;
	double _endAngle;
	int _sensorCount;
	double _rangeMin;
	double _rangeMax;
	ObjectLocation _sensorPosition;

public:
	ObjectLocation _pos;
	short _cell[LOCALMAP_SIZE][LOCALMAP_SIZE];

	inline double CU (double p)	{ return (p + LOCALMAP_CELL_SIZE/2)/LOCALMAP_CELL_SIZE; }
	// 
	inline int M2CUx (double x)	{ return (int)(LOCALMAP_SIZE/2 + x/LOCALMAP_CELL_SIZE); }
	inline int M2CUy (double y)	{ return (int)(LOCALMAP_SIZE/2 + y/LOCALMAP_CELL_SIZE); }
	inline double CU2Mx (int x)	{ return (x - LOCALMAP_SIZE/2)*LOCALMAP_CELL_SIZE; }
	inline double CU2My (int y)	{ return (y - LOCALMAP_SIZE/2)*LOCALMAP_CELL_SIZE; }

public:
	CLocalMap (double laserStartAngle, double laserEndAngle, int laserSensorCount, double laserRangeMin, double laserRangeMax, ObjectLocation laserSensorPosition) :
		_startAngle (laserStartAngle), _endAngle (laserEndAngle), _sensorCount (laserSensorCount), _rangeMin (laserRangeMin), _rangeMax (laserRangeMax), _sensorPosition (laserSensorPosition),
		_pos (0, 0, 0), _posPrev (0, 0, 0) { Clear (); }
	~CLocalMap () { }

	inline bool IsIn (int x, int y) { return (0 <= x && x < LOCALMAP_SIZE) && (0 <= y && y < LOCALMAP_SIZE); }
	inline void SetPixel (int x, int y, short mask) { if (IsIn(x, y)) _cell[y][x] |= mask; }
	void DrawLine (int x1, int y1, int x2, int y2, short mask);
	void Shift (int dx, int dy);
	void Clear ();

	void Predict (const ObjectLocation &position);
	void Update (double value[]);
};
#endif