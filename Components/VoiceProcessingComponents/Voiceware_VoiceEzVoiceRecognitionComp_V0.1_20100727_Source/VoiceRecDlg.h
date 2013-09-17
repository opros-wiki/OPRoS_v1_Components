#pragma once

#include "afxwin.h"
#include "resource.h"
#include "afxcmn.h"

#include <vector>

// VoiceRecDlg dialog

class VoiceRecDlg : public CDialog
{
	DECLARE_DYNAMIC(VoiceRecDlg)

public:
	VoiceRecDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~VoiceRecDlg();

// Dialog Data
	enum { IDD = IDD_VOICEREC_DLG };

protected:
	long _handle;
	std::string recResult;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnSpeechDetected(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	bool StartVoiceEZ();
	bool StopVoiceEZ();
	bool GetVoiceResult(std::string *result);

private:
	int LoadWordListFile (const char *fileName);
	int LoadWordList (const char *word_list);
};
