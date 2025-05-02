#include "pch.h"
#include "Actor.h"


namespace Game
{
	Actor::Actor(const Str::FString& _Name)
		: Object(_Name)
		, DrawIndexCount(0)
	{
		
	}
	Actor::Actor(const Actor& _Other)
		: Object(_Other)
		, DrawIndexCount(_Other.DrawIndexCount)
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
