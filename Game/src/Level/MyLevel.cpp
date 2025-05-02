#include "pch.h"
#include "MyLevel.h"
#include "Player/Player.h"

#include <Renderer/src/Render/IRenderer.h>
namespace Game
{
	MyLevel::MyLevel(Graphics::IDRGenerator& _Generator)
		: Level(_Generator)
	{
		GraphicProcess = new Graphics::BasicRenderProcess(Generator);
	}

	MyLevel::~MyLevel()
	{
	}

	void MyLevel::InitLevel()
	{
		Super::InitLevel();
		AddActor(new Player("Test", Generator));
	}

	void MyLevel::EnterLevel()
	{
		Super::EnterLevel();
	}

	void MyLevel::Update()
	{
		Super::Update();
	}

	void MyLevel::ExitLevel()
	{
		Super::ExitLevel();
	}
}