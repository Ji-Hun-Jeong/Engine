#pragma once
#include "Object.h"
#include <Engine/src/Input/Input.h>
#include <Engine/src/Time/Time.h>

#include "Object/KeyInput/KeyInput.h"
#include "Geometry/Geometry.h"

namespace Game
{
	using DirectX::SimpleMath::Matrix;
	struct ConstData
	{
		Matrix World;

		int Direction;
		Vector3 Dummy1;
	};

    class Actor : public Object
    {
		using Super = Object;
	public:
		Actor(const Str::FString& _Name);
		Actor(const Actor& _Other);
		Actor(Actor&& _Other) = delete;
		Actor& operator = (const Actor& _Other) = delete;
		Actor& operator = (Actor&& _Other) = delete;
		virtual ~Actor();

	public:
		virtual void InitObject() override;
		virtual void Update() override;
		virtual void Destory() override;

		virtual void InitalizeRerderInterface(Graphics::IDRGenerator& _Generator, std::shared_ptr<Graphics::IRenderInterface>& RenderInterface);

	protected:
		ConstData CpuConstData;
		std::shared_ptr<Graphics::IRenderInterface> RenderInterface;

    };
}