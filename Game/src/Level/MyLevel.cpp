#include "pch.h"
#include "MyLevel.h"
#include "Player/Player.h"

MyLevel::MyLevel(Graphics::RenderContext* _RenderContext)
	: Level(_RenderContext)
{
}

MyLevel::~MyLevel()
{
}

void MyLevel::InitLevel()
{
	Super::InitLevel();
	AddActor(new Player("Test", RenderContext));
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
