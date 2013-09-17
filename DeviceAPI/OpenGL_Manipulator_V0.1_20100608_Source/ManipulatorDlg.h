#pragma once


// ManipulatorDlg dialog

#include "Resource.h"
#include "afxwin.h"

#include "OglWndCustom.h"

class ManipulatorDlg : public CDialog
{
	DECLARE_DYNAMIC(ManipulatorDlg)

public:
	ManipulatorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~ManipulatorDlg();

// Dialog Data
	enum { IDD = IDD_MANIPULATOR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	LRESULT OnMsgCancel(WPARAM wParam, LPARAM lParam);
protected:
	virtual void OnCancel();
public:
	CButton m_cancelBtn;
	afx_msg void OnBnClickedCancelBtn();


private:
	JointInfo *jointInfo;
	COglWndCustom *view;

public:
	void AttachJoint(int jointType, int jointAxis, double x, double y, double z, double phi, double theta, double psi, double radius = 0.02);
	bool SetPosition(vector<double> position);
	vector<double> GetPosition(void);
};
