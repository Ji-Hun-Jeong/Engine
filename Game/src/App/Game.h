#pragma once
#include <Game/src/Core/Application.h>

namespace Graphics
{
	class IDRGenerator;
	class GraphicResourceMgr;
}
namespace Game
{
	class GameWorld : public Game::Application
	{
		using Super = Game::Application;
	public:
		GameWorld(UINT _ScreenWidth, UINT _ScreenHeight);
		~GameWorld();

	public:
		void Init() override;
		bool Process() override;
		void ShutDown() override;
		void Update();
		void Render();
		void AddLevel(const Str::FString& _LevelName, class Level* _Level);
		void SetCurrentLevel(const Str::FString& _LevelName);

	private:
		class Level* initLevel(class Level* _Level);

	private:
		std::map<Str::FString, class Level*> Levels;
		class Level* CurrentLevel;

		Graphics::IDRGenerator* Generator;
		Graphics::GraphicResourceMgr* GRM;

		class ClassManager* ClassMgr;
		class KeyInput* Input;
	};
}


