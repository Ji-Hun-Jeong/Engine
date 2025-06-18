#pragma once
#include "Object\Actor.h"
#include "PlayerController/PlayerController.h"

namespace Game
{
	class Player : public Actor
	{
		using Super = Actor;
		CLONE(Player, Actor);
	public:
		Player(const Str::FString& _Name);
		Player(const Player& _Other);
		Player(Player&& _Other) = delete;
		Player& operator = (const Player& _Other) = delete;
		Player& operator = (Player&& _Other) = delete;
		virtual ~Player();

	public:
		virtual void InitObject() override;
		virtual void Update() override;
		virtual void Destory() override;

		void Attack()
		{
			std::cout << "PlayerAttack!\n";
		}
		void InitalizeRenderInterface(Graphics::IDRGenerator& _Generator, std::shared_ptr<Graphics::Model>& _Model) override;
		void InitalizeCollision(Collision::ColliderManager& _CollisionMgr) override;

		Graphics::StateVariableTable& GetStateTable() { return StateTable; }
		Graphics::StateMachine& GetStateMachine() { return StateMachine; }


	private:
		Graphics::StateVariableTable StateTable;
		Graphics::StateMachine StateMachine;

	};

}

