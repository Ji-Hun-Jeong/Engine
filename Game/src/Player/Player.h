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

		void BindAction(const std::string& _ActionName, std::function<void()> _ActFunction);

	private:
		PlayerConst Constant;

		class KeyInput* PlayerKeyInput;
		class ActionController* PlayerActionController;
	};

}

