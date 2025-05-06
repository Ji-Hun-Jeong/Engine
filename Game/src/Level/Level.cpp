#include "pch.h"
#include "Level.h"

namespace Game
{
	Level::Level(Graphics::IDRGenerator& _Generator)
		: Generator(_Generator)
		, Renderer(*new Graphics::BasicRenderProcess(Generator))
	{
	}

	Level::~Level()
	{
		Utility::ClearMap(Objects);
		Utility::ClearMap(Actors);
		if (&Renderer)
			delete &Renderer;
	}

	void Level::InitLevel()
	{
	}

	void Level::EnterLevel()
	{
	}

	void Level::ExitLevel()
	{
	}

	void Level::Update()
	{
		for (auto iter = Objects.begin(); iter != Objects.end(); ++iter)
			iter->second->Update();
		for (auto iter = Actors.begin(); iter != Actors.end(); ++iter)
			iter->second->Update();
	}

	void Level::Render()
	{
		Renderer.UpdateGPUBuffer(ModelRegistry);
		Renderer.BindRenderProcess(ModelRegistry);
		Renderer.Present();
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