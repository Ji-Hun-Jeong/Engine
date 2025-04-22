#include "pch.h"
#include "Player.h"

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

		addAction();
		{
			ActionController* PActionController = this->PlayerActionController;

			auto KeyEvent = [PActionController](const std::string& _KeyName, Input::eButtonState _KeyState)->void
				{
					PActionController->AddActionQueue(_KeyName);
				};

			BindActionAndKey("LeftMove", Input::eKeyType::Left, KeyEvent);
			BindActionAndKey("RightMove", Input::eKeyType::Right, KeyEvent);
			BindActionAndKey("UpMove", Input::eKeyType::Up, KeyEvent);
			BindActionAndKey("DownMove", Input::eKeyType::Down, KeyEvent);
			BindActionAndKey("Attack", Input::eKeyType::Ctrl, KeyEvent);
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

	void Player::BindActionAndKey(const std::string& _ActionName, Input::eKeyType _KeyType, std::function<void(const std::string&, Input::eButtonState)> _KeyEvent)
	{
		const Action* Action = PlayerActionController->GetAction(_ActionName);
		if (Action == nullptr)
			assert(0);

		Key* KeyInfo = new Key;
		KeyInfo->KeyName = _ActionName;
		KeyInfo->KeyEvent = _KeyEvent;

		PlayerKeyInput->AddKey(KeyInfo, _KeyType);
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