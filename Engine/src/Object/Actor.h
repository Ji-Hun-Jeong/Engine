#pragma once
#include "Object.h"

namespace Graphics
{
	class Renderer;
	class RenderResource;
}
namespace Engine
{
    class Actor : public Object
    {
		using Super = Object;
	public:
		Actor(const std::string& _Name, Graphics::Renderer* _Renderer);
		Actor(const Actor& _Other);
		Actor(Actor&& _Other) = delete;
		Actor& operator = (const Actor& _Other) = delete;
		Actor& operator = (Actor&& _Other) = delete;
		virtual ~Actor();

	public:
		virtual void InitObject() override;
		virtual void Update() override;
		virtual void Destory() override;
		virtual void Render(Graphics::Renderer* _Renderer);


	protected:
		Graphics::RenderResource* RenderResource;
    };
}