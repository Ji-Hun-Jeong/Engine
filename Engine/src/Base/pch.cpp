#include "pch.h"

RECT Utility::GetRect(const Vector2& _Pos, const Vector2& _Size)
{
	RECT R;
	int X = static_cast<int>(_Pos.x);
	int Y = static_cast<int>(_Pos.y);
	int HalfWidth = static_cast<int>(_Size.x / 2.0f);
	int HalfHeight = static_cast<int>(_Size.y / 2.0f);
	R.left = X - HalfWidth;
	R.right = X + HalfWidth;
	R.bottom = Y + HalfHeight;
	R.top = Y - HalfHeight;
	return R;
}