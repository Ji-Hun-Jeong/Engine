#include "pch.h"
#include "Application.h"
#include "Window/Window.h"
#include "WinApiRenderer.h"

namespace Engine
{
	Application::Application(UINT _ScreenWidth, UINT _ScreenHeight)
		: Window(new Engine::Window(_ScreenWidth, _ScreenHeight))
		, Running(true)
	{
	}
	Application::~Application()
	{
		if (Window)
			delete Window;
	}

	bool Application::Init()
	{
		if (Window->Init() == false)
			return false;

		Window->ShowWindow();
		return true;
	}
}