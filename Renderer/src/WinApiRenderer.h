#pragma once
#include "Renderer.h"

namespace Renderer
{
	class RENDERER_API WinApiRenderer : public IRenderer
	{
	public:
		WinApiRenderer(HWND _MainWindowHandle);
		WinApiRenderer(const WinApiRenderer&) = delete;
		~WinApiRenderer();

	public:
		void Render() override;
		void DrawRect(RECT& _R)
		{
			::Rectangle(DrawDc, _R.left, _R.top, _R.right, _R.bottom);
		}
		void Swap()
		{
			BitBlt(MainDc, 0, 0
				, ScreenWidth
				, ScreenHeight
				, DrawDc, 0, 0, SRCCOPY);

			Rectangle(DrawDc, 0, 0
				, ScreenWidth
				, ScreenHeight);
		}

	private:
		HDC MainDc;
		HDC DrawDc;
		HBITMAP DrawBitMap;


	};
}
