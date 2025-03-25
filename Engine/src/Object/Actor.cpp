#include "pch.h"
#include "Actor.h"
#include "Component/Transform.h"

namespace Engine
{
	Actor::Actor(const std::string& _Name)
		: Object(_Name)
		, Transform(new Engine::Transform)
	{
	}
	Actor::Actor(const Actor& _Other)
		: Object(_Other)
		, Transform(new Engine::Transform(*_Other.Transform))
	{
	}
	Actor::~Actor()
	{
		if (Transform)
			delete Transform;
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
