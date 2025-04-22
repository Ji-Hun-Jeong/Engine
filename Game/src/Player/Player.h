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
		Player(const std::string& _Name, Graphics::RenderDevice* _RenderContext);
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

		void BindActionAndKey(const std::string& _ActionName, Input::eKeyType _KeyType, std::function<void(const std::string&, Input::eButtonState)> _KeyEvent);

		void Attack()
		{
			static float ActionTime = 1.0f;
			static float SumTime = 0.0f;
			static int cnt = 0;
			if (SumTime < ActionTime)
			{
				if (cnt < 1)
				{
					++cnt;
					std::cout << "PlayerAttack!\n";
				}
				SumTime += Time::DeltaTime;
			}
			else
			{
				SumTime = 0.0f;
				cnt = 0;
			}
		}
	private:
		void addAction();

	private:
		PlayerConst Constant;

		class KeyInput* PlayerKeyInput;
		class ActionController* PlayerActionController;
	};

}

