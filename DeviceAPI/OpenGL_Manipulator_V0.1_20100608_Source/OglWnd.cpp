//////////////////////////////////////////////////////
// OpenGL files for Robotics applications
// 
// Copyright (c) 2002-2010. All Rights Reserved.
// Division of Applied Robot Technology, KITECH
// Web: http://www.orobot.net
// Written by KwangWoong Yang<page365@gmail.com>
//

#include "StdAfx.h"
#include <gl/glu.h>
#include "OglWnd.h"

BEGIN_MESSAGE_MAP(COglWnd, CWnd)
	ON_WM_ERASEBKGND ()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
END_MESSAGE_MAP()

COglWnd::COglWnd() :
	_eyePos (2.5, 0., 0.4), 
	_centerPos (0, 0, 0.8), 
	_angleHor (0.), 
	_angleVer (0.), 
	_mouseButton (0), 
	_fovAngle(45.)
{
}

COglWnd::~COglWnd ()
{
}

BOOL COglWnd::SetupPixelFormat(HDC hdc)
{
	// 픽셀 코드를 설정합니다. 
	// 픽셀 포맷은 직접 그릴 객체의 대상, 즉 윈도우나 비트맵에 대한 컬러 비트의 구조에 대한 속성을 지정하는 것을 의미합니다. 
	// PIXELFORMATDESCRIPTOR 구조체는 DC에 의해 사용되는 픽셀 포맷을 지정하며, 각 윈도우는 각자의 픽셀 포맷을 가지고 있습니다. 
	// 여기서 PIXELFORMATDESCRIPTOR 구조체에는 크기, 버전 넘버, 속성 플래그, 컬러 비트 수, 어큐뮬레이터(accumulate)나 
	// 깊이(depth) 버퍼, 스텐슬(stencil), 보조(auxiliary) 버퍼 등의 지정, 메인 레이어(layer)타입등의 정보를 지정할 수 있죠. 
	// 더블 버퍼링은 전면 버퍼(Screen Buffer)와 이면 버퍼(Off-Screen Buffer, 후면 버퍼라고도 한다.)를 이용하는데, 
	// 이면 버퍼에 먼저 렌더링한 후 전면 버퍼와 교체하는 방식을 통해 보다 빠른 애니메이션을 구현할 수 있습니다. 

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL |		    // support OpenGL
		PFD_DOUBLEBUFFER,				// double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		16,                             // 16-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
    };
    
    int pixelFormat = ChoosePixelFormat(hdc, &pfd);
	if(pixelFormat == 0) { 
		::AfxMessageBox("ChoosePixelFormat failed."); 
		 return FALSE;
    } 

	BOOL ret = SetPixelFormat(hdc, pixelFormat, &pfd);
	if(ret == FALSE) { 
		::AfxMessageBox("SetPixelFormat failed."); 
		return FALSE; 
	} 
	return TRUE; 
}

void COglWnd::InitGL()  
{
	// 컬러버퍼와 깊이버퍼를 초기화
	COLORREF color = ::GetSysColor(COLOR_3DFACE);
	glClearColor((float)GetRValue(color)/255.0f,(float)GetGValue(color)/255.0f,(float)GetBValue(color)/255.0f, 1.0);
	glClearDepth(1.);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	// 조명 설정
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	float AmbientColor[]    = { 0.0f, 0.1f, 0.2f, 0.0f };         
	float DiffuseColor[]    = { 0.5f, 0.5f, 0.5f, 0.0f };         
	float SpecularColor[]   = { 0.5f, 0.5f, 0.5f, 0.0f };        
	float Position[]        = { 100.0f, 100.0f, -400.0f, 1.0f };  

	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientColor);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseColor);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularColor);
	glLightfv(GL_LIGHT1, GL_POSITION, Position);

	// 재질의 속성 설정
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
} 

void COglWnd::DeinitGL()
{
}

void COglWnd::UpdateWnd () 
{
	RECT rect;
	GetClientRect(&rect);
	InvalidateRect(&rect,FALSE);
}

BOOL COglWnd::OnEraseBkgnd(CDC* pDC)
{
	// OnEraseBkgnd() 는 WM_ERASEBKGND 의 메시지의 처리 함수로서 굳이 오버로딩할 필요는 없지만, 
	// TRUE를 반환함으로써 OpenGL 스크린을 렌더링하기 전에 스크린에 배경색을 칠하는 것을 막아줄 수 있습니다. 
	// 결과적으로 화면의 번쩍거림 현상을 없애줄 겁니다. 

	return TRUE;
}

int COglWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// DC에 대한 픽셀 포맷을 설정한 후 이와 연관된 RC를 생성합니다. 
	// RC는 모든 OpenGL 명령어들이 통과해야 하는 일종의 포트로 생각할 수 있습니다. 
	// RC는 DC에 지정된 것과 같은 픽셀 포맷을 지니는데 RC와 DC는 서로 같은 것이 아니며, 
	// DC는 GDI를 위한 정보를 포함하는 반면 RC는 OpenGL을 위한 정보를 담고 있습니다. 

	// 먼저 디바이스 컨텍스트를 얻는다. 
	CClientDC cdc(this);

	if (!SetupPixelFormat(cdc.GetSafeHdc())) {
		return -1;
	}
	// 렌더링 컨텍스트를 얻는다 
	_glrc = wglCreateContext(cdc.GetSafeHdc());
	if (!_glrc) {
		::AfxMessageBox("wglCreateContext failed"); 
		return -1; 
	} 
	// 현재의 렌더링 컨텍스트를 만든다. 
	if(!wglMakeCurrent(cdc.GetSafeHdc(), _glrc)) { 
		::AfxMessageBox("wglMakeCurrent failed"); 
		return -1; 
	} 
	
	InitGL ();
	return 0;
}

void COglWnd::OnDestroy()
{
	DeinitGL ();

	if(!wglMakeCurrent(0, 0)) { // 현재 렌더링 컨텍스트 해제 
		::AfxMessageBox("wglMakeCurrent failed"); 
	} 
	if(!wglDeleteContext(_glrc)) { // 렌더링 컨텍스트 제거 
		::AfxMessageBox("wglDeleteContext failed"); 
	} 

	CWnd::OnDestroy();
}

void COglWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	wglMakeCurrent(dc,_glrc);

	// 그림 그리기
	glMatrixMode(GL_MODELVIEW);    // Select The Modelview Matrix
	glLoadIdentity();              // Reset The Modelview Matrix

	// 그림 지우기
	// Clear The Screen And The Depth Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// virtual 함수를 호출하여 그림을 그린다.
	OnDraw (&dc);
	
	glFinish();
	SwapBuffers(dc.m_ps.hdc);
}

void COglWnd::SetViewport ()
{
	// 보는 시각 설정
	gluLookAt( _eyePos.x, _eyePos.y, _eyePos.z, _centerPos.x, _centerPos.y, _centerPos.z, 0,0,1 );

	// 좌표계 회전
	glRotated( _angleVer, 0,1,0 );
	glRotated( _angleHor, 0,0,1 );
}

void COglWnd::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	if (cx < 1) cx = 1;
	if (cy < 1) cy = 1;

	glViewport(0, 0, cx, cy);

    glMatrixMode(GL_PROJECTION);		// Select The Projection Matrix
	glLoadIdentity();					// Reset The Projection Matrix

	_glnWidth = cx;
	_glnHeight = cy;

	gluPerspective(_fovAngle, (double)_glnWidth/_glnHeight, 0.1, 1000000.);

	InvalidateRect(NULL,FALSE);
}

void COglWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	_mouseButton = 1;
	_mouseDownPoint=point;
	SetCapture();
	SetFocus ();
	
	CWnd::OnLButtonDown(nFlags, point);
}

void COglWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	_mouseDownPoint=CPoint(0, 0);
	ReleaseCapture();
	_mouseButton = 0;
	
	CWnd::OnLButtonUp(nFlags, point);
}

void COglWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	_mouseButton = 2;
	_mouseDownPoint=point;
	SetCapture();
	SetFocus ();

	CWnd::OnRButtonDown(nFlags, point);
}

void COglWnd::OnRButtonUp(UINT nFlags, CPoint point)
{
	_mouseDownPoint=CPoint(0, 0);
	ReleaseCapture();
	_mouseButton = 0;

	CWnd::OnRButtonUp(nFlags, point);
} 

void COglWnd::OnMButtonDown(UINT nFlags, CPoint point)
{
	_mouseButton = 3;
	_mouseDownPoint=point;
	SetCapture();
	SetFocus ();

	CWnd::OnMButtonDown(nFlags, point);
}

void COglWnd::OnMButtonUp(UINT nFlags, CPoint point)
{
	_mouseDownPoint=CPoint(0, 0);
	ReleaseCapture();
	_mouseButton = 0;

	CWnd::OnMButtonUp(nFlags, point);
}

void COglWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (GetCapture()==this) {
		if (_mouseButton == 1) {
			//Increment the object rotation angles
			_angleHor+=(point.x-_mouseDownPoint.x)/3.6;
			_angleVer+=(point.y-_mouseDownPoint.y)/3.6;
		}
		else if (_mouseButton == 2) {
			_centerPos.y -= (point.x-_mouseDownPoint.x)/100.;
			_centerPos.z += (point.y-_mouseDownPoint.y)/100.;
		}
		else if (_mouseButton == 3) {
		}

		//Redraw the view
        InvalidateRect(NULL,FALSE);
        //Set the mouse point
        _mouseDownPoint=point;
    }
	
	CWnd::OnMouseMove(nFlags, point);
}

BOOL COglWnd::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	_eyePos.x *= (zDelta < 0) ? 0.9 : 1.1;
	_eyePos.y *= (zDelta < 0) ? 0.9 : 1.1;
	_eyePos.z *= (zDelta < 0) ? 0.9 : 1.1;

	InvalidateRect(NULL,FALSE);
	
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

