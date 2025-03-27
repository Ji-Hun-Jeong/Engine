#include "WinApiRenderer.h"

namespace Renderer
{
	WinApiRenderer::WinApiRenderer(HWND _MainWindowHandle)
		: IRenderer(_MainWindowHandle)
		, MainDc(::GetDC(_MainWindowHandle))
		, DrawDc(::CreateCompatibleDC(MainDc))
		, DrawBitMap(nullptr)

	{


		DrawBitMap = ::CreateCompatibleBitmap(MainDc, ScreenWidth, ScreenHeight);
		HBITMAP PrevBitMap = static_cast<HBITMAP>(::SelectObject(DrawDc, DrawBitMap));
		::DeleteObject(PrevBitMap);
	}
	WinApiRenderer::~WinApiRenderer()
	{
		::DeleteDC(DrawDc);
		::DeleteObject(DrawBitMap);
		::ReleaseDC(WindowHandle, MainDc);
	}
	void WinApiRenderer::Render()
	{
	}
}