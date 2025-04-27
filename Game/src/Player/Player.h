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
		Player(const Str::FString& _Name, Graphics::RenderDevice* _RenderDevice);
		Player(const Player& _Other);
		Player(Player&& _Other) = delete;
		Player& operator = (const Player& _Other) = delete;
		Player& operator = (Player&& _Other) = delete;
		virtual ~Player();

	public:
		virtual void InitObject() override;
		virtual void Update() override;
		virtual void Destory() override;

		void Render(Graphics::RenderContext* _RenderContext) override;

		void BindActionAndKey(Input::eKeyType _KeyType, Input::eButtonState _KeyState
			, const Str::FString& _ActionClass, const Str::FString& _ActionName);

		void AddActionBySkill(const Str::FString& _ManagementName, const Str::FString& _SkillName, const Str::FString& _ActionName);

		void Attack()
		{
			std::cout << "PlayerAttack!\n";
		}

	private:
		void addAction();
		void addKey();
		void addSkill();

	private:
		PlayerConst Constant;

		class KeyInput* KeyInput;
		class ActionController* ActionController;
		class SkillManager* SkillManager;
		class PlayerSkillBundle* SkillBundle;

	};

}

