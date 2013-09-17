
// NavigationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NavigationDlg.h"
#include "../KITECH_NavigationComp.h"
#include "OprosPrintMessage.h"

extern KITECH_NavigationComp *naviComp;

int CNavigationDlg::M2Px(double _x) { return INTEGER(                    _screenOffset.x + (_robotOffsetX+_x)*_scale/_cellWidth); }
int CNavigationDlg::M2Py(double _y) { return INTEGER(_mapRect.Height() + _screenOffset.y - (_robotOffsetY+_y)*_scale/_cellWidth); }
int CNavigationDlg::M2Pl(double _d) { return INTEGER(                                      _d*_scale/_cellWidth); }
double CNavigationDlg::P2Mx(int _x) { return (                    _x - _screenOffset.x)/_scale*_cellWidth - _robotOffsetX; }
double CNavigationDlg::P2My(int _y) { return (_mapRect.Height() - _y + _screenOffset.y)/_scale*_cellWidth - _robotOffsetY; }
double CNavigationDlg::P2Ml(int _d) { return (                                      _d)/_scale*_cellWidth; }


// CNavigationDlg dialog

IMPLEMENT_DYNAMIC(CNavigationDlg, CDialog)

CNavigationDlg::CNavigationDlg(CWnd* pParent /*=NULL*/)
	: CDialogExt(CNavigationDlg::IDD, pParent)
{
	_sel = SEL_NONE;

	_scale = 1.;
	_cellWidth = 0.01;
	_screenOffset.x = 0;
	_screenOffset.y = 0;

	_robotOffsetX = 0;
	_robotOffsetY = 0;

	_mouseDragStart.x = 0;
	_mouseDragStart.y = 0;

	_targetPos.x = 0;
	_targetPos.y = 0;
	_targetPos.theta = 0;

	_rButtonDown = false;

	_safeRadius = 0.4;

	_globalMap = NULL;
}

CNavigationDlg::~CNavigationDlg()
{
}

void CNavigationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNavigationDlg, CDialog)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_BUTTON_NAVIGATION_TO, &CNavigationDlg::OnBnClickedButtonNavigationTo)
	ON_BN_CLICKED(IDC_BUTTON_MOVE, &CNavigationDlg::OnBnClickedButtonMove)
	ON_BN_CLICKED(IDC_BUTTON_TURN, &CNavigationDlg::OnBnClickedButtonTurn)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CNavigationDlg::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// CNavigationDlg message handlers

BOOL CNavigationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 맵을 그리기 위한 윈도우 크기를 가져온다.
	GetDlgItem (IDC_STATIC_MAP)->GetWindowRect (_mapRect);
	GetDlgItem (IDC_STATIC_MAP)->DestroyWindow();
	ScreenToClient(_mapRect);
	
	InitPalette ();
	if (naviComp) {
		std::string mapFile = naviComp->gridBasedGlobalMapParameter.GetValue ("MapFileName");
		_cellWidth = atof (naviComp->gridBasedGlobalMapParameter.GetValue ("MapResolution").c_str ());
		_safeRadius = atof (naviComp->gridBasedGlobalMapParameter.GetValue ("MobileSafeRadius").c_str ());
		PrintMessage ("NavigationDlg::OnInitDialog()  mapFile : %s\n", mapFile.c_str ());
		PrintMessage ("NavigationDlg::OnInitDialog()  cellWidth : %f\n", _cellWidth);
		PrintMessage ("NavigationDlg::OnInitDialog()  safeRadius : %f\n", _safeRadius);
		_globalMap = new GridBasedGlobalMap (mapFile.c_str (), _cellWidth);
		_globalMap->ExpandObstacle (1, 1, 255);
		_globalMap->ExpandObstacle (1, 255, 127);
		_globalMap->ExpandObstacle (1, 127, 63);
		_globalMap->ExpandObstacle (INTEGER(_safeRadius/_cellWidth), 1, 10);
	}

	SetTimer (1000, 200, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNavigationDlg::OnDestroy()
{
	CDialogExt::OnDestroy();

	KillTimer (1000);

	if (_globalMap) {
		delete _globalMap;
		_globalMap = NULL;
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNavigationDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	if (_memDC.GetSafeHdc() == NULL) {
		_memDC.CreateCompatibleDC(&dc);
		_bitmap.CreateCompatibleBitmap(&dc, _mapRect.Width(), _mapRect.Height());
		_bitmapOld = _memDC.SelectObject(&_bitmap);
		ASSERT (_bitmapOld);

		DrawBackground (&_memDC, 50, 50, 1);
	}

	if (_memDC.GetSafeHdc() != NULL) {
		dc.BitBlt(_mapRect.left, _mapRect.top, _mapRect.Width(), _mapRect.Height(), &_memDC, 0,0, SRCCOPY);
	}
	// Do not call CDialog::OnPaint() for painting messages
}

void CNavigationDlg::OnTimer(UINT_PTR nIDEvent)
{
	UpdateDialogItem ();
	if (_memDC.GetSafeHdc()) {
		UpdateScreen ();
	}

	CDialogExt::OnTimer(nIDEvent);
}

void CNavigationDlg::UpdateScreen ()
{
	DrawBackground (&_memDC, 50, 50, 1);
	_globalMap->PaintMap (_memDC.m_hDC, M2Px (_globalMap->CU2Mx(0)), M2Py (_globalMap->CU2My(_globalMap->_height - 1)),	(float)_scale);

	if (!(_sel == SEL_TARGET && GetCapture()==this)) {
		if (naviComp) _targetPos = naviComp->targetPosition;
	}

	if (!(_sel == SEL_CURRENT && GetCapture()==this)) {
		if (naviComp) _currentPos = naviComp->GetPosition();
	}

	if (naviComp) {
		naviComp->lock.Lock ();

		DrawRobot (&_memDC, _currentPos, (_sel == SEL_CURRENT) ? RGB(255,   0,   0) : RGB(128,   0,   0));
		DrawRobot (&_memDC, _targetPos, (_sel == SEL_TARGET ) ? RGB(128, 255, 128) : RGB(128, 196, 128));

		if (0 < _path.size ()) {
			DrawPath (&_memDC, &_path, _currentPos);
		}

		if (0 < naviComp->laserData.size ()) {
			DrawSensorRange (&_memDC, _currentPos,
				naviComp->laserScannerStartAngle, 
				naviComp->laserScannerEndAngle, 
				naviComp->laserScannerCount, 
				naviComp->laserScannerPos,
				naviComp->laserData);

		}
		naviComp->lock.Unlock ();
	}

	// Memory DC의 그림으로 Windows 다시 그리기
	InvalidateRect (&_mapRect, FALSE);
}

void CNavigationDlg::UpdateDialogItem ()
{
	SetDlgItemPosition (IDC_EDIT_CURRENT_POSITION, _currentPos);
	SetDlgItemPosition (IDC_EDIT_TARGET_POSITION, _targetPos);
	//SetDlgItemPosition (IDC_ED_LOCALIZATION2, _navi->_locationKf->_pos);
	//SetDlgItemPosition (IDC_ED_VARIANCE2, _navi->_locationKf->_var);
}

void CNavigationDlg::InitPalette ()
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
void CNavigationDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (GetCapture()==this) {
		CPoint delta = point - _mouseDragStart;
		_mouseDragStart = point;

		if (_sel == SEL_TARGET) {
			_targetPos.x += P2Ml(delta.x);
			_targetPos.y -= P2Ml(delta.y);
		}
		else if (_sel == SEL_CURRENT) {
			_currentPos.x += P2Ml(delta.x);
			_currentPos.y -= P2Ml(delta.y);
		}
		else if (_sel == SEL_MAP) {
			_screenOffset += delta;
		}
	}
	else if (_mapRect.left < point.x && _mapRect.top < point.y && point.x < _mapRect.right && point.y < _mapRect.bottom) {
		double val[2] = { P2Mx(point.x - _mapRect.left), P2My(point.y - _mapRect.top)};
		//SetDlgItemDoubleN (IDC_EDIT_MOUSE_POS, val, 2);

		//SetCursor(HC_CROSS); 
	}
	
	CDialog::OnMouseMove(nFlags, point);
}

void CNavigationDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (_mapRect.left < point.x && _mapRect.top < point.y && point.x < _mapRect.right && point.y < _mapRect.bottom) {
		// 로봇과 마우스 포인트간 거리를 계산하여 _safeRadius보다 작으면서 가장 가까운 로봇을 판별한다.
		double targetDist  = Distance (P2Mx(point.x - _mapRect.left), P2My(point.y - _mapRect.top), _targetPos.x, _targetPos.y);
		double currentDist = Distance (P2Mx(point.x - _mapRect.left), P2My(point.y - _mapRect.top), _currentPos.x, _currentPos.y);

		if (targetDist  < _safeRadius && targetDist <= currentDist) {
			_sel = SEL_TARGET;
		}
		else if (currentDist < _safeRadius && currentDist < targetDist) {
			_sel = SEL_CURRENT;
		}
		else {
			_sel = SEL_MAP;
		}

		SetCapture();
		//SetCursor(HC_MOVE); 
		_mouseDragStart = point;
	}
	else {
		_sel = SEL_NONE;
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CNavigationDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (_sel == SEL_TARGET) {
		if (naviComp) {
			naviComp->targetPosition = _targetPos;
			_currentPos = naviComp->GetPosition ();
			_path = naviComp->FindPath (_currentPos, _targetPos);
		}
	}
	else if (_sel == SEL_CURRENT) {
		if (naviComp) {
			naviComp->SetPosition (_currentPos);
			_path = naviComp->FindPath (_currentPos, _targetPos);
		}
	}
	else if (_sel == SEL_MAP) {
	}

	ReleaseCapture();
	//::SetCursor(::LoadCursor(NULL, IDC_ARROW));

	CDialog::OnLButtonUp(nFlags, point);
}

void CNavigationDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	_targetPos = ObjectLocation (P2Mx(point.x-_mapRect.left), P2My(point.y-_mapRect.top), _targetPos.theta);

	if (naviComp) {
		naviComp->targetPosition = _targetPos;
		_path = naviComp->FindPath (_currentPos, _targetPos);
	}

	_sel = SEL_TARGET;
	
	CDialog::OnLButtonDblClk(nFlags, point);
}

BOOL CNavigationDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (_sel == SEL_TARGET) {
		_targetPos.theta += zDelta/1000.;
		if (naviComp) naviComp->targetPosition.theta = _targetPos.theta;
		//_navi->_targetPosition.th = _targetPos.th;
	}
	else if (_sel == SEL_CURRENT){
		_currentPos.theta += zDelta/1000.;
		if (naviComp) naviComp->SetPosition (_currentPos);
		//_navi->SetPosition (_currentPos);
	}
	else if (_sel == SEL_MAP) {
		double d = 1. + zDelta/1000.;
		_scale *= d;
		_scale = bound (_scale, 0.1, 10.);

		double cx = _mapRect.Width() /2.;
		double cy = _mapRect.Height()/2.;

		_screenOffset.x = (long)(+(cx - d*(cx - _screenOffset.x)));
		_screenOffset.y = (long)(-(cy - d*(cy + _screenOffset.y)));
	}

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void CNavigationDlg::OnBnClickedButtonNavigationTo()
{
	if (naviComp) {
		naviComp->NavigationTo (_targetPos);
	}
}

void CNavigationDlg::OnBnClickedButtonMove()
{
	double distance = GetDlgItemDouble (IDC_EDIT_MOVE_DISTANCE);
	if (naviComp) {
		naviComp->Move (distance);
	}
}

void CNavigationDlg::OnBnClickedButtonTurn()
{
	double degree = GetDlgItemDouble (IDC_EDIT_TURN_DEGREE);
	if (naviComp) {
		naviComp->Rotate (degree);
	}
}

void CNavigationDlg::OnBnClickedButtonStop()
{
	if (naviComp) {
		naviComp->AbortNavigation ();
	}
}
