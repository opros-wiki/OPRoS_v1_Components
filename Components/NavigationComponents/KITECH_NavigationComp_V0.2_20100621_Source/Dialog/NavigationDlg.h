
// NavigationDlg.h : header file
//

#pragma once

#include "Resource.h"
#include "afxwin.h"
#include "DialogExt.h"
#include "DrawDlg.h"
#include "OprosMath.h"
#include "ApiTypes.h"
#include "GridBasedGlobalMap.h"

// CNavigationDlg dialog
class CNavigationDlg : public CDialogExt, public CDrawDlg
{
	DECLARE_DYNAMIC(CNavigationDlg)

// Construction
public:
	CNavigationDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CNavigationDlg();

// Dialog Data
	enum { IDD = IDD_NAVIGATION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	virtual int M2Px(double _x);
	virtual int M2Py(double _y);
	virtual int M2Pl(double _d);

	double P2Mx(int _x);
	double P2My(int _y);
	double P2Ml(int _d);


	inline void SetDlgItemPosition (int nIDDlgItem, ObjectLocation &fValue) 
	{
		double val[3] = {fValue.x, fValue.y, RAD2DEG(fValue.theta) };
		SetDlgItemDoubleN (nIDDlgItem, val, 3);
	}

private:
	enum eObjectSel {
		SEL_NONE = 0, SEL_TARGET, SEL_CURRENT, SEL_MAP
	};
	eObjectSel _sel;

	double	_scale;
	double	_cellWidth;
	CPoint	_screenOffset;
	CPoint	_mouseDragStart;
	CRect	_mapRect;

	double	_robotOffsetX;
	double	_robotOffsetY;

	CDC      _memDC;
	CBitmap  _bitmap;
	CBitmap* _bitmapOld;

	bool	_rButtonDown;
	CPoint	_selectedAreaStart;
	CPoint	_selectedAreaEnd;

	void UpdateScreen ();
	void UpdateDialogItem ();

	unsigned char _palette[256][4];
	void InitPalette();
	GridBasedGlobalMap *_globalMap;

	double _safeRadius;
	double _startAngle;
	double _endAngle;
	double _sensorCount;
	ObjectLocation sensorPosition;

	ObjectLocation _targetPos;
	ObjectLocation _currentPos;
	vector<ObjectLocation> _path;

	// Implementation
protected:
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnBnClickedButtonNavigationTo();
	afx_msg void OnBnClickedButtonMove();
	afx_msg void OnBnClickedButtonTurn();
	afx_msg void OnBnClickedButtonStop();
};
