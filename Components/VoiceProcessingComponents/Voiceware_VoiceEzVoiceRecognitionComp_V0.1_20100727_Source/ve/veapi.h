/*
 * Copyright (c) 2001 Voiceware Co., Ltd., All rights reserved.
 *
 * VEAPI (VoiceEffect API)
 */

#if defined(__cplusplus)
	extern "C" 
	{
#endif
#ifndef _VEAPI_H_
#define _VEAPI_H_

#define VEAPI_VERSION	"1.01"

#if !defined(DllExport)
#ifdef WIN32
#define DllExport		__declspec( dllexport )
#else
#define DllExport		extern
#endif
#endif

/*
 * VEDB::pitch & duration rate, illegal echo factor attributes
 */
#define	VEAPI_DEFAULT_PITCH_RATE			(1.0f)
#define	VEAPI_DEFAULT_DURATION_RATE			(1.0f)
#define	VEAPI_DEFAULT_ILLEGAL_ECHO_FACTOR	(0.0f)

/*
 * VEDB::echo mode attributes
 */
#define	VEAPI_ECHO_MODE_NONE				(0)
#define	VEAPI_ECHO_MODE_GRAND_CANYON		(1)
#define	VEAPI_ECHO_MODE_OUTER_SPACE			(2)
#define	VEAPI_ECHO_MODE_BIG_HALL			(3)
#define	VEAPI_ECHO_MODE_SMALL_HALL			(4)
#define	VEAPI_ECHO_MODE_DRAIN_PIPE			(5)

/*
 * VEDB::reverb mode attributes
 */
#define	VEAPI_REVERB_MODE_NONE				(0)
#define	VEAPI_REVERB_MODE_GRAND_CANYON		(1)
#define	VEAPI_REVERB_MODE_OUTER_SPACE		(2)
#define	VEAPI_REVERB_MODE_BIG_HALL			(3)
#define	VEAPI_REVERB_MODE_SMALL_HALL		(4)
#define	VEAPI_REVERB_MODE_DRAIN_PIPE		(5)

/*
 * VEDB::chorus mode attributes
 */
#define	VEAPI_CHORUS_MODE_NONE				(0)
#define	VEAPI_CHORUS_MODE_ALIEN				(1)
#define	VEAPI_CHORUS_MODE_DOUBLE_VOICE		(2)
#define	VEAPI_CHORUS_MODE_INVERTED_FEEDBACK	(3)
#define	VEAPI_CHORUS_MODE_ROBOT				(4)
#define	VEAPI_CHORUS_MODE_ROBOT2			(5)
#define	VEAPI_CHORUS_MODE_SCARY				(6)
#define	VEAPI_CHORUS_MODE_WARPED			(7)
#define	VEAPI_CHORUS_MODE_WOBBLE			(8)
#define	VEAPI_CHORUS_MODE_WOBBLE_MARTIANS	(9)

/*
 * VEDB::distortion mode attributes
 */
#define	VEAPI_DISTORTION_MODE_NONE			(0)
#define	VEAPI_DISTORTION_MODE_DIRTY			(1)
#define	VEAPI_DISTORTION_MODE_DIRTY2		(2)
#define	VEAPI_DISTORTION_MODE_FUZZ			(3)
#define	VEAPI_DISTORTION_MODE_GRUNGE		(4)
#define	VEAPI_DISTORTION_MODE_NOISE_GATE	(5)
#define	VEAPI_DISTORTION_MODE_PRE_EMPHASIS	(6)
#define	VEAPI_DISTORTION_MODE_DE_EMPHASIS	(7)

/*
 * VEDB::vibrato mode attributes
 */
#define	VEAPI_VIBRATO_MODE_NONE				(0)
#define	VEAPI_VIBRATO_MODE_CRY				(1)
#define	VEAPI_VIBRATO_MODE_ZIGZAG			(2)
#define	VEAPI_VIBRATO_MODE_USER_INPUT		(3)

/*
 * VEDB::tremolo mode attributes
 */
#define	VEAPI_TREMOLO_MODE_NONE				(0)
#define	VEAPI_TREMOLO_MODE_IS				(1)
#define	VEAPI_TREMOLO_MODE_USER_INPUT		(2)

/*
 * VEDB::high school movie mode attributes
 */
#define	VEAPI_HIGH_SCHOOL_MOVIE_MODE_NONE	(0)
#define	VEAPI_HIGH_SCHOOL_MOVIE_MODE_IS		(1)

/*
 * VEDB::zigzag mode attributes
 */
#define	VEAPI_ZIGZAG_MODE_NONE				(0)
#define	VEAPI_ZIGZAG_MODE_IS				(1)

/*
 * VEDB::asura mode attributes
 */
#define	VEAPI_ASURA_MODE_NONE				(0)
#define	VEAPI_ASURA_MODE_IS					(1)

/*
 * Data Block structure.
 * This structure is used internally to store _edb items.
 */
typedef struct {
	char	*cisp;						/* 입력 버퍼의 포인터 */
	int		org_byte;					/* 입력 버퍼의 크기(bytes)로 지연시간을 결정한다 */
	float	pit_ratio;					/* 피치변경율 (0.25~4.0 높은값일수록 하이톤) */
	float	dur_ratio;					/* 화속변경율 (0.5~2.0 높은값일수록 느린속도) */
	float	illegal_echo_factor;		/* 옛날방식의 에코효과에 사용되는 변수(현재는 사용하지 않음 0으로 둠) */
	float	samplingrate;				/* 샘플링 주파수 */
	int		echo_mode;					/* 에코 효과 모드 번호 veapi.h에 정의되어 있음 */
	int		reverb_mode;				/* 리벌브 효과 모드 번호 veapi.h에 정의되어 있음 */
	int		chorus_mode;				/* 코러스 효과 모드 번호 veapi.h에 정의되어 있음 */
	int		distortion_mode;			/* 디스토션 효과 모드 번호 veapi.h에 정의되어 있음 */
	int		vibrato_mode;				/* 바이브라토 효과 모드 번호 veapi.h에 정의되어 있음 */
	int		tremolo_mode;				/* 트레몰로 효과 모드 번호 veapi.h에 정의되어 있음 */
	int		high_school_movie_mode;		/* 플랜지 효과 모드 번호 veapi.h에 정의되어 있음 */
	int		zigzag_mode;				/* 지그재그 효과 모드 번호 veapi.h에 정의되어 있음 */
	int		asura_mode;					/* 아수라 효과 모드 번호 veapi.h에 정의되어 있음 */
	int		out_byte;					/* 출력버퍼의 크기 (bytes) */
	int		threadID;					/* 멀티쓰레드 모드에서의 쓰레드 식별 번호 (0~(VEAPI_MAXOPEN-1)사이의 값) */
	int		format;						/* 입출력 오디오 포맷 (0~VEAPI_FMT_MAX) */
	int		user_echo_delay;			/* 에코효과의 세밀한 조절을 위해 준비한 변수 (사용하지 않음) */
	int		user_echo_ratio;			/* 에코효과의 세밀한 조절을 위해 준비한 변수 (사용하지 않음) */
	int		user_reverb_delay;			/* 리벌브효과의 세밀한 조절을 위해 준비한 변수 (사용하지 않음) */
	int		user_reverb_ratio;			/* 리벌브효과의 세밀한 조절을 위해 준비한 변수 (사용하지 않음) */
	int		user_vibrato_mod_freq;		/* 바이브라토효과의 세밀한 조절을 위해 준비한 변수 (사용하지 않음) */
	int		user_vibrato_delay;			/* 바이브라토효과의 세밀한 조절을 위해 준비한 변수 (사용하지 않음) */
	float	user_tremolo_amp;			/* 트레몰로효과의 세밀한 조절을 위해 준비한 변수 (사용하지 않음) */
	float	user_tremolo_freq;			/* 트레몰로효과의 세밀한 조절을 위해 준비한 변수 (사용하지 않음) */
//	int		user_cry_mode;				/* 바이브라토효과의 세밀한 조절을 위해 준비한 변수 (사용하지 않음) */
} VEDB;

/*
 * VEAPI_OPEN()::effect Attributes
 */
#define	VEEFFECT0			0	/* Default (변조 없음) */
#define	VEEFFECT1			1	/* 추적 60분 */
#define	VEEFFECT2			2	/* M 목소리 */
#define	VEEFFECT3			3	/* 동굴 */
#define	VEEFFECT4			4	/* ET */
#define	VEEFFECT5			5	/* 라디오 스튜디오 */
#define	VEEFFECT6			6	/* 로봇 */
#define	VEEFFECT7			7	/* 우는 소리 */
#define	VEEFFECT8			8	/* 외국인 */
#define	VEEFFECT9			9	/* High School Movie */
#define	VEEFFECT10			10	/* 졸라맨 */
#define	VEEFFECT11			11	/* 지그재그(zigzag) */
#define	VEEFFECT12			12	/* 아수라(asura) */
#define	VEEFFECT13			13	/* A-Man */
#define	VEAPI_EFFECT_MAX	13

/*
 * VEAPI_OPEN()::format Attributes
 */
#define VEAPI_FMT_PCM		0	/* 16bit Linear PCM */
#define VEAPI_FMT_ALAWPCM	1	/* 8bit A-law PCM */
#define VEAPI_FMT_MULAWPCM	2	/* 8bit Mu-law PCM */
#define VEAPI_FMT_DADPCM	3	/* Dialogic ADPCM */
#define VEAPI_FMT_PCM8		4	/* 8bit Linear PCM */
#define	VEAPI_FMT_MAX		4

/*
 * Maximum VEAPI_OPEN() per process - OBSOLETE
 */
#define VEAPI_MAXOPEN		1024

/*
 * Default Buffer Size for VEAPI_WAVEFILE()
 */
#define VEAPI_DEFAULT_BUFFER_SIZE	1600

/*
 * Frame Block structure.
 * This structure is used internally to store _mfb items.
 */
typedef struct {
	short _flags;	/* for reserve the slot */
	VEDB _edb;		/* Data Block object */
} VEFB;

/*
 * get descriptor about the frame block pointed to by 'p'
 */
#define VEAPI_FBDESC(p)		((p)->_edb.threadID)

extern VEFB	_mfb[];		/* VEFB descriptor table */

/*
 * VEAPI function prototype definitions:
 */
DllExport void VEAPI_INIT (void);
DllExport void VEAPI_EXIT (void);

/*
 * for MT-Safe (Multithreaded safe library),
 * _REENTRANT or _THREAD_SAFE should be used
 */
#ifndef WIN32
	#if defined(_REENTRANT) || defined(_THREAD_SAFE)
	#define VEAPI_OPEN	VEAPI_OPEN_T
	#define VEAPI_CLOSE	VEAPI_CLOSE_T
	#endif /* _REENTRANT || _THREAD_SAFE */
#endif

DllExport VEFB *VEAPI_OPEN (int effect, float samplingrate, int format);
DllExport char *VEAPI_BUFFER (VEFB *vefb, char *input, int inlen, int *outlen);
DllExport int VEAPI_FILE (char *infile, char *outfile, int effect, float samplingrate, int format);
DllExport int VEAPI_WAVEFILE (char *infile, char *outfile, int effect);	/* 16K Linear PCM Wave Only */
DllExport int VEAPI_CLOSE (VEFB *vefb);
DllExport int GetVerifyCode(char *keyname);		/* return value 0: verify OK!  other: verify failed! */
DllExport void SetVerificationFile(char *keyname);

#endif /* _VEAPI_H_ */

#if defined(__cplusplus)
	}
#endif
