//!!! 이 파일은 EveR와 SEROPI 로봇에서 공용으로 사용하는 파일입니다.
//!!! 코드를 편집할 때 주의를 요망합니다.

#pragma once
#pragma warning(disable:4995)

class CDialogExt : public CDialog {
public:
	CDialogExt(UINT nIDTemplate, CWnd* pParentWnd = NULL) :
		CDialog (nIDTemplate, pParentWnd) { }

protected:
	inline void SetDlgItemDouble (int ID, double fValue, int digit = 3) 
	{
		char format[10], text[64+1];
		if (digit < 0) digit = 0;
		if (9 < digit) digit = 9;
		_snprintf (format, 10, "%%.%d%c", digit, (-1000000 < fValue && fValue < 1000000) ? 'f' : 'g');
		_snprintf (text, 64, format, fValue);
		text[64] = '\0';
		SetDlgItemText (ID, text);
	}

	inline void SetDlgItemDoubleN (int ID, double fValue[], int nValue) 
	{
		int n = 0;
		int nBuff = nValue*13+64;
		char *buff = new char [nBuff+1];
		for (int i=0; i<nValue; ++i) {
			if (0 < i) n += _snprintf (buff + n, nBuff - n, ", ");
			const char *format = (-1000000 < fValue[i] && fValue[i] < 1000000) ? "%10.3f" : "%10.3g";
			n += _snprintf (buff + n, nBuff - n, format, fValue[i]);
		}
		buff[nBuff] = '\0';
		SetDlgItemText (ID, buff);
		delete [] buff;
	}

	inline double GetDlgItemDouble (int ID) 
	{
		char buff[64+1];
		GetDlgItemText (ID, buff, 64);
		buff[64] = '\0';
		return atof (buff);
	}

	inline void SetDlgItemTime (int ID, DWORD clock)
	{
		int day = clock/24/60/60;
		int h = (clock/60/60)%24;
		int m = (clock/60)%60;
		int s = (clock)%60;

		char buff[64+1];
		sprintf_s (buff, sizeof(buff), "%d %02d/%02d/%02d", day, h, m, s);
		SetDlgItemText (ID, buff);
	}

	inline void SetDlgItemEnabledDouble (int ID, bool enable, double fValue)
	{
		if (enable) {
			char text[64+1];
			const char *format = (-10000. < fValue && fValue < 10000.)? "%.3f" : "%g";
			_snprintf (text, 32, format, fValue);
			text[32] = '\0';
			SetDlgItemText (ID, text);
		}
		else {
			SetDlgItemText (ID, "");
		}
	}
};