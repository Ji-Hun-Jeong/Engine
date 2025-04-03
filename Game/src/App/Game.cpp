#include "pch.h"
#include "Game.h"
#include "Level/MyLevel.h"
#include "Input/Input.h"
#include "Core/Time.h"
#include "Platform/DirectX/DXContext.h"
#include "Window/Window.h"
#include "Renderer/RenderContext.h"

GameWorld::GameWorld(UINT _ScreenWidth, UINT _ScreenHeight)
	: Super(_ScreenWidth, _ScreenHeight)
	, CurrentLevel(nullptr)
	, RenderContext(new Graphics::DX::DXContext(Window->GetWindowHandle()))
{

}

GameWorld::~GameWorld()
{
	if (RenderContext)
		delete RenderContext;
	Utility::ClearMap(Levels);
}

void GameWorld::Init()
{
	Time::Init();

	AddLevel("Test", new MyLevel(RenderContext));
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

void GameWorld::ShutDown()
{
	std::cout << "ShutDown\n";
}

void GameWorld::Update()
{
	CurrentLevel->Update();
}

void GameWorld::Render()
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

void GameWorld::AddLevel(const std::string& _LevelName, Engine::Level* _Level)
{
	auto iter = Levels.insert(std::make_pair(_LevelName, _Level));
	if (iter.second == false)
		assert(0);
}
void GameWorld::SetCurrentLevel(const std::string& _LevelName)
{
	auto iter = Levels.find(_LevelName);
	assert(iter->second);
	CurrentLevel = iter->second;
}