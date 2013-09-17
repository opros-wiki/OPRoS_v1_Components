#ifndef __YJROBOTAPI_H__
#define __YJROBOTAPI_H__

#ifdef ROBOTINTERFACE_EXPORTS
#define ROBOTINTERFACE_API __declspec(dllexport)
#else
#define ROBOTINTERFACE_API __declspec(dllimport)
#endif

#include "errdef.h"
#include "yjrobotdef.h"

//-#ifdef __cplusplus
//-extern "C" {
//-#endif

/**
 *
 * Initialize and creation
 *
 */
YJRESULT ROBOTINTERFACE_API YJCI_CreateInstance(LPROBOTINTERFACE* ppRobotInterface);

YJRESULT ROBOTINTERFACE_API YJCI_DeleteInstance(LPROBOTINTERFACE* ppRobotInterface);

YJRESULT ROBOTINTERFACE_API YJCI_InitInterface(LPROBOTINTERFACE lpRobotInterface,
											   WORD wAppID,
											   LPCTSTR lpszSocketAddress,
											   UINT uPortNum);

YJRESULT ROBOTINTERFACE_API YJCI_UnInitInterface(LPROBOTINTERFACE lpRobotInterface);

YJRESULT ROBOTINTERFACE_API YJCI_GetConnectCode(LPROBOTINTERFACE lpRobotInterface);

YJRESULT ROBOTINTERFACE_API YJCI_SetHeartbitProperty(LPROBOTINTERFACE lpRobotInterface, PHEARTBITPROPERTY phbp);

/**
 *
 * Call back function
 *
 */
YJRESULT ROBOTINTERFACE_API YJCI_RegRequestProc(LPROBOTINTERFACE lpRobotInterface,
												REQUESTPROC fnRequestProc);

YJRESULT ROBOTINTERFACE_API YJCI_RegAcknowledgeProc(LPROBOTINTERFACE lpRobotInterface,
													ACKNOWLEDGEPROC fnAcknowledgeProc);

YJRESULT ROBOTINTERFACE_API YJCI_RegResponseProc(LPROBOTINTERFACE lpRobotInterface,
												 RESPONSEPROC fnRespnseProc);

YJRESULT ROBOTINTERFACE_API YJCI_RegEventProc(LPROBOTINTERFACE lpRobotInterface,
											  EVENTPROC fnEventProc);


/**
 *
 * Command Type : Robot Behaviors
 *
 */
YJRESULT ROBOTINTERFACE_API YJBH_MoveWheel(LPROBOTINTERFACE lpRobotInterface,
										   WORD wCmdID,
										   LPWHEELACTIONPARAMS lpActionParams,
										   BOOL bReturnToOrigin,
										   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJBH_MoveHead(LPROBOTINTERFACE lpRobotInterface,
										  WORD wCmdID,
										  LPHEADACTIONPARAMS lpActionParams,
										  BOOL bReturnToOrigin,
										  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJBH_MoveHeadRel(LPROBOTINTERFACE pri,
											 WORD wCmdID,
											 LPHEADACTIONREL pha,
											 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJBH_ReqHeadPosition(LPROBOTINTERFACE pri,
												 WORD wCmdID,
												 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJBH_MoveArm(LPROBOTINTERFACE lpRobotInterface,
										 WORD wCmdID,
										 LPARMACTIONPARAMS lpActionParams,
										 BOOL bReturnToOrigin,
										 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJBH_LED(LPROBOTINTERFACE lpRobotInterface,
									 WORD wCmdID,
									 LPLEDACTIONPARAMS lpActionParams,
									 BOOL bTurnOn,
									 BOOL bNeedAck);

YJRESULT ROBOTINTERFACE_API YJBH_ReqExpressFace(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												BH_FACETYPE enFaceType,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJBH_FaceExpressEx(LPROBOTINTERFACE pri,
											   WORD wCmdID,
											   DWORD dwTemplateCode,
											   WORD wColor,
											   WORD wFrequency,
											   DWORD dwOption,
											   DWORD dwReserved,
											   BOOL bAcknowledge = FALSE);

YJRESULT ROBOTINTERFACE_API YJBH_MixedMotion(LPROBOTINTERFACE lpRobotInterface,
											 WORD wCmdID,
											 LPMIXEDMOTION lpActionParams,
											 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJBH_StopMotion(LPROBOTINTERFACE lpRobotInterface,
											WORD wCmdID,
											BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJBH_ReqExpressEmotion(LPROBOTINTERFACE lpRobotInterface,
												   WORD wCmdID,
												   BH_EMOTIONTYPE emEmotionType,
												   BOOL bNeedAck = FALSE); // obsoleted

YJRESULT ROBOTINTERFACE_API YJBH_SetEmotion(LPROBOTINTERFACE lpRobotInterface,
											WORD wCmdID,
											DWORD dwEmotion,
											DWORD dwReserved,
											BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJBH_GetEmotion(LPROBOTINTERFACE lpRobotInterface,
											WORD wCmdID,
											BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJBH_Clebo_TurnOn(LPROBOTINTERFACE lpRobotInterface,
											  WORD wCmdID,
											  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJBH_Clebo_TurnOff(LPROBOTINTERFACE lpRobotInterface,
											   WORD wCmdID,
											   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJBH_Clebo_Start(LPROBOTINTERFACE lpRobotInterface,
											 WORD wCmdID,
											 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJBH_Clebo_Stop(LPROBOTINTERFACE lpRobotInterface,
											WORD wCmdID,
											BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJBH_Clebo_SetCourse(LPROBOTINTERFACE lpRobotInterface,
												 WORD wCmdID,
												 WORD wCourseType,
												 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJBH_Clebo_SetDuration(LPROBOTINTERFACE lpRobotInterface,
												   WORD wCmdID,
												   INT nDuration,
												   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJBH_Clebo_SetReservation(LPROBOTINTERFACE lpRobotInterface,
													  WORD wCmdID,
													  LPRESERVECLEAN lpParams,
													  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJBH_SetLcdPower(LPROBOTINTERFACE lpRobotInterface,
											 WORD wCmdID,
											 BOOL bTurnOn,
											 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJBH_SetPowerSaveMode(LPROBOTINTERFACE lpRobotInterface,
												  WORD wCmdID,
												  DWORD dwType,
												  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJBH_SetMotorTorque(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												DWORD dwMotorID,
												DWORD dwValue,
												BOOL bNeedAck = FALSE);


/**
 *
 * Command Type : Voice Interfaces
 *
 */
YJRESULT ROBOTINTERFACE_API YJVC_LoadTTS(LPROBOTINTERFACE lpRobotInterface,
										 WORD wCmdID,
										 VC_SPEECHTYPE enSpeechType = VCST_KOR_ADULT,
										 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_UnloadTTS(LPROBOTINTERFACE lpRobotInterface,
										   WORD wCmdID,
										   VC_SPEECHTYPE enSpeechType,
										   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_PlayTTS(LPROBOTINTERFACE lpRobotInterface,
										 WORD wCmdID,
										 LPCTSTR LpszText,
										 VC_SPEECHTYPE enSpeechType = VCST_KOR_ADULT,
										 FLOAT fVolumn = 1.0,
										 FLOAT fPitch = 1.0,
										 FLOAT fSpeed = 1.0,
										 BOOL bNotifyCompleteSync = FALSE,
										 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_StopTTS(LPROBOTINTERFACE lpRobotInterface,
										 WORD wCmdID,
										 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_PauseTTS(LPROBOTINTERFACE lpRobotInterface,
										  WORD wCmdID,
										  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_RestartTTS(LPROBOTINTERFACE lpRobotInterface,
											WORD wCmdID,
											BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_CalculateTTSTime(LPROBOTINTERFACE lpRobotInterface,
												  WORD wCmdID,
												  LPCTSTR LpszText,
												  VC_SPEECHTYPE enSpeechType = VCST_KOR_ADULT,
												  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_StartASR(LPROBOTINTERFACE lpRobotInterface,
										  WORD wCmdID,
										  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_StartASRExt(LPROBOTINTERFACE lpRobotInterface,
											 WORD wCmdID,
											 WORD wMode,
											 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_StopASR(LPROBOTINTERFACE lpRobotInterface,
										 WORD wCmdID,
										 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_AddRecWords(LPROBOTINTERFACE lpRobotInterface,
											 WORD wCmdID,
											 LPCTSTR lpszRecWords,
											 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_AddRecWordsExt(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												DWORD dwLanguage,
												LPCTSTR lpszWordList,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_DeleteRecWords(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												LPCTSTR lpszRecWords,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_ResetRecWords(LPROBOTINTERFACE lpRobotInterface,
											   WORD wCmdID,
											   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_RegisterWordForSpeaker(LPROBOTINTERFACE lpRobotInterface,
														WORD wCmdID,
														LPCTSTR lpszWord,
														BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_UnregisterWordForSpeaker(LPROBOTINTERFACE lpRobotInterface,
														  WORD wCmdID,
														  LPCTSTR lpszWord,
														  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_ReqRegisteredWord(LPROBOTINTERFACE lpRobotInterface,
												   WORD wCmdID,
												   DWORD dwAsrType,
												   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_SetASRModel(LPROBOTINTERFACE lpRobotInterface,
											 WORD wCmdID,
											 DWORD dwModel,
											 DWORD dwReserved,
											 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_GetASRModel(LPROBOTINTERFACE lpRobotInterface,
											 WORD wCmdID,
											 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_GetASRWord(LPROBOTINTERFACE lpRobotInterface,
											WORD wCmdID,
											DWORD dwType,
											BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_AddCategory(LPROBOTINTERFACE lpRobotInterface,
											 WORD wCmdID,
											 LPCTSTR lpszCategoryName,
											 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_DeleteCategory(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												LPCTSTR lpszCategoryName,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_AddRecConnectedWords(LPROBOTINTERFACE lpRobotInterface,
													  WORD wCmdID,
													  LPCTSTR lpszCategory,
													  LPCTSTR lpszRecWords,
													  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_DeleteRecConnectedWords(LPROBOTINTERFACE lpRobotInterface,
														 WORD wCmdID,
														 LPCTSTR lpszCategory,
														 LPCTSTR lpszRecWords,
														 BOOL bNeedAck = FALSE);
												
YJRESULT ROBOTINTERFACE_API YJVC_StartASRName(LPROBOTINTERFACE lpRobotInterface,
											  WORD wCmdID,
											  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_StopASRName(LPROBOTINTERFACE lpRobotInterface,
											 WORD wCmdID,
											 BOOL bNeedAck = FALSE);
											 
YJRESULT ROBOTINTERFACE_API YJVC_AddName(LPROBOTINTERFACE lpRobotInterface,
										 WORD wCmdID,
										 LPCTSTR lpszName,
										 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_DeleteName(LPROBOTINTERFACE lpRobotInterface,
											WORD wCmdID,
											LPCTSTR lpszName,
											BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_RegisterNameForSpeaker(LPROBOTINTERFACE lpRobotInterface,
														WORD wCmdID,
														LPCTSTR lpszName,
														BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_UnregisterNameForSpeaker(LPROBOTINTERFACE lpRobotInterface,
														  WORD wCmdID,
														  LPCTSTR lpszName,
														  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_ReqRegisteredName(LPROBOTINTERFACE lpRobotInterface,
												   WORD wCmdID,
												   DWORD dwAsrType,
												   BOOL bNeedAck = FALSE);


YJRESULT ROBOTINTERFACE_API YJVC_SetASRMode(LPROBOTINTERFACE lpRobotInterface,
											WORD wCmdID,
											ASR_MODE enMode = ASR_CONNECTED,
											BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_SetASRSensitivity(LPROBOTINTERFACE lpRobotInterface,
												   WORD wCmdID,
												   int nSensitivity,
												   BOOL bNeedAck = FALSE);
												   
YJRESULT ROBOTINTERFACE_API YJVC_SetASRChannel(LPROBOTINTERFACE lpRobotInterface,
											   WORD wCmdID,
											   DWORD dwChannel,
											   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_SetASRLanguage(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												VC_RECLANGTYPE enLanguageType,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_SetASRDevice(LPROBOTINTERFACE lpRobotInterface,
											  WORD wCmdID,
											  VC_ASRDEVICE enDeviceType,
											  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_StartHandClappingDetection(LPROBOTINTERFACE lpRobotInterface,
															WORD wCmdID,
															BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_StopHandClappingDetection(LPROBOTINTERFACE lpRobotInterface,
														   WORD wCmdID,
														   BOOL bNeedAck = FALSE);

// speaker recognition

YJRESULT ROBOTINTERFACE_API YJVC_StartSpeakerRec(LPROBOTINTERFACE lpRobotInterface,
												 WORD wCmdID,
												 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_StopSpeakerRec(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_RegisterSpeaker(LPROBOTINTERFACE lpRobotInterface,
												 WORD wCmdID,
												 LPCTSTR lpszSpeakerName,
												 LPCTSTR lpszRobotName,
												 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_DeleteSpeaker(LPROBOTINTERFACE lpRobotInterface,
											   WORD wCmdID,
											   LPCTSTR lpszSpeakerName,
											   BOOL bNeedAck = FALSE);

// sound source localization 

YJRESULT ROBOTINTERFACE_API YJVC_StartSSL(LPROBOTINTERFACE lpRobotInterface,
										  WORD wCmdID,
										  LPCTSTR lpszSpeakerName,
										  LPCTSTR lpszRobotName,
										  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVC_StopSSL(LPROBOTINTERFACE lpRobotInterface,
										 WORD wCmdID,
										 BOOL bNeedAck = FALSE);


/**
 *
 * Command Type : Visual Interfaces
 *
 */

YJRESULT ROBOTINTERFACE_API YJVS_ResumeService(LPROBOTINTERFACE lpRobotInterface,
											   WORD wCmdID,
											   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_SuspendService(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												BOOL bNeedAck = FALSE);

/* obsoleted */
YJRESULT ROBOTINTERFACE_API YJVS_StartHumanDetection(LPROBOTINTERFACE lpRobotInterface,
													 WORD wCmdID,
													 BOOL bNeedAck = FALSE);

/* obsoleted */
YJRESULT ROBOTINTERFACE_API YJVS_StopHumanDetection(LPROBOTINTERFACE lpRobotInterface,
													WORD wCmdID,
													BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_StartMotionDetection(LPROBOTINTERFACE lpRobotInterface,
													  WORD wCmdID,
													  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_StopMotionDetection(LPROBOTINTERFACE lpRobotInterface,
													 WORD wCmdID,
													 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_StartHandDetection(LPROBOTINTERFACE lpRobotInterface,
													WORD wCmdID,
													BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_StopHandDetection(LPROBOTINTERFACE lpRobotInterface,
												   WORD wCmdID,
												   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_StartFaceDetection(LPROBOTINTERFACE lpRobotInterface,
													WORD wCmdID,
													BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_StopFaceDetection(LPROBOTINTERFACE lpRobotInterface,
												   WORD wCmdID,
												   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_StartFaceRecognition(LPROBOTINTERFACE lpRobotInterface,
													  WORD wCmdID,
													  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_StopFaceRecognition(LPROBOTINTERFACE lpRobotInterface,
													 WORD wCmdID,
													 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_RegisterFace(LPROBOTINTERFACE lpRobotInterface,
											  WORD wCmdID,
											  LPCTSTR lpszUserID,
											  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_DeleteFace(LPROBOTINTERFACE lpRobotInterface,
											WORD wCmdID,
											LPCTSTR lpszUserID,
											BOOL bNeedAck = FALSE);


YJRESULT ROBOTINTERFACE_API YJVS_StartStareFace(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												INT nPeriod,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_StopStareFace(LPROBOTINTERFACE lpRobotInterface,
											   WORD wCmdID,
											   BOOL bNeedAck = FALSE );


YJRESULT ROBOTINTERFACE_API YJVS_StartHumanShapeDetection(LPROBOTINTERFACE lpRobotInterface,
														  WORD wCmdID,
														  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_StopHumanShapeDetection(LPROBOTINTERFACE lpRobotInterface,
														 WORD wCmdID,
														 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_StartBodyTracking(LPROBOTINTERFACE lpRobotInterface,
												   WORD wCmdID,
												   RECT* pArea,
												   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_StopBodyTracking(LPROBOTINTERFACE lpRobotInterface,
												  WORD wCmdID,
												  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_StartFaceTracking(LPROBOTINTERFACE lpRobotInterface,
												   WORD wCmdID,
												   RECT* pArea,
												   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_StopFaceTracking(LPROBOTINTERFACE lpRobotInterface,
												  WORD wCmdID,
												  BOOL bNeedAck = FALSE);


YJRESULT ROBOTINTERFACE_API YJVS_StartRecObject(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_StopRecObject(LPROBOTINTERFACE lpRobotInterface,
											   WORD wCmdID,
											   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_AddRecObject(LPROBOTINTERFACE lpRobotInterface,
											  WORD wCmdID,
											  LPCTSTR lpszObjID,
											  LPCTSTR lpszGroupID,
											  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_DeleteRecObject(LPROBOTINTERFACE lpRobotInterface,
												 WORD wCmdID,
												 LPCTSTR lpszObjID,
												 LPCTSTR lpszGroupID,
												 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_FlushRecObject(LPROBOTINTERFACE lpRobotInterface,
											    WORD wCmdID,
											    LPCTSTR lpszGroupID,
											    BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_SetRecObjectGroup(LPROBOTINTERFACE lpRobotInterface,
												   WORD wCmdID,
												   LPCTSTR lpszGroupID,
												   BOOL bNeedAck = FALSE);


YJRESULT ROBOTINTERFACE_API YJVS_StartCallerDetection(LPROBOTINTERFACE lpRobotInterface,
													  WORD wCmdID,
													  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_StopCallerDetection(LPROBOTINTERFACE lpRobotInterface,
													 WORD wCmdID,
													 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_StartHumanFollowing(LPROBOTINTERFACE lpRobotInterface,
													 WORD wCmdID,
													 RECT* pArea,
													 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_StopHumanFollowing(LPROBOTINTERFACE lpRobotInterface,
													WORD wCmdID,
													BOOL bNeedAck = FALSE);


YJRESULT ROBOTINTERFACE_API YJVS_StartShowPreview(LPROBOTINTERFACE lpRobotInterface,
												  WORD wCmdID,
												  LPVIDEOPREVIEWPARAMS lpVideoPreviewParams,
												  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_StopShowPreview(LPROBOTINTERFACE lpRobotInterface,
												 WORD wCmdID,
												 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_SaveImage(LPROBOTINTERFACE lpRobotInterface,
										   WORD wCmdID,
										   LPSAVEIMAGEPARAMS lpSaveImageParams, 
										   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJVS_ReleaseCamera(LPROBOTINTERFACE lpRobotInterface,
											   WORD wCmdID,
											   BOOL bNeedAck = FALSE);

/**
 *
 * Command Type : Navigation Interfaces
 *
 */

YJRESULT ROBOTINTERFACE_API YJNV_SetMaxVelocity(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												INT dwValue,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_ReqMaxVelocity(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_SetObstacleAvoidance(LPROBOTINTERFACE lpRobotInterface,
													  WORD wCmdID,
													  DWORD dwAvoidanceMode,
													  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_SetTimeLimit(LPROBOTINTERFACE lpRobotInterface,
											  WORD wCmdID,
											  DWORD dwTimeLimit,
											  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_GetWheelVelocity(LPROBOTINTERFACE lpRobotInterface,
												  WORD wCmdID,
												  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_GotoID(LPROBOTINTERFACE lpRobotInterface,
										WORD wCmdID,
										LPLANDMARK lpLandmark,
										BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_GotoLabel(LPROBOTINTERFACE lpRobotInterface,
										   WORD wCmdID,
										   LPLANDMARK lpLandmark,
										   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_GotoXY(LPROBOTINTERFACE lpRobotInterface,
										WORD wCmdID,
										LPLANDMARK lpLandmark,
										BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_GotoIDEx(LPROBOTINTERFACE lpRobotInterface,
										  WORD wCmdID,
										  INT nLandmarkID,
										  DWORD dwNavigationFlag,
										  DWORD dwReserved,
										  BOOL bAcknowledge = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_GotoLabelEx(LPROBOTINTERFACE lpRobotInterface,
											 WORD wCmdID,
											 LPCTSTR lpszLandmarkLabel,
											 DWORD dwNavigationFlag,
											 DWORD dwReserved,
											 BOOL bAcknowledge = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_GotoXYEx(LPROBOTINTERFACE lpRobotInterface,
										  WORD wCmdID,
										  INT nX,
										  INT nY,
										  float fTheta,
										  DWORD dwNavigationFlag,
										  DWORD dwReserved,
										  BOOL bAcknowledge = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_GotoDir(LPROBOTINTERFACE lpRobotInterface,
										 WORD wCmdID,
										 INT nDirection,
										 INT nDegree,
										 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_GotoDirEx(LPROBOTINTERFACE lpRobotInterface,
										   WORD wCmdID,
										   INT nDirection,
										   INT nDegree,
										   DWORD dwCnstrType,
										   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_Stop(LPROBOTINTERFACE lpRobotInterface,
									  WORD wCmdID,
									  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_StartMapBuild(LPROBOTINTERFACE lpRobotInterface,
											   WORD wCmdID,
											   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_StopMapBuild(LPROBOTINTERFACE lpRobotInterface,
											  WORD wCmdID,
											  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_StartReportLocation(LPROBOTINTERFACE lpRobotInterface,
													 WORD wCmdID,
													 INT nFrequency,
													 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_StopReportLocation(LPROBOTINTERFACE lpRobotInterface,
													WORD wCmdID,
													BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_ReqLandmark(LPROBOTINTERFACE lpRobotInterface,
											 WORD wCmdID,
											 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_ReqLandmarkList(LPROBOTINTERFACE lpRobotInterface,
												 WORD wCmdID,
												 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_ReqLandmarkListString(LPROBOTINTERFACE lpRobotInterface,
												 WORD wCmdID,
												 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_AddLandmark(LPROBOTINTERFACE lpRobotInterface,
											 WORD wCmdID,
											 LPLANDMARK lpLandmark,
											 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_DeleteLandmark(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												LPLANDMARK lpLandmark,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_UpdateLandmark(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												LPLANDMARK lpLandmark,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_ReqLandmarkNearest(LPROBOTINTERFACE lpRobotInterface,
													WORD wCmdID,
													BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_DirCamera(LPROBOTINTERFACE lpRobotInterface,
										   WORD wCmdID,
										   INT nDirection,
										   INT nAngle,
										   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_ReqCalibration(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_SetNavigationDevice(LPROBOTINTERFACE lpRobotInterface,
													 WORD wCmdID,
													 WORD wDevice,
													 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_InitializeMap(LPROBOTINTERFACE lpRobotInterface,
											   WORD wCmdID,
											   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_DistanceToObstacle(LPROBOTINTERFACE lpRobotInterface,
													WORD wCmdID,
													DWORD dwDirection,
													BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_EstimateRegion(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												DWORD dwRefType,
												INT nLandmarkID = -1,
												LPCTSTR lpszLandmarkLabel = NULL,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_StartEstimateObstacle(LPROBOTINTERFACE lpRobotInterface,
													   WORD wCmdID,
													   LP_OBSTACLE_ESTIMATION lpDesired,
													   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJNV_StopEstimateObstacle(LPROBOTINTERFACE lpRobotInterface,
													  WORD wCmdID,
													  BOOL bNeedAck = FALSE);


/**
 *
 * Command Type : Robot Information Service
 *
 */
YJRESULT ROBOTINTERFACE_API YJRI_ReqBatteryStatus(LPROBOTINTERFACE lpRobotInterface,
												  WORD wCmdID,
												  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_ReqHardwareStatus(LPROBOTINTERFACE lpRobotInterface,
												   WORD wCmdID,
												   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_SetHWEventFilter(LPROBOTINTERFACE lpRobotInterface,
												  WORD wCmdID,
												  DWORD dwEventType,
												  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_SetPlayerVolume(LPROBOTINTERFACE lpRobotInterface,
												 WORD wCmdID,
												 INT nLevel,
												 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_ReqPlayerVolume(LPROBOTINTERFACE lpRobotInterface,
												 WORD wCmdID,
												 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_SetPlayerMute(LPROBOTINTERFACE	lpRobotInterface,
											   WORD wCmdID,
											   BOOL bMute,
											   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_SetAudioPlayerVolume(LPROBOTINTERFACE lpRobotInterface,
													  WORD wCmdID,
													  INT nChannel,
													  INT nLevel,
													  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_ReqAudioPlayerVolume(LPROBOTINTERFACE lpRobotInterface,
													  WORD wCmdID,
													  INT nChannel,
													  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_SetAudioPlayerMuteChannel(LPROBOTINTERFACE lpRobotInterface,
														   WORD wCmdID,
														   INT nChannel,
														   BOOL bMute,
														   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_SetAudioRecordVolume(LPROBOTINTERFACE lpRobotInterface,
													  WORD wCmdID,
													  INT nChannel,
													  INT nLevel,
													  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_ReqAudioRecordVolume(LPROBOTINTERFACE lpRobotInterface,
													  WORD wCmdID,
													  INT nChannel,
													  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_SetAudioRecordCtrlProperty(LPROBOTINTERFACE lpRobotInterface,
															WORD wCmdID,
															INT nChannel,
															INT nControlType,
															DWORD dwValue,
															BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_OpenCamera(LPROBOTINTERFACE lpRobotInterface,
											WORD wCmdID,
											LPCAMERAOPENPARAMS lpCameraParams,
											BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_OpenCameraEx(LPROBOTINTERFACE lpRobotInterface,
											  WORD wCmdID,
											  LPCAMERAOPENPARAMSEX lpCameraParamsEx,
											  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_CloseCamera(LPROBOTINTERFACE	lpRobotInterface,
											 WORD wCmdID,
											 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_StartRecordVideo(LPROBOTINTERFACE	lpRobotInterface,
												  WORD wCmdID,
												  LPVIDEORECPARAMS lpVideoRecParams,
												  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_StopRecordVideo(LPROBOTINTERFACE	lpRobotInterface,
												  WORD wCmdID,
												  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_StartPlayVideo(LPROBOTINTERFACE	lpRobotInterface,
												WORD wCmdID,
												LPVIDEOPLAYPARAMS lpVideoPlayParams,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_StopPlayVideo(LPROBOTINTERFACE	lpRobotInterface,
											   WORD wCmdID,
											   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_StartRecordAudio(LPROBOTINTERFACE	lpRobotInterface,
												  WORD wCmdID,
												  LPAUDIORECPARAMS lpAudioRecParams,
												  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_StopRecordAudio(LPROBOTINTERFACE	lpRobotInterface,
												 WORD wCmdID,
												 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_StartPlayAudio(LPROBOTINTERFACE	lpRobotInterface,
												WORD wCmdID,
												LPAUDIOPLAYPARAMS lpAudioPlayParams,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_StopPlayAudio(LPROBOTINTERFACE	lpRobotInterface,
											   WORD wCmdID,
											   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_CaptureImage(LPROBOTINTERFACE	lpRobotInterface,
											  WORD wCmdID,
											  LPCAPTUREIMAGEPARAMS lpCaptureImageParams,
											  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_StartCapImgPeriod(LPROBOTINTERFACE lpRobotInterface,
												   WORD wCmdID,
												   LPCAPIMGPERIODPARAMS lpCapImgPeriodParams,
												   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_StopCapImgPeriod(LPROBOTINTERFACE lpRobotInterface,
												  WORD wCmdID,
												  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_ReqRobotProfile(LPROBOTINTERFACE lpRobotInterface,
												 WORD wCmdID,
												 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_UpateRobotProfile(LPROBOTINTERFACE lpRobotInterface,
												   WORD wCmdID,
												   LPROBOTPROFILE lpRobotProfile,
												   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_ReqUserInfoListString(LPROBOTINTERFACE lpRobotInterface,
													   WORD wCmdID,
													   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_AddUserInfo(LPROBOTINTERFACE lpRobotInterface,
											 WORD wCmdID,
											 LPUSERINFO lpUserInfo,
											 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_DeleteUserInfo(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												INT nUserID,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_UpdateUserInfo(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												LPUSERINFO lpUserInfo,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_ReqScheduleInfoListString(LPROBOTINTERFACE lpRobotInterface,
														   WORD wCmdID,
														   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_AddScheduleInfo(LPROBOTINTERFACE lpRobotInterface,
												 WORD wCmdID,
												 LPSCHEDULEINFO lpScheduleInfo,
												 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_DeleteScheduleInfo(LPROBOTINTERFACE lpRobotInterface,
													WORD wCmdID,
													INT nScheduleID,
													BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_UpdateScheduleInfo(LPROBOTINTERFACE lpRobotInterface,
													WORD wCmdID,
													LPSCHEDULEINFO lpScheduleInfo,
													BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_ReqMemoInfoListString(LPROBOTINTERFACE lpRobotInterface,
													   WORD wCmdID,
													   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_AddMemoInfo(LPROBOTINTERFACE lpRobotInterface,
											 WORD wCmdID,
											 LPMEMOINFO lpMemoInfo,
											 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_DeleteMemoInfo(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												INT nMemoID,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_UpdateMemoInfo(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												LPMEMOINFO lpMemoInfo,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_SaveSvcConfig(LPROBOTINTERFACE lpRobotInterface,
											   WORD wCmdID,
											   LPCTSTR lpszAppName,
											   LPCTSTR lpszKeyName,
											   LPCTSTR lpszValue,
											   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_LoadSvcConfig(LPROBOTINTERFACE lpRobotInterface,
											   WORD wCmdID,
											   LPCTSTR lpszAppName,
											   LPCTSTR lpszKeyName,
											   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_LoadSysConfig(LPROBOTINTERFACE lpRobotInterface,
											   WORD wCmdID,
											   LPCTSTR lpszAppName,
											   LPCTSTR lpszKeyName,
											   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJDB_CreateTable(LPROBOTINTERFACE lpRobotInterface,
											 WORD wCmdID,
											 LPCTSTR lpszTableName,
											 LPCTSTR lpszFieldName,
											 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJDB_EraseTable(LPROBOTINTERFACE lpRobotInterface,
											WORD wCmdID,
											LPCTSTR lpszTableName,
											BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJDB_ReqRowString(LPROBOTINTERFACE lpRobotInterface,
											  WORD wCmdID,
											  LPCTSTR lpszTableName,
											  LPCTSTR lpszFieldname,
											  LPCTSTR lpszFieldData,
											  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJDB_ReqRowInt(LPROBOTINTERFACE lpRobotInterface,
										   WORD wCmdID,
										   LPCTSTR lpszTableName,
										   LPCTSTR lpszFieldName,
										   INT nFieldData,
										   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJDB_CreateRow(LPROBOTINTERFACE lpRobotInterface,
										   WORD wCmdID,
										   LPCTSTR lpszTablename,
										   LPCTSTR lpszFieldName,
										   LPCTSTR lpszFieldData,
										   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJDB_EraseRowInt(LPROBOTINTERFACE lpRobotInterface,
											 WORD wCmdID,
											 LPCTSTR lpszTableName,
											 LPCTSTR lpszFieldName,
											 INT nFieldData,
											 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJDB_EraseRowString(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												LPCTSTR lpszTableName,
												LPCTSTR lpszFieldName,
												LPCTSTR lpszFieldData,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJDB_ReqColumn(LPROBOTINTERFACE lpRobotInterface,
										   WORD wCmdID,
										   LPCTSTR lpszTableName,
										   LPCTSTR lpszFieldName,
										   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJDB_ReqCell(LPROBOTINTERFACE lpRobotInterface,
										 WORD wCmdId,
										 LPCTSTR lpszTableName,
										 LPCTSTR lpszFieldName,
										 LPCTSTR lpszCondition,
										 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJDB_UpdateCell(LPROBOTINTERFACE lpRobotInterface,
											WORD wCmdID,
											LPCTSTR lpszTablename,
											LPCTSTR lpszData,
											LPCTSTR lpszCondition,
											BOOL bNeedAck = FALSE);

/**
 *
 * Command Type : System Profiles
 *
 */

YJRESULT ROBOTINTERFACE_API YJSP_ReqIdleTime(LPROBOTINTERFACE lpRobotInterface,
											 WORD wCmdID,
											 DWORD dwOption,
											 DWORD dwReserved,
											 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_SystemDirectory(LPROBOTINTERFACE lpRobotInterface,
												 WORD wCmdID,
												 DWORD dwDirectory,
												 DWORD dwReserved,
												 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_NetworkConfiguration(LPROBOTINTERFACE lpRobotInterface,
													  WORD wCmdID,
													  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_ShowKeyboard(LPROBOTINTERFACE lpRobotInterface,
											  WORD wCmdID, 
											  BOOL bShow, 
											  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_ChangeLanguage(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												DWORD dwLanguage,
												DWORD dwReserved,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_LoadApp(LPROBOTINTERFACE lpRobotInterface,
										 WORD wCmdID,
										 WORD wTargetAppID,
										 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_LoadAppEx(LPROBOTINTERFACE lpRobotInterface,
										   WORD wCmdID,
										   DWORD dwAppID,
										   DWORD dwReserved,
										   LPCTSTR lpszArgs,
										   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_CloseApp(LPROBOTINTERFACE lpRobotInterface,
										  WORD wCmdID,
										  WORD wTargetAppID,
										  DWORD dwExitType,
										  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_CreateFolder(LPROBOTINTERFACE lpRobotInterface,
											  WORD wCmdID,
											  DWORD dwAppID,
											  LPCTSTR lpszFolderName,
											  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_DelFolder(LPROBOTINTERFACE lpRobotInterface,
										   WORD wCmdID,
										   DWORD dwAppID,
										   LPCTSTR lpszFolderName,
										   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_DelFile(LPROBOTINTERFACE lpRobotInterface,
										 WORD wCmdID,
										 DWORD dwAppID,
										 LPCTSTR lpszFileName,
										 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_FileMove(LPROBOTINTERFACE lpRobotInterface,
										  WORD wCmdID,
										  DWORD dwAppID,
										  LPCTSTR lpszSrcFileName,
										  LPCTSTR lpszDstFileName,
										  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_CopyFile(LPROBOTINTERFACE lpRobotInterface,
										  WORD wCmdID,
										  LPCTSTR lpszExistingFileName,
										  LPCTSTR lpszNewFileName,
										  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_FileList(LPROBOTINTERFACE lpRobotInterface,
										  WORD wCmdID,
										  DWORD dwAppID,
										  LPCTSTR lpszPath,
										  LPCTSTR lpszExtOpt,
										  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_FileListString(LPROBOTINTERFACE lpRobotInterface,
												WORD wCmdID,
												DWORD dwAppID,
												LPCTSTR lpszPath,
												LPCTSTR lpszExtOpt,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_DiskUsage(LPROBOTINTERFACE lpRobotInterface,
										   WORD wCmdID,
										   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_GetRemovableMedia(LPROBOTINTERFACE lpRobotInterface,
												   WORD wCmdID,
												   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_SetCurFolder(LPROBOTINTERFACE lpRobotInterface,
											  WORD wCmdID,
											  DWORD dwAppID,
											  LPCTSTR lpszSetFolderName,
											  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_WriteString(LPROBOTINTERFACE lpRobotInterface,
											 WORD wCmdID,
											 LPCTSTR lpszFileName,
											 DWORD dwOption,
											 LPCTSTR lpszText,
											 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_CreateDirectoryEx(LPROBOTINTERFACE lpRobotInterface,
												   WORD wCmdID,
												   LPCTSTR lpszPathName,
												   DWORD dwReserved,
												   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_EnumerateFilesToString(LPROBOTINTERFACE lpRobotInterface,
														WORD wCmdID,
														LPCTSTR lpszPathName,
														LPCTSTR lpszFilter,
														DWORD dwReserved,
														BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_ReqSessionKey(LPROBOTINTERFACE lpRobotInterface,
											   WORD wCmdID,
											   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_LiveUpdate(LPROBOTINTERFACE lpRobotInterface,
											WORD wCmdID,
											BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSP_HttpPost(LPROBOTINTERFACE lpRobotInterface,
										  WORD wCmdID,
										  LPCTSTR lpszServerName,
										  LPCTSTR lpszObjectName,
										  LPCTSTR lpszFormData,
										  BOOL bNeedAck = FALSE);


/**
 *
 * Utility function
 *
 */

YJRESULT ROBOTINTERFACE_API YJCI_RegAppendantParserProc(LPROBOTINTERFACE lpRobotInterface,
														APPENDANTPARSERPROC fnAppendantParser);

YJRESULT ROBOTINTERFACE_API YJCI_SendCompletionMessage(LPROBOTINTERFACE lpRobotInterface, 
													   LPCSTR lpszNomiMessage,
													   DWORD dwNomiMsgSize);

YJRESULT ROBOTINTERFACE_API YJCI_SendUserMessage(LPROBOTINTERFACE lpRobotInterface, 
												 LPCSTR lpszMessage,
												 DWORD dwMsgSize);

YJRESULT ROBOTINTERFACE_API YJCI_RegWindowHandle(LPROBOTINTERFACE lpRobotInterface, 
												 WORD wCmdID,
												 HWND hWnd);

YJRESULT ROBOTINTERFACE_API YJCI_SendAcknowledge(LPROBOTINTERFACE lpRobotInterface,
												 DWORD dwTaskID,
												 WORD wAppID,
												 WORD wCmdID);

YJRESULT ROBOTINTERFACE_API YJCI_SendResponse(LPROBOTINTERFACE lpRobotInterface,
											  DWORD dwTaskID,
											  WORD wAppID,
											  WORD wCmdID,
											  DWORD dwResultCode);

YJRESULT ROBOTINTERFACE_API YJCI_SendEvent(LPROBOTINTERFACE lpRobotInterface,
										   DWORD dwTaskID,
										   WORD wAppID,
										   WORD wCmdID,
										   DWORD dwResultCode,
										   DWORD dwStatus,
										   DWORD dwReserved);

YJRESULT ROBOTINTERFACE_API YJCI_SetRefDirectory(LPROBOTINTERFACE pri,
												 LPCTSTR lpszDirectory);


/**
 * 
 * Service specific function
 *
 */

YJRESULT ROBOTINTERFACE_API YJSS_SendRecognizedWord(LPROBOTINTERFACE pri,
													WORD wCmdID,
													LPCTSTR pszWord,
													INT nScore,
													BOOL bNeedAck = FALSE);


/**
 * 
 * Serving Interface
 *
 */

YJRESULT ROBOTINTERFACE_API YJBH_SR_MoveArm(LPROBOTINTERFACE pri,
											WORD wCmdID,
											LP_SERVING_ARM_CONTROL lpActionParams,
											BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_StartRFIDScan(LPROBOTINTERFACE lpRobotInterface,
											   WORD wCmdID,
											   BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJRI_StopRFIDScan(LPROBOTINTERFACE lpRobotInterface,
											  WORD wCmdID,
											  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSI_ReqCustomerInfo(LPROBOTINTERFACE pri,
												 WORD wCmdID,
												 LPCTSTR lpszCustomerID,
												 BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSI_ReqOrderInfo(LPROBOTINTERFACE pri,
											  WORD wCmdID,
											  LPCTSTR lpszCustomerID,
											  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSI_ReqReservationInfo(LPROBOTINTERFACE pri,
													WORD wCmdID,
													LPCTSTR lpszCustomerID,
													BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSI_ReqTableStatus(LPROBOTINTERFACE pri,
												WORD wCmdID,
												BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSI_ReqTableInfo(LPROBOTINTERFACE pri,
											  WORD wCmdID,
											  LPCTSTR lpszTableCode,
											  BOOL bNeedAck = FALSE);

YJRESULT ROBOTINTERFACE_API YJSI_ReqWaitingRoomInfo(LPROBOTINTERFACE pri,
													WORD wCmdID,
													BOOL bNeedAck = FALSE);

//-#ifdef __cplusplus
//-}
//-#endif


#endif // __YJROBOTAPI_H__
