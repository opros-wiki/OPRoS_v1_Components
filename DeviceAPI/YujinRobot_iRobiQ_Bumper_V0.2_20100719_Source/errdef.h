/**
 * 
 * \file errdef.h
 *
 * \brief
 *  Error code definition
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
 *  - 2006-01-23, Choe, Yeongil, Create
 * 
 * \see
 * 
 * Copyright(C) 2006 YUJIN ROBOTICS CO., LTD.
 *
 */

#ifndef __RSDK_ERRDEF_H__
#define __RSDK_ERRDEF_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef DWORD YJRESULT;

/**
 *
 * Common code
 *
 */

//! success
const static YJRESULT	YJERR_SUCCESS							= 0x00000000;

//! failure (general)
const static YJRESULT	YJERR_FAIL								= 0x00000001;

//! task was rejected
const static YJRESULT	YJERR_FAIL_REJECT						= 0x00000002;

//! not connected to engine
const static YJRESULT	YJERR_FAIL_INTERFACE					= 0x00000003;

//! no valid device to do task
const static YJRESULT	YJERR_FAIL_DEVICE						= 0x00000004;

//! invalid parameter
const static YJRESULT	YJERR_FAIL_INVALIDARG					= 0x00000005;

//! unexpected stop
const static YJRESULT	YJERR_FAIL_UNEXPECTEDSTOP				= 0x00000006;

//! file not found
const static YJRESULT	YJERR_FAIL_FILENOTFOUND					= 0x00000007;

//! not completed
const static YJRESULT	YJERR_FAIL_COMPLETE_COMMAND				= 0x00000008;

//! overflow
const static YJRESULT	YJERR_FAIL_OVERFLOW						= 0x00000009;

//! unknown error
const static YJRESULT	YJERR_FAIL_UNKNOWN						= 0xffffffff;


/**
 *
 * robot behaviors
 *
 */

//! failed to do motion as a connection to DC adaptor
const static YJRESULT	YJERR_FAIL_MOTION_CONN_ADAPTOR			= 0x00010021;

//! failed to do motion as a connection to docking station
const static YJRESULT	YJERR_FAIL_MOTION_CONN_STATION			= 0x00010022;

//! not compatible command to the control board
const static YJRESULT	YJERR_FAIL_NOT_COMPATIBLE_CTRL_BOARD	= 0x00010023;

//! not compatible command to the firmware
const static YJRESULT	YJERR_FAIL_NOT_COMPATIBLE_FIRMWARE		= 0x00010024;


/**
 *
 * Voice Interfaces
 *
 */

//! voice is too low to do ASR
const static YJRESULT	YJERR_FAIL_VOICE_LOW					= 0x00110021;

//! voice is too high to do ASR
const static YJRESULT	YJERR_FAIL_VOICE_HIGH					= 0x00110022;

//! not compatible ASR mode
const static YJRESULT	YJERR_FAIL_NOT_COMPATIBLE_ASR_MODE		= 0x00110023;

//! It fails to be recognized due to low confidence of results.
const static YJRESULT	YJERR_FAIL_VOICE_REJECT					= 0x00110024;

//! It fails to be recognized due to too long voice duration. 
//! Usually, background noises and two long utterance.
const static YJRESULT	YJERR_FAIL_VOICE_EXCEED					= 0x00110025;

//! The duration of voice recognition mode can be limited. 
//! If this duration passed out, this message occurs.
const static YJRESULT	YJERR_FAIL_VOICE_TIMEOUT				= 0x00110026;

//! Voice activation detected.
const static YJRESULT	YJERR_FAIL_VOICE_EPD					= 0x00110027;

//! Recording for voice recognition started.
const static YJRESULT	YJERR_FAIL_VOICE_RECORDING_START		= 0x00110028;

//! Recording stopped, and computation for recognition started.
const static YJRESULT	YJERR_FAIL_VOICE_RECORDING_STOP			= 0x00110029;


//! exceed numbers of category
const static YJRESULT	YJERR_FAIL_ASR_CATEGORY_EXCEED			= 0x00110031;

//! category name already exists
const static YJRESULT	YJERR_FAIL_ASR_CATEGORY_ALREADY_EXIST	= 0x00110032;

//! not found category name
const static YJRESULT	YJERR_FAIL_ASR_CATEGORY_NOT_FOUND		= 0x00110033;


//! exceed numbers of recognition word
const static YJRESULT	YJERR_FAIL_ASR_WORD_EXCEED				= 0x00110041;

//! recognition word already exists
const static YJRESULT	YJERR_FAIL_ASR_WORD_ALREADY_EXIST		= 0x00110042;

//! not found recognition word
const static YJRESULT	YJERR_FAIL_ASR_WORD_NOT_FOUND			= 0x00110043;

//! succeeded word-registration 1st-times
const static YJRESULT	YJERR_SUCCESS_WORD_REG_1				= 0x00110044;

//! succeeded word-registration 2nd-times
const static YJRESULT	YJERR_SUCCESS_WORD_REG_2				= 0x00110045;


//! exceed numbers of name
const static YJRESULT	YJERR_FAIL_NAME_EXCEED					= 0x00110051;

//! name already exists
const static YJRESULT	YJERR_FAIL_NAME_ALREADY_EXIST			= 0x00110052;

//! name not found
const static YJRESULT	YJERR_FAIL_NAME_NOT_FOUND				= 0x00110053;

//! succeeded name-registration 1st-times
const static YJRESULT	YJERR_SUCCESS_NAME_REG_1				= 0x00110054;

//! succeeded name-registration 2nd-times
const static YJRESULT	YJERR_SUCCESS_NAME_REG_2				= 0x00110055;


//! already registered speaker
const static YJRESULT	YJERR_FAIL_SPEAKER_ALREADY_EXIST		= 0x00110061;

//! succeeded speaker-registration 1st-times
const static YJRESULT	YJERR_SUCCESS_SPEAKER_REG_1				= 0x00110062;

//! succeeded speaker-registration 2nd-times
const static YJRESULT	YJERR_SUCCESS_SPEAKER_REG_2				= 0x00110063;

//! no one registered in speaker database
const static YJRESULT	YJERR_FAIL_SPEAKER_EMPTY				= 0x00110064;

//! registered speaker overflow
const static YJRESULT	YJERR_FAIL_SPEAKER_OVERFLOW				= 0x00110065;


/**
 *
 * Vision Interfaces
 *
 */

//! already registered face ID
const static YJRESULT	YJERR_FAIL_FACE_ALREADY_EXIST			= 0x01010011;

//! failed human following. not initialized	
const static YJRESULT	YJERR_FAIL_FOLLOWING_NOT_INIT			= 0x01010012;

//! failed human following. forcely stop
const static YJRESULT	YJERR_FAIL_FOLLOWING_FORCELY_STOP		= 0x01010013;

//! failed human following. temporarily lost
const static YJRESULT	YJERR_FAIL_FOLLOWING_TEMP_LOST			= 0x01010014;

//! succeeded face-registration 1-times
const static YJRESULT	YJERR_SUCCESS_FACE_REG_1				= 0x01010015;

//! succeeded face-registration 1-times
const static YJRESULT	YJERR_SUCCESS_FACE_REG_2				= 0x01010016;

//! detected stranger
const static YJRESULT	YJERR_SUCCESS_STRANGER_DETECTED			= 0x01010017;

//! no one registered in face database
const static YJRESULT	YJERR_FAIL_FACE_EMPTY					= 0x01010018;

//! registered face overflow
const static YJRESULT	YJERR_FAIL_FACE_OVERFLOW				= 0x01010019;


/**
 *
 * Navigation
 *
 */

//! can not completed navigation
const static YJRESULT	YJERR_FAIL_MOVE_COMP					= 0x00810001;

//! can not find specific landmark ID
const static YJRESULT	YJERR_FAIL_FIND_ID						= 0x00810011;

//! can not find specific landmark label
const static YJRESULT	YJERR_FAIL_FIND_LABEL					= 0x00810012;

//! can not find specific landmark coordinate
const static YJRESULT	YJERR_FAIL_FIND_XY						= 0x00810013;

//! can not find specific landmark (general)
const static YJRESULT	YJERR_FAIL_FIND_LANDMARK				= 0x00810019;

//! can not know where I am
const static YJRESULT	YJERR_FAIL_CURR_POS						= 0x00810014;

//! can not generate path
const static YJRESULT	YJERR_FAIL_MAKE_PATH					= 0x00810015;

//! obstructed by obstacle
const static YJRESULT	YJERR_FAIL_OBSTRUCTED					= 0x00810016;

//! bumped against obstacle
const static YJRESULT	YJERR_FAIL_BUMPED						= 0x00810017;

//! can not sensed ground
const static YJRESULT	YJERR_FAIL_GROUND						= 0x00810018;

//! not estimated calibration
const static YJRESULT	YJERR_FAIL_NOT_CALIBRATED				= 0x00810020;
 
//! failed to do navigation with a connection to DC adaptor
const static YJRESULT	YJERR_FAIL_NAVI_CONN_ADAPTOR			= 0x00810021;

//! canceled by stop command
const static YJRESULT	YJERR_FAIL_CANCEL_BY_STOP				= 0x00810022;

//! canceled by new navigating command
const static YJRESULT	YJERR_FAIL_CANCEL_BY_NEW				= 0x00810023;

//! canceled by remote-control
const static YJRESULT	YJERR_FAIL_CANCEL_BY_REMOCON			= 0x00810024;

//! failed to go charging due to in charge 
const static YJRESULT	YJERR_FAIL_ALREADY_CHARGE				= 0x00810025;

//! failed to communicate with device
const static YJRESULT	YJERR_FAIL_COMM_DEVICE					= 0x00810026;

//! failed to initialize sensor
const static YJRESULT	YJERR_FAIL_INIT_SENSOR					= 0x00810027;

//! failed to analysis figure of camera
const static YJRESULT	YJERR_FAIL_DISTURBED_FIGURE				= 0x00810028;

//! be being delayed measuring height of ceil
const static YJRESULT	YJERR_FAIL_DELAY_CALIBRATION			= 0x00810029;

//! succeeded to initialize sensor
const static YJRESULT	YJERR_SUCCESS_STARGAZER_INIT			= 0x0081002a;

//! CMOS sensor error of stargazer
const static YJRESULT	YJERR_FAIL_STARGAZER_CMOS_ERROR			= 0x0081002b;

//! stargazer operation error
const static YJRESULT	YJERR_FAIL_STARGAZER_OPERATION_ERROR	= 0x0081002c;

//! failed to complete navigation as time-out
const static YJRESULT	YJERR_FAIL_NAVI_TIME_LIMIT				= 0x0081002d;

//! on gray
const static YJRESULT	YJERR_FAIL_NAVI_ON_GRAY					= 0x0081002e;

//! force to arrive
const static YJRESULT	YJERR_SUCCESS_FORCE_TO_ARRIVE			= 0x0081002f;

//! failed to recover stargazer
const static YJRESULT	YJERR_FAIL_STARGAZER_RECOVERY			= 0x00810030;

//! stopped forcely by person's touch
const static YJRESULT	YJERR_FAIL_NAVI_STOPPED_FORCELY			= 0x00810031;


/**
 *
 * Robot Information
 *
 */

//! not compatible command
const static YJRESULT	YJERR_FAIL_NOT_COMPATIBLE				= 0x00080011;


//! another application should use camera exclusively
const static YJRESULT	YJERR_FAIL_GET_CAMERA					= 0x00080101;

//! another application should use mic exclusively
const static YJRESULT	YJERR_FAIL_GET_MIC						= 0x00080102;


//! can not create table (already exist same table)
const static YJRESULT	YJERR_FAIL_CREATE_TABLE					= 0x00080001;

//! can not find table
const static YJRESULT	YJERR_FAIL_FIND_TABLE					= 0x00080002;


/**
 *
 * Contents Interfaces
 *
 */

//! not exist application
const static YJRESULT	YJERR_FAIL_NOT_EXIST_APP				= 0x0f010001;

//! failed to connect service application
const static YJRESULT	YJERR_FAIL_CONNECT_APP_SERVICE			= 0x0f010002;


//! can not find target content
const static YJRESULT	YJERR_FAIL_OPEN_CONTENT					= 0xf0010001;


/**
 *
 * System
 *
 */

//! connected to server
const static YJRESULT	YJERR_CONN_SUCCESS						= 0x00000100;

//! A socket operation was attempted to 
//! an unreachable host
const static YJRESULT	YJERR_CONN_HOSTUNREACH					= 0x00000101;

//! A connection attempt failed 
//! because the connected party did not properly respond 
//! after a period of time, or established connection 
//! failed because connected host has failed to respond
const static YJRESULT	YJERR_CONN_TIMEDOUT						= 0x00000102;

//! No connection could be made because the target machine 
//! actively refused it. This usually results 
//! from trying to connect to a service that is 
//! inactive on the foreign host - i.e. one with 
//! no server program running
const static YJRESULT	YJERR_CONN_CONNREFUSED					= 0x00000103;

//! The connection was terminated 
const static YJRESULT	YJERR_CONN_CLOSED						= 0x00000104;


//! file already exist
const static YJRESULT	YJERR_FAIL_FILE_ALREADY_EXIST			= 0x00001001;

//! file access denied
const static YJRESULT	YJERR_FAIL_FILE_ACCESS_DENIED			= 0x00001002;

//! disk full
const static YJRESULT	YJERR_FAIL_FILE_DISK_FULL				= 0x00001003;


//! failed to connect to authentication server
const static YJRESULT	YJERR_FAIL_CONN_AUTH_SERVER				= 0x00002001;

//! rejected to authenticate the robot
const static YJRESULT	YJERR_FAIL_REJECT_AHTH					= 0x00002002;

//! connection timeout to authentication server
const static YJRESULT	YJERR_FAIL_CONN_AUTH_TIMEOUT			= 0x00002003;

//! failed to connect to server
const static YJRESULT	YJERR_FAIL_CONN_SERVER					= 0x00002004;

//! failed to request service to server
const static YJRESULT	YJERR_FAIL_REQ_SERVER_SERVICE			= 0x00002005;


/**
 *
 * Serving interface
 *
 */

//! not connected DB
const static YJRESULT	YJERR_FAIL_CONNECT_STORE_DB				= 0x10010011;

//! not found customer matched given ID
const static YJRESULT	YJERR_FAIL_CUSTOMER_MATCHED_ID			= 0x10010021;

//! not found table matched given number
const static YJRESULT	YJERR_FAIL_TABLE_MATCHED_NUM			= 0x10010031;


#ifdef __cplusplus
}
#endif

#endif // __RSDK_ERRDEF_H__

