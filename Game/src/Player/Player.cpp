#include "pch.h"
#include "Player.h"

#include <Engine/src/Input/Input.h>
#include <Engine/src/Time/Time.h>
#include <Renderer/src/Render/Renderer.h>
#include <Renderer/src/Render/RenderContext.h>
#include <Renderer/src/Geometry/Geometry.h>

#include "Base/KeyInput.h"
#include "Base/Action.h"

namespace Game
{
	Player::Player(const std::string& _Name, Graphics::RenderDevice* _RenderDevice)
		: Super(_Name)
		, PlayerKeyInput(new KeyInput)
		, PlayerActionController(new ActionController)
	{
		Graphics::Geometry::MeshData Md = Graphics::Geometry::GenerateSquare();

		DrawIndexCount = static_cast<UINT>(Md.Indices.size());

		_RenderDevice->MakeGeometryBuffers(Name, Md.Vertices, Md.Indices);

		_RenderDevice->MakeVSConstBuffer(Name, eCategoryVSConst::Basic, sizeof(Constant));

		Transform = new Game::Transform;

		auto LeftMove = [this]()->void
			{
				Vector3 Position = Transform->GetPosition();
				Position.x += -1 * Time::DeltaTime;
				Transform->SetPosition(Position);
			};

		BindAction("LeftMove", LeftMove);
	}

	Player::Player(const Player& _Other)
		: Super(_Other)
	{
	}

	Player::~Player()
	{
		if (PlayerKeyInput)
			delete PlayerKeyInput;
		if (PlayerActionController)
			delete PlayerActionController;
	}

	void Player::InitObject()
	{
		Super::InitObject();
	}

	void Player::Update()
	{
		Super::Update();
		PlayerKeyInput->UpdateKeyState();

		PlayerActionController->PerformActions();
		Constant.MVP = Transform->GetModel().Transpose();
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

	void Player::BindAction(const std::string& _ActionName, std::function<void()> _ActFunction)
	{
		ActionController* PActionController = this->PlayerActionController;

		Action* PlayerAction = new Action(_ActionName, _ActFunction);
		PActionController->AddAction(PlayerAction);

		auto KeyEvent = [PActionController](const std::string& _KeyName, Input::eButtonState _KeyState)->void
			{
				PActionController->AddActionQueue(_KeyName);
			};

		Key* KeyInfo = new Key;
		KeyInfo->KeyName = _ActionName;
		KeyInfo->KeyEvent = KeyEvent;

		PlayerKeyInput->AddKey(KeyInfo, Input::eKeyType::Left);
	}
}