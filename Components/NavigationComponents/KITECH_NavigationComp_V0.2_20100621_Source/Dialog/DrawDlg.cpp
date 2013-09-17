#include "stdafx.h"
#include "DrawDlg.h"

#pragma pack( push, packing_alignments, 1 )

struct BMP_FILE_HEAD { 
	short bfType;
	long  bfSize;
	short bfReserved0;
	short bfReserved2;
	long  bfOffBits;
};

struct BMP_INFO_HEAD{ 
	long  biSize;
	long  biWidth;
	long  biHeight;
	short biPlanes;
	short biBitCount;
	long  biCompression;
	long  biSizeImage;
	long  biXPelsPerMeter;
	long  biYPelsPerMeter;
	long  biClrUsed;
	long  biClrImportant;
};

#pragma pack( pop, packing_alignments )

struct BITMAPINFO_256C { 
  BITMAPINFOHEADER bmiHeader; 
  RGBQUAD          bmiColors[256]; 
}; 

void CDrawDlg::DrawBackground (CDC *pDC, double dx, double dy, double d)
{
	HPEN pen = CreatePen (PS_SOLID, 1, RGB(196,196,196));

	HPEN pen_old = (HPEN)::SelectObject (pDC->m_hDC, ::GetStockObject (BLACK_PEN));
	HBRUSH brush_old = (HBRUSH)::SelectObject (pDC->m_hDC, ::GetStockObject (WHITE_BRUSH));

	pDC->SelectObject (::GetStockObject (WHITE_PEN));
	pDC->SelectObject (::GetStockObject (WHITE_BRUSH));
	pDC->Rectangle (0, 0, 2560, 1600);

	pDC->SelectObject (pen);

	double x, y;
	for (x=-dx; x<=dx; x+=d) {
		pDC->MoveTo (M2Px(x), M2Py(-50));
		pDC->LineTo (M2Px(x), M2Py(50));
	}
	for (y=-dy; y<=dy; y+=d) {
		pDC->MoveTo (M2Px(-50), M2Py(y));
		pDC->LineTo (M2Px(50), M2Py(y));
	}

	::SelectObject (pDC->m_hDC, pen_old);
	::SelectObject (pDC->m_hDC, brush_old);

	DeleteObject (pen);
}

void CDrawDlg::DrawRobot (CDC *pDC, ObjectLocation &robot_pos, COLORREF crColor)
{
	// SEROPI-1
	static const double robot_wire_frame_seropi1[][3] = {
		{ 111,    0, 1}, { 111,   90, 0}, {  95,  140, 0}, {  69,  156, 0}, {-191,  156, 0},
		{-191,  140, 0}, {-311,  140, 0}, {-311,  100, 0}, {-351,  100, 0}, {-351,    0, 0}, 
		{ 111,    0, 1}, { 111,  -90, 0}, {  95, -140, 0}, {  69, -156, 0}, {-191, -156, 0},
		{-191, -140, 0}, {-311, -140, 0}, {-311, -100, 0}, {-351, -100, 0}, {-351,    0, 0}, 
		{  29,   27, 1}, {  83,   27, 0}, {  83,  -27, 0}, {  29,  -27, 0}, {  29,   27, 0},
		{-151,   70, 1}, {-291,   70, 0}, {-291,  -70, 0}, {-151,  -70, 0}, {-151,   70, 0},
		{  99, -166, 1}, {  99, -222, 0}, {-101, -222, 0}, {-101, -166, 0}, {  99, -166, 0}, 
		{  99,  166, 1}, {  99,  222, 0}, {-101,  222, 0}, {-101,  166, 0}, {  99,  166, 0}, 
		{  99,  175, 1}, { 111,  130, 0}, { 111, -130, 0}, {  99, -175, 0},
	};

	static const double robot_circle_seropi1[][3] = {
		{  56,    0, 20}, 
		{   0,  148, 10}, 
		{   0, -148, 10}, 
		{-281,  110, 10}, 
		{-281, -110, 10}, 
	};

	// CMR-P3
	static const double robot_wire_frame_cmr_p3[][3] = {
		{ 111,  -90, 1}, {  91, -150, 0}, {-126, -150, 0}, {-289,  -70, 0}, {-289,   70, 0},
		{-126,  150, 0}, {  91,  150, 0}, { 111,   90, 0}, { 111,  -90, 0}, { 101, -150, 1},
		{ 101, -200, 0}, { -99, -200, 0}, { -99, -150, 0}, { 101, -150, 0}, { 101,  150, 1},
		{ 101,  200, 0}, { -99,  200, 0}, { -99,  150, 0}, { 101,  150, 0}, { 121,  175, 1},
		{ 131,  130, 0}, { 131, -130, 0}, { 121, -175, 0},
	};

	// CMR-P2
	static const double robot_wire_frame_cmr_p2[][3] = {
		{-280,    0, 1}, {-220,  260, 0}, {-140,  300, 0}, {  40, 300,  0}, { 180,  240, 0},
		{ 230,  150, 0}, { 260,    0, 0}, { 230, -150, 0}, { 180,-240,  0}, {  40, -300, 0},
		{-140, -300, 0}, {-220, -260, 0}, {-280,    0, 0}, 
		{ 230,  150, 1}, { 290,  150, 0}, { 320,   80, 0}, { 320, -80,  0}, { 290,- 150, 0},
		{ 230, -150, 0}, 		
		{  30,    0, 1}, {  40,   40, 0}, { 240,   40, 0}, { 250,    0, 0}, { 240,  -40, 0}, 
		{  40,  -40, 0}, {  30,    0, 0}, 
		{-140,    0, 1}, {-130,   40, 0}, { -80,   90, 0}, { 220,   80, 0}, { 250,   40, 0}, 
		{ 250,  -40, 0}, { 220,  -80, 0}, { -80,  -90, 0}, {-130,  -40, 0}, {-140,    0, 0}, 
	};

	int n_robot_wire_frame = 0;
	int n_robot_circle = 0;
	const double (*robot_wire_frame)[3] = NULL;
	const double (*robot_circle)[3] = NULL;

	//if (model == ROBOTMODEL_MRS || model == ROBOTMODEL_SEROPI1 || model == ROBOTMODEL_WEBOTS) {	// MRS Simulator, SEROPI-1, WEBOT
	//	n_robot_wire_frame = sizeof(robot_wire_frame_seropi1)/sizeof(double)/3;
	//	n_robot_circle = sizeof(robot_circle_seropi1)/sizeof(double)/3;
	//	robot_wire_frame = robot_wire_frame_seropi1;
	//	robot_circle = robot_circle_seropi1;
	//}
	//else if (model == ROBOTMODEL_CMR_P3) {	// CMR-P3
	//	n_robot_wire_frame = sizeof(robot_wire_frame_cmr_p3)/sizeof(double)/3;
	//	robot_wire_frame = robot_wire_frame_cmr_p3;
	//}
	//else if (model == ROBOTMODEL_CMR_P2) {	// CMR-P2
	//	n_robot_wire_frame = sizeof(robot_wire_frame_cmr_p2)/sizeof(double)/3;
	//	robot_wire_frame = robot_wire_frame_cmr_p2;
	//}

	n_robot_wire_frame = sizeof(robot_wire_frame_cmr_p3)/sizeof(double)/3;
	robot_wire_frame = robot_wire_frame_cmr_p3;

	HPEN pen = CreatePen (PS_SOLID, 1, crColor);

	HPEN pen_old = (HPEN)::SelectObject (pDC->m_hDC, ::GetStockObject (BLACK_PEN));
	HBRUSH brush_old = (HBRUSH)::SelectObject (pDC->m_hDC, ::GetStockObject (WHITE_BRUSH));

	pDC->SelectObject (pen);
	pDC->SelectObject (::GetStockObject (NULL_BRUSH));

	for (int i=0; i<n_robot_wire_frame; ++i) {
		double rm[3];
		double wf[3] = {robot_wire_frame[i][0], robot_wire_frame[i][1], robot_wire_frame[i][2]};
		Rotate (rm, wf, robot_pos.theta);

		int x = M2Px(robot_pos.x + rm[0]/1000.);
		int y = M2Py(robot_pos.y + rm[1]/1000.);
		if (robot_wire_frame[i][2] == 1) pDC->MoveTo (x, y);
		else pDC->LineTo (x, y);
	}

	for (int i=0; i<n_robot_circle; ++i) {
		double rm[3];
		double rc[3] = {robot_circle[i][0], robot_circle[i][1], robot_circle[i][2]};

		Rotate (rm, rc, robot_pos.theta);
		rm[2] = robot_circle[i][2];

		int x = M2Px(robot_pos.x + rm[0]/1000.);
		int y = M2Py(robot_pos.y + rm[1]/1000.);
		int r = M2Pl(rm[2]/1000.);
		pDC->Ellipse (x-r, y-r, x+r,y+r);
	}

	::SelectObject (pDC->m_hDC, pen_old);
	::SelectObject (pDC->m_hDC, brush_old);

	DeleteObject (pen);
}

void CDrawDlg::DrawBmp256 (HDC hDC, int _offsetX, int _offsetY, int imageWidth, int imageHeight, float imageScale, unsigned char *image, unsigned char palette[256][4])
{
	BITMAPINFO_256C biBitmap;
	biBitmap.bmiHeader.biSize = sizeof( BITMAPINFOHEADER );
	biBitmap.bmiHeader.biWidth = imageWidth;
	biBitmap.bmiHeader.biHeight = imageHeight;
	biBitmap.bmiHeader.biPlanes = 1;
	biBitmap.bmiHeader.biBitCount = 8;
	biBitmap.bmiHeader.biCompression = BI_RGB;
	biBitmap.bmiHeader.biSizeImage = imageWidth * imageHeight * 1;
	biBitmap.bmiHeader.biClrUsed = 0;
	biBitmap.bmiHeader.biClrImportant = 0;
	
	for (int i=0; i<256; ++i) {
		biBitmap.bmiColors[i].rgbBlue  = palette[i][0]; 
		biBitmap.bmiColors[i].rgbGreen = palette[i][1]; 
		biBitmap.bmiColors[i].rgbRed   = palette[i][2]; 
		biBitmap.bmiColors[i].rgbReserved = 0; 
	}
	int rval = StretchDIBits (hDC, _offsetX, _offsetY, (int)(imageWidth*imageScale), (int)(imageHeight*imageScale),
		0, 0, imageWidth, imageHeight, image, (LPBITMAPINFO) &biBitmap, DIB_RGB_COLORS, SRCCOPY );
}

void CDrawDlg::DrawSensorRange (CDC *pDC, ObjectLocation &robot_pos, double startAngle, double endAngle, double sensorCount, ObjectLocation sensorPosition, vector<double> value, COLORREF crColor, int point_size, bool line)
{
	HPEN pen_gray = CreatePen (PS_SOLID, 1, RGB(192,192,192));
	HPEN pen = CreatePen (PS_SOLID, 1, crColor);
	HPEN pen_dot = CreatePen (PS_DOT, 1, crColor);

	HPEN pen_old = (HPEN)::SelectObject (pDC->m_hDC, ::GetStockObject (BLACK_PEN));
	HBRUSH brush_old = (HBRUSH)::SelectObject (pDC->m_hDC, ::GetStockObject (WHITE_BRUSH));

	pDC->SelectObject (pen);
	pDC->SelectObject (::GetStockObject (NULL_BRUSH));

	ObjectLocation sp = sensorPosition;
	sp.Rotate (robot_pos.theta);

	double resolution = (endAngle - startAngle)/(sensorCount-1);

	for (int i=0; i<(int)value.size (); ++i) {
		double &v = value[i];
		ObjectLocation ep (v, 0, 0);
		ep.Rotate (robot_pos.theta + startAngle + i*resolution);

		int x = M2Px(robot_pos.x + sp.x + ep.x);
		int y = M2Py(robot_pos.y + sp.y + ep.y);
		int r = point_size;
		if (line) {
			pDC->SelectObject (pen_gray);
			if (i==0) pDC->MoveTo (x, y);
			else   	  pDC->LineTo (x, y);
		}
		pDC->SelectObject (pen);
		if (r==1) pDC->SetPixel (x, y, crColor);
		else 	  pDC->Ellipse (x-r, y-r, x+r, y+r);
	}

	::SelectObject (pDC->m_hDC, pen_old);
	::SelectObject (pDC->m_hDC, brush_old);

	DeleteObject (pen_gray);
	DeleteObject (pen_dot);
	DeleteObject (pen);
}

#if 0
void CDrawDlg::DrawLoadCell (CDC *pDC, CLoc2d &robot_pos, double zmp_x, double zmp_y, COLORREF crColor, int point_size)
{
	HPEN pen = CreatePen (PS_SOLID, 1, crColor);
	HPEN pen_dot = CreatePen (PS_DOT, 1, crColor);

	HPEN pen_old = (HPEN)::SelectObject (pDC->m_hDC, ::GetStockObject (BLACK_PEN));
	HBRUSH brush_old = (HBRUSH)::SelectObject (pDC->m_hDC, ::GetStockObject (WHITE_BRUSH));

	pDC->SelectObject (pen);
	pDC->SelectObject (::GetStockObject (NULL_BRUSH));

	int x = M2Px(robot_pos.x + zmp_x);
	int y = M2Py(robot_pos.y + zmp_y);
	int r = point_size; //M2Pl(v);

	pDC->Ellipse (x-r, y-r, x+r,y+r);

	::SelectObject (pDC->m_hDC, pen_old);
	::SelectObject (pDC->m_hDC, brush_old);

	DeleteObject (pen);
	DeleteObject (pen_dot);
}

void CDrawDlg::DrawLocPoint (CDC *pDC, CLoc2d &robot_pos, COLORREF crColor)
{
	HPEN pen = CreatePen (PS_SOLID, 1, crColor);

	HPEN pen_old = (HPEN)::SelectObject (pDC->m_hDC, ::GetStockObject (BLACK_PEN));
	
	pDC->SelectObject (pen);
	pDC->SelectObject (::GetStockObject (NULL_BRUSH));

	int x = M2Px(robot_pos.x);
	int y = M2Py(robot_pos.y);
	int r = 3;

	pDC->Ellipse (x-r, y-r, x+r,y+r);
	pDC->MoveTo (x, y);
	
	r = 15;
	double rad = robot_pos.th;
	x += (int)(r*cos(rad));
	y += (int)(-r*sin(rad));

	pDC->LineTo (x, y);

	::SelectObject (pDC->m_hDC, pen_old);

	DeleteObject (pen);
}
#endif

void CDrawDlg::DrawPath (CDC *pDC, vector<ObjectLocation> *path, ObjectLocation &robot_pos, COLORREF crColor)
{
	HPEN pen = CreatePen (PS_SOLID, 1, crColor);
	HBRUSH brush = CreateSolidBrush (crColor);

	HPEN pen_old = (HPEN)::SelectObject (pDC->m_hDC, ::GetStockObject (BLACK_PEN));
	HBRUSH brush_old = (HBRUSH)::SelectObject (pDC->m_hDC, ::GetStockObject (WHITE_BRUSH));

	pDC->SelectObject (pen);
	pDC->SelectObject (::GetStockObject (WHITE_BRUSH));

	pDC->MoveTo (M2Px(robot_pos.x), M2Py(robot_pos.y));

	vector<ObjectLocation >::iterator it;
	for (it=path->begin (); it!=path->end(); ++it) {
		pDC->LineTo (M2Px(it->x), M2Py(it->y));
		pDC->Ellipse (M2Px(it->x)-3, M2Py(it->y)-3, M2Px(it->x)+3, M2Py(it->y)+3);
	}

	::SelectObject (pDC->m_hDC, pen_old);
	::SelectObject (pDC->m_hDC, brush_old);
	
	DeleteObject (pen);
	DeleteObject (brush);
}

#if 0
void CDrawDlg::DrawParticle(CDC *pDC, vector<CVirtualRobot> &particles)
{
	HPEN pen_old = (HPEN)::SelectObject (pDC->m_hDC, ::GetStockObject (BLACK_PEN));
	HBRUSH brush_old = (HBRUSH)::SelectObject (pDC->m_hDC, ::GetStockObject (WHITE_BRUSH));
	HFONT font_old = (HFONT)::SelectObject (pDC->m_hDC, ::GetStockObject (SYSTEM_FIXED_FONT));

	for (int i=particles.size()-1; 0<=i; i--) {
		int c = (int)(255*(1-particles[i].prob));
		c = bound (c, 0, 255);
		double mx = particles[i].pos.x;
		double my = particles[i].pos.y;

		pDC->SetPixel (M2Px(mx), M2Py(my), RGB(0, 0, c));
	}

	::SelectObject (pDC->m_hDC, pen_old);
	::SelectObject (pDC->m_hDC, brush_old);
	::SelectObject (pDC->m_hDC, font_old);
}

void CDrawDlg::DrawVfh(CDC *pDC, CLoc2d &robot_pos, CVfh *pvfh, double safe_radius, double max_velocity)
{
	HPEN PenBlue   = CreatePen (PS_DOT, 1, RGB(0, 0, 255));
	HPEN PenBlack  = CreatePen (PS_SOLID, 1, RGB(32, 32, 32));
	HPEN PenGreen  = CreatePen (PS_SOLID, 1, RGB(0, 128,0));
	HPEN PenGreen2 = CreatePen (PS_SOLID, 2, RGB(0, 192,0));
	HPEN PenLtGray = CreatePen (PS_SOLID, 1, RGB(192,192,255));

	HPEN pen_old = (HPEN)::SelectObject (pDC->m_hDC, ::GetStockObject (BLACK_PEN));

	int x, y;
	for (y=0; y<LOCALMAP_SIZE; y++) {
		for (x=0; x<LOCALMAP_SIZE; x++) {
			int nx = M2Px(robot_pos.x + (x - LOCALMAP_SIZE/2) * LOCALMAP_CELL_SIZE);
			int ny = M2Py(robot_pos.y + (y - LOCALMAP_SIZE/2) * LOCALMAP_CELL_SIZE);
			if (0 < pvfh->_localMap._cell[y][x]) {
				pDC->SetPixel (nx+0, ny+0, RGB(128,0,0));
				pDC->SetPixel (nx+0, ny+1, RGB(128,0,0));
				pDC->SetPixel (nx+1, ny+0, RGB(128,0,0));
				pDC->SetPixel (nx+1, ny+1, RGB(128,0,0));
			}
			else {
				// pDC->SetPixel (nx+0, ny+0, RGB(192,192,192));
			}
		}
	}

	::SelectObject (pDC->m_hDC, PenLtGray);

	int i;
	for (i=0; i<360; i++) {
		double rad = DEG2RAD(i);
		double cos_r = cos (rad);
		double sin_r = sin (rad);
		double rx = safe_radius * cos_r;
		double ry = safe_radius * sin_r;

		double vel_radius = safe_radius + (max_velocity - pvfh->_polarHistogram[i]); // / max_velocity * safe_radius;
		double ox = vel_radius * cos_r;
		double oy = vel_radius * sin_r;

		pDC->MoveTo (M2Px(robot_pos.x + rx), M2Py(robot_pos.y + ry));
		pDC->LineTo (M2Px(robot_pos.x + ox), M2Py(robot_pos.y + oy));
		pDC->SetPixel (M2Px(robot_pos.x + rx), M2Py(robot_pos.y + ry), RGB(128,128,128));
	}

	double rx, ry;

	::SelectObject (pDC->m_hDC, PenBlue);
	rx = pvfh->_targetDistance * cos (robot_pos.th + pvfh->_targetDirection);
	ry = pvfh->_targetDistance * sin (robot_pos.th + pvfh->_targetDirection);
	pDC->MoveTo (M2Px(robot_pos.x + 0),  M2Py(robot_pos.y + 0));
	pDC->LineTo (M2Px(robot_pos.x + rx), M2Py(robot_pos.y + ry));

	::SelectObject (pDC->m_hDC, PenGreen2);
	rx = pvfh->_steerForwardVel * cos (robot_pos.th + pvfh->_steerAngularVel);
	ry = pvfh->_steerForwardVel * sin (robot_pos.th + pvfh->_steerAngularVel);
	pDC->MoveTo (M2Px(robot_pos.x + 0),  M2Py(robot_pos.y + 0));
	pDC->LineTo (M2Px(robot_pos.x + rx), M2Py(robot_pos.y + ry));

	::SelectObject (pDC->m_hDC, pen_old);

	DeleteObject (PenBlue);
	DeleteObject (PenBlack);
	DeleteObject (PenGreen);
	DeleteObject (PenGreen2);
	DeleteObject (PenLtGray);
}

void CDrawDlg::DrawPosInfo (CDC *pDC, const string &id, const CLoc2d &position, COLORREF crColor)
{
	HPEN pen = CreatePen (PS_SOLID, 1, crColor);

	HPEN pen_old = (HPEN)::SelectObject (pDC->m_hDC, ::GetStockObject (BLACK_PEN));

	pDC->SelectObject (pen);
	pDC->SelectObject (::GetStockObject (NULL_BRUSH));

	int rad = M2Pl(0.3);
	double rx = 0.3 * cos (position.th);
	double ry = 0.3 * sin (position.th);
	pDC->Ellipse (M2Px(position.x)-rad, M2Py(position.y)-rad, M2Px(position.x)+rad, M2Py(position.y)+rad);
	pDC->MoveTo (M2Px(position.x + 0),  M2Py(position.y + 0));
	pDC->LineTo (M2Px(position.x + rx), M2Py(position.y + ry));

	pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextAlign (TA_CENTER | TA_BASELINE);
	pDC->SetTextColor (crColor);

	pDC->TextOut (M2Px(position.x), M2Py(position.y)+rad+13, id.c_str (), id.size ());

	::SelectObject (pDC->m_hDC, pen_old);
	
	DeleteObject (pen);
}

void CDrawDlg::DrawTopologicalMap (CDC *pDC, CTopologicalMap *map, double cellWidth, COLORREF crColor)
{
	HPEN pen = CreatePen (PS_SOLID, 1, crColor);

	HPEN pen_old = (HPEN)::SelectObject (pDC->m_hDC, ::GetStockObject (BLACK_PEN));
	//HBRUSH brush_old = (HBRUSH)::SelectObject (pDC->m_hDC, ::GetStockObject (WHITE_BRUSH));

	pDC->SelectObject (pen);
	//pDC->SelectObject (::GetStockObject (NULL_BRUSH));

	vector<sTpNode>::iterator i1;
	vector<sTpRoute>::iterator i2;

	if (map->_topologicalMap.size () > 0){
		for (i1 = map->_topologicalMap.begin (); i1 != map->_topologicalMap.end (); i1++) {
			pDC->Rectangle (M2Px(i1->x)-3, M2Py(i1->y)-3, M2Px(i1->x)+3,  M2Py(i1->y)+3);

			for (i2 = i1->route.begin (); i2 != i1->route.end (); i2++) {
				pDC->MoveTo (M2Px(i1->x), M2Py(i1->y));
				pDC->LineTo (M2Px(i2->connectedNode->x), M2Py(i2->connectedNode->y));
			}
		}
	}

	::SelectObject (pDC->m_hDC, pen_old);
	//::SelectObject (pDC->m_hDC, brush_old);

	DeleteObject (pen);
}
/*
void CDrawDlg::DrawAStarMap (CDC *pDC, TaskAstarPath *Astar, COLORREF crColor)
{
	HPEN pen = CreatePen (PS_SOLID, 1, crColor);

	HPEN pen_old = (HPEN)::SelectObject (pDC->m_hDC, ::GetStockObject (BLACK_PEN));
	//HBRUSH brush_old = (HBRUSH)::SelectObject (pDC->m_hDC, ::GetStockObject (WHITE_BRUSH));

	pDC->SelectObject (pen);
	//pDC->SelectObject (::GetStockObject (NULL_BRUSH));	
	
	int x, y;

	for (y = 0; y < Astar->_height; y++) {
		for (x = 0; x < Astar->_width; x++) {
			if (Astar->ConvertedMap->GetPixelCELL (x, y)){
				pDC->Ellipse (x*Astar->_scalefactor - 5, (Astar->_height-y)*Astar->_scalefactor-5, x*Astar->_scalefactor + 5, (Astar->_height-y)*Astar->_scalefactor+5);
			}
		}
	}

	::SelectObject (pDC->m_hDC, pen_old);
	//::SelectObject (pDC->m_hDC, brush_old);

	DeleteObject (pen);
}
*/
void CDrawDlg::DrawRobotFootMark (CDC *pDC, vector<CLoc2d> *footmark, COLORREF crColor)
{
	HPEN pen = CreatePen (PS_SOLID, 1, crColor);

	HPEN pen_old = (HPEN)::SelectObject (pDC->m_hDC, ::GetStockObject (BLACK_PEN));
	//HBRUSH brush_old = (HBRUSH)::SelectObject (pDC->m_hDC, ::GetStockObject (WHITE_BRUSH));

	pDC->SelectObject (pen);
	//pDC->SelectObject (::GetStockObject (NULL_BRUSH));

	vector<CLoc2d>::iterator i1;
	int rad = M2Pl(0.3);

	for (i1 = footmark->begin (); i1 != footmark->end (); i1++) {
		pDC->Ellipse (M2Px(i1->x)-rad, M2Py(i1->y)-rad, M2Px(i1->x)+rad, M2Py(i1->y)+rad);
	}

	::SelectObject (pDC->m_hDC, pen_old);
	//::SelectObject (pDC->m_hDC, brush_old);

	DeleteObject (pen);
}

void CDrawDlg::DrawSelectedArea (CDC *pDC, int sx, int sy, int ex, int ey)
{
	RECT rect;
	CBrush brush(RGB(255, 0, 0));

	if (sx < ex) {
		rect.left = sx;
		rect.right = ex;
	}
	else {
		rect.left = ex;
		rect.right = sx;
	}

	if (sy < ey) {
		rect.top = sy;
		rect.bottom = ey;
	}
	else {
		rect.top = ey;
		rect.bottom =sy;
	}

	pDC->FrameRect (&rect, &brush);
}

#endif