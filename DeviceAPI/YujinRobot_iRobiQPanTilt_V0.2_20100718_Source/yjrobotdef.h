#ifndef __YJROBOTDEF_H__
#define __YJROBOTDEF_H__

#include <windows.h>

class RobotInterface;

#ifndef LPROBOTINTERFACE
typedef RobotInterface* LPROBOTINTERFACE;
#endif

/**
 *
 * Call back function allocation
 * 
 */
typedef VOID(CALLBACK* REQUESTPROC)(LPROBOTINTERFACE, DWORD, WORD, WORD, WPARAM, LPARAM);
typedef VOID(CALLBACK* ACKNOWLEDGEPROC)(LPROBOTINTERFACE, DWORD, WORD, WPARAM, LPARAM);
typedef VOID(CALLBACK* RESPONSEPROC)(LPROBOTINTERFACE, DWORD, WORD, WPARAM, LPARAM);
typedef VOID(CALLBACK* EVENTPROC)(LPROBOTINTERFACE, DWORD, WORD,WPARAM, LPARAM);

/**
 *
 * Structure containing heart-bit property
 * 
 */
typedef struct tagHEARTBITPROPERTY {
	BOOL invite;
	int period;
	int tolerance;
	int counter; // system reserved
} HEARTBITPROPERTY, FAR* PHEARTBITPROPERTY;

/**
 *
 * ASR Event Msg wParam
 * 
 */
#define VOICE_REC_START		0
#define VOICE_REC_STOP		1
#define VOICE_REC_NORMAL	2
#define VOICE_REC_UP		3
#define VOICE_REC_DOWN		4

/**
 *
 * Language type of TTS DB
 *
 */
#define VCLT_KOREAN			0x00
#define VCLT_ENGLISH		0x01


/**
 *
 * Navigation Direction
 * 
 */
#define NVFORWARD			1
#define NVBACKWARD			2
#define NVTURNLEFT			3
#define NVTURNRIGHT			4
#define NVSTOP				5

/**
 *
 * String
 * 
 */
typedef struct tagSTRINGTYPE {
	DWORD	dwLength;
	LPCTSTR	lpszBuffer;
} STRINGTYPE, FAR* LPSTRINGTYPE;

/**
 *
 * structure for ASR result
 * 
 */
typedef struct tagASRRESULT {
	STRINGTYPE	stRecWord;
	BYTE		cPrecision;
} ASRRESULT, FAR* LPASRRESULT;

/**
 *
 * structure for ASR result(extended)
 * 
 */
typedef struct tagASRRESULTEXT {
	WORD		wMode;
	LPCTSTR		lpszRobotName;
	LPCTSTR		lpszSpeakerName;
	INT			nDir;
} ASRRESULTEXT, FAR* LPASRRESULTEXT;

/**
 *
 * Rect Params
 * 
 */
typedef struct tagRECTPARAMS {
	DWORD	dwResultCode;
	int		nLeft;
	int		nTop;
	int		nRight;
	int		nBottom;
} RECTPARAMS, FAR* WRECTPARAMS;

/**
 *
 * Record Object Event Message
 * 
 */
typedef struct tagRECOBJECTEVENTMSGPARAMS {
	DWORD	dwResltCode;
	DWORD	dwLength;
	char	cObjID[128];	
} RECOBJECTEVENTMSGPARAMS, FAR* LPRECOBJECTEVENTMSGPARAMS;

/**
 *
 * Robot Location structure
 * 
 */
typedef struct tagROBOTLOC {
	int		nX;
	int		nY;
	float	fTheta;
	int		nPan;
	int		nTilt;
} ROBOTLOC, FAR* LPROBOTLOC;

/**
 *
 * LandMark structure
 * 
 */
typedef struct tagLANDMARK {
	int			nID;
	CHAR		szLabel[256];
	ROBOTLOC	stLocInfo;
} LANDMARK, FAR* LPLANDMARK;

/**
 *
 * Nearest landMark info.
 * 
 */
typedef struct tagLANDMARKNEAREST {
	int			nDistance;
	LANDMARK	stLandmark;
} LANDMARKNEAREST, FAR* LPLANDMARKNEAREST;

/**
 *
 * LandMark List Structure
 * 
 */
typedef struct tagLANDMARKLIST {
	int			nNumOfLandmarks;
	LPLANDMARK	lpLandmarks;
} LANDMARKLIST, FAR* LPLANDMARKLIST;

/**
 *
 * Battery Status Structure
 * 
 */
typedef struct tagBATTERYSTATUS {
	WORD		wFullChargeTime;
	WORD 		wRemainTime;
	BYTE 		cRemainPercents;
	DWORD 		dwStatus;
	DWORD 		dwDevice;
} BATTERYSTATUS, FAR* LPBATTERYSTATUS;

/**
 *
 * Move Wheel
 * 
 */
typedef struct tagWHEELACTIONPARAMS {
	WORD	wTemplateCode;
	WORD	wExecuteTime;
	WORD	wRepeatNum;
	SHORT	shAngle;
	SHORT	shDistance;
} WHEELACTIONPARAMS, FAR* LPWHEELACTIONPARAMS;

/**
 *
 * Move Head
 * 
 */
typedef struct tagHEADACTIONPARAMS {
	WORD	wTemplateCode;
	WORD	wPanExecuteTime;
	WORD	wPanRepeatNum;
	SHORT	shPanAngle;
	WORD	wTiltExecuteTime;
	WORD	wTiltRepeatNum;
	SHORT	shTiltAngle;
} HEADACTIONPARAMS, FAR* LPHEADACTIONPARAMS;

/**
 *
 * move head relatively
 *
 */
typedef struct tagHEADACTIONREL {
	double	dPanExecuteTime;
	SHORT	shPanAngle;
	double	dTiltExecuteTime;
	SHORT	shTiltAngle;
} HEADACTIONREL, FAR* LPHEADACTIONREL;

/**
 *
 * Move Arm
 * 
 */
typedef struct tagARMACTIONPARAMS {
	WORD	wTemplateCode;
	WORD	wLeftExecuteTime;
	WORD	wLeftRepeatNum;
	SHORT	shLeftAngle;
	WORD	wRightExecuteTime;
	WORD	wRightRepeatNum;
	SHORT	shRightAngle;
} ARMACTIONPARAMS, FAR* LPARMACTIONPARAMS;

/**
 *
 * LED
 * 
 */
typedef struct tagLEDACTIONPARAMS {
	WORD	wTemplateCode;
	WORD	wExecuteTime;
	WORD	wRepeatNum;
} LEDACTIONPARAMS, FAR* LPLEDACTIONPARAMS;

/**
 *
 * Camera Open Parameter
 * 
 */
typedef struct tagCAMERAOPENPARAMS {
	WORD	wShowPreview;
	HWND	hPreviewWindow;
	INT		nLeft;
	INT		nTop;
	INT		nWidth;
	INT		nHeight;
} CAMERAOPENPARAMS, FAR* LPCAMERAOPENPARAMS;

/**
 *
 * Camera Open Parameter(extended)
 * 
 */
typedef struct tagCAMERAOPENPARAMSEX {
	WORD	wShowPreview;
	HWND	hPreviewWindow;
	INT		nLeft;
	INT		nTop;
	INT		nWidth;
	INT		nHeight;
	WORD	wResolution;
	DWORD	dwReserved;
} CAMERAOPENPARAMSEX, FAR* LPCAMERAOPENPARAMSEX;

/**
 *
 * Video Record Parameter
 * 
 */
typedef struct tagVIDEORECPARAMS {
	LPCTSTR	lpszFileName;
	WORD	wAudioMixType;
} VIDEORECPARAMS, FAR* LPVIDEORECPARAMS;

/**
 *
 * Video Play Parameter
 * 
 */
typedef struct tagVIDEOPLAYPARAMS {
	LPCTSTR	lpszFileName;
	HWND	hWindow;
	INT		nLeft;
	INT		nTop;
	INT		nWidth;
	INT		nHeight;
} VIDEOPLAYPARAMS, FAR* LPVIDEOPLAYPARAMS;

/**
 *
 * Audio Record Parameter
 * 
 */
typedef struct tagAUDIORECPARAMS {
	LPCTSTR	lpszFileName;
	WORD	wSamplingRateType;
} AUDIORECPARAMS, FAR* LPAUDIORECPARAMS;

/**
 *
 * Audio Play Parameter
 * 
 */
typedef struct tagAUDIOPLAYPARAMS {
	LPCTSTR	lpszFileName;
} AUDIOPLAYPARAMS, FAR* LPAUDIOPLAYPARAMS;

/**
 *
 * Capture Image Parameter
 * 
 */
typedef struct tagCAPTUREIMAGEPARAMS {
	LPCTSTR	lpszFileName;
	WORD	wFormat;
} CAPTUREIMAGEPARAMS, FAR* LPCAPTUREIMAGEPARAMS;

/**
 *
 * Capture Image Period Parameter
 * 
 */
typedef struct tagCAPIMGPERIODPARAMS {
	INT		nPeriod;
	WORD	wResolution;
	WORD	wFormat;
} CAPIMGPERIODPARAMS, FAR* LPCAPIMGPERIODPARAMS;

/**
 *
 * Capture Image Result Parameter
 * 
 */
typedef struct tagCAPIMGRESULT {
	WORD	wResolution;
	WORD	wFormat;
	DWORD	dwFileLength;
	LPVOID	lpFileBuffer;
} CAPIMGRESULT, FAR* LPCAPIMGRESULT;

/**
 *
 * Express Face
 * 
 */
typedef enum {
	BHFE_BLANK			= 0x00,
	BHFE_HAPPINESS		= 0x01,
	BHFE_SURPRISE		= 0x02,
	BHFE_NORMAL			= 0x03,
	BHFE_DISAPPOINTMENT	= 0x04,
	BHFE_SHAME			= 0x05,
	BHFE_SPEAKING		= 0x06,
	BHFE_ASR_SUCCESS	= 0x07,
	BHFE_ASR_FAIL		= 0x08,
	BHFE_ASR_ONWAY		= 0x09,
	BHFE_POSITIVE		= 0x0a,
	BHFE_NEGATIVE		= 0x0b,
	BHFE_STARE_LDOWN	= 0x0c,
	BHFE_STARE_RDOWN	= 0x0d,
	BHFE_STARE_LUP		= 0x0e,
	BHFE_STARE_RUP		= 0x0f,
	BHFE_LIPSYNC_START	= 0x10,
	BHFE_LIPSYNC_STOP	= 0x11,
	BHFE_TURN_OFF_ALL   = 0x12,
	BHFE_SLEEPINESS		= 0x13,
	BHFE_IRRITABLE		= 0x21,		// only primary edition #3
	BHFE_HARDWAREERROR	= 0x31,		// only primary edition #3
	BHFE_CHARGEBATTERY	= 0x41,		// only primary edition #3
	BHFE_LACKBATTERY	= 0x42,		// only primary edition #3
	BHFE_DOINGTASK		= 0x43,		// only primary edition #3
	BHFE_COMPLETETASK	= 0x44		// only primary edition #3
} BH_FACETYPE;

/**
 *
 * Express Emotion
 * 
 */
typedef enum {
	BHET_HAPPINESS		= 1,
	BHET_SURPRISE		= 2,
	BHET_NORMAL			= 3,
	BHET_DISAPPOINMENT	= 4,
	BHET_SHAME			= 5
} BH_EMOTIONTYPE;

/**
 *
 * Play TTS
 * 
 */
typedef enum {
	VCST_KOR_ADULT			= 0x00,
	VCST_KOR_CHILD_NORMAL	= 0x01,
	VCST_KOR_CHILD_DIALOGUE	= 0x02,
	VCST_KOR_CHILD_STORY	= 0x03,
	VCST_ENG_ADULT			= 0x04,
	VCST_ENG_CHILD			= 0x05,
	VCST_CHN_ADULT			= 0x06,
	VCST_CHN_CHILD			= 0x07
} VC_SPEECHTYPE;

/**
 *
 * ASR Language Type
 * 
 */
typedef enum {
	VCRL_KOREAN		= 0x01,
	VCRL_ENGLISH	= 0x02,
	VCRL_CHINESE	= 0x03,
	VCRL_KORENG		= 0x10,
	VCRL_KORENGCHN	= 0x20
} VC_RECLANGTYPE;

/**
 *
 * ASR Device Type
 * 
 */
typedef enum {
	VCASRD_SRC_FROM_LINE_IN = 0x01,
	VCASRD_SRC_FROM_MIC_IN = 0x02
} VC_ASRDEVICE;

/**
 *
 * ASR mode
 *
 */
typedef enum {
	ASR_CONNECTED,
	ASR_ISOLATED
} ASR_MODE;

/**
 *
 * Remote Control BTN Parameters
 * 
 */
typedef struct tagREMOTECTRLBTNPARAMS{
	DWORD	dwButtonID;
	DWORD	dwStatus;
} REMOTECTRLBTNPARAMS, FAR* WREMOTECTRLBTNPARAMS;

/**
 *
 * Sonar Sensor Parameters
 * 
 */
typedef struct tagSONARSENSORPARAMS{
	DWORD	dwSonarID;
	FLOAT	fdistance;
} SONARSENSORPARAMS, FAR* WSONARSENSORPARAMS;

/**
 *
 * Touch Sensor Parameters
 * 
 */
typedef struct tagTOUCHSENSORPARAMS{
	DWORD	dwButtonID;
	DWORD	dwStatus;
} TOUCHSENSORPARAMS, FAR* WTOUCHSENSORPARAMS;

/**
 *
 * Docking Sensor Parameters
 * 
 */
typedef struct tagDOCKINGSENSORPARAMS{
	DWORD	dwDevice;
	DWORD	dwStatus;
} DOCKINGSENSORPARAMS, FAR* WDOCKINGSENSORPARAMS;

/**
 *
 * event of enforcement of motor
 *
 */
typedef struct tagMOTORENFORCEDPARAMS {
	DWORD	dwMotorID;
	DWORD	dwStatus;
	DWORD	dwValue;
} MOTORENFORCEDPARAMS, FAR* LPMOTORENFORCEDPARAMS;

/**
 *
 * LCD Touch event parameter
 *
 */
typedef struct tagLCDTOUCHPARAMS {
	DWORD	dwStatus;
	DWORD	dwReserved;
} LCDTOUCHPARAMS, FAR* LPLCDTOUCHPARAMS;

/**
 *
 * video preview
 * 
 */
typedef struct tagVIDEOPREVIEWPARAMS{
	HWND	hPreviewWindow;
	INT		nLeft;
	INT		nTop;
	INT		nWidth;
	INT		nHeight;
} VIDEOPREVIEWPARAMS, FAR* LPVIDEOPREVIEWPARAMS;

/**
 *
 * Allocating utility call back function 
 * 
 */
typedef BOOL (CALLBACK* APPENDANTPARSERPROC)(LPROBOTINTERFACE, LPCSTR, DWORD);

/**
 *
 * App Status Parameters
 *
 */
typedef struct tagAPPSTATUSPARAMS {
	WORD	wSvcAppID;
	DWORD	dwStatus;
} APPSTATUSPARAMS, FAR* LPAPPSTATUSPARAMS;

/**
 *
 * structure for the event inforamtion of a face recognition
 *
 */
typedef struct tagFACERECINFO {
	STRINGTYPE	stFaceID;
	RECT		stRegion;
} FACERECINFO, FAR* LPFACERECINFO;

/**
 *
 * structure for the face recognition event message
 *
 */
typedef struct tagFACERECINFO2 {
	LPCTSTR		lpszFaceID;
	RECT		stRegion;
	INT			nPanAngle;
	INT			nTiltAngle;
} FACERECINFO2, FAR* LPFACERECINFO2;

/**
 *
 * structure for the File Information of DiskAccess API
 *
 */
typedef struct tagFILEINFO {
	char		szFileName[260];
	DWORD		dwFileSize;
	BOOL		bIsFolder;
} FILEINFO, FAR* LPFILEINFO;

/**
 *
 * structure for the File List of DiskAccess API
 *
 */
typedef struct tagFILELIST {
	DWORD		dwNumOfFile;
	LPFILEINFO  pstFileInfo;
} FILELIST, FAR* LPFILELIST;

/**
 *
 * structure for the Disk Usage Information of DiskAccess API
 *
 */
typedef struct tagDISKUSE {
	DWORD		dwDiskUsage;
	DWORD		dwDiskAvail;
} DISKUSE, FAR* LPDISKUSE;

/**
 *
 * structure for expression of time
 *
 */
typedef struct tagDATEPARAMS {
	int		nYear;
	int		nMonth;
	int		nDay;
	int		nHour;
	int		nMinute;
	int		nSecond;
} DATEPARAMS, FAR* LPDATEPARAMS;

/**
 *
 * structure for robot profile
 *
 */
typedef struct tagROBOTPROFILE {
	LPCTSTR			lpszName;
	LPCTSTR			lpszAddress;
	LPDATEPARAMS	lpLastSavedDate;
	LPCTSTR			lpszSWVersion;
	LPDATEPARAMS	lpSWDate;
	LPCTSTR			lpszHWVersion;
	LPDATEPARAMS	lpHWDate;
} ROBOTPROFILE, FAR* LPROBOTPROFILE;

/**
 *
 * structure for user information
 *
 */
typedef struct tagUSERINFO {
	INT				nID;
	LPCTSTR			lpszName;
	LPCTSTR			lpszClass;
} USERINFO, FAR* LPUSERINFO;

/**
 *
 * structure for schedule information
 *
 */
typedef struct tagSCHEDULEINFO {
	INT				nID;
	LPCTSTR			lpszTitle;
	BOOL			bNotified;
	BOOL			bExecuted;
	WORD			wService;
	LPDATEPARAMS	lpExecuteTime;
	LPCTSTR			lpszPlace;
	LPCTSTR			lpszSound;
	LPCTSTR			lpszRepeat;
} SCHEDULEINFO, FAR* LPSCHEDULEINFO;

/**
 *
 * structure for mixed motion
 *
 */
typedef struct tagMIXEDMOTION {
	WORD		wTemplateCode;
	WORD 		wRepeatNum;
} MIXEDMOTION, FAR* LPMIXEDMOTION;

/**
 *
 * structure for reservation of clean
 *
 */
typedef struct tagRESERVECLEAN {
	LPDATEPARAMS	lpDateParams;
	WORD			wCourseType;
	INT 			nDuration;
} RESERVECLEAN, FAR* LPRESERVECLEAN;

/**
 *
 * structure for memo info
 *
 */
typedef struct tagMEMOINFO {
	INT				nID;
	BOOL			bVerified;
	LPCTSTR			lpszReceiver;
	LPCTSTR			lpszTitle;
	LPDATEPARAMS	lpRecordTime;
	LPCTSTR			lpszFileName;
	LPCTSTR			lpszSender;
} MEMOINFO, FAR* LPMEMOINFO;

/**
 *
 * structure for map building event message
 *
 */
typedef struct tagMAPBUILDPARAMS {
	INT 			nAddProjector;
	INT 			nFindDoorSill;
} MAPBUILDPARAMS, FAR* LPMAPBUILDPARAMS;

/**
 *
 * structure for charging by navigation
 *
 */
typedef struct tagNAVICHARGEPARAMS {
	DWORD			dwStatus;
} NAVICHARGEPARAMS, FAR* LPNAVICHARGEPARAMS;

/**
 *
 * structure for saving image by vision engine
 *
 */
typedef struct tagSAVEIMAGEPARAMS {
	WORD		wResolution;
	WORD		wFormat;
	LPCTSTR		lpszFileName;
} SAVEIMAGEPARAMS, FAR* LPSAVEIMAGEPARAMS;

/**
 *
 * structure for information of authentication to server
 *
 */
typedef struct tagAUTHENTICATIONINFO {
	LPCTSTR		lpszRobotId;
	LPCTSTR		lpszSessionKey;
} AUTHENTICATIONINFO, FAR* LPAUTHENTICATIONINFO;

/**
 *
 * structure for volume of channel
 *
 */
typedef struct tagCHANNELVOLUME {
	int			nChannel;
	int 		nLevel;
} CHANNELVOLUME, FAR* LPCHANNELVOLUME;


/**
 *
 * Serving interface
 *
 */

/**
 *
 * structure for parameter of serving robot's arm contorl
 *
 */
typedef struct tagSERVING_ARM_CONTROL {
	WORD		wTemplateCode;
	DWORD		dwPositionID;
	BOOL		bReturn;
} SERVING_ARM_CONTROL, FAR* LP_SERVING_ARM_CONTROL;

/**
 *
 * customer information
 *
 */
typedef struct tagSERVING_CUSTOMER_INFO {
	BOOL		bMember;
	LPCTSTR		lpszKeyNumber;
	LPCTSTR		lpszName;
	LPCTSTR		lpszPhoneNumber;
	LPCTSTR		lpszBirthday;
	int			nVisitCounter;
} SERVING_CUSTOMER_INFO, FAR* LP_SERVING_CUSTOMER_INFO;

/**
 *
 * food info
 *
 */
typedef struct tagSERVING_FOOD_INFO {
	LPCTSTR		lpszFoodCode;
	int			nQuantity;
} SERVING_FOOD_INFO, FAR* LP_SERVING_FOOD_INFO;

/**
 *
 * order information
 *
 */
typedef struct tagSERVING_ORDER_INFO {
	int			nMembers;
	LPCTSTR		lpszTableCode;
	LPCTSTR		lpszTime;
	BOOL		bOrdered;
	int			nNumberOfFood;
	LP_SERVING_FOOD_INFO	pstFoodInfo;
} SERVING_ORDER_INFO, FAR* LP_SERVING_ORDER_INFO;

/**
 *
 * reservation information
 *
 */
typedef struct tagSERVING_RESERVATION_INFO {
	int			bReserved;
	LPCTSTR		lpszDate;
	int			nMembers;
	LPCTSTR		lpszTableCode;
	BOOL		bOrdered;
	int			nNumberOfFood;
	LP_SERVING_FOOD_INFO	pstFoodInfo;
} SERVING_RESERVATION_INFO, FAR* LP_SERVING_RESERVATION_INFO;

/**
 *
 * table info
 *
 */
typedef struct tagSERVING_TABLE_INFO {
	LPCTSTR		lpszTableCode;
	int			nCapacity;
	BOOL		bAvailable;
	int			nOccupied;
	LPCTSTR		lpszID;
} SERVING_TABLE_INFO, FAR* LP_SERVING_TABLE_INFO;

/**
 *
 * table status of store
 *
 */
typedef struct tagSERVING_TABLE_STATUS {
	int			nNumberOfTables;
	LP_SERVING_TABLE_INFO	pstTableInfo;
} SERVING_TABLE_STATUS, FAR* LP_SERVING_TABLE_STATUS;

/**
 *
 * table info
 *
 */
typedef struct tagSERVING_WAITING_CUSTOMER {
	int			nRank;
	LPCTSTR		lpszID;
	LPCTSTR		lpszTime;
} SERVING_WAITING_CUSTOMER, FAR* LP_SERVING_WAITING_CUSTOMER;

/**
 *
 * waiting list
 *
 */
typedef struct tagSERVING_WAITING_LIST {
	int			nWaitingList;
	LP_SERVING_WAITING_CUSTOMER	pstWaitingCustomer;
} SERVING_WAITING_LIST, FAR* LP_SERVING_WAITING_LIST;

/**
 *
 * call
 *
 */
typedef struct tagSERVING_CALL {
	LPCTSTR		lpszTableCode;
	DWORD		dwCallType;
	DWORD		dwReserved;
} SERVING_CALL, FAR* LP_SERVING_CALL;

/**
 *
 * hardware status code
 *
 */
#define HWSC_NO_ERROR						0x00000000
#define HWSC_FAIL_INIT_MOTOR_LWHEEL			0x00000001
#define HWSC_FAIL_INIT_MOTOR_RWHEEL			0x00000002
#define HWSC_FAIL_INIT_MOTOR_PHEAD			0x00000004
#define HWSC_FAIL_INIT_MOTOR_THEAD			0x00000008
#define HWSC_FAIL_INIT_MOTOR_RARM			0x00000010
#define HWSC_FAIL_INIT_MOTOR_LARM			0x00000020
#define HWSC_FAIL_OPEN_PORT_CONTROLLER		0x00000100
#define HWSC_FAIL_OPEN_PORT_REMOCON			0x00000200

/**
 *
 * recognized speaker info
 *
 */
typedef struct tagSPEAKERRESULT {
	LPCTSTR		lpszSpeakerName;
	WORD		wDirection;
} SPEAKERRESULT, FAR* LPSPEAKERRESULT;

/**
 *
 * human following features
 *
 */
typedef enum {
	HFF_FACE = 0,
	HFF_GESTURE,
	HFF_BODY
} FOLLOWING_FEATURE;

/**
 *
 * ASR channel type
 *
 */
typedef enum {
   LEFT_CHANNEL = 0,
   RIGHT_CHANNEL 
} VC_ASR_CHANNEL;

/**
 *
 * ASR application type
 *
 */
typedef enum {
	ASR_NONE = 0x0000,
    ASR_NAMECALL = 0x0004,
    ASR_SPEAKER = 0x0008,
    ASR_DIR = 0x0010
} VC_ASR_APP; 

/**
 *
 * structure for hunman(motion) detection information
 *
 */
typedef struct tagHUMANDETECTINFO {
	RECT		stRegion;
	int			nPanAngle;
	int			nTiltAngle;
} HUMANDETECTINFO, FAR* LPHUMANDETECTINFO;

/**
 *
 * structure for hand detection information
 *
 */
typedef struct tagHANDDETECTINFO {
	RECT		stRegion;
	int			nPanAngle;
	int			nTiltAngle;
} HANDDETECTINFO, FAR* LPHANDDETECTINFO;

/**
 *
 * structure for face detection information
 *
 */
typedef struct tagFACEDETECTINFO {
	RECT		stRegion;
	int			nPanAngle;
	int			nTiltAngle;
} FACEDETECTINFO, FAR* LPFACEDETECTINFO;

/**
 *
 * structure for distance to obstacle
 *
 */
typedef struct tagOBSTACLE_DISTANCE {
	DWORD		dwDirection;
	DWORD		dwDistance;
} OBSTACLE_DISTANCE, FAR* LP_OBSTACLE_DISTANCE;

/**
 *
 * structure containing information of obstacle estimation
 *
 */
typedef struct tagOBSTACLE_ESTIMATION {
	DWORD 		dwDirection;
	DWORD		dwSample;
	DWORD		dwFrequency;
	DWORD		dwDistance;
} OBSTACLE_ESTIMATION, FAR* LP_OBSTACLE_ESTIMATION;

/**
 *
 * structure for vision detection information
 *
 */
typedef struct tagVISIONDETECTINFO {
	RECT		stRegion;
	int			nPanAngle;
	int			nTiltAngle;
} VISIONDETECTINFO, FAR* LPVISIONDETECTINFO;

/**
 *
 * structure containing information of recognition
 *
 */
typedef struct tagRECOGNITION_INFO {
	LPCTSTR		lpszName;
	DWORD		dwScore;
} RECOGNITION_INFO, FAR* LP_RECOGNITION_INFO;

/**
 *
 * structure containing list of recognition information
 *
 */
typedef struct tagRECOGNITION_LIST {
	DWORD		dwCount;
	LP_RECOGNITION_INFO		pRecInfo;
} RECOGNITION_LIST, FAR* LP_RECOGNITION_LIST;

/**
 *
 * structure for vision recognition information
 *
 */
typedef struct tagVISION_REC_INFO {
	LPVISIONDETECTINFO		pDetectInfo;
	LP_RECOGNITION_LIST		pRecList;
} VISION_REC_INFO, FAR* LP_VISION_REC_INFO;

/**
 *
 * structure for head position
 *
 */
typedef struct tagHEADPOS {
	int			nPanAngle;
	int			nTiltAngle;
} HEADPOS, FAR* LPHEADPOS;

/**
 *
 * LIST_TYPE structure
 *
 */
typedef struct tagLIST_TYPE {
	int			nItem;
	LPCTSTR		lpszBuffer;
} LIST_TYPE, FAR* LP_LIST_TYPE;

/**
 *
 * SYSDIRINFO structure
 *
 */
typedef struct tagSYSDIRINFO {
	DWORD		dwDirectory;
	LPCTSTR		lpszPathName;
} SYSDIRINFO, FAR* LPSYSDIRINFO;

/**
 *
 * LANGUAGE_TYPE structure
 *
 */
typedef struct tagLANGUAGEINFO {
	DWORD		dwLanguage;
	DWORD		dwReserved;
} LANGUAGEINFO, FAR* LPLANGUAGEINFO;

/**
 *
 * NETWORK_CONFIGURATION structure
 *
 */
typedef struct tagNETWORK_CONFIGURATION {
	LPCTSTR lpszDeviceName;
	BOOL	bDHCPEnabled;
	LPCTSTR	lpszIPAddress;
	LPCTSTR	lpszDefaultIPGateway;
	LPCTSTR	lpszMacAddress;
	int		nConnectStatus;
	LPCTSTR	lpszSsid;
	int		nStrength;
} NETWORK_CONFIGURATION, FAR* LP_NETWORK_CONFIGURATION;

/**
 *
 * ASRWORDINFO structure
 *
 */
typedef struct tagASRWORDINFO {
	DWORD		dwType;
	LPCTSTR		lpszWordList;
} ASRWORDINFO, FAR* LPASRWORDINFO;

/**
 *
 * WHEEL_VELOCITY structure
 *
 */
typedef struct tagWHEEL_VELOCITY {
	DWORD		dwLeft;
	DWORD		dwRight;
	DWORD		dwReserved;
} WHEEL_VELOCITY, FAR* LP_WHEEL_VELOCITY;

#endif // __YJROBOTDEF_H__
