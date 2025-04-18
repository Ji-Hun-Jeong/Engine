#include "pch.h"
#include "Player.h"

#include <Engine/src/Input/Input.h>
#include <Engine/src/Time/Time.h>
#include <Renderer/src/Render/Renderer.h>
#include <Renderer/src/Render/RenderContext.h>
#include <Renderer/src/Geometry/Geometry.h>

namespace Game
{
	Player::Player(const std::string& _Name, Graphics::RenderDevice* _RenderDevice)
		: Super(_Name)
	{
		Graphics::Geometry::MeshData Md = Graphics::Geometry::GenerateSquare();

		DrawIndexCount = static_cast<UINT>(Md.Indices.size());

		_RenderDevice->MakeGeometryBuffers(Name, Md.Vertices, Md.Indices);

		_RenderDevice->MakeVSConstBuffer(Name, eCategoryVSConst::Basic, sizeof(Constant));

		Transform = new Game::Transform;
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
		_RenderContext->UpdateVSConstBuffer(Name, eCategoryVSConst::Basic, &Constant, sizeof(Constant));
		Renderer->BasicRender(_RenderContext, Name, DrawIndexCount);
	}
}