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
	char	*cisp;						/* �Է� ������ ������ */
	int		org_byte;					/* �Է� ������ ũ��(bytes)�� �����ð��� �����Ѵ� */
	float	pit_ratio;					/* ��ġ������ (0.25~4.0 �������ϼ��� ������) */
	float	dur_ratio;					/* ȭ�Ӻ����� (0.5~2.0 �������ϼ��� �����ӵ�) */
	float	illegal_echo_factor;		/* ��������� ����ȿ���� ���Ǵ� ����(����� ������� ���� 0���� ��) */
	float	samplingrate;				/* ���ø� ���ļ� */
	int		echo_mode;					/* ���� ȿ�� ��� ��ȣ veapi.h�� ���ǵǾ� ���� */
	int		reverb_mode;				/* ������ ȿ�� ��� ��ȣ veapi.h�� ���ǵǾ� ���� */
	int		chorus_mode;				/* �ڷ��� ȿ�� ��� ��ȣ veapi.h�� ���ǵǾ� ���� */
	int		distortion_mode;			/* ����� ȿ�� ��� ��ȣ veapi.h�� ���ǵǾ� ���� */
	int		vibrato_mode;				/* ���̺���� ȿ�� ��� ��ȣ veapi.h�� ���ǵǾ� ���� */
	int		tremolo_mode;				/* Ʈ������ ȿ�� ��� ��ȣ veapi.h�� ���ǵǾ� ���� */
	int		high_school_movie_mode;		/* �÷��� ȿ�� ��� ��ȣ veapi.h�� ���ǵǾ� ���� */
	int		zigzag_mode;				/* ������� ȿ�� ��� ��ȣ veapi.h�� ���ǵǾ� ���� */
	int		asura_mode;					/* �Ƽ��� ȿ�� ��� ��ȣ veapi.h�� ���ǵǾ� ���� */
	int		out_byte;					/* ��¹����� ũ�� (bytes) */
	int		threadID;					/* ��Ƽ������ ��忡���� ������ �ĺ� ��ȣ (0~(VEAPI_MAXOPEN-1)������ ��) */
	int		format;						/* ����� ����� ���� (0~VEAPI_FMT_MAX) */
	int		user_echo_delay;			/* ����ȿ���� ������ ������ ���� �غ��� ���� (������� ����) */
	int		user_echo_ratio;			/* ����ȿ���� ������ ������ ���� �غ��� ���� (������� ����) */
	int		user_reverb_delay;			/* ������ȿ���� ������ ������ ���� �غ��� ���� (������� ����) */
	int		user_reverb_ratio;			/* ������ȿ���� ������ ������ ���� �غ��� ���� (������� ����) */
	int		user_vibrato_mod_freq;		/* ���̺����ȿ���� ������ ������ ���� �غ��� ���� (������� ����) */
	int		user_vibrato_delay;			/* ���̺����ȿ���� ������ ������ ���� �غ��� ���� (������� ����) */
	float	user_tremolo_amp;			/* Ʈ������ȿ���� ������ ������ ���� �غ��� ���� (������� ����) */
	float	user_tremolo_freq;			/* Ʈ������ȿ���� ������ ������ ���� �غ��� ���� (������� ����) */
//	int		user_cry_mode;				/* ���̺����ȿ���� ������ ������ ���� �غ��� ���� (������� ����) */
} VEDB;

/*
 * VEAPI_OPEN()::effect Attributes
 */
#define	VEEFFECT0			0	/* Default (���� ����) */
#define	VEEFFECT1			1	/* ���� 60�� */
#define	VEEFFECT2			2	/* M ��Ҹ� */
#define	VEEFFECT3			3	/* ���� */
#define	VEEFFECT4			4	/* ET */
#define	VEEFFECT5			5	/* ���� ��Ʃ��� */
#define	VEEFFECT6			6	/* �κ� */
#define	VEEFFECT7			7	/* ��� �Ҹ� */
#define	VEEFFECT8			8	/* �ܱ��� */
#define	VEEFFECT9			9	/* High School Movie */
#define	VEEFFECT10			10	/* ����� */
#define	VEEFFECT11			11	/* �������(zigzag) */
#define	VEEFFECT12			12	/* �Ƽ���(asura) */
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
