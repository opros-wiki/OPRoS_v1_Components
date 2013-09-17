// ManipulatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL_Manipulator.h"
#include "ManipulatorDlg.h"


// ManipulatorDlg dialog

IMPLEMENT_DYNAMIC(ManipulatorDlg, CDialog)

ManipulatorDlg::ManipulatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ManipulatorDlg::IDD, pParent)
{
	jointInfo = new JointInfo();
}

ManipulatorDlg::~ManipulatorDlg()
{
}

void ManipulatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CANCEL_BTN, m_cancelBtn);
}


BEGIN_MESSAGE_MAP(ManipulatorDlg, CDialog)
	ON_BN_CLICKED(IDC_CANCEL_BTN, &ManipulatorDlg::OnBnClickedCancelBtn)
	ON_MESSAGE(0, OnMsgCancel)
END_MESSAGE_MAP()


// ManipulatorDlg message handlers

BOOL ManipulatorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	int xSize = 640;
	int ySize = 480;
	this->MoveWindow(GetSystemMetrics(SM_CXSCREEN) / 2 - (xSize / 2), GetSystemMetrics(SM_CYSCREEN) / 2 - (ySize / 2), xSize, ySize);

	CRect rect;
	GetClientRect(rect);
	
	m_cancelBtn.EnableWindow(FALSE);
	m_cancelBtn.ShowWindow(FALSE);

	view = new COglWndCustom(jointInfo);
	view->CreateEx(0, "#32770", "", WS_TABSTOP | WS_CHILD | WS_VISIBLE, rect, this, 0);
	view->_showAxis = true;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void ManipulatorDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	delete view;		view = NULL;
	delete jointInfo;	jointInfo = NULL;

	CDialog::OnCancel();
}

LRESULT ManipulatorDlg::OnMsgCancel(WPARAM wParam, LPARAM lParam)
{
	OnCancel();
	return 0;
}

void ManipulatorDlg::OnBnClickedCancelBtn()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void ManipulatorDlg::AttachJoint(int jointType, int jointAxis, double x, double y, double z, double phi, double theta, double psi, double radius)
{
	jointInfo->AttachJoint(jointType, jointAxis, x, y, z, phi, theta, psi, radius);
}

bool ManipulatorDlg::SetPosition(vector<double> position)
{
	vector<JointEx *> &robot = jointInfo->GetJointList ();
	
	if(position.size() != robot.size()) {
		return false;
	}

	for(size_t i = 0; i < position.size(); i++) {
		robot[i]->q = position[i] * _DEG2RAD;
	}

	view->InvalidateRect (NULL, FALSE);

	return true;
}

vector<double> ManipulatorDlg::GetPosition(void)
{
	vector<double> position;
	vector<JointEx *> &robot = jointInfo->GetJointList ();
	
	for(size_t i = 0; i < robot.size(); i++) {
		position.push_back(robot[i]->q * _RAD2DEG);
	}
	
	return position;
}