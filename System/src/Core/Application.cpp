#include "pch.h"
#include "Application.h"
#include "Window.h"
#include "Core.h"
namespace System
{
	Application::Application(UINT _ScreenWidth, UINT _ScreenHeight)
		: AppWindow(new Window(_ScreenWidth, _ScreenHeight))
		, Running(true)
	{
		AppWindow->ShowWindow();
	}
	Application::~Application()
	{
		if (AppWindow)
			delete AppWindow;
	}
}