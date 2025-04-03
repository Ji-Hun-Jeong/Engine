#pragma once
#include "Object\Actor.h"

class Player : public Engine::Actor
{
	using Super = Engine::Actor;
	CLONE(Player, Actor)
public:
	Player(const std::string& _Name, Graphics::RenderContext* _RenderContext);
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
private:

	

};

