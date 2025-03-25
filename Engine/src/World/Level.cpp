#include "pch.h"
#include "Level.h"

namespace Engine
{
	Level::Level()
	{
	}

	Level::~Level()
	{
		Utility::ClearMap(Objects);
		Utility::ClearMap(Actors);
	}

	void Level::InitLevel()
	{
		
	}

	void Level::EnterLevel()
	{
	}

	void Level::Update()
	{
		for (auto iter = Objects.begin(); iter != Objects.end(); ++iter)
			iter->second->Update();
		for (auto iter = Actors.begin(); iter != Actors.end(); ++iter)
			iter->second->Update();
	}

	void Level::Render(Renderer::WinApiRenderer* Renderer)
	{
		for (auto iter = Actors.begin(); iter != Actors.end(); ++iter)
			iter->second->Render(Renderer);
	}

	void Level::ExitLevel()
	{
	}

	void Level::AddObject(Object* _Object)
	{
		auto iter = Objects.insert(std::make_pair(_Object->GetName(), _Object));
		if (iter.second == false)
			assert(0);

		_Object->InitObject();
	}
	void Level::AddActor(Actor* _Actor)
	{
		auto iter = Actors.insert(std::make_pair(_Actor->GetName(), _Actor));
		if (iter.second == false)
			assert(0);

		_Actor->InitObject();
	}
}