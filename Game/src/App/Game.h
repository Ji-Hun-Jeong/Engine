#pragma once
#include <System/src/Core/Application.h>

namespace Graphics
{
	class IDRGenerator;
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
		void AddLevel(const Str::FString& _LevelName, class Level* _Level);
		void SetCurrentLevel(const Str::FString& _LevelName);

	private:
		std::map<Str::FString, class Level*> Levels;
		class Level* CurrentLevel;

		Graphics::IDRGenerator* RenderResourceGenerator;
	};
}


