#pragma once
#include "Core/Application.h"

namespace Graphics
{
	class RenderContext;
}
namespace Engine
{
	class Level;
};
class GameWorld : public Engine::Application
{
	using Super = Engine::Application;
public:
	GameWorld(UINT _ScreenWidth, UINT _ScreenHeight);
	~GameWorld();

public:
	void Init() override;
	bool Process() override;
	void ShutDown() override;
	void Update();
	void Render();
	void AddLevel(const std::string& _LevelName, Engine::Level* _Level);
	void SetCurrentLevel(const std::string& _LevelName);

private:
	std::map<std::string, Engine::Level*> Levels;
	Engine::Level* CurrentLevel;

	Graphics::RenderContext* RenderContext;
};

