//////////////////////////////////////////////////////
// OpenGL files for Robotics applications
// 
// Copyright (c) 2002-2010. All Rights Reserved.
// Division of Applied Robot Technology, KITECH
// Web: http://www.orobot.net
// Written by KwangWoong Yang<page365@gmail.com>
//

#pragma once
#pragma comment(lib, "Opengl32.lib")
#pragma comment(lib, "Glu32.lib")

#include "afxwin.h"
#include "OglDef.h"

//  OpenGL 윈도우 조작 명령:
//	마우스 왼쪽 버튼 클릭 후 이동 – 로봇을 좌우, 상하로 회전한다.
//	마우스 오른쪽 버튼 클릭 후 이동 – 로봇을 좌우, 상하로 이동한다.
//	마우스 스크롤 이동 – 로봇의 원근을 조절한다.


class COglWnd : public CWnd
{
public:
	COglWnd ();
	virtual ~COglWnd ();

	void UpdateWnd ();

public:
	// 아래 변수들로부터 로봇을 바라보는 눈의 위치와 방향을 설정한다.
	// 눈의 위치(_eyePos)로부터 물체의 중심(_centerPos)을 바라보는데 수평(_angleHor)과 
	// 수직(_angleVer)로 물체를 회전한다.
	CPoint3d _eyePos;	
	CPoint3d _centerPos;
	double _angleHor;
	double _angleVer;

	// Perspective projection 설정
	double _fovAngle;
	int _glnWidth, _glnHeight;

	void SetViewport ();
	virtual void OnDraw (CDC* pDC) { }

private:
	int _lookMethod;
	int _mouseButton;
	CPoint _mouseDownPoint;

	HGLRC _glrc;	//Rendering Context

	void InitGL();
	void DeinitGL();
	BOOL SetupPixelFormat(HDC hdc);

public:
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
