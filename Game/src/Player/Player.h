#pragma once
#include "Object\Actor.h"

namespace Game
{
	using DirectX::SimpleMath::Matrix;
	struct PlayerConst
	{
		Matrix MVP;
	};

	class Player : public Actor
	{
		using Super = Actor;
		CLONE(Player, Actor)
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

		void BindRendererInterface(Graphics::IDRGenerator& _Generator, std::shared_ptr<Graphics::Model>& _Model);

		void AddActionBySkill(const Str::FString& _ManagementName, const Str::FString& _SkillName, const Str::FString& _ActionName);

		void Attack()
		{
			std::cout << "PlayerAttack!\n";
		}

		void Move(float _Speed)
		{
			Vector3 Position = Transform->GetPosition();
			Position.x += _Speed * Time::GetDT();
			Transform->SetPosition(Position);
		}

		Graphics::StateVariableTable& GetStateTable() { return StateTable; }
		Graphics::StateMachine& GetStateMachine() { return StateMachine; }

	private:
		void addAction();
		void addKey();
		void addSkill();

	private:
		PlayerConst ConstData;
		std::shared_ptr<Graphics::RenderInterface> PlayerInterface;
		Graphics::StateVariableTable StateTable;
		Graphics::StateMachine StateMachine;

		class ActionController* ActionController;
		class SkillManager* SkillManager;
		class PlayerSkillBundle* SkillBundle;

	};

}

