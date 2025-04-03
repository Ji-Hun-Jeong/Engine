#pragma once
#include "World/Level.h"

class MyLevel : public Engine::Level
{
	using Super = Engine::Level;
public:
	explicit MyLevel(Graphics::RenderContext* _RenderContext);
	~MyLevel();

public:
	void InitLevel() override;
	void EnterLevel() override;
	void Update() override;
	void ExitLevel() override;

private:

};

