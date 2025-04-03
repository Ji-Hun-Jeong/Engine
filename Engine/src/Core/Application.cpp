#include "pch.h"
#include "Application.h"
#include "Window/Window.h"

namespace Engine
{
	Application::Application(UINT _ScreenWidth, UINT _ScreenHeight)
		: Window(new Engine::Window(_ScreenWidth, _ScreenHeight))
		, Running(true)
	{
		Window->ShowWindow();
	}
	Application::~Application()
	{
		if (Window)
			delete Window;
	}
}