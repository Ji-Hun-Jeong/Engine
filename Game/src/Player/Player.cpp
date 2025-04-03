#include "pch.h"
#include "Player.h"
#include "Object/Component/Transform.h"
#include "Input/Input.h"
#include "Core/Time.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderContext.h"

Player::Player(const std::string& _Name, Graphics::RenderContext* _RenderContext)
	: Super(_Name, _RenderContext)
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

	_RenderContext->MakeBuffers(Name, Vertices, Indices);
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
	/*Vector2 Pos = Transform->GetPos();
	if (Input::GetKey(Input::eKeyType::A, Input::eButtonState::Hold))
		Pos.x -= 200.0f * Time::DeltaTime;
	if (Input::GetKey(Input::eKeyType::D, Input::eButtonState::Hold))
		Pos.x += 200.0f * Time::DeltaTime;
	if (Input::GetKey(Input::eKeyType::W, Input::eButtonState::Hold))
		Pos.y -= 200.0f * Time::DeltaTime;
	if (Input::GetKey(Input::eKeyType::S, Input::eButtonState::Hold))
		Pos.y += 200.0f * Time::DeltaTime;
	Transform->SetPos(Pos);*/
}

void Player::Destory()
{
	Super::Destory();
}

void Player::Render(Graphics::RenderContext* _RenderContext)
{
	Renderer->BasicRender(_RenderContext, Name, DrawIndexCount);
}
