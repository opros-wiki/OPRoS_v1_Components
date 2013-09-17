#pragma once

#define	UCMC_DEVICE_TYPE					0x1000, 0x00	//											(unsigned 32bit, RO)
	#define	UCMC_SERVO_CONTROLLER				0x00020192	//	CiA Draft Standard Proposal 402

#define UCMC_ERROR_REGISTER					0x1001,	0x00	//	CANOpen Error 							(unsigned 8bit, RO)
	#define	UCMC_GENERIC_ERROR					0x01
	#define	UCMC_CURRENT_ERROR					0x02
	#define	UCMC_VOLTAGE_ERROR					0x04
	#define	UCMC_TEMP_ERROR						0x08
	#define	UCMC_COMM_ERROR						0x10
	#define	UCMC_DEV_PROFILE_ERROR				0x20
	#define	UCMC_MOTION_ERROR					0x80

#define UCMC_VENDOR_ID						0x1018,	0x01	//											(unsigned 32bit, RO)
#define UCMC_PRODUCT_CODE					0x1018,	0x02	//											(unsigned 32bit, RO)

#define	UCMC_COMMUNICATION_TYPE				0x2000, 0x00	//	Communication type
#define	UCMC_COMMUNICATION_SPEED			0x2001, 0x00	//	Communication speed
#define	UCMC_COMMUNICATION_ID				0x2002, 0x00	//	Communication ID

#define	UCMC_TARGET_CURRENT					0x2100, 0x00	//	The current mode setting value			(signed 32bit, RW)
#define UCMC_CURRENT_ACTUAL_VALUE_AVERAGED	0x2101,	0x00	//	The averaged current (RO)				(signed 32bit, RO)
#define	UCMC_HALL_SENSOR					0x2180, 0x00	//	The hall sensor pattern					(unsigned 8bit, RO)
#define UCMC_ENCODER_PULSE_NUMBER			0x2200,	0x00	//	The encoder pulse number				(unsigned 16bit, RW)
#define	UCMC_REFERENCE_VELOCITY				0x2201, 0x00	//	The reference velocity					(signed 16bit, RW)
#define	UCMC_REFERENCE_POSITION				0x2300, 0x00	//	The reference position					(signed 32bit, RW)
#define	UCMC_ABSOLUTE_POSITION				0x2301, 0x00	//	The absolute position					(signed 32bit, RO)
#define UCMC_DEVICE_WARNING					0x2F00, 0x00	//  Device Warning							(unsigned 16bit, RO)
	#define UCMC_WARNING_NSW_LIMIT				0x2001		// Negative SW Limit Error
	#define UCMC_WARNING_PSW_LIMIT				0x2002		// Positive SW Limit Error
	#define UCMC_WARNING_VEL					0x2003		// Velocity Error (abs(profile - actual) > xx pulse/ms)
	#define UCMC_WARNING_POS					0x2004		// Position Error (abs(profile - actual) > xx pulse)

// Analog and Digital Input/Output Device
#define	UCMC_NUMBER_OF_DIS					0x3000, 0x00	//	Count of Digital Input Port				(unsigned 8bit, RO)
#define	UCMC_DI_0							0x3001, 0x00	//	Value of Digital Input					(unsigned 32bit, RO)
#define	UCMC_NUMBER_OF_DOS					0x3002, 0x00	//	Count of Digital Output Port			(unsigned 8bit, RO)
#define	UCMC_DO_0							0x3003, 0x00	//	Value of Digital Output					(unsigned 32bit, RW)
#define	UCMC_AI_0							0x3010, 0x00	//	Analog input							(unsigned 16bit, RO)
#define	UCMC_AO_0							0x3011, 0x00	//	Analog output							(unsigned 16bit, RW)

#define	UCMC_DEVICE_ERROR					0x603F, 0x00	//	Device Error							(unsigned 16bit, RO)
	#define UCMC_ERROR_GEN_ERR					0x0001		// 
	#define UCMC_ERROR_SW_RESET					0x0002		// Software Reset (WatchDog)
	#define UCMC_ERROR_MOTOR_ERR				0x1001		// Motor Error(No Motor Current)
	#define UCMC_ERROR_ENC_ERR					0x1002		// Encoder Error
	#define UCMC_ERROR_HALL_ERR					0x1003		// Hall Sensor Error
	#define UCMC_ERROR_OVER_LOAD				0x1004		// Overload Error
	#define UCMC_ERROR_OVER_CUR					0x1005		// Over Current Error
	#define UCMC_ERROR_PEAK_CUR_ERR				0x1006		// Peak Current Error

#define UCMC_CONTROL_WORD					0x6040,	0x00	 //	Command									(unsigned 8bit, WO)
	#define	UCMC_INIT							0x0001
	#define	UCMC_RESET							0x0002
	#define	UCMC_CLEAR_ERROR					0x0003
	#define	UCMC_EN_SERVO						0x0004
	#define	UCMC_DI_SERVO						0x0005
	#define	UCMC_QUICK_STOP						0x0006
	#define	UCMC_START_HOMING					0x0007
	#define	UCMC_SAVE_TO_EEPROM					0x00FE		//	Save parameters to EEPROM
	#define	UCMC_LOAD_FROM_EEPROM				0x00FF		//	Load parameters from EEPROM

#define UCMC_STATUS_WORD					0x6041,	0x00	//	Status									(unsigned 16bit, RO)
	#define	UCMC_STATUS_CUR						0x0001		//	The current mode
	#define	UCMC_STATUS_VEL						0x0002		//	The velocity mode
	#define	UCMC_STATUS_PRO_VEL					0x0004		//	The profile velocity mode
	#define	UCMC_STATUS_POS						0x0008		//	The position mode
	#define	UCMC_STATUS_PRO_POS					0x0010		//	The profile position mode
	#define	UCMC_STATUS_HOMING					0x0020		//	The homing mode
	#define	UCMC_SERVO_ON						0x0080		//	The servo on/off
	#define	UCMC_COMP_HOME						0x0100		//	Complete homing
	#define	UCMC_OCCUR_ERR						0x0200		//	Occur a error
	#define	UCMC_OCCUR_WARN						0x0400		//	Occur a warning
	#define	UCMC_RUNNING						0x8000		//	Is Running

#define UCMC_MODES_OF_OPERATION				0x6060,	0x00  	//	Mode									(unsigned 8bit, RW)
	#define	UCMC_MODE_HOMING					0x06
	#define	UCMC_MODE_PRO_VEL					0x03
	#define	UCMC_MODE_PRO_POS					0x01
	#define	UCMC_MODE_POS						0xFF
	#define	UCMC_MODE_VEL						0xFE
	#define	UCMC_MODE_CUR						0xFC

#define UCMC_POSITION_ACTUAL_VALUE			0x6064,	0x00  	//	The actual position						(signed 32bit, RW)

#define UCMC_VELOCITY_ACTUAL_VALUE			0x606C,	0x00	//	The actual velocity						(signed 16bit, RO)  

#define UCMC_CURRENT_ACTUAL_VALUE			0x6078,	0x00	//	The actual current						(signed 32bit, RO)

#define UCMC_PROFILE_TARGET_POSITION		0x607A,	0x00  	//	The target position						(signed 32bit, RW)
#define UCMC_MIN_POSITION_LIMIT				0x607D,	0x01  	//	The minimal position limit				(signed 32bit, RW)
#define UCMC_MAX_POSITION_LIMIT				0x607D,	0x02  	//	The maximum position limit				(signed 32bit, RW)

#define UCMC_MAX_VELOCITY					0x607F,	0x00 	//	The maximum velocity					(signed 16bit, RW) 
#define UCMC_PROFILE_VELOCITY				0x6081,	0x00 	//	The profile velocity					(signed 16bit, RW) 
#define UCMC_PROFILE_ACCELERATION			0x6083,	0x00 	//	The acceleration						(signed 32bit, RW) 
#define UCMC_PROFILE_DECELERATION			0x6084,	0x00 	//	The deceleration						(signed 32bit, RW) 
#define UCMC_QUICKSTOP_DECELERATION			0x6085,	0x00 	//	The quick stop deceleration				(signed 32bit, RW) 

#define	UCMC_MOTION_PROFILE_TYPE			0x6086, 0x00	//	The motion profile type					(singed 16bit, RW)

#define UCMC_HOMING_METHOD					0x6098,	0x00	//	The homing method						(unsigned 8bit, RW)
															//	0 - Absolute encoder or potentiometer, 1 - Home sensor
#define UCMC_SPEED_FOR_SWITCH_SEARCH		0x6099,	0x01  	//	The velocity for switch search			(signed 16bit, RW)
#define UCMC_SPEED_FOR_ZERO_SEARCH			0x6099,	0x02  	//	The velocity for zero search			(signed 16bit, RW)

#define UCMC_CURRENT_REGULATOR_P_GAIN		0x60F6,	0x01	//	The P gain for current control			(signed 16bit, RW)
#define UCMC_CURRENT_REGULATOR_I_GAIN		0x60F6,	0x02	//	The I gain for current control			(signed 16bit, RW)

#define UCMC_SPEED_REGULATOR_P_GAIN			0x60F9,	0x01  	//	The velocity P gain						(signed 16bit, RW)
#define UCMC_SPEED_REGULATOR_I_GAIN			0x60F9,	0x02  	//	The velocity I gain						(signed 16bit, RW)
#define UCMC_SPEED_REGULATOR_D_GAIN			0x60F9,	0x03  	//	The velocity D gain						(signed 16bit, RW)

#define UCMC_POSITION_REGULATOR_P_GAIN		0x60FB,	0x01	//	The position P gain						(signed 16bit, RW)
#define UCMC_POSITION_REGULATOR_I_GAIN		0x60FB,	0x02  	//	The position I gain						(signed 16bit, RW)
#define UCMC_POSITION_REGULATOR_D_GAIN		0x60FB,	0x03  	//	The position D gain						(signed 16bit, RW)

#define UCMC_PROFILE_TARGET_VELOCITY		0x60FF,	0x00 	//	The target velocity						(signed 16bit, RW) 

#define UCMC_CONTINUOUS_CURRENT_LIMIT		0x6410,	0x01	//	The continuous current limit			(signed 32bit, RW)
#define UCMC_OUTPUT_CURRENT_LIMIT			0x6410,	0x02	//	The output current limit				(signed 32bit, RW)
#define UCMC_OUTPUT_POLE_PAIR_NUM			0x6410,	0x03	//	The pole pair number					(unsigned 8bit, RW)

#define UCMC_SUPPORTED_DRIVE_MODES			0x6502,	0x00	//	Control Mode							(unsigned 32bit, RW)
	#define	UCMC_CURRENT_CTRL_MODE				0x01
	#define	UCMC_VELOCITY_CTRL_MODE				0x02
	#define	UCMC_POSITION_CTRL_MODE				0x04

//	Synchronization
	#define	UCMC_SYNC_SET_NONE					0x00
	#define	UCMC_SYNC_SET_CURRENT				0x01
	#define	UCMC_SYNC_SET_VELOCITY				0x02
	#define	UCMC_SYNC_SET_POSITION				0x03
	#define	UCMC_SYNC_GET_STATUS				0x10
	#define	UCMC_SYNC_GET_CURRENT				0x20
	#define	UCMC_SYNC_GET_VELOCITY				0x40
	#define	UCMC_SYNC_GET_POSITION				0x80

//	Abort messages
#define	MC_ABORT_MSG						0x00C0
	#define	MC_NO_OBJ_ERR						0x06020000	//	Object does not exist Error
	#define	MC_SUB_INDEX_ERR					0x06090011	//	Sub-Index Error
	#define	MC_ACC_ERR							0x06010000	//	General parameter incompatibility
	#define	MC_RD_ERR							0x06010001	//	Read Error -> Write Only Object
	#define	MC_WR_ERR							0x06010002	//	Write Error -> Read Only Object
	#define	MC_SP_ERR							0x06070010	//	Service Parameter Error
	#define	MC_VH_ERR							0x06090031	//	Value too High Error
	#define	MC_VL_ERR							0x06090032	//	Value too Low Error
	#define	MC_LESS_ERR							0x06090036	//	Maximal value is less than minimal value
	#define	MC_MORE_ERR							0x06090037	//	Minimal value is more than maximal value
	#define	MC_GEN_ERR							0x08000000	//	General Parameter Error
	#define	MC_ID_ERR							0x0F00FFB8	//	ID Error
	#define	MC_SM_ERR							0x0F00FFBC	//	Not support the service in present mode

#define	MAX_TARGET_CURRENT					4096
#define	MAX_TARGET_VELOCITY					1024
#define	MAX_TARGET_POSITION					65535

enum eSDO_COMMAND {
	WRITE_REQUEST			= 0x22,
	WRITE_REQUEST_4BYTE		= 0x23,
	WRITE_REQUEST_2BYTE		= 0x2B,
	WRITE_REQUEST_1BYTE		= 0x2F,
	WRITE_RESPONSE			= 0x60,

	READ_REQUEST			= 0x40,
	READ_RESPONSE_MAX4BYTE	= 0x42,
	READ_RESPONSE_4BYTE		= 0x43,
	READ_RESPONSE_2BYTE		= 0x4B,
	READ_RESPONSE_1BYTE		= 0x4F,

	ABORT_MESSAGE1			= 0x80,	// BMMX Absolute encoder
	ABORT_MESSAGE2			= 0xC0,	// EPOS, UCMC
};

enum eFC_PTP_ID {
	FC_EMERGENCY		= 0x80,
	FC_SDO1_RX			= 0x580,
	FC_SDO1_TX			= 0x600,
	FC_Heartbeat		= 0x700,
};
