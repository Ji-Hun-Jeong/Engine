#include "pch.h"
#include "Actor.h"

#include <Renderer/src/RenderProcess/PixelCollisionProcess.h>

namespace Game
{
	Actor::Actor(const Str::FString& _Name)
		: Object(_Name)
		, PixelCollisionInterface(nullptr)
	{
		
	}

	Actor::Actor(const Actor& _Other)
		: Object(_Other)
		, PixelCollisionInterface(nullptr)
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

	void Actor::PostUpdate()
	{
		CpuConstData.World = Transform.GetModel().Transpose();
		CpuConstData.Direction = Transform.GetDirection();

		RenderInterface->UpdateConstBuffer();
	}

	void Actor::Destory()
	{
		Super::Destory();
	}

	void Actor::InitPixelCollision(Graphics::PixelCollisionProcess& _Process)
	{
		auto Interface = _Process.RegistPixelCollision(Transform.GetPositionRef());
		Interface->SetActive(true);
		PixelCollisionInterface = Interface;
	}
}
