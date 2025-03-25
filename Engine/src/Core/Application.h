#pragma once

namespace Engine
{
	class Application
	{
	public:
		Application(UINT _ScreenWidth, UINT _ScreenHeight);
		virtual ~Application();

	public:
		virtual bool Init();
		virtual bool Process() = 0;
		virtual void ShutDown() = 0;

	protected:
		class Window* Window;

		bool Running;
	};
}

