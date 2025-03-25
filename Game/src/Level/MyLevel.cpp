#include "pch.h"
#include "MyLevel.h"
#include "Player/Player.h"

MyLevel::MyLevel()
	: Level()
{
}

MyLevel::~MyLevel()
{
}

void MyLevel::InitLevel()
{
	Super::InitLevel();
	AddActor(new Player("Test"));
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
