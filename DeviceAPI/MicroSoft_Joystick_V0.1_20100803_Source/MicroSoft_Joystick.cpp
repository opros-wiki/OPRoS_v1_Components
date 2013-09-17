#include "MicroSoft_Joystick.h"
#include "OprosPrintMessage.h"

#include <Mmsystem.h>

#if defined(WIN32)
#pragma warning(disable : 4996)
#endif

MicroSoft_Joystick::MicroSoft_Joystick(void)
{
}

MicroSoft_Joystick::~MicroSoft_Joystick(void)
{
}

int MicroSoft_Joystick::Initialize(Property parameter)
{
	if( SetParameter(parameter) == API_ERROR ) {
		return API_ERROR;
	}
	return API_SUCCESS;
}

int MicroSoft_Joystick::Enable(void)
{
	return API_SUCCESS;
}

int MicroSoft_Joystick::Disable(void)
{
	return API_SUCCESS;
}

int MicroSoft_Joystick::Finalize(void)
{
	return API_SUCCESS;
}

int MicroSoft_Joystick::SetParameter(Property parameter)
{
	this->parameter = parameter;

	return API_SUCCESS;
}

int MicroSoft_Joystick::GetParameter(Property &parameter)
{
	parameter = this->parameter;

	return API_SUCCESS;
}

int MicroSoft_Joystick::GetJoystickData(JoystickData &joystickData)
{
	JOYINFOEX joyinfo;

	memset (&joyinfo, 0, sizeof(JOYINFOEX));
	joyinfo.dwSize = sizeof(JOYINFOEX);
	joyinfo.dwFlags = JOY_RETURNALL;

	if (joyGetPosEx(JOYSTICKID1 , &joyinfo) == JOYERR_NOERROR) {
		//DWORD wJoyButtons = joyinfo.dwButtons;
		WORD wJoyXPos = WORD(joyinfo.dwXpos);
		WORD wJoyYPos = WORD(joyinfo.dwYpos);
		WORD wJoyThrottle = WORD(joyinfo.dwZpos);

		// !!! Joystic의 중심값에 대한 공차 설정
		const long joystickDeadZone = 3500;
		if ((32768-joystickDeadZone) < (long)wJoyYPos && (long)wJoyYPos < (32768+joystickDeadZone)) wJoyYPos = 32768;
		if ((32768-joystickDeadZone) < (long)wJoyXPos && (long)wJoyXPos < (32768+joystickDeadZone)) wJoyXPos = 32768;

		joystickData.x = (wJoyXPos-32768)/32768.;
		joystickData.y = (wJoyYPos-32768)/32768.;
		joystickData.z = (wJoyThrottle-32768)/32768.;
		joystickData.button.resize(32);

		WORD buttons = WORD(joyinfo.dwButtons);
		for( int i = 0  ;  i < 32  ;  i++ ) {
			joystickData.button[i] = (joyinfo.dwButtons & (1<<i)) ? true : false;
		}
		return API_SUCCESS;
	}
	else {
		PrintMessage("ERROR:MicroSoft_Joystick::GetJoystickData() -> Joystick Error\n");
		return API_ERROR;
	}
}

#if defined(WIN32)
extern "C"
{
__declspec(dllexport) OprosApi *GetAPI();
__declspec(dllexport) void ReleaseAPI(OprosApi *api);
}

OprosApi *GetAPI()
{
	return new MicroSoft_Joystick();
}

void ReleaseAPI(OprosApi *api)
{
	delete api;
}
#endif
