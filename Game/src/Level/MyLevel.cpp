#include "pch.h"
#include "MyLevel.h"
#include "Player/Player.h"

MyLevel::MyLevel(Graphics::RenderDevice* _RenderDevice)
	: Level(_RenderDevice)
{
}

MyLevel::~MyLevel()
{
}

void MyLevel::InitLevel()
{
	Super::InitLevel();
	AddActor(new Player("Test", RenderDevice));
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
