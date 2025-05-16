#pragma once

namespace Game
{
	class Window
	{
	public:
		explicit Window(UINT _ScreenWidth, UINT _ScreenHeight);
		~Window();

	public:
		void ShowWindow() const
		{
			::ShowWindow(WindowHandle, SW_SHOW);
		}
		HWND GetWindowHandle() const { return WindowHandle; }

	private:
		HWND WindowHandle;
		UINT ScreenWidth;
		UINT ScreenHeight;
	};
}
