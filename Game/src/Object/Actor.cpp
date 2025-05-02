#include "pch.h"
#include "Actor.h"


namespace Game
{
	Actor::Actor(const Str::FString& _Name)
		: Object(_Name)
	{
		
	}
	Actor::Actor(const Actor& _Other)
		: Object(_Other)
	{
	}
	Actor::~Actor()
	{
		
	}
	void Actor::InitObject()
	{
		Super::InitObject();
	}
	void Actor::Update()
	{
		Super::Update();
	}
	void Actor::Destory()
	{
		Super::Destory();
	}
}
