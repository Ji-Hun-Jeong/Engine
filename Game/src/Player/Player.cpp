#include "pch.h"
#include "Player.h"

#include <Renderer/src/Render/Renderer.h>
#include <Renderer/src/Render/RenderContext.h>
#include <Renderer/src/Geometry/Geometry.h>

#include "Base/KeyInput.h"
#include "Base/Action.h"

namespace Game
{
	Player::Player(const Str::FString& _Name, Graphics::RenderDevice* _RenderDevice)
		: Super(_Name)
		, PlayerKeyInput(new KeyInput)
		, PlayerActionController(new ActionController)
	{
		Graphics::Geometry::ColorMeshData Md = Graphics::Geometry::GenerateColorTriangle();

		DrawIndexCount = static_cast<UINT>(Md.Indices.size());

		auto Vertices = Md.Vertices;
		_RenderDevice->MakeGeometryBuffers(Name, Vertices.data(), sizeof(ColorVertex), Vertices.size(), Md.Indices);

		_RenderDevice->MakeVSConstBuffer(Name, eCategoryVSConst::Basic, sizeof(Constant));

		Transform = new Game::Transform;

		addAction();

		{
			ActionController* PActionController = this->PlayerActionController;

			auto KeyEvent = [PActionController](const Str::FString& _KeyName)->void
				{
					PActionController->AddActionQueue(_KeyName);
				};

			PlayerKeyInput->GetKeyActioner()->SetAction(KeyEvent);

			BindActionAndKey(Input::eKeyType::Left, Input::eButtonState::Hold, "LeftMove");
			BindActionAndKey(Input::eKeyType::Right, Input::eButtonState::Hold, "RightMove");
			BindActionAndKey(Input::eKeyType::Up, Input::eButtonState::Hold, "UpMove");
			BindActionAndKey(Input::eKeyType::Down, Input::eButtonState::Hold, "DownMove");
			BindActionAndKey(Input::eKeyType::Ctrl, Input::eButtonState::Tap, "Attack");
			BindActionAndKey(Input::eKeyType::Ctrl, Input::eButtonState::Released, "Attack");

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

		KeyActioner* KeyActioner = PlayerKeyInput->GetKeyActioner();
		KeyActioner->PerformKeyAction();

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

	void Player::BindActionAndKey(Input::eKeyType _KeyType, Input::eButtonState _KeyState, const Str::FString& _ActionName)
	{
		const Action* Action = PlayerActionController->GetAction(_ActionName);
		if (Action == nullptr)
			assert(0);

		PlayerKeyInput->AddKey(_KeyType, _KeyState, _ActionName);
	}

	void Player::addAction()
	{
		auto LeftMove = [this]()->void
			{
				Vector3 Position = Transform->GetPosition();
				Position.x += -1 * Time::DeltaTime;
				Transform->SetPosition(Position);
			};
		auto RightMove = [this]()->void
			{
				Vector3 Position = Transform->GetPosition();
				Position.x += 1 * Time::DeltaTime;
				Transform->SetPosition(Position);
			};
		auto UpMove = [this]()->void
			{
				Vector3 Position = Transform->GetPosition();
				Position.y += 1 * Time::DeltaTime;
				Transform->SetPosition(Position);
			};
		auto DownMove = [this]()->void
			{
				Vector3 Position = Transform->GetPosition();
				Position.y += -1 * Time::DeltaTime;
				Transform->SetPosition(Position);
			};

		

		Action* PlayerAction = new Action("LeftMove", LeftMove);
		PlayerActionController->AddAction(PlayerAction);

		PlayerAction = new Action("RightMove", RightMove);
		PlayerActionController->AddAction(PlayerAction);

		PlayerAction = new Action("UpMove", UpMove);
		PlayerActionController->AddAction(PlayerAction);

		PlayerAction = new Action("DownMove", DownMove);
		PlayerActionController->AddAction(PlayerAction);

		PlayerAction = new Action("Attack", std::bind(&Player::Attack, this));
		PlayerActionController->AddAction(PlayerAction);

	}
}