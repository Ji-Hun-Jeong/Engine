#include "pch.h"
#include "TestLevel.h"
#include "Player/Player.h"

namespace Game
{
	TestLevel::TestLevel(Graphics::IDRGenerator& _Generator)
		: Level()
		, Generator(_Generator)
		, GraphicProcess(*new Graphics::BasicRenderProcess(Generator))
	{

	}

	TestLevel::~TestLevel()
	{
		if (&GraphicProcess)
			delete &GraphicProcess;
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
	void TestLevel::Render()
	{
		GraphicProcess.UpdateGPUBuffer();
		GraphicProcess.RenderProcess();
	}
}