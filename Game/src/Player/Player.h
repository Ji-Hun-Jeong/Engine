#pragma once
#include "Object\Actor.h"
#include "PlayerController/PlayerController.h"

namespace Game
{
	class Player : public Actor
	{
		using Super = Actor;
		CLONE(Player, Actor);
		friend Player* CreatePlayer(Graphics::IDRGenerator& _Generator, std::shared_ptr<Graphics::Model>& _Model);
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

		Graphics::StateVariableTable& GetStateTable() { return StateTable; }
		Graphics::StateMachine& GetStateMachine() { return StateMachine; }

	private:
		void addSkill();

	private:
		Graphics::StateVariableTable StateTable;
		Graphics::StateMachine StateMachine;

		class SkillManager* SkillManager;
		class PlayerSkillBundle* SkillBundle;

	};

	extern Player* CreatePlayer(Graphics::IDRGenerator& _Generator, std::shared_ptr<Graphics::Model>& _Model);
}

