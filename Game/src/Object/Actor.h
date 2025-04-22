#pragma once
#include "Object.h"
#include <Renderer/src/Render/RenderDevice.h>
#include <Engine/src/Input/Input.h>
#include <Engine/src/Time/Time.h>

namespace Graphics
{
	class Renderer;
	class RenderContext;
}
namespace Game
{
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
		virtual void Render(Graphics::RenderContext* _RenderContext) = 0;

	protected:
		Graphics::Renderer* Renderer;
		UINT DrawIndexCount;

    };
}