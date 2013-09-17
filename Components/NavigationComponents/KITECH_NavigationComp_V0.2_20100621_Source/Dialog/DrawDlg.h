#pragma once

#include <vector>
#include <deque>
#include "ApiTypes.h"
//#include "../Navigation/ParticleFilter.h"
//#include "../Navigation/VFH.h"

using namespace std;

class CDrawDlg
{
protected:
	virtual int M2Px(double _x) { return (int)(_x); }
	virtual int M2Py(double _y) { return (int)(_y); }
	virtual int M2Pl(double _d) { return (int)(_d); }

public:
	void DrawBackground		(CDC *pDC, double dx, double dy, double d);
	void DrawRobot			(CDC *pDC, ObjectLocation &robot_pos, COLORREF crColor = RGB(127,127,127));
	void DrawBmp256			(HDC hDC, int _offsetX, int _offsetY, int imageWidth, int imageHeight, float imageScale, unsigned char *image, unsigned char palette[256][4]);
	void DrawSensorRange	(CDC *pDC, ObjectLocation &robot_pos, double startAngle, double endAngle, double sensorCount, ObjectLocation sensorPosition, vector<double> value, COLORREF crColor = RGB(255,0,0), int point_size = 2, bool line = false);
	//void DrawLoadCell		(CDC *pDC, CLoc2d &robot_pos, double com_x, double com_y, COLORREF crColor = RGB(255,0,0), int point_size = 3);

	//void DrawLocPoint		(CDC *pDC, CLoc2d &robot_pos, COLORREF crColor = RGB(0,128,0));
	void DrawPath			(CDC *pDC, vector<ObjectLocation> *path, ObjectLocation &robot_pos, COLORREF crColor = RGB(0,0,255));
	//void DrawParticle		(CDC *pDC, vector<CVirtualRobot> &particles);
	//void DrawVfh			(CDC *pDC, CLoc2d &robot_pos, CVfh *pvfh, double safe_radius, double max_velocity);
	//void DrawPosInfo		(CDC *pDC, const string &id, const CLoc2d &position, COLORREF crColor = RGB(64,64,127));
	//void DrawTopologicalMap (CDC *pDC, CTopologicalMap *map, double cellWidth, COLORREF crColor = RGB(127,127,127));
	//void DrawAStarMap		(CDC *pDC, TaskAstarPath *Astar, COLORREF crColor = RGB(127,127,127));
	//void DrawRobotFootMark	(CDC *pDC, vector<CLoc2d> *footmark, COLORREF crColor = RGB(127, 64, 200));
	//void DrawSelectedArea (CDC *pDC, int sx, int sy, int ex, int ey);
};

