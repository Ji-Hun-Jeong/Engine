#include "pch.h"
#include "Player.h"

#include <Renderer/src/Render/Renderer.h>
#include <Renderer/src/Render/RenderContext.h>
#include <Renderer/src/Geometry/Geometry.h>

namespace Game
{
	using DirectX::SimpleMath::Vector3;
	using DirectX::SimpleMath::Matrix;

	Player::Player(const std::string& _Name, Graphics::RenderDevice* _RenderDevice)
		: Super(_Name)
	{
		Graphics::Geometry::MeshData Md = Graphics::Geometry::GenerateSquare();

		DrawIndexCount = static_cast<UINT>(Md.Indices.size());

		_RenderDevice->MakeGeometryBuffers(Name, Md.Vertices, Md.Indices);

		Constant.MVP = Matrix::CreateTranslation(Vector3(0.3f, 0.0f, 0.0f)).Transpose();

		_RenderDevice->MakeVSConstBuffer(Name, eCategoryVSConst::Basic, Constant);
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