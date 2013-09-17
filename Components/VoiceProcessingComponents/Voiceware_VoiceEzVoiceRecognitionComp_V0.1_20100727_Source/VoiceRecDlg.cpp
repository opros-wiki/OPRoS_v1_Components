// VoiceRecDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Voiceware_VoiceEzVoiceRecognitionComp.h"
#include "VoiceRecDlg.h"
#include "OprosPrintMessage.h"

#include "ve/veapi.h"
#include "vez/VezIF.h"
// VoiceRecDlg dialog

IMPLEMENT_DYNAMIC(VoiceRecDlg, CDialog)

VoiceRecDlg::VoiceRecDlg(CWnd* pParent /*=NULL*/)
	: CDialog(VoiceRecDlg::IDD, pParent)
{

}

VoiceRecDlg::~VoiceRecDlg()
{
}

void VoiceRecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(VoiceRecDlg, CDialog)
	ON_MESSAGE(WM_SPEECH_DETECTED, OnSpeechDetected)
END_MESSAGE_MAP()


// VoiceRecDlg message handlers

BOOL VoiceRecDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	PrintMessage("VoiceRecDlg::OnInitDialog()\n");
	_handle = InitVoiceEZWinMessage (this->m_hWnd, WM_SPEECH_DETECTED, 0, NULL);
	if (_handle <= 0) {
		PrintMessage ("ERROR: InitVoiceEZWinMessage() failed, return %d\n", _handle);
		return false;
	}

	LoadWordListFile("WordList.txt");

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT VoiceRecDlg::OnSpeechDetected(WPARAM wParam, LPARAM lParam)
{
//	PrintMessage("Success:VoiceRecDlg::OnSpeechDetected() %s\n", lParam);
	recResult = (char *)lParam;
	return 0;
}

bool VoiceRecDlg::StartVoiceEZ()
{
	if( StartRecognition (_handle, TRUE) )
		return true;
	else
		return false;

	return true;
}

bool VoiceRecDlg::StopVoiceEZ()
{
	return StopRecognition (_handle);
}

bool VoiceRecDlg::GetVoiceResult(std::string *result)
{
	if( recResult.size() ) {
		*result = recResult;
		recResult.clear();
		return true;
	}
	else {
		return false;
	}
}

int VoiceRecDlg::LoadWordListFile (const char *fileName)
{
	if (_handle <= 0) return -1;

	string word_list;
	word_list.reserve (100000);

	FILE *fp = fopen(fileName, "rt");
	if (fp) {
		char word[256+1];
		while (fgets (word, 256, fp)) {
			int i;
			for (i=strlen(word)-1; 0<=i && (word[i] == '\r' || word[i] == '\n' || word[i] == ' ' || word[i] == '\t'); i--) {
				word[i] = '\0';
			}
			if (0 < i && word[0] != ';' && word[0] != '#') {
				word_list += word;
				word_list += "\n";
			}
		}
		fclose(fp);
	}
	else {
		PrintMessage ("ERROR: Can't load word list file: %s\n", fileName);
		return 0;
	}

	return LoadWordList (word_list.c_str ());
}

int VoiceRecDlg::LoadWordList (const char *word_list)
{
	if (_handle <= 0) return -1;

	// StopRecognition (_handle);
	NewList (_handle, (char *)word_list, NULL);
	FlushVSRList (_handle);

	return 0;
}
