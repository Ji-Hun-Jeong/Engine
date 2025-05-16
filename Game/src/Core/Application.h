#pragma once

namespace Game
{
	class Application
	{
	public:
		Application(UINT _ScreenWidth, UINT _ScreenHeight);
		virtual ~Application();

	public:
		virtual void Init() = 0;
		virtual bool Process() = 0;
		virtual void ShutDown() = 0;

	protected:
		class Window* AppWindow;

		bool Running;
	};
}