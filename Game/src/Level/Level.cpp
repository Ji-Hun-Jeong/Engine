#include "pch.h"
#include "Level.h"
#include <Renderer/src/RenderProcess/ImageRenderProcess.h>

namespace Game
{
	Level::Level(Graphics::IDRGenerator& _Generator)
		: Input{}
		, Generator(_Generator)
		, Renderer(*new Graphics::ImageRenderProcess(Generator, 2))
		, CollisionMgr()
		, CollisionDetector(CollisionMgr)
	{
	}

	Level::~Level()
	{
		Utility::ClearMap(Objects);
		if (&Renderer)
			delete& Renderer;
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
		Input.UpdateKeyState();
		for (auto iter = Objects.begin(); iter != Objects.end(); ++iter)
			iter->second->Update();

		CollisionDetector.CheckCollisionProcessing();
	}

	void Level::Render()
	{
		Renderer.BindRenderProcess();
		Renderer.Present();
	}


	void Level::AddObject(Object* _Object)
	{
		auto iter = Objects.insert(std::make_pair(_Object->GetName(), _Object));
		if (iter.second == false)
			assert(0);

		_Object->InitObject();
	}
}