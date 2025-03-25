#include "pch.h"
#include "Input.h"

namespace Input
{
	const char KeyMapping[] =
	{
		VK_TAB, VK_SHIFT, VK_CONTROL, VK_MENU, VK_ESCAPE, VK_SPACE, VK_LEFT, VK_UP, VK_RIGHT, VK_DOWN,
		'0','1','2','3','4','5','6','7','8','9',
		'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
	};
	bool IsPressed[(UINT)eKeyType::End] = { 0 };
	eButtonState KeyState[(UINT)eKeyType::End];
	void Update()
	{
		for (UINT i = 0; i < (UINT)eKeyType::End; ++i)
		{
			if (GetAsyncKeyState(KeyMapping[i]) & 0x8000)
			{
				if (IsPressed[i])
					KeyState[i] = eButtonState::Hold;
				else
					KeyState[i] = eButtonState::Tap;
				IsPressed[i] = true;
			}
			else
			{
				if (IsPressed[i])
					KeyState[i] = eButtonState::Released;
				else
					KeyState[i] = eButtonState::None;
				IsPressed[i] = false;
			}
		}
	}
	bool GetKey(eKeyType _KeyType, eButtonState _ButtonState)
	{
		return KeyState[(UINT)_KeyType] == _ButtonState;
	}
}