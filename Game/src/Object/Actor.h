#pragma once
#include "Object.h"
#include <Engine/src/Input/Input.h>
#include <Engine/src/Time/Time.h>

#include <Renderer/src/RenderProcess/IGraphicProcess.h>
#include <Renderer/src/Render/IRenderInterface.h>
#include <Renderer/src/State/State.h>

#include "Object/KeyInput/KeyInput.h"
#include "Geometry/Geometry.h"

namespace Graphics
{
	class PixelCollisionProcess;
	class PixelCollisionInterface;
}
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
		virtual void PostUpdate() override;
		virtual void Destory() override;

		virtual void InitalizeRenderInterface(Graphics::IDRGenerator& _Generator, std::shared_ptr<Graphics::Model>& _Model)
		{
			RenderInterface = std::make_shared<Graphics::IRenderInterface>();
			initalizeConstBuffer(_Generator);

			_Model->AddRenderInterface(RenderInterface);
		}
		void SetRenderInterface(Graphics::IDRGenerator& _Generator, std::shared_ptr<Graphics::Model>& _Model, std::shared_ptr<Graphics::IRenderInterface>& _RenderInterface)
		{
			RenderInterface = _RenderInterface;
			initalizeConstBuffer(_Generator);

			_Model->AddRenderInterface(RenderInterface);
		}

		void InitPixelCollision(Graphics::PixelCollisionProcess& _Process);
	protected:
		void initalizeConstBuffer(Graphics::IDRGenerator& _Generator)
		{
			std::vector<Graphics::CpuConstData> CpuConstDatas{ {&CpuConstData, sizeof(CpuConstData)} };
			auto ConstBuffer = _Generator.GenerateConstBuffer(CpuConstDatas);
			RenderInterface->SetConstBuffer(ConstBuffer);
		}

	protected:
		ConstData CpuConstData;
		std::shared_ptr<Graphics::IRenderInterface> RenderInterface;
		Graphics::PixelCollisionInterface* PixelCollisionInterface;
    };
}