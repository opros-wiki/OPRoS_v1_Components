#pragma once

#define	INSTRUCTION_ERROR	0x40	//정의되지 않은 Instruction이 전송된 경우. 또는 reg_write 명령없이 action명령이 전달된 경우 1로 설정됨
#define	OVERLOAD_ERROR		0x20	//지정된 최대 Torque로 현재의 하중을 제어할 수 없을 때 1로 설정됨
#define	CHECKSUM_ERROR		0x10	//전송된 Instruction Packet의 Checksum이 맞지 않을 때1로 설정됨
#define	RANGE_ERROR			0x08	//사용범위를 벗아난 명령일 경우 1로 설정됨.
#define	OVERHEATING_ERROR	0x04	//Dynamixel 내부 온도가 Control Table에 설정된 동작 온도범위를 벗어났을 때 1로 설정됨
#define	ANGLELIMIT_ERROR	0x02	//Goal Position이 CW Angle Limit ~ CCW Angle Limit 범위밖의 값으로 Writing 되었을때 1로 설정됨
#define	INPUTVOLTAGE_ERROR	0X01	//인가된 전압이 Control Table에 설정된 동작 전압 범위를벗어났을 경우 1로 설정됨

#define ID_BROADCAST		0xFE

#define	START_PACK			0xFFFF
#define	PING				0x01
#define	READ_DATA			0x02
#define	WRITE_DATA			0x03
#define	REG_WRITE			0x04
#define	ACTION				0x05
#define	RESET				0x06
#define	SYNC_WRITE			0x83

//	Control Table
#define	DynamixelCAN_MODEL_NUMBER_W					0x00	//	RD
#define	DynamixelCAN_VERSION_OF_FIRMWARE			0x02	//	RD
#define	DynamixelCAN_ID								0x03	//	RD, WR
#define	DynamixelCAN_BAUDRATE						0x04	//	RD,	WR
#define	DynamixelCAN_RETURN_DELAY_TIME				0x05	//	RD, WR
#define	DynamixelCAN_CW_ANGLE_LIMIT_W				0x06	//	RD, WR
#define	DynamixelCAN_CCW_ANGLE_LIMIT_W				0x08	//	RD, WR
#define	DynamixelCAN_HIGHTEST_LIMIT_TEMPERATURE		0x0B	//	RD, WR
#define	DynamixelCAN_LOWEST_LIMIT_VOLTAGE			0x0C	//	RD, WR
#define	DynamixelCAN_HIGHEST_LIMIT_VOLTAGE			0x0D	//	RD, WR
#define	DynamixelCAN_MAX_TORQUE_W					0x0E	//	RD, WR
#define	DynamixelCAN_STATUS_RETURN_VALUE			0x10	//	RD, WR
#define	DynamixelCAN_ALARM_LED						0x11	//	RD, WR
#define	DynamixelCAN_ALARM_SHUTDOWN					0x12	//	RD, WR
#define	DynamixelCAN_DOWN_CALIBRATION_W				0x14	//	RD
#define	DynamixelCAN_UP_CALIBRATION_W				0x16	//	RD
#define	DynamixelCAN_TORQUE_EABLE					0x18	//	RD, WR
#define	DynamixelCAN_LED							0x19	//	RD, WR
#define	DynamixelCAN_CW_COMPLIANCE_MARGIN			0x1A	//	RD, WR
#define	DynamixelCAN_CCW_COMPLIANCE_MARGIN			0x1B	//	RD, WR
#define	DynamixelCAN_CW_COMPLICANCE_SLOPE			0x1C	//	RD, WR
#define	DynamixelCAN_CCW_COMPLICANCE_SLOPE			0x1D	//	RD, WR
#define	DynamixelCAN_GOAL_POSITION_W				0x1E	//	RD, WR
#define	DynamixelCAN_MOVING_SPEED_W					0x20	//	RD, WR
#define	DynamixelCAN_TORQUE_LIMIT_W					0x22	//	RD, WR
#define	DynamixelCAN_PRESENT_POSITION_W				0x24	//	RD
#define	DynamixelCAN_PRESENT_SPEED_W				0x26	//	RD
#define	DynamixelCAN_PRESENT_LOAD_W					0x28	//	RD
#define	DynamixelCAN_PRESENT_VOLTAGE				0x2A	//	RD
#define	DynamixelCAN_PRESETN_TEMPERATURE			0x2B	//	RD
#define	DynamixelCAN_REGISTERED_INSTRUCTION			0x2C	//	RD, WR
#define	DynamixelCAN_MOVING							0x2E	//	RD, WR
#define	DynamixelCAN_LOCK							0x2F	//	RD, WR
#define	DynamixelCAN_PUNCH_W						0x30	//	RD, WR