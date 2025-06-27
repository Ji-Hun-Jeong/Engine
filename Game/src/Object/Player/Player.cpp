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
		if (PixelCollisionInterface)
			delete PixelCollisionInterface;
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

		Animation* AlertAnim = new Animation(0.5f, true, true);
		AddFrameInfoToAnimation(_Generator, AlertAnim, { "Game/resource/image/Player/Alert/0.png" });
		AddFrameInfoToAnimation(_Generator, AlertAnim, { "Game/resource/image/Player/Alert/1.png" });
		AddFrameInfoToAnimation(_Generator, AlertAnim, { "Game/resource/image/Player/Alert/2.png" });
		AddFrameInfoToAnimation(_Generator, AlertAnim, { "Game/resource/image/Player/Alert/3.png" });
		auto Alert = StateMachine.AddState("Alert", new State(AlertAnim));

		Animation* WalkAnim = new Animation(0.5f, true, true);
		AddFrameInfoToAnimation(_Generator, WalkAnim, { "Game/resource/image/Player/Walk/0.png" });
		AddFrameInfoToAnimation(_Generator, WalkAnim, { "Game/resource/image/Player/Walk/1.png" });
		AddFrameInfoToAnimation(_Generator, WalkAnim, { "Game/resource/image/Player/Walk/2.png" });
		AddFrameInfoToAnimation(_Generator, WalkAnim, { "Game/resource/image/Player/Walk/3.png" });
		auto Walk = StateMachine.AddState("Walk", new State(WalkAnim));

		Animation* AttackAnim = new Animation(0.5f, false, false);
		AddFrameInfoToAnimation(_Generator, AttackAnim, { "Game/resource/image/Player/Attack/0/0.png" });
		AddFrameInfoToAnimation(_Generator, AttackAnim, { "Game/resource/image/Player/Attack/0/1.png" }, std::bind(&Player::Attack, this));
		AddFrameInfoToAnimation(_Generator, AttackAnim, { "Game/resource/image/Player/Attack/0/2.png" });
		auto Attack = StateMachine.AddState("Attack", new State(AttackAnim));

		StateMachine.SetCurrentState(Alert);
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