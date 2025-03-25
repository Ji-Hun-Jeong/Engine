#pragma once
#include <Windows.h>

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
		IRenderer(HWND _WindowHandle) : WindowHandle(_WindowHandle) {}
		IRenderer(const IRenderer&) = delete;
		virtual ~IRenderer() {}

	public:
		virtual void Render() {}

	protected:
		HWND WindowHandle;

	};
}


