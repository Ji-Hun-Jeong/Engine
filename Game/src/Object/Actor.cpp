#include "pch.h"
#include "Actor.h"

#include <Renderer/src/Render/Renderer.h>

namespace Game
{
	Actor::Actor(const Str::FString& _Name)
		: Object(_Name)
		, Renderer(new Graphics::Renderer)
		, DrawIndexCount(0)
	{
		
	}
	Actor::Actor(const Actor& _Other)
		: Object(_Other)
		, Renderer(new Graphics::Renderer(*_Other.Renderer))
		, DrawIndexCount(_Other.DrawIndexCount)
	{
	}
	Actor::~Actor()
	{
		if (Renderer)
			delete Renderer;
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
