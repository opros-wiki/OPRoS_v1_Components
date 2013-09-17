/**
 * 
 * \file taskdef.h
 *
 * \brief
 *  task ID definition
 *
 * Tested Environments :
 *  C, VC++6.0, Win32
 * 
 * \warning
 *
 * \author 
 *  Choe, Yeongil( yichoe@yujinrobot.com )
 * 
 * \date
 *  - 2006-02-02, Choe, Yeongil, Create
 * 
 * \see
 * 
 * Copyright(C) 2006 YUJIN ROBOTICS CO., LTD.
 *
 */

#ifndef __RSDK_TASKDEF_H__
#define __RSDK_TASKDEF_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef DWORD TASKID;


/**
 *
 * Robot Behaviors
 *
 */

//! request wheel control
const static TASKID		TASK_BH_WHEEL						= 0x00010011;

//! request head control
const static TASKID		TASK_BH_HEAD						= 0x00010021;

//! request head relative control
const static TASKID		TASK_BH_HEAD_REL					= 0x00010022;

//! request of head position
const static TASKID		TASK_BH_HEAD_POSITION				= 0x00010023;

//! request arm control
const static TASKID		TASK_BH_ARM							= 0x00010031;

//! request LED control
const static TASKID		TASK_BH_LED							= 0x00010041;

//! request face expression
const static TASKID		TASK_BH_FACEPPT						= 0x00010051;

//! request face expression(extended)
const static TASKID		TASK_BH_FACEEXPRESS_EX				= 0x00010052;

//! request mixed motion
const static TASKID		TASK_BH_MIXEDMOTION					= 0x00010061;

//! request stop action
const static TASKID		TASK_BH_STOPMOTION					= 0x00010101;

//! request emotion expression
const static TASKID		TASK_BH_EMOTIONPPT					= 0x00010111;	// obsoleted

//! set emotion
const static TASKID		TASK_BH_SET_EMOTION					= 0x00010112;

//! get emotion
const static TASKID		TASK_BH_GET_EMOTION					= 0x00010113;

//! turn on clean robot
const static TASKID		TASK_BH_CLEBO_TURN_ON				= 0x00011011;

//! turn off clean robot
const static TASKID		TASK_BH_CLEBO_TURN_OFF				= 0x00011012;

//! start clean
const static TASKID		TASK_BH_CLEBO_START					= 0x00011013;

//! stop clear
const static TASKID		TASK_BH_CLEBO_STOP					= 0x00011014;

//! set cleaning course
const static TASKID		TASK_BH_CLEBO_COURSE				= 0x00011015;

//! set cleaning period
const static TASKID		TASK_BH_CLEBO_DURATION				= 0x00011016;

//! reserve cleaning time
const static TASKID		TASK_BH_CLEBO_RESERVATION			= 0x00011017;

//! set LCD power
const static TASKID		TASK_BH_LCD_TURN					= 0x00010201;

//! set power save type
const static TASKID		TASK_BH_SET_POWER_SAVE_MODE			= 0x00010202;

//! set motor torque
const static TASKID		TASK_BH_SET_MOTOR_TORQUE			= 0x00010203;

//! arm control for serve
const static TASKID		TASK_BH_SERVING_ARM_CONTROL			= 0x00011031;


/**
 *
 * Voice Interfaces
 *
 */

//! load TTS DB
const static TASKID		TASK_VC_LOAD_TTS					= 0x00110001;

//! unload TTS DB
const static TASKID		TASK_VC_UNLOAD_TTS					= 0x00110002;

//! start TTS
const static TASKID		TASK_VC_TTS_START					= 0x00110011;

//! stop TTS
const static TASKID		TASK_VC_TTS_STOP					= 0x00110012;

//! pause TTS
const static TASKID		TASK_VC_TTS_PAUSE					= 0x00110013;

//! resume TTS
const static TASKID		TASK_VC_TTS_RESUME					= 0x00110014;

//! calculate TTS time
const static TASKID		TASK_VC_CALCUALTE_TTS				= 0x00110015;

//! play TTS DB
const static TASKID		TASK_VC_DB_TTS						= 0x00110021;

//! start ASR
const static TASKID		TASK_VC_ASR_START					= 0x00110081;

//! stop ASR
const static TASKID		TASK_VC_ASR_STOP					= 0x00110082;

//! register recognition word
const static TASKID		TASK_VC_ASR_REGWORD					= 0x00110083;

//! register recognition word by language
const static TASKID		TASK_VC_ASR_REGWORD_EXT				= 0x00110087;

//! delete recognition word
const static TASKID		TASK_VC_ASR_DELWORD					= 0x00110084;

//! reset recognition word
const static TASKID		TASK_VC_ASR_RESETWORD				= 0x00110085;

//! start ASR(Extended)
const static TASKID		TASK_VC_ASR_START_EXT				= 0x00110086;


//! register word for the speaker dependent mode
const static TASKID		TASK_VC_ASR_REGWORD_SPEAKER			= 0x00110088;

//! unregister word for the speaker dependent mode
const static TASKID		TASK_VC_ASR_UNREGWORD_SPEAKER		= 0x00110089;

//! obtain registered words
const static TASKID		TASK_VC_ASR_REGISTERED_WORD			= 0x0011008a;


//! change event of ASR word
const static TASKID		TASK_VC_ASR_E_CHANGE_WORD			= 0x0011008b;

//! set ASR model
const static TASKID		TASK_VC_ASR_SET_MODEL				= 0x0011008c;

//! get ASR model
const static TASKID		TASK_VC_ASR_GET_MODEL				= 0x0011008d;

//! get ASR word
const static TASKID		TASK_VC_ASR_GET_ASR_WORD			= 0x0011008f;


//! add category
const static TASKID		TASK_VC_ASR_ADD_CATEGORY			= 0x00110091;

//! delete category
const static TASKID		TASK_VC_ASR_DEL_CATEGORY			= 0x00110092;

//! add connected word
const static TASKID		TASK_VC_ASR_ADD_CON_WORD			= 0x00110093;

//! delete connected word
const static TASKID		TASK_VC_ASR_DEL_CON_WORD			= 0x00110094;

//! start name recognition
const static TASKID		TASK_VC_ASR_START_NAME				= 0x001100a1;

//! stop name recognition
const static TASKID		TASK_VC_ASR_STOP_NAME				= 0x001100a2;

//! add name
const static TASKID		TASK_VC_ASR_ADD_NAME				= 0x001100a3;

//! delete name
const static TASKID		TASK_VC_ASR_DEL_NAME				= 0x001100a4;


//! register name for the speaker dependent mode
const static TASKID		TASK_VC_ASR_REGNAME_SPEAKER			= 0x001100a5;

//! unregister name for the speaker dependent mode
const static TASKID		TASK_VC_ASR_UNREGNAME_SPEAKER		= 0x001100a6;

//! obtain registered names
const static TASKID		TASK_VC_ASR_REGISTERED_NAME			= 0x001100a7;


//! set mode for ASR
const static TASKID		TASK_VC_ASR_SET_MODE				= 0x00110203;

//! set sensitivity for ASR
const static TASKID		TASK_VC_ASR_SET_SENSITIVITY			= 0x00110204;

//! set ASR channel
const static TASKID		TASK_VC_ASR_SET_CHANNEL				= 0x00110205;

//! select language for recognition
const static TASKID		TASK_VC_ASR_SETLANG					= 0x00110201;

//! select device for recognition
const static TASKID		TASK_VC_ASR_SETDEVICE				= 0x00110202;


//! start detection of clapping
const static TASKID		TASK_VC_CLAP_DETECT_START			= 0x00110071;

//! stop detection of clapping
const static TASKID		TASK_VC_CLAP_DETECT_STOP			= 0x00110072;


//! start speaker recognition
const static TASKID		TASK_VC_SPEAKER_REC_START			= 0x001100b1;

//! stop speaker recognition
const static TASKID		TASK_VC_SPEAKER_REC_STOP			= 0x001100b2;

//! add speaker
const static TASKID		TASK_VC_SPEAKER_REG					= 0x001100b3;

//! delete speaker
const static TASKID		TASK_VC_SPEAKER_DEL					= 0x001100b4;


//! start sound source localization
const static TASKID		TASK_VC_SSL_START					= 0x001100c1;

//! stop sound source localization
const static TASKID		TASK_VC_SSL_STOP					= 0x001100c2;

/**
 *
 * Visual Interfaces
 *
 */

//! resume vision service
const static TASKID		TASK_VS_RESUME						= 0x01011001;

//! suspend vision service
const static TASKID		TASK_VS_SUSPEND						= 0x01011002;

//! start motion detection
const static TASKID		TASK_VS_HUMAN_DETECT_START			= 0x01010011;	// obsoleted

//! stop motion detection
const static TASKID		TASK_VS_HUMAN_DETECT_STOP			= 0x01010012;	// obsoleted

//! start motion detection
const static TASKID		TASK_VS_MOTION_DETECT_START			= 0x01010011;

//! stop motion detection
const static TASKID		TASK_VS_MOTION_DETECT_STOP			= 0x01010012;

//! start hand(gesture) detection
const static TASKID		TASK_VS_HAND_DETECT_START			= 0x01010021;

//! stop (gesture) detection
const static TASKID		TASK_VS_HAND_DETECT_STOP			= 0x01010022;

//! start face detection
const static TASKID		TASK_VS_FACE_DETECT_START			= 0x01010031;

//! stop face detection
const static TASKID		TASK_VS_FACE_DETECT_STOP			= 0x01010032;

//! start face recognition
const static TASKID		TASK_VS_FACE_REC_START				= 0x010100C1;

//! stop face recognition
const static TASKID		TASK_VS_FACE_REC_STOP				= 0x010100C2;

//! register face
const static TASKID		TASK_VS_FACE_REG					= 0x01010033;

//! delete face
const static TASKID		TASK_VS_FACE_DEL					= 0x01010034;

//! request start of starring
const static TASKID		TASK_VS_FACE_STARE_START			= 0x01010038;

//! stop starring
const static TASKID		TASK_VS_FACE_STARE_STOP				= 0x01010039;

//! start detection of human shape
const static TASKID		TASK_VS_HUMAN_SHAPE_DETECT_START	= 0x01010061;

//! start detection of human shape
const static TASKID		TASK_VS_HUMAN_SHAPE_DETECT_STOP		= 0x01010062;

//! start body tracking
const static TASKID		TASK_VS_BODY_TRACKING_START			= 0x01010071;

//! stop body tracking
const static TASKID		TASK_VS_BODY_TRACKING_STOP			= 0x01010072;

//! start face tracking
const static TASKID		TASK_VS_FACE_TRACKING_START			= 0x01010081;

//! stop face tracking
const static TASKID		TASK_VS_FACE_TRACKING_STOP			= 0x01010082;

//! start object detection
const static TASKID		TASK_VS_OBJ_DETECT_START			= 0x01010041;

//! stop object detection
const static TASKID		TASK_VS_OBJ_DETECT_STOP				= 0x01010042;

//! register object
const static TASKID		TASK_VS_OBJ_REG						= 0x01010043;

//! delete object
const static TASKID		TASK_VS_OBJ_DEL						= 0x01010044;

//! refresh object DB
const static TASKID		TASK_VS_OBJ_FLUSH					= 0x01010045;

//! configuration object
const static TASKID		TASK_VS_OBJ_CFG						= 0x01010048;

//! start caller detection
const static TASKID		TASK_VS_CALLER_DETECT_START			= 0x01010211;

//! stop caller detection
const static TASKID		TASK_VS_CALLER_DETECT_STOP			= 0x01010212;

//! start human following
const static TASKID		TASK_VS_HUMAN_FOLLOW_START			= 0x01010221;

//! stop human following
const static TASKID		TASK_VS_HUMAN_FOLLOW_STOP			= 0x01010222;

//! register object
const static TASKID		TASK_VS_START_VIDEO_RENDER			= 0x01010101;

//! delete object
const static TASKID		TASK_VS_STOP_VIDEO_RENDER			= 0x01010102;

//! save image
const static TASKID		TASK_VS_SAVE_IMAGE					= 0x01010103;

//! configuration object
const static TASKID		TASK_VS_RELEASE_CAMERA				= 0x0101f001;


/**
 *
 * Navigation Interfaces
 *
 */

//! set maximum velocity
const static TASKID		TASK_NV_SET_MAX_VELOCITY			= 0x00810101;

//! get maximum velocity
const static TASKID		TASK_NV_REQ_MAX_VELOCITY			= 0x00810102;

//! obstacle avoidance mode
const static TASKID		TASK_NV_OBSTACLE_AVOIDANCE			= 0x00810103;

//! navigation timeout
const static TASKID		TASK_NV_TIME_LIMIT					= 0x00810104;

//! get velocity of wheel
const static TASKID		TASK_NV_GET_WHEEL_VELOCITY			= 0x00810105;


//! go to landmark ID
const static TASKID		TASK_NV_GOTO_ID						= 0x00810011;

//! go to landmark label
const static TASKID		TASK_NV_GOTO_LABEL					= 0x00810012;

//! go to specific X, Y, theta
const static TASKID		TASK_NV_GOTO_XY						= 0x00810013;

//! go to landmark ID(extended)
const static TASKID		TASK_NV_GOTO_ID_EX					= 0x00810014;

//! go to landmark label(extended)
const static TASKID		TASK_NV_GOTO_LABEL_EX				= 0x00810015;

//! go to coordinates(extended)
const static TASKID		TASK_NV_GOTO_XY_EX					= 0x00810016;


//! start reporting of robot location
const static TASKID		TASK_NV_LOC_START					= 0x00810021;

//! stop reporting of robot location
const static TASKID		TASK_NV_LOC_STOP					= 0x00810022;

//! request landmark info.
const static TASKID		TASK_NV_LANDMARK					= 0x00810023;

//! request landmark list info.
const static TASKID		TASK_NV_LANDMARKLIST				= 0x00810024;

//! request landmark list string
const static TASKID		TASK_NV_LANDMARKLISTSTRING			= 0x00810028;

//! add landmark
const static TASKID		TASK_NV_ADD_LANDMARK				= 0x00810025;

//! delete landmark
const static TASKID		TASK_NV_DEL_LANDMARK				= 0x00810026;

//! configuration landmark
const static TASKID		TASK_NV_CFG_LANDMARK				= 0x00810027;

//! request nearest landmark
const static TASKID		TASK_NV_LANDMARK_NEAREST			= 0x00810029;


//! start move
const static TASKID		TASK_NV_MOVE_START					= 0x00810031;

//! stop move
const static TASKID		TASK_NV_MOVE_STOP					= 0x00810032;

//! start move(extended)
const static TASKID		TASK_NV_MOVE_START_EX				= 0x00810033;


//! start map building
const static TASKID		TASK_NV_MAPBUILD_START				= 0x00810041;

//! stop map building
const static TASKID		TASK_NV_MAPBUILD_STOP				= 0x00810042;

//! initialize map
const static TASKID		TASK_NV_INITIALIZE_MAP				= 0x00810043;


//! camera position control
const static TASKID		TASK_NV_DIR_CAMERA					= 0x00810051;


//! request calibration
const static TASKID		TASK_NV_REQ_CALIBRATION				= 0x00810061;


//! set navigation device
const static TASKID		TASK_NV_SET_NAVIGATION_DEVICE		= 0x00810071;


//! auto-charging event
const static TASKID		TASK_NV_E_NAVI_CHARGE				= 0x00810081;

//! obstacle event
const static TASKID		TASK_NV_E_OBSTACLE					= 0x00810082;

//! navigation global error event
const static TASKID		TASK_NV_E_GLOBAL_ERROR				= 0x00810083;


//! distance to obstable
const static TASKID		TASK_NV_OBSTACLE_DISTANCE			= 0x00810201;

//! estimate to locate in specific region
const static TASKID		TASK_NV_ESTIMATE_REGION				= 0x00810202;


//! start estimation of obstacle using sonar
const static TASKID		TASK_NV_ESTIMATE_OBSTACLE_START		= 0x00810211;

//! stop estimation of obstacle using sonar
const static TASKID		TASK_NV_ESTIMATE_OBSTACLE_STOP		= 0x00810212;


/**
 *
 * Robot Information Services
 *
 */

//! battery info.
const static TASKID		TASK_RI_HW_BATTERY					= 0x00080011;

//! hardware status info
const static TASKID		TASK_RI_HW_STATUS					= 0x00080016;

//! set HW event filter
const static TASKID		TASK_RI_SET_HW_EVENT_FILTER			= 0x00080071;

//! start RFID scanning
const static TASKID		TASK_RI_START_SCAN_RFID				= 0x00081011;

//! stop RFID scanning
const static TASKID		TASK_RI_STOP_SCAN_RFID				= 0x00081012;


//! remocon button event
const static TASKID		TASK_RI_HW_E_REMOCON				= 0x00080081;

//! remocon button event(emergency stop)
const static TASKID		TASK_RI_HW_E_REMOCON_EMG			= 0x00080082;	

//! touch sensor event
const static TASKID		TASK_RI_HW_E_TOUCH					= 0x00080083;	

//! touch sensor event(power off)
const static TASKID		TASK_RI_HW_E_TOUCH_POW				= 0x00080084;	

//! sonar sensor event
const static TASKID		TASK_RI_HW_E_SONAR					= 0x00080085;	

//! front proximity IR sensor event
const static TASKID		TASK_RI_HW_E_PRXIR					= 0x00080086;	

//! bottom sensor event
const static TASKID		TASK_RI_HW_E_BOTTOM					= 0x00080087;	

//! bumper sensor event
const static TASKID		TASK_RI_HW_E_BUMPER					= 0x00080088;	

//! docking sensor event
const static TASKID		TASK_RI_HW_E_DOCK					= 0x00080089;	

//! enforcement of motor externally
const static TASKID		TASK_RI_HW_E_MOTOR_ENFORCED			= 0x0008008c;

//! LCD touch event
const static TASKID		TASK_RI_HW_E_LCD_TOUCH				= 0x0008008d;

//! rear proximity IR sensor event
const static TASKID		TASK_RI_HW_E_PRXIR_REAR				= 0x0008008e;


//! emergency stop button event
const static TASKID		TASK_RI_HW_E_BTN_EMG				= 0x00081081;


//! set sound volume
const static TASKID		TASK_RI_HW_VOLUME					= 0x00080021;

//! request sound volume level
const static TASKID		TASK_RI_HW_REQ_VOLUME				= 0x00080022;

//! set sound mute
const static TASKID		TASK_RI_HW_MUTE						= 0x00080023;

//! set audio player to mute each channel
const static TASKID		TASK_RI_SET_AUDIO_PLAYER_MUTE		= 0x00080024;

//! set volume of audio recorder
const static TASKID		TASK_RI_SET_AUDIO_RECORD_VOLUME		= 0x00080025;

//! request volume of audio recorder
const static TASKID		TASK_RI_GET_AUDIO_RECORD_VOLUME		= 0x00080026;

//! set control parameters of audio recorder
const static TASKID		TASK_RI_SET_AUDIO_RECORD_CONTROL	= 0x00080027;

//! set volume of audio player
const static TASKID		TASK_RI_SET_AUDIO_PLAYER_VOLUME		= 0x00080028;

//! request volume of audio player
const static TASKID		TASK_RI_GET_AUDIO_PLAYER_VOLUME		= 0x00080029;

//! open camera
const static TASKID		TASK_RI_OPEN_CAMERA					= 0x00080061;

//! open camera(extended)
const static TASKID		TASK_RI_OPEN_CAMERA_EX				= 0x00080063;

//! close camera
const static TASKID		TASK_RI_CLOSE_CAMERA				= 0x00080062;

//! start video recording
const static TASKID		TASK_RI_START_REC_VIDEO				= 0x00080031;

//! end video recording
const static TASKID		TASK_RI_STOP_REC_VIDEO				= 0x00080032;

//! start of playing video
const static TASKID		TASK_RI_START_PLAY_VIDEO			= 0x00080033;

//! end of playing video
const static TASKID		TASK_RI_STOP_PLAY_VIDEO				= 0x00080034;

//! start audio recording
const static TASKID		TASK_RI_START_REC_AUDIO				= 0x00080041;

//! end audio recording
const static TASKID		TASK_RI_STOP_REC_AUDIO				= 0x00080042;

//! start audio playing
const static TASKID		TASK_RI_START_PLAY_AUDIO			= 0x00080043;

//! end audio playing
const static TASKID		TASK_RI_STOP_PLAY_AUDIO				= 0x00080044;

//! capture image
const static TASKID		TASK_RI_CAPTURE_IMAGE				= 0x00080051;

//! start periodic capture of image
const static TASKID		TASK_RI_START_CAPIMG_PERIOD			= 0x00080052;

//! stop periodic capture of image
const static TASKID		TASK_RI_STOP_CAPIMG_PERIOD			= 0x00080053;

//! request robot profile
const static TASKID		TASK_RI_REQ_ROBOTPROFILE			= 0x00080201;

//! update robot profile
const static TASKID		TASK_RI_UPDATE_ROBOTPROFILE			= 0x00080202;

//! request string of user info list
const static TASKID		TASK_RI_REQ_USERINFOLISTSTRING		= 0x00080211;

//! add user info
const static TASKID		TASK_RI_ADD_USERINFO				= 0x00080212;

//! delete user info
const static TASKID		TASK_RI_DELETE_USERINFO				= 0x00080213;

//! update user info
const static TASKID		TASK_RI_UPDATE_USERINFO				= 0x00080214;

//! request string of schedule info list
const static TASKID		TASK_RI_REQ_SCHEDULEINFOLISTSTRING	= 0x00080221;

//! add schedule info
const static TASKID		TASK_RI_ADD_SCHEDULEINFO			= 0x00080222;

//! delete schedule info
const static TASKID		TASK_RI_DELETE_SCHEDULEINFO			= 0x00080223;

//! update schedule info
const static TASKID		TASK_RI_UPDATE_SCHEDULEINFO			= 0x00080224;

//! request string of memo info list
const static TASKID		TASK_RI_REQ_MEMOINFOLISTSTRING		= 0x00080231;

//! add memo info
const static TASKID		TASK_RI_ADD_MEMOINFO				= 0x00080232;

//! delete memo info
const static TASKID		TASK_RI_DELETE_MEMOINFO				= 0x00080233;

//! update schedule info
const static TASKID		TASK_RI_UPDATE_MEMOINFO				= 0x00080234;

//! save service configuration value
const static TASKID		TASK_RI_SAVE_SVC_CFG				= 0x000802f1;

//! load service configuration value
const static TASKID		TASK_RI_LOAD_SVC_CFG				= 0x000802f2;

//! load system configuration value
const static TASKID		TASK_RI_LOAD_SYS_CFG				= 0x000802f4;

//! add DB table
const static TASKID		TASK_RI_DB_TABLE_ADD				= 0x00080101;

//! delete DB table
const static TASKID		TASK_RI_DB_TABLE_DEL				= 0x00080102;

//! get row of DB table from integer
const static TASKID		TASK_RI_DB_ROW_INT					= 0x00080111;

//! get row of DB table from string
const static TASKID		TASK_RI_DB_ROW_STR					= 0x00080112;

//! add row of DB table
const static TASKID		TASK_RI_DB_ROW_ADD					= 0x00080113;

//! delete row of DB table by integer
const static TASKID		TASK_RI_DB_ROW_DEL_INT				= 0x00080114;

//! delete row of DB table by string
const static TASKID		TASK_RI_DB_ROW_DEL_STR				= 0x00080115;

//! get column of DB table
const static TASKID		TASK_RI_DB_COL						= 0x00080121;

//! get cell of DB table
const static TASKID		TASK_RI_DB_CEL						= 0x00080131;

//! change cell of DB table
const static TASKID		TASK_RI_DB_CEL_CFG					= 0x00080134;


/**
 *
 * System Profiles
 *
 */

//! get idling time
const static TASKID		TASK_SYS_IDLE_TIME					= 0x00000021;

//! get system directory
const static TASKID		TASK_SYS_SYSTEM_DIRECTORY			= 0x00000022;

//! get network configuration
const static TASKID		TASK_SYS_NETWORK_CONFIGURATION		= 0x00000023;


//! connection event
const static TASKID		TASK_SYS_CONN						= 0x00000101;


//! regiter window handle
const static TASKID		TASK_SYS_REGWND						= 0x00000111;

//! show screen keyboard
const static TASKID		TASK_SYS_SHOWKEYBOARD				= 0x00000112;

//! change language
const static TASKID		TASK_SYS_CHANGE_LANGUAGE			= 0x00000113;


//! load application
const static TASKID		TASK_SYS_LOADAPP					= 0x00000121;

//! close application
const static TASKID		TASK_SYS_CLOSEAPP					= 0x00000122;

//! launching & termination of service application
const static TASKID		TASK_SYS_APPSTATUS					= 0x00000123;

//! load application(extended)
const static TASKID		TASK_SYS_LOADAPP_EX					= 0x00000126;


//! create folder
const static TASKID		TASK_SYS_CREATEFOLDER				= 0x00000301;

//! delete folder
const static TASKID		TASK_SYS_DELFOLDER					= 0x00000302;

//! delete file
const static TASKID		TASK_SYS_DELFILE					= 0x00000303;

//! rename or move file
const static TASKID		TASK_SYS_FILEMOVE					= 0x00000304;

//! copy file with full-path
const static TASKID		TASK_SYS_COPYFILE					= 0x00000305;


//! request file list
const static TASKID		TASK_SYS_FILELIST					= 0x00000311;

//! request string of file list
const static TASKID		TASK_SYS_FILELISTSTRING				= 0x00000313;

//! request disk space information
const static TASKID		TASK_SYS_DISKUSAGE					= 0x00000312;

//! get removable media
const static TASKID		TASK_SYS_REMOVABLEMEDIA				= 0x00000314;

//! set current directory
const static TASKID		TASK_SYS_SETCURFOLDER				= 0x00000321;


//! write string to file
const static TASKID		TASK_SYS_WRITE_STRING				= 0x00000341;


//! create directory with full path name
const static TASKID		TASK_SYS_CREATE_DIRECTORY_EX		= 0x00000381;

//! enumerate files to string
const static TASKID		TASK_SYS_ENUM_FILES_STRING			= 0x000003a3;


//! session key
const static TASKID		TASK_SYS_SESSION_KEY				= 0x00002001;

//! send form-data to the HTTP server through POST operation as the HTTP verb
const static TASKID		TASK_SYS_HTTP_POST					= 0x00002031;


//! liveupdate notification
const static TASKID		TASK_SYS_LIVEUPDATE_NOTFIFY			= 0x00000401;

//! request liveupdate
const static TASKID		TASK_SYS_LIVEUPDATE_EXECUTE			= 0x00000402;


/**
 *
 * service specific command
 *
 */

//! request customer info.
const static TASKID		TASK_SI_CUSTOMER_INFO				= 0x10010101;

//! request order info.
const static TASKID		TASK_SI_ORDER_INFO					= 0x10010121;

//! request reservation info.
const static TASKID		TASK_SI_RESERVATION_INFO			= 0x10010131;

//! when the customer has entered into store, it is generated.
const static TASKID		TASK_SI_E_ENTER_CUSTOMER			= 0x10010102;

//! when the customer has completed the check, it is generated.
const static TASKID		TASK_SI_E_COMPLETED_CHECK			= 0x10010142;

//! request table status
const static TASKID		TASK_SI_TABLE_STATUS				= 0x10010201;

//! request table info.
const static TASKID		TASK_SI_TABLE_INFO					= 0x10010202;

//! request waiting room status
const static TASKID		TASK_SI_WAITING_ROOM_STATUS			= 0x10010203;

//! calling
const static TASKID		TASK_SI_CALL						= 0x10010311;


/**
 *
 * service specific command
 *
 */

//! send recognized word
const static TASKID		TASK_SPE_ASR						= 0x00120081;


#ifdef __cplusplus
}
#endif

#endif // __RSDK_TASKDEF_H__
