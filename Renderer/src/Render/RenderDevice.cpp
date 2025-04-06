#include "pch.h"
#include "RenderDevice.h"

namespace Graphics
{
	RenderDevice::RenderDevice(HWND _WindowHandle)
		: WindowHandle(_WindowHandle)
		, ScreenWidth(0)
		, ScreenHeight(0)
	{
		RECT r = { 0 };
		::GetWindowRect(WindowHandle, &r);
		ScreenWidth = r.right - r.left;
		ScreenHeight = r.bottom - r.top;
	}
}