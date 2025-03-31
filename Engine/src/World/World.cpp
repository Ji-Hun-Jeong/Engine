#include "pch.h"
#include "World.h"
#include "Level.h"
#include "Window/Window.h"
#include "Renderer/DXRenderer.h"

namespace Engine
{
	World::World(Window* _Window)
		: CurrentLevel(nullptr)
		, MyRenderer(new Renderer::DXRenderer(_Window->GetWindowHandle()))
	{
	}
	World::~World()
	{
		if (MyRenderer)
			delete MyRenderer;
		Utility::ClearMap(Levels);
	}
	bool World::InitWorld()
	{
		for (auto iter : Levels)
			iter.second->InitLevel();

		return true;
	}
	void World::Update()
	{
		CurrentLevel->Update();
	}
	void World::Render()
	{
		MyRenderer->Clear();

		CurrentLevel->Render(MyRenderer);

		MyRenderer->Present();
	}
	void World::ShutDownWorld()
	{
	}
	void World::AddLevel(const std::string& _LevelName, Level* _Level)
	{
		auto iter = Levels.insert(std::make_pair(_LevelName, _Level));
		if (iter.second == false)
			assert(0);
	}
	void World::SetCurrentLevel(const std::string& _LevelName)
	{
		auto iter = Levels.find(_LevelName);
		assert(iter->second);
		CurrentLevel = iter->second;
	}
}

