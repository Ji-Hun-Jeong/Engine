#pragma once
#include <System/src/Core/Application.h>

namespace Graphics
{
	class RenderDevice;
	class RenderContext;
}

namespace Game
{
	class GameWorld : public System::Application
	{
		using Super = System::Application;
	public:
		GameWorld(UINT _ScreenWidth, UINT _ScreenHeight);
		~GameWorld();

	public:
		void Init() override;
		bool Process() override;
		void ShutDown() override;
		void Update();
		void Render();
		void AddLevel(const std::string& _LevelName, class Level* _Level);
		void SetCurrentLevel(const std::string& _LevelName);

	private:
		std::map<std::string, class Level*> Levels;
		class Level* CurrentLevel;

		Graphics::RenderDevice* RenderDevice;
		Graphics::RenderContext* RenderContext;
	};
}


