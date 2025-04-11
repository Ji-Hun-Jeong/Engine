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

	void Player::Move()
	{
		Vector3 Position = Transform.GetPosition();
		if (Input::GetKey(Input::eKeyType::A, Input::eButtonState::Hold))
			Position.x -= Time::DeltaTime * 2;
		if (Input::GetKey(Input::eKeyType::D, Input::eButtonState::Hold))
			Position.x += Time::DeltaTime * 2;
		if (Input::GetKey(Input::eKeyType::W, Input::eButtonState::Hold))
			Position.y += Time::DeltaTime * 2;
		if (Input::GetKey(Input::eKeyType::S, Input::eButtonState::Hold))
			Position.y -= Time::DeltaTime * 2;

		Transform.SetPosition(Position);

		Constant.MVP = Transform.GetModel().Transpose();
	}

	void Player::Render(Graphics::RenderContext* _RenderContext)
	{
		_RenderContext->UpdateVSConstBuffer(Name, eCategoryVSConst::Basic, &Constant, sizeof(Constant));
		Renderer->BasicRender(_RenderContext, Name, DrawIndexCount);
	}
}