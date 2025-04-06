#pragma once

namespace System
{
	class Core
	{
	public:
		explicit Core(class Application* _App);
		~Core();

	public:
		void Init();

		int Run();

	private:
		class Application* App;

	};
}