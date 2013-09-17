// PowerSTT V.2009	HCILAB

enum POWER_STT_RECOG_TYPE
{
	COMMAND_TYPE,  CONNECTED_TYPE
};



typedef	struct	RESULT_API
{
	unsigned short			NumResult;								// no. of sentence candidates        
	char					OutString[3][512];						// recognized strings 		     
	unsigned long			OutIndex [3][2];
	int						OutScore[3]; 
} RESULT_API_t;


int	_declspec (dllexport)	power_stt_kor_create (char * strDBPath);
int	_declspec (dllexport)	power_stt_kor_set_vocab (char * strVocabList, char*strSubWord);

int	_declspec (dllexport)	power_stt_kor_init_voice (); // bBatch : Batch Test O/X
int	_declspec (dllexport)	power_stt_kor_frame_proc (short * inBuf);
int	_declspec (dllexport)	power_stt_kor_decod_proc ();

int	_declspec (dllexport)	power_stt_kor_get_result ( RESULT_API_t *pResult);
void _declspec (dllexport)	power_stt_kor_destroy ();


int _declspec (dllexport)	power_stt_kor_start_record ();
int _declspec (dllexport)	power_stt_kor_stop_record ();
int _declspec (dllexport)	power_stt_kor_get_frame (short * pBuf, BOOL bWait);


