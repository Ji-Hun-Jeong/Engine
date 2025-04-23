#pragma once

namespace Input
{
	enum class eButtonState : uint16_t
	{
		None,
		Tap,
		Hold,
		Released,
	};
	enum class eKeyType : uint16_t
	{
		Tab, Shift, Ctrl, Alt, Esc, Space, Left, Up, Right, Down,
		_0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		End,
	};
	extern void Update();
	extern bool GetKey(eKeyType _KeyType, eButtonState _ButtonState);
	extern eButtonState GetKeyState(eKeyType _KeyType);
}
