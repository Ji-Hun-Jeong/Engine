#include "pch.h"
#include "TestLevel.h"
#include "Player/Player.h"

namespace Game
{
	TestLevel::TestLevel(Graphics::DX::DXRGenerator& _Generator)
		: Level(nullptr)
		, Generator(_Generator)
		, GraphicProcess(new Graphics::BasicRenderProcess(Generator))
	{

	}

	TestLevel::~TestLevel()
	{
	}

	void TestLevel::InitLevel()
	{
		Super::InitLevel();
		
	}

	void TestLevel::EnterLevel()
	{
		Super::EnterLevel();
	}

	void TestLevel::Update()
	{
		Super::Update();
	}

	void TestLevel::ExitLevel()
	{
		Super::ExitLevel();
	}
	void TestLevel::Render(Graphics::RenderContext* _RenderContext)
	{
		GraphicProcess->UpdateGPUBuffer();
		GraphicProcess->RenderProcess();
	}
}