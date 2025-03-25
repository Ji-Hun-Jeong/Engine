#pragma once

namespace Engine
{
	class Core
	{
	public:
		explicit Core(class Application* _App);
		~Core();

	public:
		bool Init();

		int Run();

	private:
		class Application* App;

	};
}
