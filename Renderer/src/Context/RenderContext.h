#pragma once

namespace Graphics
{
	class RENDERER_API RenderContext
	{
	public:
		RenderContext(HWND _WindowHandle)
			: WindowHandle(_WindowHandle)
			, ScreenWidth(0)
			, ScreenHeight(0)
		{
			RECT r = { 0 };
			::GetWindowRect(WindowHandle, &r);
			ScreenWidth = r.right - r.left;
			ScreenHeight = r.bottom - r.top;
		}
		RenderContext(const RenderContext&) = delete;
		virtual ~RenderContext() {}
	public:

	protected:
		HWND WindowHandle;
		UINT ScreenWidth;
		UINT ScreenHeight;

	};
}