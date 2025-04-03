#pragma once

namespace Engine
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
