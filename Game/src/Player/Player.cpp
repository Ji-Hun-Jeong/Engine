#include "pch.h"
#include "Player.h"

#include "Component/Skill/Skill.h"
#include "PlayerComponent/PlayerActionController.h"
#include "PlayerComponent/PlayerSkillBundle.h"

namespace Game
{
	Player::Player(const Str::FString& _Name)
		: Super(_Name)
		, ActionController(new PlayerActionController)
		, SkillManager(new Game::SkillManager)
		, SkillBundle(new PlayerSkillBundle(this))
		, StateTable{}
		, StateMachine(StateTable)
	{
		Transform = new Game::Transform;
		Transform->SetScale(Vector3(0.2f, 0.2f, 1.0f));
	}

	Player::Player(const Player& _Other)
		: Super(_Other)
		, ActionController(nullptr)
		, SkillManager(nullptr)
		, SkillBundle(nullptr)
		, StateTable(_Other.StateTable)
		, StateMachine(_Other.StateMachine)
	{
	}

	Player::~Player()
	{
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
		Graphics::AddFrameInfoToAnimation(_Generator, AttackAnim, { "Game/resource/image/Player/Attack/0/1.png" }, std::bind(&Player::Attack, this));
		Graphics::AddFrameInfoToAnimation(_Generator, AttackAnim, { "Game/resource/image/Player/Attack/0/2.png" });
		auto Attack = StateMachine.AddState("Attack", new Graphics::State(AttackAnim));

		_Model->AddRenderInterface(PlayerInterface);
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

	void Player::addSkill()
	{
		SkillManager->AddManagement("1");

		Skill* Skill = new Game::Skill("UltimitDrive", 0.5f, std::bind(&PlayerSkillBundle::UltimitDrive, SkillBundle));

		SkillManager->AddSkillToManagement("1", Skill);
	}
}