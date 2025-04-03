#include "pch.h"
#include "World.h"
#include "../../Game/src/Level/MyLevel.h"
#include "Window/Window.h"
#include "Platform/DirectX/DXContext.h"

namespace Engine
{
	World::World(Window* _Window)
		: CurrentLevel(nullptr)
		, RenderContext(new Graphics::DXContext(_Window->GetWindowHandle()))
	{
		AddLevel("Test", new MyLevel(RenderContext));
		SetCurrentLevel("Test");
	}
	World::~World()
	{
		if (RenderContext)
			delete RenderContext;
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
		static const float ClearColor[4] = { 0.0f,0.0f,0.0f,1.0f };
		RenderContext->ClearRenderTargetView(eCategoryRTV::BackBuffer, ClearColor);
		RenderContext->ClearDepthStencilView(eCategoryDSV::BackBuffer, D3D11_CLEAR_DEPTH, 1.0f, 0);
		
		eCategoryRTV RenderTargets[1] = { eCategoryRTV::BackBuffer };
		RenderContext->OMSetRenderTargets(1, RenderTargets, eCategoryDSV::BackBuffer);
		RenderContext->OMSetDepthStencilState(eCategoryDSS::Basic, 0);

		CurrentLevel->Render();

		RenderContext->Present();
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

