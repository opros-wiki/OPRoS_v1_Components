/*************************************************************

 file: KeyInputComponent.cpp
 author: S.G. Bang
 begin: April 20 2010
 copyright: (c) 2010 KNU, OPRoS
 email: hspark@kangwon.ac.kr

***************************************************************

OPRoS source code is provided under a dual license mode:
 LGPL and OPRoS individually.

LGPL: You can redistribute it and/or modify it under the terms
 of the Less GNU General Public License as published by the Free
 Software Foundation, either version 3 of the License.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of 
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 Less GNU General Public License for more details. 

 You should have received a copy of the Less GNU General Public
 License along with this program. If not, see 
 <http://www.gnu.org/licenses/>.

OPRoS individual license: An individual license is a license for
 modifying the source code of OPRoS and distiributing it in a
 closed format for commercial purposes.

 If you are interested in this option, please see 
 <http://www.opros.or.kr>.

This license policy may be changed without prior notice.

***************************************************************/
#include "KeyInputComponent.h"

//
// constructor declaration
//
KeyInputComponent::KeyInputComponent()
{
	ptrKeyInputServicePort = this;
	portSetup();
}

//
// constructor declaration (with name)
//
KeyInputComponent::KeyInputComponent(const std::string &name):Component(name)
{
	ptrKeyInputServicePort = this;
	portSetup();
}

//
// destructor declaration
//

KeyInputComponent::~KeyInputComponent()
{

}

void KeyInputComponent::portSetup()
{
	// provided mehod port setup
	// assert(ptrKeyInputServicePort != NULL);
	ProvidedServicePort *pa1;
	pa1=new KeyInputServicePortProvided(this);


	addPort("KeyInputServicePort",pa1);

	// data port setup
	//	addPort("distanceValue", &distanceValue);
}

// Call back Declaration
ReturnType KeyInputComponent::onInitialize()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KeyInputComponent::onStart()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KeyInputComponent::onStop()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KeyInputComponent::onReset()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KeyInputComponent::onError()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KeyInputComponent::onRecover()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KeyInputComponent::onDestroy()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KeyInputComponent::onEvent(Event *evt)
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KeyInputComponent::onExecute()
{
	// user code here
	ret = 0;

	if(GetAsyncKeyState('0'))	{
		ret = 48;
	}
	else if(GetAsyncKeyState('1'))	{
		ret = 49;
	}
	else if(GetAsyncKeyState('2'))	{
		ret = 50;
	}
	else if(GetAsyncKeyState('3'))	{
		ret = 51;
	}
	else if(GetAsyncKeyState('4'))	{
		ret = 52;
	}
	else if(GetAsyncKeyState('5'))	{
		ret = 53;
	}
	else if(GetAsyncKeyState('6'))	{
		ret = 54;
	}
	else if(GetAsyncKeyState('7'))	{
		ret = 55;
	}
	else if(GetAsyncKeyState('8'))	{
		ret = 56;
	}
	else if(GetAsyncKeyState('9'))	{
		ret = 57;
	}
	else if(GetAsyncKeyState('A'))	{
		ret = 64;
	}
	else if(GetAsyncKeyState('B'))	{
		ret = 65;
	}
	else if(GetAsyncKeyState('C'))	{
		ret = 66;
	}
	else if(GetAsyncKeyState('D'))	{
		ret = 67;
	}
	else if(GetAsyncKeyState('E'))	{
		ret = 68;
	}
	else if(GetAsyncKeyState('F'))	{
		ret = 69;
	}
	else if(GetAsyncKeyState('G'))	{
		ret = 70;
	}
	else if(GetAsyncKeyState('H'))	{
		ret = 71;
	}
	else if(GetAsyncKeyState('I'))	{
		ret = 72;
	}
	else if(GetAsyncKeyState('J'))	{
		ret = 73;
	}
	else if(GetAsyncKeyState('K'))	{
		ret = 74;
	}
	else if(GetAsyncKeyState('L'))	{
		ret = 75;
	}
	else if(GetAsyncKeyState('M'))	{
		ret = 76;
	}
	else if(GetAsyncKeyState('N'))	{
		ret = 77;
	}
	else if(GetAsyncKeyState('O'))	{
		ret = 78;
	}
	else if(GetAsyncKeyState('P'))	{
		ret = 79;
	}
	else if(GetAsyncKeyState('Q'))	{
		ret = 80;
	}
	else if(GetAsyncKeyState('R'))	{
		ret = 81;
	}
	else if(GetAsyncKeyState('S'))	{
		ret = 82;
	}
	else if(GetAsyncKeyState('T'))	{
		ret = 83;
	}
	else if(GetAsyncKeyState('U'))	{
		ret = 84;
	}
	else if(GetAsyncKeyState('V'))	{
		ret = 85;
	}
	else if(GetAsyncKeyState('W'))	{
		ret = 86;
	}
	else if(GetAsyncKeyState('X'))	{
		ret = 87;
	}
	else if(GetAsyncKeyState('Y'))	{
		ret = 88;
	}
	else if(GetAsyncKeyState('Z'))	{
		ret = 89;
	}
	else if(GetAsyncKeyState(VK_NUMPAD0))	{
		ret = 96;
	}
	else if(GetAsyncKeyState(VK_NUMPAD1))	{
		ret = 97;
	}
	else if(GetAsyncKeyState(VK_NUMPAD2))	{
		ret = 98;
	}
	else if(GetAsyncKeyState(VK_NUMPAD3))	{
		ret = 99;
	}
	else if(GetAsyncKeyState(VK_NUMPAD4))	{
		ret = 100;
	}
	else if(GetAsyncKeyState(VK_NUMPAD5))	{
		ret = 101;
	}
	else if(GetAsyncKeyState(VK_NUMPAD6))	{
		ret = 102;
	}
	else if(GetAsyncKeyState(VK_NUMPAD7))	{
		ret = 103;
	}
	else if(GetAsyncKeyState(VK_NUMPAD8))	{
		ret = 104;
	}
	else if(GetAsyncKeyState(VK_NUMPAD9))	{
		ret = 105;
	}
	else if(GetAsyncKeyState(VK_MULTIPLY))	{
		ret = 106;
	}
	else if(GetAsyncKeyState(VK_ADD))	{
		ret = 107;
	}
	else if(GetAsyncKeyState(VK_SEPARATOR))	{
		ret = 108;
	}
	else if(GetAsyncKeyState(VK_SUBTRACT))	{
		ret = 109;
	}
	else if(GetAsyncKeyState(VK_DECIMAL))	{
		ret = 110;
	}
	else if(GetAsyncKeyState(VK_DIVIDE))	{
		ret = 111;
	}
	else
		ret=0;
	return OPROS_SUCCESS;
}

ReturnType KeyInputComponent::onUpdated()
{
	// user code here
	return OPROS_SUCCESS;
}

ReturnType KeyInputComponent::onPeriodChanged()
{
	// user code here
	return OPROS_SUCCESS;
}

bool KeyInputComponent::setParameter(Property parameter)
{
	return true;
}

bool KeyInputComponent::getParameter(Property *parameter)
{
	return true;
}


int KeyInputComponent::getKeyInput()//HWND hWnd)  // 키보드 입력 처리 
{
	return ret;
}




#ifdef WIN32
#ifdef MAKE_COMPONENT_DLL

extern "C"
{
	__declspec(dllexport) Component *getComponent();
	__declspec(dllexport) void releaseComponent(Component *pcom);
}

Component *getComponent()
{
	return new KeyInputComponent();
}

void releaseComponent(Component *com)
{
	delete com;
}


#endif
#else
extern "C"
{
	Component *getComponent();
	void releaseComponent(IComponent *com);
}
Component *getComponent()
{
	return new KeyInputComponent();
}

void releaseComponent(Component *com)
{
	delete com;
}
#endif
