// VezIF.h : main header file for the VEZIF DLL
//

#if !defined(AFX_VEZIF_H__8E2C11DD_8CBC_4A17_AE3B_1CBEAE5EE43B__INCLUDED_)
#define AFX_VEZIF_H__8E2C11DD_8CBC_4A17_AE3B_1CBEAE5EE43B__INCLUDED_

#ifdef VEZIF_EXPORT
#define VOICEEZ_API __declspec(dllexport) __stdcall
#else
#define VOICEEZ_API __declspec(dllimport) __stdcall
#endif

#define VW_SET_PARAM_SR_REJECTION_ENABLE	1
#define VW_SET_PARAM_SR_THRESHOLD			2
#define VW_SET_PARAM_SR_MINENERGY			3
#define VW_SET_PARAM_SR_SILENCE				4
#define VW_SET_PARAM_SR_MAXSPEECHFRAME		5

#define VW_GET_PARAM_SR_IS_RECORDING		4

#ifdef __cplusplus
extern "C"                          // assume C declarations for C++
{
#endif


typedef BOOL  (CALLBACK* LPPRecoged)(int iValue, char *szWord);

long VOICEEZ_API InitVoiceEZWinMessage(HWND hWnd, UINT nMsg, UINT nWimMsg, LPPRecoged pFunctionRecoged = NULL);
int VOICEEZ_API EndVoiceEZClient(long);

int VOICEEZ_API NewList(long,char *szVar, char *szFsgFileName);
int VOICEEZ_API AddVSRWord(long, char *pWord);
int VOICEEZ_API DeleteVSRWord(long, char *pWord);
int VOICEEZ_API EditOutputWord(long, char *pWord, char *pOutput);
int VOICEEZ_API FlushVSRList(long);

int VOICEEZ_API StartRecognition(long, BOOL bContinuous);
int VOICEEZ_API StopRecognition(long);

int VOICEEZ_API GetDetectStr(long, char * szWord);
int VOICEEZ_API SetParam(long, int nParamID, void *Param) ;
int VOICEEZ_API GetParam(long, int nParamID, void *Param) ; 

int	VOICEEZ_API StartSaveWav(long, char *szWavFile); 
int	VOICEEZ_API StopSaveWav(long); 

int VOICEEZ_API SetLogFile(long);
int VOICEEZ_API DisableLogFile(long);



#ifdef __cplusplus
}
#endif


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VEZIF_H__8E2C11DD_8CBC_4A17_AE3B_1CBEAE5EE43B__INCLUDED_)
