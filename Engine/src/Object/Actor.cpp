#include "pch.h"
#include "Actor.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderContext.h"

namespace Engine
{
	using DirectX::SimpleMath::Vector3;
	Actor::Actor(const std::string& _Name, Graphics::RenderContext* _RenderContext)
		: Object(_Name)
		, Renderer(new Graphics::Renderer)
		, DrawIndexCount(0)
	{
		std::vector<Vertex> Vertices;
		Vertex V;
		V.pos = Vector3(-0.3f, -0.3f, 0.1f);
		V.color = Vector3(1.0f, 0.0f, 0.0f);
		Vertices.push_back(V);
		V.pos = Vector3(0.0f, 0.3f, 0.1f);
		V.color = Vector3(0.0f, 1.0f, 0.0f);
		Vertices.push_back(V);
		V.pos = Vector3(0.3f, -0.3f, 0.1f);
		V.color = Vector3(0.0f, 0.0f, 1.0f);
		Vertices.push_back(V);

		std::vector<uint32_t> Indices{ 0,1,2 };
		
		DrawIndexCount = static_cast<UINT>(Indices.size());

	}
	Actor::Actor(const Actor& _Other)
		: Object(_Other)
		, Renderer(new Graphics::Renderer(*_Other.Renderer))
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
	void Actor::Render(Graphics::RenderContext* _RenderContext)
	{
		
	}
}
