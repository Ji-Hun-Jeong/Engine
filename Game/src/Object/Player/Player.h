#pragma once
#include "Object\Character.h"

namespace Game
{
	class Player : public Character
	{
		using Super = Character;
		CLONE(Player, Character)
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
		void InitalizeKeyInput(class KeyInput& _KeyInput);

	private:
		

	};

}

