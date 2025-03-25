#pragma once

namespace Input
{
	enum class eButtonState
	{
		None,
		Tap,
		Hold,
		Released,
	};
	enum class eKeyType
	{
		Tab, Shift, Ctrl, Alt, Esc, Space, Left, Up, Right, Down,
		_0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		End,
	};
	extern void Update();
	extern bool GetKey(eKeyType _KeyType, eButtonState _ButtonState);
}
