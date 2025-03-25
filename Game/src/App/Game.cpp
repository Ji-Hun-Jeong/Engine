#include "pch.h"
#include "Game.h"
#include "World/World.h"
#include "Level/MyLevel.h"
#include "Input/Input.h"
#include "Core/Time.h"

Game::Game(UINT _ScreenWidth, UINT _ScreenHeight)
	: Super(_ScreenWidth, _ScreenHeight)
	, GameWorld(nullptr)
{
}

Game::~Game()
{
	if (GameWorld)
		delete GameWorld;
}

bool Game::Init()
{
	if (Super::Init() == false)
		return false;

	Time::Init();
	GameWorld = new Engine::World(Window);
	GameWorld->AddLevel("Test", new MyLevel);
	GameWorld->SetCurrentLevel("Test");

	if (GameWorld->InitWorld() == false)
		return false;

	return true;
}

bool Game::Process()
{
	Time::Update();
	Input::Update();
	GameWorld->Update();
	GameWorld->Render();

	if (Input::GetKey(Input::eKeyType::Esc, Input::eButtonState::Tap))
		Running = false;

	return Running;
}

void Game::ShutDown()
{
	GameWorld->ShutDownWorld();
	std::cout << "ShutDown\n";
}
