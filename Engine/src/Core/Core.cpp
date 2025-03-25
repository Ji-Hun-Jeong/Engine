#include "pch.h"
#include "Core.h"
#include "Application.h"

namespace Engine
{
	Core::Core(Application* _App)
		: App(_App)
	{
	}
	Core::~Core()
	{
		if (App)
			delete App;
	}

	bool Core::Init()
	{
		if (App->Init() == false)
			return false;
		return true;
	}
	
	int Core::Run()
	{
		static MSG msg;

		while (true)
		{
			// �޽��� ť���� �޽��� Ȯ��
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					break;

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				if (App->Process() == false)
					break;
			}
		}
		App->ShutDown();
		return 0;
	}
}