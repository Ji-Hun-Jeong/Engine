#include "pch.h"
#include "Player.h"

namespace Game
{
	Player::Player(const Str::FString& _Name)
		: Super(_Name)
		, StateTable{}
		, StateMachine(StateTable)
	{
		Transform.SetScale(Vector3(0.2f, 0.2f, 1.0f));
	}

	Player::Player(const Player& _Other)
		: Super(_Other)
		, StateTable(_Other.StateTable)
		, StateMachine(_Other.StateMachine)
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

		StateMachine.UpdateCurrentState(*RenderInterface.get());
	}

	void Player::Destory()
	{
		Super::Destory();
	}

	void Player::InitalizeRenderInterface(Graphics::IDRGenerator& _Generator, std::shared_ptr<Graphics::Model>& _Model)
	{
		Super::InitalizeRenderInterface(_Generator, _Model);

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