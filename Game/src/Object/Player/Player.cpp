#include "pch.h"
#include "Player.h"

namespace Game
{
	Player::Player(const Str::FString& _Name)
		: Super(_Name)
	{
		Transform.SetScale(Vector3(0.2f, 0.2f, 1.0f));
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
	}

	void Player::Destory()
	{
		Super::Destory();
	}

	void Player::InitalizeRenderInterface(Graphics::IDRGenerator& _Generator, std::shared_ptr<Graphics::Model>& _Model)
	{
		Super::InitalizeRenderInterface(_Generator, _Model);

		Animation* AlertAnim = new Animation(0.5f, true);
		AddFrameInfoToAnimation(_Generator, AlertAnim, { "Game/resource/image/Player/Alert/0.png" });
		AddFrameInfoToAnimation(_Generator, AlertAnim, { "Game/resource/image/Player/Alert/1.png" });
		AddFrameInfoToAnimation(_Generator, AlertAnim, { "Game/resource/image/Player/Alert/2.png" });
		AddFrameInfoToAnimation(_Generator, AlertAnim, { "Game/resource/image/Player/Alert/3.png" });
		auto Alert = StateMachine.AddState("Alert", (new State(AlertAnim))->SetName("Alert"));

		Animation* WalkAnim = new Animation(0.5f, true);
		AddFrameInfoToAnimation(_Generator, WalkAnim, { "Game/resource/image/Player/Walk/0.png" });
		AddFrameInfoToAnimation(_Generator, WalkAnim, { "Game/resource/image/Player/Walk/1.png" });
		AddFrameInfoToAnimation(_Generator, WalkAnim, { "Game/resource/image/Player/Walk/2.png" });
		AddFrameInfoToAnimation(_Generator, WalkAnim, { "Game/resource/image/Player/Walk/3.png" });
		auto Walk = StateMachine.AddState("Walk", (new State(WalkAnim))->SetName("Walk"));

		Animation* AttackAnim = new Animation(0.5f, false);
		AddFrameInfoToAnimation(_Generator, AttackAnim, { "Game/resource/image/Player/Attack/0/0.png" });
		AddFrameInfoToAnimation(_Generator, AttackAnim, { "Game/resource/image/Player/Attack/0/1.png" }, std::bind(&Player::Attack, this));
		AddFrameInfoToAnimation(_Generator, AttackAnim, { "Game/resource/image/Player/Attack/0/2.png" });
		auto Attack = StateMachine.AddState("Attack", (new State(AttackAnim))->SetName("Attack"));

		Animator.SetCurrentAnimation(AlertAnim);

		Alert->SetEnterState([this]()->void
			{
				Transform.SetMove(true);
			});
		Attack->SetEnterState([this]()->void
			{
				Transform.SetMove(false);
			});

		TriggerVariable& AttackTrigger = StateTable.RegistTrigger("Attack");

		StateCondition* Condition = new TriggerCondition(AttackTrigger);
		Alert->AddTransition(new StateTransition(Condition, Attack));
		// Attack애니메이션 끝나면 바로 Alert로 돌아오기 위해서 조건없이 설정
		Attack->AddTransition(new StateTransition(nullptr, Alert));

		StateMachine.SetCurrentState(Alert);
	}

	void Player::InitalizeKeyInput(KeyInput& _KeyInput)
	{
		_KeyInput.AddKey("PlayerMoveLeft", Input::eKeyType::Left, Input::eButtonState::Hold, [this]()->void
			{
				Transform.Move(Vector3(-1.0f, 0.0f, 0.0f), 1.0f);
			});
		_KeyInput.AddKey("PlayerMoveRight", Input::eKeyType::Right, Input::eButtonState::Hold, [this]()->void
			{
				Transform.Move(Vector3(1.0f, 0.0f, 0.0f), 1.0f);
			});
		_KeyInput.AddKey("PlayerMoveUp", Input::eKeyType::Up, Input::eButtonState::Hold, [this]()->void
			{
				RigidBody->SetVelocity(Vector2(0.0f, 3.0f));
			});

		TriggerVariable& AttackTrigger = StateTable.GetTrigger("Attack");
		_KeyInput.AddKey("PlayerAttack", Input::eKeyType::Ctrl, Input::eButtonState::Tap, [this, &AttackTrigger]()->void
			{
				AttackTrigger.SetTrigger();
			});

		/*StateCondition* Condition = new BoolCondition(&MoveState, true);
		Alert->AddTransition(new StateTransition(Condition, Walk));

		Condition = new BoolCondition(&MoveState, false);
		Walk->AddTransition(new StateTransition(Condition, Alert));*/
	}

	void Player::InitalizeCollision(Collision::ColliderManager& _CollisionMgr)
	{
		auto C = _CollisionMgr.GetRectCollider("Player");
		C->SetSize(GetScale());
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
		Collider = C;
	}
}