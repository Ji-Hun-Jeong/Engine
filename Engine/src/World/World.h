#pragma once

namespace Renderer
{
	class IRenderer;
	class WinApiRenderer;
}
namespace Engine
{
	class World
	{
	public:
		explicit World(class Window* _Window);
		~World();

	public:
		bool InitWorld();
		void Update();
		void Render();
		void ShutDownWorld();
		void AddLevel(const std::string& _LevelName, class Level* _Level);
		void SetCurrentLevel(const std::string& _LevelName);

	private:
		std::map<std::string, class Level*> Levels;
		class Level* CurrentLevel;

		Renderer::WinApiRenderer* MyRenderer;

	};
}


