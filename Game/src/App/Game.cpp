#include "pch.h"
#include "Game.h"
#include "Level/MyLevel.h"

#include <Engine/src/Time/Time.h>
#include <Engine/src/Input/Input.h>
#include <Engine/src/Path/Path.h>
#include <Game/src/Core/Window.h>
#include <Renderer/src/MyTime.h>

namespace Game
{
	GameWorld::GameWorld(UINT _ScreenWidth, UINT _ScreenHeight)
		: Super(_ScreenWidth, _ScreenHeight)
		, CurrentLevel(nullptr)
		, Generator(*new Graphics::DX::DXRGenerator(AppWindow->GetWindowHandle()))
	{
		// rendering리소스 정의
	}

	GameWorld::~GameWorld()
	{
		Utility::ClearMap(Levels);
		if (&Generator)
			delete &Generator;
	}

	void GameWorld::Init()
	{
		Time::Init();
		Path::Init("Game");

		AddLevel("Test", new MyLevel(Generator));
		SetCurrentLevel("Test");

		for (auto iter : Levels)
			iter.second->InitLevel();
	}

	bool GameWorld::Process()
	{
		Time::Update();
		GraphicsTime::SetDT(Time::GetDT());
		Input::Update();

		this->Update();

		this->Render();

		if (Input::GetKey(Input::eKeyType::Esc, Input::eButtonState::Tap))
			Running = false;

		return Running;
	}

	void GameWorld::Render()
	{
		CurrentLevel->Render();
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
