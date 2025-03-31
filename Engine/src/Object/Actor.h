#pragma once
#include "Object.h"

namespace Renderer
{
	class IRenderer;
	class RenderResource;
}
namespace Engine
{
    class Actor : public Object
    {
		using Super = Object;
	public:
		Actor(const std::string& _Name, Renderer::IRenderer* _Renderer);
		Actor(const Actor& _Other);
		Actor(Actor&& _Other) = delete;
		Actor& operator = (const Actor& _Other) = delete;
		Actor& operator = (Actor&& _Other) = delete;
		virtual ~Actor();

	public:
		virtual void InitObject() override;
		virtual void Update() override;
		virtual void Destory() override;
		virtual void Render(Renderer::IRenderer* _Renderer);


	protected:
		Renderer::RenderResource* RenderResource;
    };
}