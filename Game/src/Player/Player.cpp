#include "pch.h"
#include "Player.h"

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
		, StateTable{}
		, StateMachine(StateTable)
	{
		Transform = new Game::Transform;
		Transform->SetScale(Vector3(0.2f, 0.2f, 1.0f));

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
		, StateTable(_Other.StateTable)
		, StateMachine(_Other.StateMachine)
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

		KeyActioner& KeyActioner = KeyInput->GetKeyActioner();
		KeyActioner.PerformKeyAction();

		ActionController->Update();

		ConstData.MVP = Transform->GetModel().Transpose();

		PlayerInterface->UpdateConstBuffer();

		StateMachine.UpdateCurrentState(*PlayerInterface.get());
	}

	void Player::Destory()
	{
		Super::Destory();
	}

	void Player::BindRendererInterface(Graphics::IDRGenerator& _Generator, std::shared_ptr<Graphics::Model>& _Model)
	{
		std::vector<Graphics::CpuConstData> CpuConstDatas{ {&ConstData, sizeof(ConstData)} };
		auto ConstBuffer = _Generator.GenerateConstBuffer(CpuConstDatas);

		PlayerInterface = std::make_shared<Graphics::RenderInterface>(ConstBuffer);

		Graphics::Animation* AlertAnim = new Graphics::Animation(0.5f, true);
		Graphics::AddFrameInfoToAnimation(_Generator, AlertAnim, { "Game/resource/image/Player/Alert/0.png" });
		Graphics::AddFrameInfoToAnimation(_Generator, AlertAnim, { "Game/resource/image/Player/Alert/1.png" });
		Graphics::AddFrameInfoToAnimation(_Generator, AlertAnim, { "Game/resource/image/Player/Alert/2.png" });
		Graphics::AddFrameInfoToAnimation(_Generator, AlertAnim, { "Game/resource/image/Player/Alert/3.png" });
		auto Alert = StateMachine.AddState("Alert", new Graphics::State(AlertAnim));

		Graphics::Animation* WalkAnim = new Graphics::Animation(0.5f, true);
		Graphics::AddFrameInfoToAnimation(_Generator, WalkAnim, { "Game/resource/image/Player/Walk/0.png" });
		Graphics::AddFrameInfoToAnimation(_Generator, WalkAnim, { "Game/resource/image/Player/Walk/1.png" });
		Graphics::AddFrameInfoToAnimation(_Generator, WalkAnim, { "Game/resource/image/Player/Walk/2.png" });
		Graphics::AddFrameInfoToAnimation(_Generator, WalkAnim, { "Game/resource/image/Player/Walk/3.png" });
		auto Walk = StateMachine.AddState("Walk", new Graphics::State(WalkAnim));

		Graphics::Animation* AttackAnim = new Graphics::Animation(0.5f, false);
		Graphics::AddFrameInfoToAnimation(_Generator, AttackAnim, { "Game/resource/image/Player/Attack/0/0.png" });
		Graphics::AddFrameInfoToAnimation(_Generator, AttackAnim, { "Game/resource/image/Player/Attack/0/1.png" });
		Graphics::AddFrameInfoToAnimation(_Generator, AttackAnim, { "Game/resource/image/Player/Attack/0/2.png" });
		auto Attack = StateMachine.AddState("Attack", new Graphics::State(AttackAnim));

		auto ChangeFunc = [this](Graphics::State* _HeadState)->void
			{
				StateMachine.SetCurrentState(_HeadState);
			};

		bool* Move = StateTable.GetBool("Move");
		Graphics::StateCondition* Condition = new Graphics::BoolCondition(Move, true);
		Graphics::AddTransition(StateMachine, Condition, *Alert, *Walk);

		Condition = new Graphics::BoolCondition(Move, false);
		Graphics::AddTransition(StateMachine, Condition, *Walk, *Alert);

		StateMachine.SetCurrentState(Alert);
		_Model->AddRenderInterface(PlayerInterface);
	}

	void Player::BindAnimationAndAction()
	{

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
		bool* Move = StateTable.RegistBool("Move", false);
		auto LeftMove = [this, Move]()->void
			{
				Vector3 Position = Transform->GetPosition();
				Position.x += -1 * Time::GetDT();
				Transform->SetPosition(Position);
				*Move = true;
			};
		auto RightMove = [this, Move]()->void
			{
				Vector3 Position = Transform->GetPosition();
				Position.x += 1 * Time::GetDT();
				Transform->SetPosition(Position);
				*Move = false;
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