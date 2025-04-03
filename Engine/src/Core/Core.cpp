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

	void Core::Init()
	{
		App->Init();
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