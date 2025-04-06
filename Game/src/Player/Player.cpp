#include "pch.h"
#include "Player.h"

#include <Renderer/src/Render/Renderer.h>
#include <Renderer/src/Render/RenderContext.h>
#include <Renderer/src/Render/RenderDevice.h>

namespace Game
{
	using DirectX::SimpleMath::Vector3;
	Player::Player(const std::string& _Name, Graphics::RenderDevice* _RenderDevice)
		: Super(_Name)
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

		_RenderDevice->MakeBuffers(Name, Vertices, Indices);
	}

	Player::Player(const Player& _Other)
		: Super(_Other)
	{
	}

	Player::~Player()
	{
	}

	void Player::InitObject()
	{
		Super::InitObject();
	}

	void Player::Update()
	{
		Super::Update();
	}

	void Player::Destory()
	{
		Super::Destory();
	}

	void Player::Render(Graphics::RenderContext* _RenderContext)
	{
		Renderer->BasicRender(_RenderContext, Name, DrawIndexCount);
	}
}