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
	// �ȼ� �ڵ带 �����մϴ�. 
	// �ȼ� ������ ���� �׸� ��ü�� ���, �� �����쳪 ��Ʈ�ʿ� ���� �÷� ��Ʈ�� ������ ���� �Ӽ��� �����ϴ� ���� �ǹ��մϴ�. 
	// PIXELFORMATDESCRIPTOR ����ü�� DC�� ���� ���Ǵ� �ȼ� ������ �����ϸ�, �� ������� ������ �ȼ� ������ ������ �ֽ��ϴ�. 
	// ���⼭ PIXELFORMATDESCRIPTOR ����ü���� ũ��, ���� �ѹ�, �Ӽ� �÷���, �÷� ��Ʈ ��, ��ť�ķ�����(accumulate)�� 
	// ����(depth) ����, ���ٽ�(stencil), ����(auxiliary) ���� ���� ����, ���� ���̾�(layer)Ÿ�Ե��� ������ ������ �� ����. 
	// ���� ���۸��� ���� ����(Screen Buffer)�� �̸� ����(Off-Screen Buffer, �ĸ� ���۶�� �Ѵ�.)�� �̿��ϴµ�, 
	// �̸� ���ۿ� ���� �������� �� ���� ���ۿ� ��ü�ϴ� ����� ���� ���� ���� �ִϸ��̼��� ������ �� �ֽ��ϴ�. 

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
	// �÷����ۿ� ���̹��۸� �ʱ�ȭ
	COLORREF color = ::GetSysColor(COLOR_3DFACE);
	glClearColor((float)GetRValue(color)/255.0f,(float)GetGValue(color)/255.0f,(float)GetBValue(color)/255.0f, 1.0);
	glClearDepth(1.);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	// ���� ����
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

	// ������ �Ӽ� ����
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
	// OnEraseBkgnd() �� WM_ERASEBKGND �� �޽����� ó�� �Լ��μ� ���� �����ε��� �ʿ�� ������, 
	// TRUE�� ��ȯ�����ν� OpenGL ��ũ���� �������ϱ� ���� ��ũ���� ������ ĥ�ϴ� ���� ������ �� �ֽ��ϴ�. 
	// ��������� ȭ���� ��½�Ÿ� ������ ������ �̴ϴ�. 

	return TRUE;
}

int COglWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// DC�� ���� �ȼ� ������ ������ �� �̿� ������ RC�� �����մϴ�. 
	// RC�� ��� OpenGL ��ɾ���� ����ؾ� �ϴ� ������ ��Ʈ�� ������ �� �ֽ��ϴ�. 
	// RC�� DC�� ������ �Ͱ� ���� �ȼ� ������ ���ϴµ� RC�� DC�� ���� ���� ���� �ƴϸ�, 
	// DC�� GDI�� ���� ������ �����ϴ� �ݸ� RC�� OpenGL�� ���� ������ ��� �ֽ��ϴ�. 

	// ���� ����̽� ���ؽ�Ʈ�� ��´�. 
	CClientDC cdc(this);

	if (!SetupPixelFormat(cdc.GetSafeHdc())) {
		return -1;
	}
	// ������ ���ؽ�Ʈ�� ��´� 
	_glrc = wglCreateContext(cdc.GetSafeHdc());
	if (!_glrc) {
		::AfxMessageBox("wglCreateContext failed"); 
		return -1; 
	} 
	// ������ ������ ���ؽ�Ʈ�� �����. 
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

	if(!wglMakeCurrent(0, 0)) { // ���� ������ ���ؽ�Ʈ ���� 
		::AfxMessageBox("wglMakeCurrent failed"); 
	} 
	if(!wglDeleteContext(_glrc)) { // ������ ���ؽ�Ʈ ���� 
		::AfxMessageBox("wglDeleteContext failed"); 
	} 

	CWnd::OnDestroy();
}

void COglWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	wglMakeCurrent(dc,_glrc);

	// �׸� �׸���
	glMatrixMode(GL_MODELVIEW);    // Select The Modelview Matrix
	glLoadIdentity();              // Reset The Modelview Matrix

	// �׸� �����
	// Clear The Screen And The Depth Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// virtual �Լ��� ȣ���Ͽ� �׸��� �׸���.
	OnDraw (&dc);
	
	glFinish();
	SwapBuffers(dc.m_ps.hdc);
}

void COglWnd::SetViewport ()
{
	// ���� �ð� ����
	gluLookAt( _eyePos.x, _eyePos.y, _eyePos.z, _centerPos.x, _centerPos.y, _centerPos.z, 0,0,1 );

	// ��ǥ�� ȸ��
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

