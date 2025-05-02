#include "pch.h"
#include "Game.h"
#include "Level/MyLevel.h"
#include "Level/TestLevel.h"

#include <Engine/src/Time/Time.h>
#include <Engine/src/Input/Input.h>
#include <Engine/src/Path/Path.h>
#include <System/src/Core/Window.h>

namespace Game
{
	GameWorld::GameWorld(UINT _ScreenWidth, UINT _ScreenHeight)
		: Super(_ScreenWidth, _ScreenHeight)
		, CurrentLevel(nullptr)
		, RenderResourceGenerator(new Graphics::DX::DXRGenerator(AppWindow->GetWindowHandle()))
	{
		
	}

	GameWorld::~GameWorld()
	{
		Utility::ClearMap(Levels);
		if (RenderResourceGenerator)
			delete RenderResourceGenerator;
	}

	void GameWorld::Init()
	{
		Time::Init();
		Path::Init("Game");

		// AddLevel("Test", new MyLevel(RenderDevice));
		AddLevel("Test", new TestLevel(*RenderResourceGenerator));
		SetCurrentLevel("Test");

		for (auto iter : Levels)
			iter.second->InitLevel();
	}

	bool GameWorld::Process()
	{
		Time::Update();
		Input::Update();

		this->Update();

		this->Render();

		if (Input::GetKey(Input::eKeyType::Esc, Input::eButtonState::Tap))
			Running = false;

		return Running;
	}

	void GameWorld::Render()
	{
		//static const float ClearColor[4] = { 0.0f,0.0f,0.0f,1.0f };
		//RenderContext->ClearRenderTargetView(eCategoryRTV::BackBuffer, ClearColor);
		//RenderContext->ClearDepthStencilView(eCategoryDSV::BackBuffer, D3D11_CLEAR_DEPTH, 1.0f, 0);
		//
		//eCategoryRTV RenderTargets[1] = { eCategoryRTV::BackBuffer };
		//RenderContext->OMSetRenderTargets(1, RenderTargets, eCategoryDSV::BackBuffer);
		//RenderContext->OMSetDepthStencilState(eCategoryDSS::Basic, 0);
		
		CurrentLevel->Render();
		
		//RenderContext->Present();
	}

	void GameWorld::ShutDown()
	{
		std::cout << "ShutDown\n";
	}

	void GameWorld::Update()
	{
		CurrentLevel->Update();
	}

	void GameWorld::AddLevel(const Str::FString& _LevelName, Level* _Level)
	{
		auto iter = Levels.insert(std::make_pair(_LevelName, _Level));
		if (iter.second == false)
			assert(0);
	}

	void GameWorld::SetCurrentLevel(const Str::FString& _LevelName)
	{
		auto iter = Levels.find(_LevelName);
		assert(iter->second);
		CurrentLevel = iter->second;
	}
}
