#pragma once
#include "Core/Application.h"

namespace Engine
{
	class World;
}
class Game : public Engine::Application
{
	using Super = Engine::Application;
public:
	Game(UINT _ScreenWidth, UINT _ScreenHeight);
	~Game();

public:
	bool Init() override;
	bool Process() override;
	void ShutDown() override;

private:
	Engine::World* GameWorld;
};

