#include "pch.h"
#include "Level.h"
#include <Renderer/src/RenderProcess/ImageRenderProcess.h>

#include "Object/Camera/Camera.h"

namespace Game
{
	Level::Level()
		: Input{}
		, Generator(nullptr)
		, Renderer(nullptr)
		, GRM(nullptr)
		, CollisionMgr()
		, CollisionDetector(CollisionMgr)
		, ClassMgr(nullptr)
	{
	}

	Level::~Level()
	{
		Utility::ClearMap(Objects);
		if (Renderer)
			delete Renderer;
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
		Input->UpdateKeyState();

		for (auto iter = Cameras.begin(); iter != Cameras.end(); ++iter)
			iter->second->Update();

		for (auto iter = Objects.begin(); iter != Objects.end(); ++iter)
			iter->second->Update();

		CollisionDetector.CheckCollisionProcessing();
	}

	void Level::PostUpdate()
	{
		for (auto iter = Objects.begin(); iter != Objects.end(); ++iter)
			iter->second->PostUpdate();
	}

	void Level::Render()
	{
		Renderer->BindRenderProcess();
		Renderer->Present();
	}

	void Level::InitRenderer(Graphics::IDRGenerator* _Generator, Graphics::GraphicResourceMgr* _GRM)
	{
		Generator = _Generator;
		GRM = _GRM;
		Renderer = new Graphics::ImageRenderProcess(*Generator, 0);
		Renderer->InitRenderProcess();
	}


	void Level::AddObject(Object* _Object)
	{
		auto iter = Objects.insert(std::make_pair(_Object->GetName(), _Object));
		if (iter.second == false)
			assert(0);

		_Object->InitObject();
	}

	void Level::AddCamera(Camera* _Camera)
	{
		auto iter = Cameras.insert(std::make_pair(_Camera->GetName(), _Camera));
		if (iter.second == false)
			assert(0);

		_Camera->InitObject();
	}
}