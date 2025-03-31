#pragma once

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
		virtual void Render(class RenderResource* _Resource) = 0;
		virtual void Present() {}
		virtual void Clear() {}
		virtual class RenderResource* NewRenderResource() = 0;
	protected:
		HWND WindowHandle;
		UINT ScreenWidth;
		UINT ScreenHeight;

	};
}


