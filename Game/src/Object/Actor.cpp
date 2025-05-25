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

		CpuConstData.MVP = Transform.GetModel().Transpose();
		CpuConstData.Direction = Transform.GetDirection();
		RenderInterface->UpdateConstBuffer();
	}

	void Actor::Destory()
	{
		Super::Destory();
	}

	void Actor::InitalizeRerderInterface(Graphics::IDRGenerator& _Generator, std::shared_ptr<Graphics::IRenderInterface>& _RenderInterface)
	{
		std::vector<Graphics::CpuConstData> CpuConstDatas{ {&CpuConstData, sizeof(CpuConstData)} };
		auto ConstBuffer = _Generator.GenerateConstBuffer(CpuConstDatas);

		RenderInterface = _RenderInterface;
		RenderInterface->SetConstBuffer(ConstBuffer);
	}
}
