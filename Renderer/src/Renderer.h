#pragma once
#include <Windows.h>
#include <cassert>
#include <vector>
#include <iostream>

#ifdef RENDERER_DEFINE
	#define RENDERER_API __declspec(dllexport)
#else
	#define RENDERER_API __declspec(dllimport)
#endif

namespace Renderer
{
	class RENDERER_API IRenderer
	{
	public:
		IRenderer(HWND _WindowHandle) 
			: WindowHandle(_WindowHandle)
			, ScreenWidth(0)
			, ScreenHeight(0) 
		{
			RECT r = { 0 };
			::GetWindowRect(WindowHandle, &r);
			ScreenWidth = r.right - r.left;
			ScreenHeight = r.bottom - r.top;
		}
		IRenderer(const IRenderer&) = delete;
		virtual ~IRenderer() {}

	public:
		virtual void Render() = 0;
		virtual void Present() {}
		virtual void Clear() {}
	protected:
		HWND WindowHandle;
		UINT ScreenWidth;
		UINT ScreenHeight;
	};
}


