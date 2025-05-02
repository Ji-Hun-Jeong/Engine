#include "pch.h"
#include "Player.h"
#include <Renderer/src/Geometry/Geometry.h>

#include "Component/KeyInput/KeyInput.h"
#include "Component/Skill/Skill.h"
#include "PlayerComponent/PlayerActionController.h"
#include "PlayerComponent/PlayerSkillBundle.h"

namespace Game
{
	Player::Player(const Str::FString& _Name)
		: Super(_Name)
		, KeyInput(new Game::KeyInput)
		, ActionController(new PlayerActionController)
		, SkillManager(new Game::SkillManager)
		, SkillBundle(new PlayerSkillBundle(this))

	{
		Graphics::Geometry::ColorMeshData Md = Graphics::Geometry::GenerateColorTriangle();

		DrawIndexCount = static_cast<UINT>(Md.Indices.size());

		auto Vertices = Md.Vertices;
		/*_RenderDevice->MakeGeometryBuffers(Name, Vertices.data(), sizeof(ColorVertex), Vertices.size(), Md.Indices);

		_RenderDevice->MakeVSConstBuffer(Name, eCategoryVSConst::Basic, sizeof(Constant));*/

		Transform = new Game::Transform;

		// Skill을 미리 정의해두고 Skill을 Action에 넣어서 바인딩한다.
		// Action과 Key를 정의해두고 두개를 바인딩한다.
		addSkill();
		addKey();
		addAction();

		BindActionAndKey(Input::eKeyType::Left, Input::eButtonState::Hold, "BasicAction", "LeftMove");
		BindActionAndKey(Input::eKeyType::Right, Input::eButtonState::Hold, "BasicAction", "RightMove");
		BindActionAndKey(Input::eKeyType::Up, Input::eButtonState::Hold, "BasicAction", "UpMove");
		BindActionAndKey(Input::eKeyType::Down, Input::eButtonState::Hold, "BasicAction", "DownMove");
		BindActionAndKey(Input::eKeyType::Ctrl, Input::eButtonState::Hold, "CantMoveAction", "Attack");
		BindActionAndKey(Input::eKeyType::Shift, Input::eButtonState::Hold, "MoveAction", "UltimitDrive");

	}

	Player::Player(const Player& _Other)
		: Super(_Other)
		, KeyInput(nullptr)
		, ActionController(nullptr)
		, SkillManager(nullptr)
		, SkillBundle(nullptr)
	{
	}

	Player::~Player()
	{
		if (KeyInput)
			delete KeyInput;
		if (ActionController)
			delete ActionController;
		if (SkillManager)
			delete SkillManager;
		if (SkillBundle)
			delete SkillBundle;
	}

	void Player::InitObject()
	{
		Super::InitObject();
	}

	void Player::Update()
	{
		Super::Update();

		KeyInput->UpdateKeyState();

		KeyActioner* KeyActioner = KeyInput->GetKeyActioner();
		KeyActioner->PerformKeyAction();

		ActionController->Update();

		Constant.MVP = Transform->GetModel().Transpose();
	}

	void Player::Destory()
	{
		Super::Destory();
	}

	void Player::BindActionAndKey(Input::eKeyType _KeyType, Input::eButtonState _KeyState
		, const Str::FString& _ActionClass, const Str::FString& _ActionName)
	{
		if (ActionController->IsExistAction(_ActionName) == false)
			return;

		KeyValue* FindKeyValue = KeyInput->GetKeyValue(_KeyType, _KeyState);
		if (FindKeyValue == nullptr)
			return;

		Game::ActionController* PActionController = ActionController;
		auto Event = [PActionController, _ActionClass, _ActionName](const Str::FString& _KeyName)->void
			{
				PActionController->PrepareAction(_ActionClass, _ActionName);
			};
		FindKeyValue->SetKeyEvent(Event);

	}

	void Player::AddActionBySkill(const Str::FString& _ManagementName, const Str::FString& _SkillName, const Str::FString& _ActionName)
	{
		if (ActionController->IsExistAction(_ActionName) == true)
			return;

		Skill* FindSkill = SkillManager->GetSkill(_ManagementName, _SkillName);
		if (FindSkill == nullptr)
			return;

		Action* Action = new Game::Action(_ActionName, FindSkill->GetSkillAction());
		Action->SetActionDelay(FindSkill->GetSkillDelay());
		ActionController->AddAction(Action);
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

		AddActionBySkill("1", "UltimitDrive", "UltimitDrive");

	}

	void Player::addKey()
	{
		KeyInput->AddKey(Input::eKeyType::Left, Input::eButtonState::Hold, "LeftMove");
		KeyInput->AddKey(Input::eKeyType::Right, Input::eButtonState::Hold, "RightMove");
		KeyInput->AddKey(Input::eKeyType::Up, Input::eButtonState::Hold, "UpMove");
		KeyInput->AddKey(Input::eKeyType::Down, Input::eButtonState::Hold, "DownMove");
		KeyInput->AddKey(Input::eKeyType::Ctrl, Input::eButtonState::Hold, "Attack");
		KeyInput->AddKey(Input::eKeyType::Shift, Input::eButtonState::Hold, "Uld");
	}

	void Player::addSkill()
	{
		SkillManager->AddManagement("1");

		Skill* Skill = new Game::Skill("UltimitDrive", 0.5f, std::bind(&PlayerSkillBundle::UltimitDrive, SkillBundle));

		SkillManager->AddSkillToManagement("1", Skill);
	}
}