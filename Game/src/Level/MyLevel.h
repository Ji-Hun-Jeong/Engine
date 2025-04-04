#pragma once
#include "Level/Level.h"

class MyLevel : public Engine::Level
{
	using Super = Engine::Level;
public:
	explicit MyLevel(Graphics::RenderDevice* _RenderDevice);
	~MyLevel();

public:
	void InitLevel() override;
	void EnterLevel() override;
	void Update() override;
	void ExitLevel() override;

private:

};

