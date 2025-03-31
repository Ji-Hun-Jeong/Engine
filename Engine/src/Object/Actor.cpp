#include "pch.h"
#include "Actor.h"
#include "Renderer/Renderer.h"
#include "Resource/RenderResource.h"

namespace Engine
{
	using DirectX::SimpleMath::Vector3;
	Actor::Actor(const std::string& _Name, Graphics::Renderer* _Renderer)
		: Object(_Name)
		, RenderResource(_Renderer->NewRenderResource())
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
		RenderResource->MakeIABuffer(Vertices, Indices);
	}
	Actor::Actor(const Actor& _Other)
		: Object(_Other)
	{
	}
	Actor::~Actor()
	{
		if (RenderResource)
			delete RenderResource;
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
	void Actor::Render(Graphics::Renderer* _Renderer)
	{
		_Renderer->Render(RenderResource);
	}
}
