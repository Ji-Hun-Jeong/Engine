#include "pch.h"
#include "Player.h"
#include "Object/Component/Transform.h"
#include "Input/Input.h"
#include "Core/Time.h"

Player::Player(const std::string& _Name, Renderer::IRenderer* _Renderer)
	: Super(_Name, _Renderer)
{

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
