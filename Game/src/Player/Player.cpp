#include "pch.h"
#include "Player.h"

#include "Component/Skill/Skill.h"
#include "PlayerComponent/PlayerSkillBundle.h"

namespace Game
{
	Player::Player(const Str::FString& _Name)
		: Super(_Name)
		, SkillManager(new Game::SkillManager)
		, SkillBundle(new PlayerSkillBundle(this))
		, StateTable{}
		, StateMachine(StateTable)
	{
		Transform.SetScale(Vector3(0.2f, 0.2f, 1.0f));
	}

	Player::Player(const Player& _Other)
		: Super(_Other)
		, SkillManager(nullptr)
		, SkillBundle(nullptr)
		, StateTable(_Other.StateTable)
		, StateMachine(_Other.StateMachine)
	{
	}

	Player::~Player()
	{
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

		StateMachine.UpdateCurrentState(*RenderInterface.get());
	}

	void Player::Destory()
	{
		Super::Destory();
	}

	void Player::addSkill()
	{
		SkillManager->AddManagement("1");

		Skill* Skill = new Game::Skill("UltimitDrive", 0.5f, std::bind(&PlayerSkillBundle::UltimitDrive, SkillBundle));

		SkillManager->AddSkillToManagement("1", Skill);
	}

	Player* CreatePlayer(Graphics::IDRGenerator& _Generator, std::shared_ptr<Graphics::Model>& _Model, Collision::ColliderManager& _CollisionMgr)
	{
		Player* PlayerInstance = new Player("Player");

		auto RenderInterface = std::make_shared<Graphics::IRenderInterface>();

		PlayerInstance->InitalizeRerderInterface(_Generator, RenderInterface);

		Graphics::Animation* AlertAnim = new Graphics::Animation(0.5f, true);
		Graphics::AddFrameInfoToAnimation(_Generator, AlertAnim, { "Game/resource/image/Player/Alert/0.png" });
		Graphics::AddFrameInfoToAnimation(_Generator, AlertAnim, { "Game/resource/image/Player/Alert/1.png" });
		Graphics::AddFrameInfoToAnimation(_Generator, AlertAnim, { "Game/resource/image/Player/Alert/2.png" });
		Graphics::AddFrameInfoToAnimation(_Generator, AlertAnim, { "Game/resource/image/Player/Alert/3.png" });
		auto Alert = PlayerInstance->StateMachine.AddState("Alert", new Graphics::State(AlertAnim));

		Graphics::Animation* WalkAnim = new Graphics::Animation(0.5f, true);
		Graphics::AddFrameInfoToAnimation(_Generator, WalkAnim, { "Game/resource/image/Player/Walk/0.png" });
		Graphics::AddFrameInfoToAnimation(_Generator, WalkAnim, { "Game/resource/image/Player/Walk/1.png" });
		Graphics::AddFrameInfoToAnimation(_Generator, WalkAnim, { "Game/resource/image/Player/Walk/2.png" });
		Graphics::AddFrameInfoToAnimation(_Generator, WalkAnim, { "Game/resource/image/Player/Walk/3.png" });
		auto Walk = PlayerInstance->StateMachine.AddState("Walk", new Graphics::State(WalkAnim));

		Graphics::Animation* AttackAnim = new Graphics::Animation(0.5f, false);
		Graphics::AddFrameInfoToAnimation(_Generator, AttackAnim, { "Game/resource/image/Player/Attack/0/0.png" });
		Graphics::AddFrameInfoToAnimation(_Generator, AttackAnim, { "Game/resource/image/Player/Attack/0/1.png" }, std::bind(&Player::Attack, PlayerInstance));
		Graphics::AddFrameInfoToAnimation(_Generator, AttackAnim, { "Game/resource/image/Player/Attack/0/2.png" });
		auto Attack = PlayerInstance->StateMachine.AddState("Attack", new Graphics::State(AttackAnim));

		_Model->AddRenderInterface(RenderInterface);
		
		auto C = _CollisionMgr.GetRectCollider("Player");
		C->SetSize(PlayerInstance->GetScale());
		C->AddCollisionEnter([&_CollisionMgr](Collision::Collider* _Collider)->void
			{
				if (_CollisionMgr.GetTypeByString("Monster") == _Collider->GetColliderType())
					std::cout << "CollisionEnter\n";
			});
		C->AddCollisionExit([&_CollisionMgr](Collision::Collider* _Collider)->void
			{
				if (_CollisionMgr.GetTypeByString("Monster") == _Collider->GetColliderType())
					std::cout << "CollisionExit\n";
			});
		PlayerInstance->SetCollider(C);

		return PlayerInstance;
	}
}