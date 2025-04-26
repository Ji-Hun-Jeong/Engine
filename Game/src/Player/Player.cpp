#include "pch.h"
#include "Player.h"

#include <Renderer/src/Render/Renderer.h>
#include <Renderer/src/Render/RenderContext.h>
#include <Renderer/src/Geometry/Geometry.h>

#include "Component/KeyInput/KeyInput.h"
#include "PlayerComponent/PlayerActionController.h"

namespace Game
{
	Player::Player(const Str::FString& _Name, Graphics::RenderDevice* _RenderDevice)
		: Super(_Name)
		, PlayerKeyInput(new KeyInput)
		, ActionController(new PlayerActionController)
	{
		Graphics::Geometry::ColorMeshData Md = Graphics::Geometry::GenerateColorTriangle();

		DrawIndexCount = static_cast<UINT>(Md.Indices.size());

		auto Vertices = Md.Vertices;
		_RenderDevice->MakeGeometryBuffers(Name, Vertices.data(), sizeof(ColorVertex), Vertices.size(), Md.Indices);

		_RenderDevice->MakeVSConstBuffer(Name, eCategoryVSConst::Basic, sizeof(Constant));

		Transform = new Game::Transform;

		addAction();
		addKey();
		{
			BindActionAndKey(Input::eKeyType::Left, Input::eButtonState::Hold, "BasicAction", "LeftMove");
			BindActionAndKey(Input::eKeyType::Right, Input::eButtonState::Hold, "BasicAction", "RightMove");
			BindActionAndKey(Input::eKeyType::Up, Input::eButtonState::Hold, "BasicAction", "UpMove");
			BindActionAndKey(Input::eKeyType::Down, Input::eButtonState::Hold, "BasicAction", "DownMove");
			BindActionAndKey(Input::eKeyType::Ctrl, Input::eButtonState::Hold, "CantMoveAction", "Attack");
			BindActionAndKey(Input::eKeyType::Shift, Input::eButtonState::Hold, "MoveAction", "Uld");
		}
	}

	Player::Player(const Player& _Other)
		: Super(_Other)
	{
	}

	Player::~Player()
	{
		if (PlayerKeyInput)
			delete PlayerKeyInput;
		if (ActionController)
			delete ActionController;
	}

	void Player::InitObject()
	{
		Super::InitObject();
	}

	void Player::Update()
	{
		Super::Update();

		PlayerKeyInput->UpdateKeyState();

		KeyActioner* KeyActioner = PlayerKeyInput->GetKeyActioner();
		KeyActioner->PerformKeyAction();

		ActionController->Update();

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

	void Player::BindActionAndKey(Input::eKeyType _KeyType, Input::eButtonState _KeyState
		, const Str::FString& _ActionClass, const Str::FString& _ActionName)
	{
		if (ActionController->IsExistAction(_ActionName) == false)
			return;

		KeyValue* FindKeyValue = PlayerKeyInput->GetKeyValue(_KeyType, _KeyState);
		if (FindKeyValue == nullptr)
			return;

		Game::ActionController* PActionController = ActionController;
		auto Event = [PActionController, _ActionClass, _ActionName](const Str::FString& _KeyName)->void
			{
				PActionController->PrepareAction(_ActionClass, _ActionName);
			};
		FindKeyValue->SetKeyEvent(Event);

	}

	void Player::addAction()
	{
		auto LeftMove = [this]()->void
			{
				Vector3 Position = Transform->GetPosition();
				Position.x += -1 * Time::GetDT();
				Transform->SetPosition(Position);
			};
		auto RightMove = [this]()->void
			{
				Vector3 Position = Transform->GetPosition();
				Position.x += 1 * Time::GetDT();
				Transform->SetPosition(Position);
			};
		auto UpMove = [this]()->void
			{
				Vector3 Position = Transform->GetPosition();
				Position.y += 1 * Time::GetDT();
				Transform->SetPosition(Position);
			};
		auto DownMove = [this]()->void
			{
				Vector3 Position = Transform->GetPosition();
				Position.y += -1 * Time::GetDT();
				Transform->SetPosition(Position);
			};

		Action* PlayerAction = new Action("LeftMove", LeftMove);
		ActionController->AddAction(PlayerAction);

		PlayerAction = new Action("RightMove", RightMove);
		ActionController->AddAction(PlayerAction);

		PlayerAction = new Action("UpMove", UpMove);
		ActionController->AddAction(PlayerAction);

		PlayerAction = new Action("DownMove", DownMove);
		ActionController->AddAction(PlayerAction);

		PlayerAction = new Action("Attack", std::bind(&Player::Attack, this));
		PlayerAction->SetActionDelay(1.0f);
		ActionController->AddAction(PlayerAction);

		PlayerAction = new Action("Uld", std::bind(&Player::Uld, this));
		PlayerAction->SetActionDelay(0.5f);
		ActionController->AddAction(PlayerAction);
	}
	void Player::addKey()
	{
		PlayerKeyInput->AddKey(Input::eKeyType::Left, Input::eButtonState::Hold, "LeftMove");
		PlayerKeyInput->AddKey(Input::eKeyType::Right, Input::eButtonState::Hold, "RightMove");
		PlayerKeyInput->AddKey(Input::eKeyType::Up, Input::eButtonState::Hold, "UpMove");
		PlayerKeyInput->AddKey(Input::eKeyType::Down, Input::eButtonState::Hold, "DownMove");
		PlayerKeyInput->AddKey(Input::eKeyType::Ctrl, Input::eButtonState::Hold, "Attack");
		PlayerKeyInput->AddKey(Input::eKeyType::Shift, Input::eButtonState::Hold, "Uld");
	}
}